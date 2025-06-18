//#include <WiFi.h>
//#include <WebServer.h>

//const char* ssid     = "1010031";
//const char* password = "85bfa37109";
//const IPAddress ip(192,168,11,32);
//const IPAddress gateway(192,168,11,1);
//const IPAddress subnet(255,255,255,0);

//#define LED_BUILTIN 2
#define AD_PIN 36
#define LOOP_COUNT 2000

//WebServer server(80);

void setup() {
  /* ----- Setting up serial communication with PC ------ */
  /* ここでUSBを介してPCとシリアル通信を始める。115200はシリアル通信のボーレート */
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  // 何らかの問題があってシリアルポートに接続できないときは、このループにトラップされる    
  }
  delay(100);

	// 減衰を-6dbに設定
  analogSetAttenuation(ADC_6db);  // ATT -6dB
  pinMode(AD_PIN, ANALOG);

	// WiFi 設定
  //if (!WiFi.config(ip,gateway,subnet)){
  //    Serial.println("Failed to configure!");
  //}

	// WiFi 接続開始
  //WiFi.begin(ssid, password);

	// WiFi 接続待機
  //while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //}

	// WiFi ステータス表示
  //Serial.println("");
  //Serial.println("WiFi connected.");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  // サーバにアクセスしたときの挙動
  //server.on("/", handleRoot);
  //server.onNotFound(handleNotFound);

	// サーバ起動
  //server.begin();
}

void loop() {
  // 待ち
	//server.handleClient();

	// A0から電圧読み取り
  //Serial.printf("%d[mV]\n", analogReadMilliVolts(AD_PIN) );
  //delay(500);
 
  long adMillivoltTemp = 0;
  for ( int i = 0 ; i < LOOP_COUNT ; i++ )
  {
    adMillivoltTemp += (long)analogReadMilliVolts(AD_PIN);
  }
  float adMillivolt = (float)((double)adMillivoltTemp / (double)LOOP_COUNT); //mV Average
  Serial.printf("%d[mV]\n", (int)(adMillivolt+0.5) );
  delay(500);
}

/*
void handleRoot() {
  String html;

  //HTML記述
  html = "<!DOCTYPE html>";
  html += "<html lang='ja'>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Lesson 04</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Hello omoroya!!</h1>";
  html += "<p><h2>こんにちは omoroya!!</h2></p>";
  html += "</body>";
  html += "</html>";

  // HTMLを出力する
  //server.send(200, "text/html", html);
  server.send(200, "text/html", String(analogReadMilliVolts(A0)));
}

void handleNotFound(void) {
  server.send(404, "text/plain", "Not Found");
}
*/