#include <MsTimer2.h>　


// 仕様：ROW側がカソード、COLOMN側がアノードの8x8マトリックスLED
int ANODEPIN[8]   = { 
  12, 13, 14, 15, 16, 17, 18 ,19};  //highピン　high　にて動作
int CATHODEPIN[8] = {  
  4,  5,  6,  7,  8,  9 ,10,11};    //lowピン　  low　にて動作


int batu[8][12] = {    //Ending 時に表示するためのもの　表示処理をこぴぺするために8*12になっている
  { 0,0,1,1,0,0,0,0,1,1,1 },
  { 0,0,1,1,1,0,0,1,1,1,1 },
  { 0,0,0,1,1,1,1,1,1,0,1 },
  { 0,0,0,0,1,1,1,1,0,0,1 },
  { 0,0,0,0,1,1,1,1,0,0,1 },
  { 0,0,0,1,1,1,1,1,1,0,1 },
  { 0,0,1,1,1,0,0,1,1,1,1 },
  { 0,0,1,1,0,0,0,0,1,1,1 }
};
//死亡エリア  stage[3][2]とstage[4][2]
//        ↑右
//←上               下→
//        ↓左
volatile int stage[10][14] ={      //
  { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,1 },
  { 1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

volatile int row;         //ブロックの現在の横部分を担当
volatile int line;        //ブロックの現在の高さを担当
volatile int time = 0;    

int blockNumber = 0;
int kaiten= 0;

boolean running = true;   //falseになることにより　ブロックが下に下りることをやめ回転する



void flash() {
  time++;
  if(digitalRead(2) == HIGH && digitalRead(3) == HIGH && (time %2) == 0){    //ボタンが二つ同時に押された場合に使用
    b_tune();
  }
  else{
    if(digitalRead(2) == HIGH){                                              //左のボタンが押されたときに使用
      l_push();
    }
     if(digitalRead(3) == HIGH){                                            //右のボタンが押されたときに使用
      r_push(); 
    }
  }
  if(time >= 7){                                                              //0.7秒ごとにブロックが落下する処理
      b_down();
      time = 0;
  }
}



void setup()
{
  pinMode(2,INPUT);            //左入力ピン
  pinMode(3,INPUT);            //右入力ピン
  
  // アノードを、LOWで初期化
  for( int ano = 0; ano < 8; ano++ )
  {
    pinMode( ANODEPIN[ano], OUTPUT );
    digitalWrite( ANODEPIN[ano], LOW );
  }
  // カソードを、HIGHで初期化
  for( int cat = 0; cat < 8; cat++ )
  {
    pinMode( CATHODEPIN[cat], OUTPUT );
    digitalWrite( CATHODEPIN[cat], HIGH );
  }
  MsTimer2::set(100, flash); //タイマーセット0.1秒ごとにflash()関数を呼ぶ    include物
  MsTimer2::start();
}

void loop()
{

  if(stage[5][4]== 1 || stage[4][4] == 1) Ending();            //ブロックが降りてくる排出口　つまると　ゲームオーバー
  else b_create();

  running = true;
  while(running){
    show();
  }
  b_check();
  b_check();
  b_check();
  
}



//ここから下が自作の関数たち

void b_create(){
  blockNumber = random(0,100)%2;
  if(blockNumber == 0){
  row=4;
  line=3;
  stage[row][line]=1;            
  stage[row+1][line]=1;
  stage[row][line+1]=1;    //下の段
  stage[row+1][line+1]=1;
  //line行を＋すると下へ行く
  }
  else if(blockNumber == 1){
    kaiten = 0;
    row = 4;
    line = 4;
    kaiten = 0;
    stage[row][line-1]=1;            
    stage[row][line]= 1;
    stage[row][line+1]=1;
  }
}

void b_check(){
 noInterrupts();
 int temp = 0;
 int cat2 = 0;
 int ano2 = 0;
 for(int ano = 0; ano < 8; ano++){
   temp = 0;
   for(int cat = 0; cat < 8; cat++){
     temp= temp+stage[cat+1][ano+4];
   }
   if(temp == 8){
     for(int ano2 = ano ;ano2>=-2;ano2--)
         {
            for(int cat2=0;cat2<8;cat2++)
            {
               stage[cat2+1][ano2+4]=stage[cat2+1][ano2+3];
            }
         }
   }
 }
 interrupts();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・・・この枠内移動処理・・・・・・・・・・・・・・・・・・・・・・・・・・・
void b_down(){

  if(stage[row][line+2]==0 && stage[row+1][line+2]==0 && blockNumber == 0){
    stage[row][line]=0;
    stage[row+1][line]=0;
    stage[row][line+2]=1;
    stage[row+1][line+2]=1;
    line++;
  }
  else if(blockNumber == 1 && stage[row][line+2] == 0 && kaiten == 0){
    stage[row][line-1]=0;
    stage[row][line+2]=1;
    line++;
    }
  else if(blockNumber == 1 && stage[row-1][line+1]==0 && stage[row][line+1]==0 && stage[row+1][line+1]==0 && kaiten == 1){
      stage[row-1][line]=0;
      stage[row][line]=0;
      stage[row+1][line]=0;
      stage[row-1][line+1]=1;
      stage[row][line+1]=1;
      stage[row+1][line+1]=1;
      line++;
  }
  else{
    running = false;
  }
}

void l_push(){

  if(stage[row-1][line]==0 && stage[row-1][line+1]==0 && blockNumber == 0 )  {
    stage[row+1][line]=0;
    stage[row+1][line+1]=0;
    stage[row-1][line]=1;
    stage[row-1][line+1]=1;
    row--;
  }
  else if (blockNumber == 1){
    if(stage[row-1][line-1]==0 &&stage[row-1][line]==0 &&stage[row-1][line+1]==0 && kaiten == 0){
    stage[row][line-1]=0;
    stage[row][line]=0;
    stage[row][line+1]=0;
    stage[row-1][line-1]= 1;
    stage[row-1][line]=1;
    stage[row-1][line+1]=1;
    row--;
    }
    else if(stage[row-2][line]==0 &&kaiten == 1){
      stage[row+1][line]=0;
      stage[row-2][line]=1;
      row--;
    }
  }
}

void r_push(){
  
  if(stage[row+2][line]==0 && stage[row+2][line+1]==0 && blockNumber == 0)  {
    stage[row][line]=0;
    stage[row][line+1]=0;
    stage[row+2][line]=1;
    stage[row+2][line+1]=1;
    row++;
  }
  else if (blockNumber == 1){
    if(stage[row+1][line-1]==0 &&stage[row+1][line]==0 &&stage[row+1][line+1]==0 && kaiten == 0){
    stage[row][line-1]=0;
    stage[row][line]=0;
    stage[row][line+1]=0;
    stage[row+1][line-1]= 1;
    stage[row+1][line]=1;
    stage[row+1][line+1]=1;
    row++;
    }
    else if(stage[row+2][line]==0 &&kaiten == 1){
      stage[row-1][line]=0;
      stage[row+2][line]=1;
      row++;
    }
  }
}

void b_tune(){
  if(blockNumber == 0) return;
  else{
    if(kaiten == 0){
      stage[row][line-1]=0;
      stage[row][line+1]=0;
      stage[row-1][line]=1;
      stage[row+1][line]=1;
      kaiten = 1;
    }else{      
      stage[row-1][line]=0;
      stage[row+1][line]=0;
      stage[row][line-1]=1;
      stage[row][line+1]=1;
      kaiten = 0;
    }
}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・ここまで・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・・


void show(){

  // カソードのループ
  for( int cat = 0; cat < 8; cat++ )
  {
    digitalWrite( CATHODEPIN[cat], LOW );	// LOWに変更
    // アノードのループ
    for( int ano = 0; ano < 8; ano++ )
    {
      digitalWrite( ANODEPIN[ano], stage[cat+1][ano+4] );	// HIGH or LOW
    }
    delayMicroseconds(100);	//点灯時間
    for( int ano = 0; ano < 8; ano++ )
    {
      digitalWrite( ANODEPIN[ano], LOW );	// LOWに戻す
    }
    digitalWrite( CATHODEPIN[cat], HIGH );	// HIGHに戻す
  }
}

void Ending(){
  noInterrupts();
  int timecount= 0;
  while(true){
    for( int cat = 0; cat < 8; cat++ )
    {
      digitalWrite( CATHODEPIN[cat], LOW );	// LOWに変更
      // アノードのループ
      for( int ano = 0; ano < 8; ano++ )
      {
        digitalWrite( ANODEPIN[ano], batu[cat][ano+2] );	// HIGH or LOW
      }
      delay(10);
      for( int ano = 0; ano < 8; ano++ )
      {
        digitalWrite( ANODEPIN[ano], LOW );	// LOWに戻す
      }
      digitalWrite( CATHODEPIN[cat], HIGH );	// HIGHに戻す
      
    }
    
    if(timecount >=50){
      delay(12000);
      timecount = 0;
    }
    timecount++;
  }
}





