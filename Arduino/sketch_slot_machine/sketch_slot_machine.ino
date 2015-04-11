#include <MsTimer2.h>　

#define SPEAKER A4
// 仕様：ROW側がカソード、COLOMN側がアノードの7セグメントLED*4
int ANODEPIN[8]   = { 
  6, 7, 8, 9, 10, 11, 12, 13};
int CATHODEPIN[8] = {  
  2, 3, 4, 5 };
  
int stage[10][9] = {
  {  //0を表示
          1,
        1,  1,
          0,
        1,  1,
          1,  0
  },
  {  //1を表示
          0,
        0,  1,
          0,
        0,  1,
          0,  0
  },
  {  //2を表示
          1,
        0,  1,
          1,
        1,  0,
          1,  0
  },
  {  //3を表示
          1,
        0,  1,
          1,
        0,  1,
          1,  0
  },
  {  //4を表示
          0,
        1,  1,
          1,
        0,  1,
          0,  0
  },{  //5を表示
          1,
        1,  0,
          1,
        0,  1,
          1,  0
  },{  //6を表示
          1,
        1,  0,
          1,
        1,  1,
          1,  0
  },{  //7を表示
          1,
        0,  1,
          0,
        0,  1,
          0,  0
  },{  //8を表示
          1,
        1,  1,
          1,
        1,  1,
          1,  0
  },{  //9を表示
          1,
        1,  1,
          1,
        0,  1,
          1,  0
  }
};
  
volatile int number[4] = {0,3,6,8};
volatile int time = 0;

volatile boolean b_check[4] = {true, true, true, true};

  
void flash() {
  if( digitalRead(A0) == HIGH) b_check[0] = false; 
  if( digitalRead(A1) == HIGH) b_check[1] = false;
  if( digitalRead(A2) == HIGH) b_check[2] = false;
  if( digitalRead(A3) == HIGH) b_check[3] = false;
  
  if ( b_check[0]) number[0]++;
  if ( b_check[1]) number[1]++;
  if ( b_check[2]) number[2]++;
  if ( b_check[3]) number[3]++;
  
  if(number[0] >= 10) number[0]= 0;
  if(number[1] >= 10) number[1]= 0;
  if(number[2] >= 10) number[2]= 0;
  if(number[3] >= 10) number[3]= 0;
  
  
}  
  
void setup()
{ 
  //アノードを、LOWで初期化
  for(int ano = 0; ano < 8; ano++)
  {
    pinMode( ANODEPIN[ano], OUTPUT);
    digitalWrite( ANODEPIN[ano], LOW);
  }
  //カソードを、HIGHで初期化
    // カソードを、HIGHで初期化
  for( int cat = 0; cat < 4; cat++ )
  {
    pinMode( CATHODEPIN[cat], OUTPUT );
    digitalWrite( CATHODEPIN[cat], HIGH );
  }
   MsTimer2::set(100, flash); //タイマーセット0.1秒ごとにflash()関数を呼ぶ    include物
   MsTimer2::start();
}

void loop()
{
  for( int cat = 0; cat < 4; cat++ ){
    digitalWrite( CATHODEPIN[cat], LOW );
    show(cat);
    digitalWrite( CATHODEPIN[cat], HIGH );
  }
  if(b_check[0] == false && b_check[1] == false && b_check[2] == false && b_check[3] == false) time++;
  if(time >=300) finish();
}

void show(int n){
    // アノードのループ
    for( int ano = 0; ano < 8; ano++ )
    {
      digitalWrite( ANODEPIN[ano], stage[number[n]][ano] );	// HIGH or LOW
    }
    delayMicroseconds(100);	//点灯時間
    for( int ano = 0; ano < 8; ano++ )
    {
      digitalWrite( ANODEPIN[ano], LOW );	// LOWに戻す
    }
}
  
void finish(){
  
  if(number[0] == number[1] == number[2] == number[3])
      win();
   lose();
}

void win(){
  while(true){
    tone(A4,554,300);
    delay(1000);
  }
}

void lose(){
  while(true){
  
    tone(A4,2620,200);
    delay(200);
    tone(A4,2620,200);
    delay(200);
    tone(A4,2620,200);
    delay(200);
    tone(A4,2620,200);
    delay(1000);
  }
}
