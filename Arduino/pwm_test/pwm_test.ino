void setup() {
  Serial.begin(9600);
  Serial.print("TCCR1A before: "); Serial.println(_SFR_BYTE(TCCR1A),BIN);//制御レジスタA
  Serial.print("TCCR1B before: "); Serial.println(_SFR_BYTE(TCCR1B),BIN);//制御レジスタB

  Serial.print("OCR1A before: "); Serial.println(_SFR_BYTE(OCR1A),BIN);//比較レジスタA
  Serial.print("OCR1B before: "); Serial.println(_SFR_BYTE(OCR1B),BIN);//比較レジスタB
  
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  TCCR1A = _BV(WGM11);                      //タイマ１波形モード１０番を使用するための設定。
  TCCR1B = _BV(WGM13);                      //タイマ１波形モード１０番を使用するための設定。
  
  TCCR1B |= _BV(CS10);                      //タイマ１の分周比を１に設定   クロック周波数は16Mhz pwm周波数は500Hz
  
  TCCR1A |= _BV(COM1A1);                    //タイマ１とGPIO9をつなげる。
  TCCR1A |= _BV(COM1B1);                    //タイマ１とGPIO10をつなげる。

  ICR1   = 0x00FF;                          //タイマ１の最大値を255へ;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  OCR1A = (1150 - 1000) >> 2;               //タイマ１と比較し　タイマ１ < OCR1A　ならばGPIO9をOnにする
  OCR1B = (1800 - 1000) >> 2;               //タイマ１と比較し　タイマ１ < OCR1B　ならばGPIO10をOnにする
}
