/**********************************************************************
【ライセンスについて】
Copyright(c) 2022 by tamanegi
Released under the MIT license
'http://tamanegi.digick.jp/about-licence//【スケッチの説明】

【スケッチの説明】
NeoPixel搭載RP2040基板で使用できます。
実装 W2812を点灯させます。
1秒間隔で、赤->緑->黄->青->紫->水->白　の順で点灯させます。

【バージョン情報】
 2022/7/6 : 新規
 2022/9/8 : RP2040-Zero用にBuilt In LEDのピン番号を変更 23 -> 16
**********************************************************************/

#include <Adafruit_NeoPixel.h>

#define DIN_PIN 16            // NeoPixel　の出力ピン番号はGP16
#define LED_COUNT 1           // LEDの連結数
#define WAIT_MS 100          // 次の点灯までのウエイト
#define BRIGHTNESS 64        // 輝度
Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();             //NeoPixel制御開始
}

void loop()
{
  pixels.clear();
  
  //pixels.Color(Red, Green, Blue)で、パレット情報を作成する。
  //赤点灯
  pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, 0, 0));
  pixels.show();
  delay(WAIT_MS);

  //緑点灯
  pixels.setPixelColor(0, pixels.Color(0, BRIGHTNESS, 0));
  pixels.show();
  delay(WAIT_MS);

  //赤　＋　緑　で　黄点灯
  pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, BRIGHTNESS, 0));
  pixels.show();
  delay(WAIT_MS);

  //青点灯
  pixels.setPixelColor(0, pixels.Color(0, 0, BRIGHTNESS));
  pixels.show();
  delay(WAIT_MS);

  //赤　＋　青　で　紫点灯
  pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, 0, BRIGHTNESS));
  pixels.show();
  delay(WAIT_MS);

  //緑　＋　青　で　水点灯
  pixels.setPixelColor(0, pixels.Color(0, BRIGHTNESS, BRIGHTNESS));
  pixels.show();
  delay(WAIT_MS);

  //赤　＋　緑　＋　青　で　白点灯
  pixels.setPixelColor(0, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.show();
  delay(WAIT_MS);
}