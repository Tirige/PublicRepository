#include <avr/interrupt.h>

volatile uint8_t atomicPWM_PIN5_lowState;
volatile uint8_t atomicPWM_PIN5_highState;
volatile uint8_t atomicPWM_PIN6_lowState;
volatile uint8_t atomicPWM_PIN6_highState;

ISR(TIMER0_COMPB_vect) { 
  static uint8_t state = 0;
  if(state == 0){
    if (atomicPWM_PIN5_highState>0) 
      PORTD |= 1<<5;//SOFT_PWM_1_PIN_HIGH;
    OCR0B += atomicPWM_PIN5_highState;
    state = 1;
  }else if(state == 1){
    OCR0B += atomicPWM_PIN5_highState;
    state = 2;
  }else if(state == 2){
    PORTD &= ~(1<<5);//SOFT_PWM_1_PIN_LOW;
    OCR0B += atomicPWM_PIN5_lowState;
    state = 3;  
  }else if(state == 3){
    OCR0B += atomicPWM_PIN5_lowState;
    state = 0;   
  }
}

ISR(TIMER0_COMPA_vect) { 
  static uint8_t state = 0;
  if(state == 0){
    if (atomicPWM_PIN6_highState>0) 
      PORTD |= 1<<6;//SOFT_PWM_2_PIN_HIGH;
    OCR0A += atomicPWM_PIN6_highState;
    state = 1;
  }else if(state == 1){
    OCR0A += atomicPWM_PIN6_highState;
    state = 2;
  }else if(state == 2){
    PORTD &= ~(1<<6);//SOFT_PWM_2_PIN_LOW;
    OCR0A += atomicPWM_PIN6_lowState;
    state = 3;  
  }else if(state == 3){
    OCR0A += atomicPWM_PIN6_lowState;
    state = 0;   
  }
}

void setup() {
  Serial.begin(9600);
  Serial.print("TCCR1A before: "); Serial.println(_SFR_BYTE(TCCR1A),BIN);//制御レジスタA
  Serial.print("TCCR1B before: "); Serial.println(_SFR_BYTE(TCCR1B),BIN);//制御レジスタB

  Serial.print("OCR1A before: "); Serial.println(_SFR_BYTE(OCR1A),BIN);//比較レジスタA
  Serial.print("OCR1B before: "); Serial.println(_SFR_BYTE(OCR1B),BIN);//比較レジスタB
  
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  
  TCCR0A = 0; // normal counting mode。
  TIMSK0 |= (1<<OCIE0B);  //割り込み処理設定　ISR(TIMER0_COMPB_vect)へ飛ぶ？
  TIMSK0 |= (1<<OCIE0A);  //割り込み処理設定　ISR(TIMER0_COMPA_vect)へ飛ぶ？
  
  atomicPWM_PIN6_highState = (1500 >> 2) -250;
  atomicPWM_PIN5_highState = (1200 >> 2) -250;
  atomicPWM_PIN6_lowState  = 255-atomicPWM_PIN6_highState;
  atomicPWM_PIN5_lowState  = 255-atomicPWM_PIN5_highState; 

  delay(5000);


  
}

void loop() {

}
