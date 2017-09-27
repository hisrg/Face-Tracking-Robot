
/*#define TLF0 31 //
#define TLF1 33//左上轮控制引脚
#define TLB0 35 
#define TLB1 37 //左下轮控制引脚
#define TRF0 39
#define TRF1 41 //右上轮控制引脚
#define TRB0 43
#define TRB1 45 //右下轮控制引脚
*/
#include <PID_v1.h>
#define TLF0 43 //
#define TLF1 45//左上轮控制引脚
#define TLB0 39 
#define TLB1 41 //左下轮控制引脚
#define TRF0 35
#define TRF1 37 //右上轮控制引脚
#define TRB0 31
#define TRB1 33 //右下轮控制引脚
#define PTL0 10//左上轮PWM控制引脚
#define PTL1 11//左下轮PWM控制引脚
#define PTR0 12//右上轮PWM控制引脚
#define PTR1 13//右下轮PWM控制引脚

char PWMPTLF=40;
char PWMPTLB=40;
char PWMPTRB=40;
char PWMPTRF=40;

const int TrigPin =53;//超声波模块发射引脚
const int EchoPin = 51;//超声波模块接收引脚

const byte TLFW=2;//左前轮中断
const byte TRFW=3;//右 前轮中断
const byte TLBW=18;//左后轮中断
const byte TRBW=19;//右后轮中断
char rev_buff[100];//串口0接收缓冲区
char send_buff[100];//串口发送缓冲区
int state=0;//状态变量
char counter_TLFW=0;                                                                                                                                                                                                       
char counter_TRFW=0;
char counter_TLBW=0;
char counter_TRBW=0;
float distance;

void intialztion_Exinter(){
  
   pinMode(TLFW, INPUT_PULLUP);
   pinMode(TRFW, INPUT_PULLUP);
   pinMode(TLBW, INPUT_PULLUP);
   pinMode(TRBW, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(TLFW), EX_INTER_TLFW, FALLING);
   attachInterrupt(digitalPinToInterrupt(TRFW), EX_INTER_TRFW, FALLING);
   attachInterrupt(digitalPinToInterrupt(TRBW), EX_INTER_TRBW, FALLING);
   attachInterrupt(digitalPinToInterrupt(TLBW),EX_INTER_TLBW, FALLING);
  }
void EX_INTER_TLFW(){
  counter_TLFW++;
 
  }
void EX_INTER_TRFW(){
  counter_TRFW++;
  }
void EX_INTER_TLBW(){
  counter_TLBW++;
  }
void EX_INTER_TRBW(){
  counter_TRBW++;
  }
void intialztion_digital(){
   pinMode(TLF0, OUTPUT);
   pinMode(TLF1,OUTPUT);
   pinMode(PTR1,OUTPUT);//
   pinMode(TLB0,OUTPUT);
   pinMode(TLB1,OUTPUT);
   pinMode(TRF0,OUTPUT);
   pinMode(TRF1,OUTPUT);
   pinMode(TRB0,OUTPUT);
   pinMode(TRB1,OUTPUT);
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,LOW);
   state=0;
  }
void wohlespeedcontrol(){
   if(state==1){//左转
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,HIGH);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,HIGH);
   digitalWrite(TRB1,LOW);
   // analogWrite(PTR0, PWMPTRB);
    }
  else if(state==2){//右转
   digitalWrite(TLF0, HIGH);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,HIGH);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,LOW);
    }
   else if(state==3){//前进
   digitalWrite(TLF0, HIGH);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,HIGH);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,HIGH);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,HIGH);
   digitalWrite(TRB1,LOW);
    }
    else if(state==4){//后退
      
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,HIGH);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,HIGH);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,HIGH);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,HIGH);
   
      }
    else if(state==5){
   digitalWrite(TLF0, LOW);//左转PWM控制
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,HIGH);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,HIGH);
   digitalWrite(TRB1,LOW);
   analogWrite(PTR1, PWMPTRB);  
   analogWrite(PTR0, PWMPTRF);      
   }
    else if(state==6){
   digitalWrite(TLF0, HIGH);//右转转PWM控制
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,HIGH);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,LOW);
   analogWrite(PTL0, PWMPTLF);  
   analogWrite(PTL1, PWMPTLB);    
      }
   else if(state==7){
   digitalWrite(TLF0, HIGH);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,HIGH);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,HIGH);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,HIGH);
   digitalWrite(TRB1,LOW);
   analogWrite(PTR1, PWMPTRB);  
   analogWrite(PTR0, PWMPTRF);   
   analogWrite(PTL0, PWMPTLF);  
   analogWrite(PTL1, PWMPTLB);     
    }
   else if(state==8){
    
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,HIGH);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,HIGH);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,HIGH);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,HIGH);
   analogWrite(PTR1, PWMPTRB);  
   analogWrite(PTR0, PWMPTRF);   
   analogWrite(PTL0, PWMPTLF);  
   analogWrite(PTL1, PWMPTLB);     
    }
    else {
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,LOW);
      }
  }

