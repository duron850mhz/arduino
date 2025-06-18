#include <math.h>
#include <Adafruit_NeoPixel.h>

#define DIN_PIN 16            // NeoPixel　の出力ピン番号はGP16
#define LED_COUNT 1           // LEDの連結数
#define BRIGHTNESS 16        // 輝度
Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

#define SW_PIN1 7     //スイッチピン番号1
#define SW_PIN2 8     //スイッチピン番号2
#define BUZZER_PIN 6  //出力ピン番号
#define WAIT_TIME 10  //開放許容秒数
int WaitCnt = 0;  //待ち秒数カウンタ
int BeepCnt = 0;  //鳴動秒数カウンタ
#define BEEP_MAX 300  //最大鳴動秒数

#define THERMISTOR_PIN1 27  //103JTピン番号1(長いほう)
#define THERMISTOR_PIN2 28  //103JTピン番号2(短いほう)
const float DIVIDER = 10000.0; // 分圧抵抗10kΩ
const float T0 = 273.15;  //絶対零度
const float R0 = 27700.0; //0℃時の抵抗値
const float B = 3435.0; //B定数
float temp1 = 0;  //温度1
float temp2 = 0;  //温度2
int TempCnt = 99; //温度測定カウンタ
int TempOverCnt = 0;  //温度超過回数カウンタ
#define TEMP_MAX1 -5 //温度計1警告値
#define TEMP_MAX2 15  //温度計2警告値

//温度測定ルーチン
float calcTemp(int PIN) {
  float Aout =  float(analogRead(PIN));
  float Rt = DIVIDER * Aout / (1024.0 - Aout);
  float T_bar = 1/T0 + 1/B * log(Rt/R0);
  return 1.0/T_bar - 273.15;
}

void setup() {
  Serial.begin(9600);
  pixels.begin();             //NeoPixel制御開始

  pinMode(SW_PIN1, INPUT_PULLUP);
  pinMode(SW_PIN2, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(THERMISTOR_PIN1, INPUT);
  pinMode(THERMISTOR_PIN2, INPUT);
}

void loop() {

  int stat = 0;   //ステータス初期化(0:正常)

  if (TempCnt > 5) {
    //5秒ごとに温度測定
    temp1 = calcTemp(THERMISTOR_PIN1);
    temp2 = calcTemp(THERMISTOR_PIN2);
    TempCnt = 0;

    Serial.print("Temp1:");
    Serial.print(temp1);
    Serial.print(" Temp2:");
    Serial.println(temp2);

    if (temp1 > TEMP_MAX1 || temp2 > TEMP_MAX2) {
      //温度超過
      TempOverCnt += 1;
      if (TempOverCnt >= 12) {
        //12回連続でOUT
        stat = 4;
      }
    } else {
      TempOverCnt = 0;
    }
  }
  TempCnt += 1;

  if (stat == 0) {
    if (digitalRead(SW_PIN1) == HIGH || digitalRead(SW_PIN2) == HIGH) {
      //開けた
      WaitCnt += 1; //待ち秒数カウンタ加算

      //10秒過ぎた?
      if (WaitCnt > WAIT_TIME) {
        if (BeepCnt > BEEP_MAX) {
          //鳴りすぎ防止
          stat = 3;
        } else {
          //鳴動
          stat = 2;

          //あきらめカウンタ加算
          BeepCnt += 1;
        }
      } else {
        //警告表示
        stat = 1;
      }
    } else {
      //閉めた
      WaitCnt = 0;  //待ち秒数カウンタ初期化
      BeepCnt = 0;  //あきらめカウンタ初期化

      stat = 0;
    }
  }

  switch (stat) {
    case 1:
      //警告表示
      pixels.setPixelColor(0, pixels.Color(0, BRIGHTNESS, 0)); //黄点灯
      pixels.show();
      break;
    case 2:
      //鳴動
      digitalWrite(BUZZER_PIN, HIGH); //鳴動開始
      pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, 0, 0)); //赤点灯
      pixels.show();
      break;
    case 3:
      //あきらめた
      digitalWrite(BUZZER_PIN, LOW);  //停止
      pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, 0, 0)); //赤点灯
      pixels.show();
      break;
    case 4:
      //アツゥイ！！
      digitalWrite(BUZZER_PIN, HIGH); //鳴動開始
      pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, 0, BRIGHTNESS)); //紫点灯
      pixels.show();
      break;
    default:
      //正常状態
      digitalWrite(BUZZER_PIN, LOW);  //停止
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));  //消灯
      pixels.show();
  }

  delay(1000); //1秒待機
  //Serial.print("WaitCnt=");
  //Serial.print(WaitCnt);
  //Serial.print(" BeepCnt=");
  //Serial.print(BeepCnt);
  //Serial.print(" stat=");
  //Serial.println(stat);
}
