#include <Wire.h>

#define ACC_ADDR (0x53)   //i2cスレーブデバイスのアドレス　加速度センサーで使用   使用しているデバイス名はADXL345
#define GYRO_ADDR (0x6A)  //i2cスレーブデバイスのアドレス　角速度センサーで使用   使用しているデバイス名はAE-L3GD20
#define MAG_ADDR  (0x1E)    //i2cスレーブデバイスのアドレス　地磁気センサーで使用   使用しているデバイス名はHMC5883L

int length = 6;
byte buff[6];              //i2c_getで使用　スレーブからのデータを格納する。

int acc_x,acc_y,acc_z;    //加速度センサーの取得パラメータを格納する場所
int gyro_x,gyro_y,gyro_z; //ジャイロセンサーの取得パラメータを格納する場所
int mag_x,mag_y,mag_z;    //地磁気センサーの取得パラメータを格納する場所

void setup() {
  // put your setup code here, to run once:

 Wire.begin();                  //I2Cの開始
 Serial.begin(9600);           //シリアルポートでのデバッグで利用する。

 //加速度センサーのセットアップ
 i2c_setup(ACC_ADDR,0x31,0x00);
 i2c_setup(ACC_ADDR,0x2d, 0x08);

 //角速度センサーのセットアップ
 i2c_setup(GYRO_ADDR,0x20,0x0f);

 //地磁気センサーのセットアップ
 i2c_setup(MAG_ADDR,0x02,0x00);

 //デバッグ時に見やすい用に枠組みを表示
 Serial.println("ACC_x , ACC_y , ACC_z | ");//加速度センサー各値名
 Serial.print("Gyro_x , Gyro_y , Gyro_z | ");//ジャイロセンサー各値名
 Serial.print("MAG_x , MAG_y , MAG_z");//地磁気センサー各値名
 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  i2c_get(ACC_ADDR, 0x32, length, buff);   //加速度デバイスからパラメータを取得
  acc_x = (((int)buff[1]) << 8) | buff[0];   
  acc_y = (((int)buff[3]) << 8) | buff[2];
  acc_z = (((int)buff[5]) << 8) | buff[4];

  i2c_get(GYRO_ADDR, 0x28, length, buff);  //加速度デバイスからパラメータを取得
  gyro_x = (((int)buff[1]) << 8) | buff[0];   
  gyro_y = (((int)buff[3]) << 8) | buff[2];
  gyro_z = (((int)buff[5]) << 8) | buff[4];

  i2c_get(MAG_ADDR, 0x03, length, buff);   //加速度デバイスからパラメータを取得
  mag_x = (((int)buff[1]) << 8) | buff[0];   
  mag_y = (((int)buff[3]) << 8) | buff[2];
  mag_z = (((int)buff[5]) << 8) | buff[4];

  Serial.print(acc_x);Serial.print(" , ");Serial.print(acc_y);Serial.print(" , ");Serial.print(acc_z);Serial.print(" | ");    //加速度を表示
  Serial.print(gyro_x);Serial.print(" , ");Serial.print(gyro_y);Serial.print(" , ");Serial.print(gyro_z);Serial.print(" | "); //角速度を表示
  Serial.print(mag_x);Serial.print(" , ");Serial.print(mag_y);Serial.print(" , ");Serial.print(mag_z);Serial.println();       //地磁気を表示
  
  for(;;);
  //ここには来ない
}

//基本的にはパワーのレジスタをオンにする。
void i2c_setup(int device_addr,byte register_addr, byte value)
{
  Wire.beginTransmission(device_addr);    //利用するデバイスの選択する。
  Wire.write(register_addr);              //スレーブデバイスのキューに書き込み先データ   をストックする。
  Wire.write(value);                      //スレーブデバイスのキューに書き込み内容データ をストックする。
  Wire.endTransmission();                 //スレーブデバイスへの送信を終了する。
}

//i2c_setupでレジスタアドレスからnum bit分データを格納する。
void i2c_get(int device_addr,byte register_addr, int num, byte buffer[])
{
  Wire.beginTransmission(device_addr);    //利用するデバイスの選択
  Wire.write(register_addr);              //スレーブデバイスのキューにデータをストックする
  Wire.endTransmission();                 //スレーブデバイスへの送信を終了する。

  Wire.beginTransmission(device_addr);    //利用するデバイスの選択
  Wire.requestFrom(device_addr, num);     //上記のwriteでストックされたデータからnum byte分データの取得宣言をする

  int i = 0;
  while(Wire.available() || i < num)      //最高num回スタックデータを受信        
  { 
    buffer[i] = Wire.read();              //取得したデータを引数配列に格納   
    i++;
  }
  Wire.endTransmission();
}

