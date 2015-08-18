void setup() {

  Serial.begin(9600);
  Serial.print("TCCR1A before: "); Serial.println(_SFR_BYTE(TCCR1A),BIN);//制御レジスタA  GPIO9
  Serial.print("TCCR1B before: "); Serial.println(_SFR_BYTE(TCCR1B),BIN);//制御レジスタB  GPIO10
  Serial.print("TCCR2A before: "); Serial.println(_SFR_BYTE(TCCR2A),BIN);//制御レジスタA  GPIO11
  Serial.print("TCCR2B before: "); Serial.println(_SFR_BYTE(TCCR2B),BIN);//制御レジスタB  GPIO3
  Serial.print("TCCR0A before: "); Serial.println(_SFR_BYTE(TCCR0A),BIN);//制御レジスタA  GPIO6
  Serial.print("TCCR0B before: "); Serial.println(_SFR_BYTE(TCCR0B),BIN);//制御レジスタB  GPIO5

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);

//タイマ１のＰＷＭ波形設定  Pin9 Pin10対応  タイマ１のみ使用レジスタが16ビットのため設定量が多い
  TCCR1A = _BV(WGM11);                      //タイマ１波形モード 10番を使用するための設定。
  TCCR1B = _BV(WGM13);                      //タイマ１波形モード 10番を使用するための設定。
  TCCR1B |= _BV(CS10);                      //タイマ１の分周比を 1に設定   クロック周波数は16Mhz pwm周波数は500Hz
  TCCR1A |= _BV(COM1A1);                    //タイマ１とGPIO9をつなげる。
  TCCR1A |= _BV(COM1B1);                    //タイマ１とGPIO10をつなげる。
  ICR1   = 0x00FF;                          //タイマ１の最大値を255へ;

//タイマ２のＰＷＭ波形設定  Pin11 Pin3対応
  TCCR2B =  _BV(CS20);                      //タイマ２の分周比を1に設定                  //タイマ１の最大値を255へ;
  TCCR2A =  _BV(WGM20);                     //タイマ２の波形モード  1を使用するための設定
  TCCR2A |= _BV(COM2A1);                    //タイマ２とGPIO11をつなげる。
  TCCR2A |= _BV(COM2B1);                    //タイマ２とGPIO3をつなげる。

//タイマ０のＰＷＭ波形設定　Pin5 Pin6対応
  TCCR0B =  _BV(CS00);                      //タイマ０の分周比を１に設定                  //タイマ１の最大値を255へ;
  TCCR0A =  _BV(WGM00);                     //タイマ０の波形モード  1を使用するための設定
  TCCR0A |= _BV(COM0A1);                    //タイマ０とGPIO11をつなげる。
  TCCR0A |= _BV(COM0B1);                    //タイマ０とGPIO3をつなげる。

  Serial.print("TCCR2A after: "); Serial.println(_SFR_BYTE(TCCR1A),BIN);//制御レジスタA  GPIO9
  Serial.print("TCCR2B after: "); Serial.println(_SFR_BYTE(TCCR1B),BIN);//制御レジスタB  GPIO10
  Serial.print("TCCR2A after: "); Serial.println(_SFR_BYTE(TCCR2A),BIN);//制御レジスタA  GPIO11
  Serial.print("TCCR2B after: "); Serial.println(_SFR_BYTE(TCCR2B),BIN);//制御レジスタB  GPIO3
  Serial.print("TCCR0A after: "); Serial.println(_SFR_BYTE(TCCR0A),BIN);//制御レジスタA  GPIO6
  Serial.print("TCCR0B after: "); Serial.println(_SFR_BYTE(TCCR0B),BIN);//制御レジスタB  GPIO5
}

void loop() {
  // put your main code here, to run repeatedly:

  OCR1A = (1500 - 1000) >> 2;               //タイマ１と比較し　タイマ１ < OCR1A　ならばGPIO9  をOnにする
  OCR1B = (1500 - 1000) >> 2;               //タイマ１と比較し　タイマ１ < OCR1B　ならばGPIO10 をOnにする
  OCR2A = (1500 - 1000) >> 2;               //タイマ２と比較し　タイマ２ < OCR2A　ならばGPIO11 をOnにする
  OCR2B = (1500 - 1000) >> 2;               //タイマ２と比較し　タイマ２ < OCR2B　ならばGPIO3  をOnにする
  OCR0A = (1500 - 1000) >> 2;               //タイマ０と比較し　タイマ０ < OCR0A　ならばGPIO6  をOnにする
  OCR0B = (1500 - 1000) >> 2;               //タイマ０と比較し　タイマ０ < OCR0B　ならばGPIO5  をOnにする
  
}

