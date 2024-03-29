**バージョンによって、ピンアサインが変更になっています。ご注意ください。誤って設定した場合もモジュールが破損することはありません。**

# EnOceanModule
![商品](https://github.com/yukima77/EnOceanModule/blob/images/001.JPG)

# 説明
EnOcean用送受信モジュールです。TCM410Jを搭載しています。

# ピンアサイン
Seeed株式会社のGroveSystemのピンアサインに合わせる為、v1.1よりピンアサインを変更しています。バージョン情報がプリント基板に記載されていない以前のモジュールとはピンアサインが変更になっていますのでご注意下さい。v1.1以降は、GroveSystemの使ったボードでのHardwareSerialを使った通信も可能になります。
[Seeed株式会社GroveSystem](https://wiki.seeedstudio.com/Grove_System/)

### v1.1
1.RX (which the base unit uses to receive data, so it is an input)  
2.TX (which the base unit uses to transmit data to the Grove module)  
3.VCC  
4.GND  

### 無印
1.TX (which the base unit uses to transmit data to the Grove module)  
2.RX (which the base unit uses to receive data, so it is an input)  
3.VCC  
4.GND  

# 使い方
ボーレート57600baudでシリアル通信が出来ます

# 対応基板(動作確認済み)
M5Stack  
M5Stick  
M5Paper  
Atom Matrix  
micro:bit  
SeeeduinoXIAO

# 接続例
![M5Stack](https://github.com/yukima77/EnOceanModule/blob/images/002.JPG)
![micro:bit](https://github.com/yukima77/EnOceanModule/blob/images/003.JPG)

# License
This software is released under the MIT License, see LICENSE.
