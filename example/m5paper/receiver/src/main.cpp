#include <M5EPD.h>

#define SYNC 0x55         // SYNCバイト
#define TEMPID 0xFFFFFFFF // EnOceanモジュールID

M5EPD_Canvas canvas(&M5.EPD);

void setup()
{

  M5.begin();
  M5.EPD.SetRotation(90);
  M5.EPD.Clear(true);

  M5.RTC.begin();

  Serial1.begin(57600, SERIAL_8N1, 25, 32); // PORT.A
  //Serial1.begin(57600, SERIAL_8N1, 26, 33);   // PORT.B
  //Serial1.begin(57600, SERIAL_8N1, 18, 19);   // PORT.C

  canvas.createCanvas(540, 960);
  canvas.setTextSize(3);
  canvas.drawString("M5Paper EnOcean Test", 45, 350);
  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void loop()
{

  /********* EnOcean add *********/
  unsigned char dataReceive = 0; //受信確認フラグ
  unsigned char aChar = 0;       //データ格納用変数
  unsigned char pos = 0;         //ESPデータ位置
  unsigned long senderID = 0;    //モジュールのID
  unsigned short dataLength = 0; //データ長
  unsigned char optLength = 0;   //オプションデータ長
  unsigned char packettype = 0;  //パケットタイプ
  unsigned char doorStatus = 0;  // ドアの状態
  char buf[8];
  bool isOpen = true;
  bool shouldSendMessage = false;

  // EnOceanからのデータ受信
  while (Serial1.available() > 0)
  {
    //delay(5);
    aChar = Serial1.read();

    switch (pos)
    {
    case (0):
      if (SYNC == aChar)
      { // SYNCバイトだったら受信開始
        delay(5);
        pos++; // pos移動　SYNC -> dataLength
        dataReceive = 1;
      }
      break;
    case (1):
      dataLength = 0x00FF & aChar; // dataLength 上位1バイトです。
      pos++;                       // pos移動 dataLength -> dataLength
      break;
    case (2):
      dataLength = (dataLength << 8) + aChar; // dataLength 下位1バイトです。
      pos++;                                  // pos移動 dataLength -> optLength
      break;
    case (3):
      optLength = aChar; //  optionLength
      pos++;             // pos移動　optLength -> packet type
      break;
    case (4):
      packettype = aChar; //   packettype
      pos++;              // pos移動  packet type -> crc
      break;
    case (5):
      pos++; // pos移動　crc -> header
      break;
    case (6):
      pos++; // pos移動  header -> ID1
      break;
    case (7):
      senderID = 0x0000FF & aChar; // ID1バイト
      pos++;                       // pos移動  ID1 -> ID2
      break;
    case (8):
    case (9):
    case (10):
      senderID = (senderID << 8) + aChar; // ID2-4バイト
      pos++;                              // pos移動  ID2 -> ID4 -> data1
      break;
    case (11):
      if (TEMPID == senderID)
      {
        // ドアビット
        doorStatus = aChar;
      }

      pos++; // pos移動  data1 -> data2
      break;
    case (12):
      pos++; // pos移動  data2(hum) -> data3(temp)
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
    //sprintf(buf, "%04b", aChar);
    Serial.print(aChar, HEX);
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
        canvas.fillCanvas(0);
        canvas.setTextSize(5);
        canvas.drawString("Open", 45, 350);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
      }
      else if (doorStatus == 0x09)
      {
        Serial.println("Close");
        canvas.fillCanvas(0);
        canvas.setTextSize(5);
        canvas.drawString("Close", 45, 350);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
      }

      Serial.println("");
    }
  }

  // Battery
  uint32_t vol = M5.getBatteryVoltage();

  if (vol < 3300)
  {
    vol = 3300;
  }
  else if (vol > 4350)
  {
    vol = 4350;
  }
  float battery = (float)(vol - 3300) / (float)(4350 - 3300);
  if (battery <= 0.01)
  {
    battery = 0.01;
  }
  if (battery > 1)
  {
    battery = 1;
  }
  uint8_t px = battery * 25;
  sprintf(buf, "%d%%", (int)(battery * 100));
  canvas.setTextSize(2);
  canvas.drawString(buf, 498 - 10, 24);
  canvas.fillRect(498 + 3, 8 + 10, px, 13, 15);
  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);

  M5.update();
  sleep(5);
}