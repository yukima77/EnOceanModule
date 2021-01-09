#include <M5StickC.h>
#include <SoftwareSerial.h>

#define TEMPID 0xXXXXXXXX // EnOceanモジュールID
#define SYNC 0x55         // SYNCバイト

SoftwareSerial enoceanSerial(32, 33); // RX, TX

void setup()
{
  M5.begin();
  M5.Lcd.setRotation(3);

  Serial.begin(9600);
  Serial.println();

  // Initialize EnOcean.
  enoceanSerial.begin(57600);

  // 初期化画面
  M5.Lcd.fillScreen(BLACK);
}

void loop()
{

  /********* EnOcean add *********/
  unsigned char dataReceive = 0; //受信確認フラグ
  unsigned char data = 0;        //データ格納用変数
  unsigned char pos = 0;         //ESPデータ位置
  unsigned long senderID = 0;    //モジュールのID
  unsigned short dataLength = 0; //データ長
  unsigned char optLength = 0;   //オプションデータ長
  unsigned char packettype = 0;  //パケットタイプ
  unsigned char doorStatus = 0;  // ドアの状態
  char buf[8];
  bool isOpen = true;

  // EnOceanからのデータ受信
  while (enoceanSerial.available() > 0)
  {
    //delay(5);
    data = enoceanSerial.read();

    switch (pos)
    {
    case (0):
      if (SYNC == data)
      { // SYNCバイトだったら受信開始
        delay(5);
        pos++;
        dataReceive = 1;
      }
      break;
    case (1):
      dataLength = 0x00FF & data;
      pos++;
      break;
    case (2):
      dataLength = (dataLength << 8) + data;
      pos++;
      break;
    case (3):
      optLength = data;
      pos++;
      break;
    case (4):
      packettype = data;
      pos++;
      break;
    case (5):
      pos++;
      break;
    case (6):
      pos++;
      break;
    case (7):
      senderID = 0x0000FF & data;
      pos++;
      break;
    case (8):
    case (9):
    case (10):
      senderID = (senderID << 8) + data;
      pos++;
      break;
    case (11):
      if (TEMPID == senderID)
      {
        // ドアビット
        doorStatus = data;
      }

      pos++;
      break;
    case (12):
      pos++;
      break;
    case (13):
      pos++;
      break;
    case (14):
      pos++;
      break;
    case (15):
      pos++;
      break;
    default:
      pos++;
      break;
    }
    // デバッグ用のシリアルモニタ出力
    Serial.print(data, HEX);
    Serial.print("  ");
  }

  // データ受信時の処理
  if (dataReceive == 1)
  {
    if (TEMPID == senderID)
    {
      // ドア状態の判定
      if (doorStatus == 0x08)
      {
        Serial.println("Open");
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextSize(3);
        M5.Lcd.println("Open");
      }
      else if (doorStatus == 0x09)
      {
        Serial.println("Close");
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextSize(3);
        M5.Lcd.println("Close");
      }
    }
  }

  M5.Lcd.setCursor(5, 5);
  M5.update();
  delay(100);
}