**バージョンによって、ピンアサインが変更になっています。ご注意ください。誤って設定した場合もモジュールが破損することはありません。**

# EnOceanModule

## 概要
EnOcean用送受信モジュールです。TCM410Jを搭載しています。
![](https://github.com/yukima77/EnOceanModule/blob/images/001.JPG)

## ピンアサイン
Seeed株式会社のGroveSystemのピンアサインに合わせる為、v1.1よりピンアサインを変更しています。バージョン情報がプリント基板に記載されていない以前のモジュールとはピンアサインが変更になっていますのでご注意下さい。v1.1以降は、GroveSystemの使ったボードでのHardwareSerialを使った通信も可能になります。
[Seeed株式会社GroveSystem](https://wiki.seeedstudio.com/Grove_System/)

### v1.1/v1.2
1.RX (which the base unit uses to receive data, so it is an input)  
2.TX (which the base unit uses to transmit data to the Grove module)  
3.VCC  
4.GND  

### 無印
1.TX (which the base unit uses to transmit data to the Grove module)  
2.RX (which the base unit uses to receive data, so it is an input)  
3.VCC  
4.GND  

## 仕様
* 電源電圧：5.0 V
* シリアルインタフェース：UART（ボーレート：57600）
* 無線周波数：928.35 MHz
* TCM410J搭載（技適番号206-000372）

## 使用方法
* シリアルインタフェース：UART
* ボーレート：57600

## 対応基板(動作確認済み)
M5Stack  
M5Stick  
M5Paper  
Atom Matrix  
micro:bit  
SeeeduinoXIAO

## 接続例
![M5Stack](https://github.com/yukima77/EnOceanModule/blob/images/002.JPG)
![micro:bit](https://github.com/yukima77/EnOceanModule/blob/images/003.JPG)

## バージョン情報
2024.10.1：v1.2リリース

## License
This software is released under the MIT License, see LICENSE.
