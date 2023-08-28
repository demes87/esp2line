#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
HTTPClient httpClient;

String ssid = "";     // Wi-FiのSSID
String password = ""; // Wi-Fiのパスワード
String LINE_NOTIFY_TOKEN = ""; //トークンを入力

#define SEND_PERIOD 3000  //送信間隔設定（初期値で3000ミリ秒 = 3秒）

void WIFIconnect(void){
  if(WiFi.status() == WL_CONNECTED) return;  //予め接続されていたら戻す

  WiFi.begin(ssid.c_str(), password.c_str());

  int i = 0;
  while(WiFi.status() != WL_CONNECTED){
    delay(100); //100ms待ち
    i++;

    if(i >= 50) return;  //5秒つながらないと強制中断
  }
}

void Sendmsg2LINE(String body){ 
  // HTTPClinetでPOSTする
  httpClient.begin("https://notify-api.line.me/api/notify");
  httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
  httpClient.addHeader("Authorization", "Bearer " + LINE_NOTIFY_TOKEN);

  u_int status_code = httpClient.POST("message=" + body);  // POSTで送信、LINE Notifyからの戻り値を変数に格納

  //戻り値次第で何かする
  if (status_code == 200){  //送信OK
    //do anything
  }  else{  //送信NG
    //do anything
  }

  httpClient.end();  // HTTPClinetを終了する
}

void setup() {
  WIFIconnect();
}

void loop() {
  delay(SEND_PERIOD);
  Sendmsg2LINE("検出しました");
}