void pasue_100ms(){
   digitalWrite(TLF0, LOW);
   digitalWrite(TLF1,LOW);
   digitalWrite(TLB0,LOW);
   digitalWrite(TLB1,LOW);
   digitalWrite(TRF0,LOW);
   digitalWrite(TRF1,LOW);
   digitalWrite(TRB0,LOW);
   digitalWrite(TRB1,LOW);
   delay(100);
  }
void Communication(){
  char Pre_buff[10];
  int num=0;
  /*if(Serial.available()>0){
       delay(10);
       num=Serial.readBytes(Pre_buff,4);
      num=Pre_buff[0]*256*256*256+Pre_buff[1]*256*256+Pre_buff[2]*256+Pre_buff[3]; 
    }
   
  if(num!=0 || num>100){
    num=Serial.readBytes(rev_buff,num-4);
    }
   else
      Serial.print(" Rec Bytes ERROR!");
   if(rev_buff[0]=='H' && rev_buff[1]=='S')
      Serial.print("Handshake OK");
   else if(rev_buff[0]=='T'&& rev_buff[1]=='S'){
       if(rev_buff[2]=='T'&&rev_buff[3]=='L') state=1;
       else if(rev_buff[2]=='T'&&rev_buff[3]=='R')state=2;
        else if(rev_buff[2]=='A'&&rev_buff[3]=='C')state=3;
        else if(rev_buff[2]=='D'&&rev_buff[3]=='C')state=4;
        else
         state=0;
    }
   //Serial.write(Pre_buff,4);
   //Serial.write(rev_buff,num-4);*/
   if(Serial.available()>0)
   {
    num=Serial.readBytes(rev_buff,12);
    //Serial.flush();
    if(rev_buff[4]=='H' && rev_buff[5]=='S')
      {Serial.print("Handshake OK");}
    else if(rev_buff[4]=='T'&& rev_buff[5]=='S'){
       if(rev_buff[6]=='T'&&rev_buff[7]=='L') {pasue_100ms();state=1;}
       else if(rev_buff[6]=='T'&&rev_buff[7]=='R'){pasue_100ms();state=2;}
        else if(rev_buff[6]=='A'&&rev_buff[7]=='C'){pasue_100ms();state=3;}
        else if(rev_buff[6]=='D'&&rev_buff[7]=='C'){pasue_100ms();state=4;}
        else
         state=0;
        }
       else if(rev_buff[4]=='P'&& rev_buff[5]=='S'){
       if(rev_buff[6]=='T'&&rev_buff[7]=='L') {pasue_100ms();PWMPTRB=rev_buff[8];PWMPTRF=rev_buff[9];state=5;}
       else if(rev_buff[6]=='T'&&rev_buff[7]=='R'){pasue_100ms();PWMPTLF=rev_buff[8];PWMPTLB=rev_buff[9];state=6;}
        else if(rev_buff[6]=='A'&&rev_buff[7]=='C'){pasue_100ms();PWMPTLF=rev_buff[8];PWMPTLB=rev_buff[9];PWMPTRF=rev_buff[10];PWMPTRB=rev_buff[11];state=7;}
        else if(rev_buff[6]=='D'&&rev_buff[7]=='C'){pasue_100ms();PWMPTLF=rev_buff[8];PWMPTLB=rev_buff[9];PWMPTRF=rev_buff[10];PWMPTRB=rev_buff[11];state=8;}
        else
         state=0;
        }
    else if(rev_buff[4]=='S'&& rev_buff[5]=='T')state=0;//停止
    Serial.print("Return Data:");
    Serial.print(rev_buff);
    for(num=0;rev_buff[num]!='\0';num++)
   rev_buff[num]='\0';
    }
  
  }
void intialztion_Ultrasonic(){
  pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);
  }
void setup() {
  // put your setup code here, to run once:
  intialztion_digital();
  intialztion_Exinter();
  intialztion_Ultrasonic();
  Serial.begin(9600);
  
}
void serial_senddata(){
  Serial.print("CCDDBA");//6
  Serial.write(counter_TLFW);//7
  Serial.write(counter_TLBW);//8
  Serial.write(counter_TRFW);//9
  Serial.write(counter_TRBW);//10
  Serial.print(distance,2);//N
  Serial.print("DDCC\n");//N+11
  counter_TLFW=0;
  counter_TLBW=0;
  counter_TRFW=0;
  counter_TRBW=0;
  }
void Procesing_Ultrasonic(){
 
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);
  
distance = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米，声音的速度340m/s或29us/cm，脉冲传播出来再折返回来，所以所求对象的距离行程的一般/29/2=/58
}

void loop() {
Communication();
  // put your main code here, to run repeatedly:
wohlespeedcontrol();
serial_senddata();
Procesing_Ultrasonic();
delay(300);
//Serial.print("Windows");
}
