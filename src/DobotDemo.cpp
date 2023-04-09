/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.cpp
** Latest modified Date:2016-10-24
** Latest Version:      V2.0.0
** Descriptions:        main body
**
**--------------------------------------------------------------------------------------------------------
** Modify by:           Edward
** Modified date:       2016-11-25
** Version:             V1.0.0
** Descriptions:        Modified,From DobotDemoForSTM32
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "Arduino.h"
#include "stdio.h"
#include "Dobot.h"
#include "FlexiTimer2.h"
#include "MemoryFree.h"
#include "hardcoded-g-code.h"
#include "parser.h" 
#include "string" 


//Set Serial TX&RX Buffer Size
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 256

#define DEBUG 1

#define HOME_PIN 52
#define CLEAR_ALARM_PIN  40
#define IDLE_PIN  48
#define START_STOP_PIN 36
#define SIMPLE_PIN1 32
#define SIMPLE_PIN2 28
#define SIMPLE_PIN3 24
#define ENSEMBLE_PIN 25

#define TESTGCODE 29

#define DRAW 33

#define STATUSLED 12


//#define JOG_STICK
#define JOYSTICKX A0 //care it's analog pin
#define JOYSTICKY A1 //care it's analog pin
#define JOYSTICKBUTTON 53
#define ENABLEJOYSTICK 29

bool joyStickDobot = 0;
unsigned long previousActivationJoyStickButton=0;

bool stateStartStop = 1; //Start=1, Stop=0

/*********************************************************************************************************
** Global parameters
*********************************************************************************************************/


int count;
unsigned long previousActivation1=0;
unsigned long previousActivation2=0;
unsigned long previousActivation3=0;
unsigned long previousActivation4=0;
unsigned long previousActivation5=0;
unsigned long previousActivation6=0;
unsigned long previousActivation7=0;
unsigned long previousHomeActivation=0;
unsigned long previousStartStopActivation=0;
unsigned long previousClearAlarm=0;

const unsigned int securityTime=1000;

bool draw_enabled = false;
int draw_index=0;

Point2D A;
Point2D B;
Point2D C;
Point2D D;
Point2D E;
Point2D F;
Point2D G;
Point2D H;
Point2D I;
Point2D J;


bool digitalReadMaison(unsigned char pin);
void pinSwitchPullUp(unsigned char pin);
void ActionSimple();
void drawNext(int index);

Dobot dobot1(DOBOT_1);
Dobot dobot2(DOBOT_2);
Dobot dobot3(DOBOT_3);

//gpr::gcode_program p;
int test=0;


void clearQueue() {
  //printf("==Debut Interuption\n");
  //dobot1.ClearAllAlarms();
  printf("#STOP & CLEAR QUEUE\n");
  dobot1.StopQueueExec(); // ca marche
  dobot1.ClearDobotBuffer(0);
  dobot1.ClearAllAlarms();
  dobot1.StartQueueExec();
  dobot1.ProtocolProcess();
  dobot2.StopQueueExec(); // ca marche
  dobot2.ClearDobotBuffer(0);
  dobot2.ClearAllAlarms();
  dobot2.StartQueueExec();
  dobot2.ProtocolProcess();
  dobot3.StopQueueExec(); // ca marche
  dobot3.ClearDobotBuffer(0);
  dobot3.ClearAllAlarms();
  dobot3.StartQueueExec();
  dobot3.ProtocolProcess();
  stateStartStop = 1;

  //printf("==Fin Interuption (Clear Alarm 21, Stop command exec 241, clear dobot buffer 245, home 31)\n");
}



//SetHOMECmd(HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex);

/*********************************************************************************************************
** Function name:       Serialread
** Descriptions:        import data to rxbuffer
** Input parametersnone:
** Output parameters:   
** Returned value:      
*********************************************************************************************************/

//TODO mettre le serial read dans classe dobot
void Serialread() {
  while (Serial1.available()) {
    uint8_t data = Serial1.read();
    if (RingBufferIsFull(&dobot1._gSerialProtocolHandler.rxRawByteQueue) == false) {
      RingBufferEnqueue(&dobot1._gSerialProtocolHandler.rxRawByteQueue, &data);
    }
  }
  while (Serial2.available()) {
    uint8_t data = Serial2.read();
    if (RingBufferIsFull(&dobot2._gSerialProtocolHandler.rxRawByteQueue) == false) {
      RingBufferEnqueue(&dobot2._gSerialProtocolHandler.rxRawByteQueue, &data);
    }
  }
  while (Serial3.available()) {
    uint8_t data = Serial3.read();
    if (RingBufferIsFull(&dobot3._gSerialProtocolHandler.rxRawByteQueue) == false) {
      RingBufferEnqueue(&dobot3._gSerialProtocolHandler.rxRawByteQueue, &data);
    }
  }
}
/*********************************************************************************************************
** Function name:       Serial_putc
** Descriptions:        Remap Serial to Printf
** Input parametersnone:
** Output parameters:   
** Returned value:      
*********************************************************************************************************/

int Serial_putc(char c, struct __file*) {
  Serial.write(c);
  return c;
}

/*********************************************************************************************************
** Function name:       printf_begin
** Descriptions:        Initializes Printf
** Input parameters:    
** Output parameters:
** Returned value:      
*********************************************************************************************************/

void printf_begin(void) {
  fdevopen(&Serial_putc, 0);
}



/*********************************************************************************************************
** Function name:       setup
** Descriptions:        Initializes Serial
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  printf_begin();
  //Set Timer Interrupt
  FlexiTimer2::set(100, Serialread);
  FlexiTimer2::start();
  pinSwitchPullUp(SIMPLE_PIN1);
  pinSwitchPullUp(SIMPLE_PIN2);
  pinSwitchPullUp(ENSEMBLE_PIN);
  pinSwitchPullUp(JOYSTICKBUTTON);
  pinSwitchPullUp(ENABLEJOYSTICK);
  pinSwitchPullUp(HOME_PIN);
  pinSwitchPullUp(START_STOP_PIN);
  pinSwitchPullUp(CLEAR_ALARM_PIN);
  pinMode(STATUSLED, OUTPUT);

  count = 0;
  attachInterrupt(digitalPinToInterrupt(2), clearQueue, RISING);
  dobot1.ProtocolInit();
  dobot1.InitRam();
  dobot1.SetJOGJointParams(true);
  dobot1.SetJOGCommonParams(true);
  dobot1.SetJOGCoordinateParams(true);
  dobot1.ProtocolProcess();
  printf("FIN SETUP DOBOT 1! \n");
  dobot2.InitRam();
  dobot2.ProtocolInit();
  dobot2.SetJOGJointParams(true);
  dobot2.SetJOGCommonParams(true);
  dobot2.SetJOGCoordinateParams(true);
  dobot2.ProtocolProcess();
  printf("FIN SETUP DOBOT 2! \n");
  dobot3.InitRam();
  dobot3.ProtocolInit();
  dobot3.SetJOGJointParams(true);
  dobot3.SetJOGCommonParams(true);
  dobot3.SetJOGCoordinateParams(true);
  dobot3.ProtocolProcess();
  printf("FIN SETUP DOBOT 3! \n");
  clearQueue();
  
  printf("Test coords \n");

  /*
  float x;
  float y;
  float z;
  x = 148;
  y = 105;
  z = 0;

  dobot1.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 1: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);
  x = 148;
  y = 105;
  z = 0;

  dobot2.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 2: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);

  x = 148;
  y = 105;
  z = 0;

  dobot3.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 3: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);

  x = 0;
  y = 105;
  z = 0;

  dobot1.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 1: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);
  x = 0;
  y = 105;
  z = 0;

  dobot2.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 2: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);

  x = 0;
  y = 105;
  z = 0;

  dobot3.transformFcoordsToDobotCoords(&x, &y, &z);
  printf("dobot 3: x: ");
  Serial.print(x);
  printf(" y: "); 
  Serial.print(y);
  printf(" z: "); 
  Serial.println(z);*/


  ////PARSE G CODE PROGRAMME
  //printf("memoire avant le parse : %d\n",freeMemory());
  //dobot1.prog = gpr::parse_gcode(hardcoded_prog);
  //printf("programme gcode parsé\n");
  //printf("memoire apres le parse : %d\n",freeMemory());

  A.x = 92;
  A.y = 65;
  A.z = 0;

  B.x = 167;
  B.y = 37;
  B.z = 0;

  C.x = 213;
  C.y = 107;
  C.z = 0;

  D.x = 167;
  D.y = 172;
  D.z = 0;
  
  E.x = 92;
  E.y = 147;
  E.z = 0;
  
  F.x = 137;
  F.y = 134;
  F.z = 0;
  
  G.x = 118;
  G.y = 107;
  G.z = 0;
  
  H.x = 137;
  H.y = 78;
  H.z = 0;

  I.x = 166;
  I.y = 78;
  I.z = 0;
  
  J.x = 166;
  J.y = 134;
  J.z = 0;
  
}
/*********************************************************************************************************
** Function name:       loop
** Descriptions:        Program entry
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/

void loop() {
  //home button
  if(digitalReadMaison(HOME_PIN) && millis() - previousHomeActivation > securityTime){
    dobot1.SetHOMECmd(1);
    dobot1.StartQueueExec();
    dobot1.ProtocolProcess();
    dobot2.SetHOMECmd(1);
    dobot2.StartQueueExec();
    dobot2.ProtocolProcess();
    dobot3.SetHOMECmd(1);
    dobot3.StartQueueExec();
    dobot3.ProtocolProcess();
    previousHomeActivation = millis();
  }

  if(digitalReadMaison(START_STOP_PIN) && millis() - previousStartStopActivation > securityTime*0.5){
    if(stateStartStop==1){
      printf("@STOP Queue\n");
      dobot1.StopQueueExec();
      dobot2.StopQueueExec();
      dobot3.StopQueueExec();
    }
    else{
      printf("@START Queue\n");
      dobot1.StartQueueExec();
      dobot2.StartQueueExec();
      dobot3.StartQueueExec();
    }
    stateStartStop ^=1;
    previousStartStopActivation = millis();
  }

  if(digitalReadMaison(SIMPLE_PIN1) && millis() - previousActivation1 > securityTime){
    previousActivation1 = millis();
    dobot1.firstMove();
  }

  if(digitalReadMaison(SIMPLE_PIN2) && millis() - previousActivation2 > securityTime){
    previousActivation2 = millis();
    dobot2.firstMove();
    
    //printf("dobot 1 prochaine instruction\n");
    //dobot1.nextGCodeInstruction();
  }
  if(digitalReadMaison(SIMPLE_PIN3) && millis() - previousActivation4 > securityTime){
    previousActivation4 = millis();
    dobot3.firstMove();
  }

  if(digitalReadMaison(ENSEMBLE_PIN) && millis() - previousActivation3 > securityTime){
    previousActivation3 = millis();
    //dobot1.firstMove();
    //dobot2.firstMove();
    //dobot3.firstMove();
    dobot1.danse();
    dobot2.danse();
    dobot3.danse();

  }
  //ca marche pas
  if(digitalReadMaison(CLEAR_ALARM_PIN) && millis() - previousClearAlarm > securityTime){
    previousClearAlarm = millis();
    dobot1.ClearAllAlarms();
    dobot2.ClearAllAlarms();
  }

  if(digitalReadMaison(TESTGCODE) && millis() - previousActivation5 > securityTime){
    previousActivation5 = millis();
    dobot1.nextGCodeInstruction();
    dobot2.nextGCodeInstruction();
    dobot3.nextGCodeInstruction();
  }
  if(digitalReadMaison(IDLE_PIN) && millis() - previousActivation6 > securityTime){
    previousActivation6 = millis();
    dobot1.idlePos();
    dobot2.idlePos();
    dobot3.idlePos();
  }

  if(digitalReadMaison(DRAW) && millis() - previousActivation7 > securityTime){
    previousActivation7 = millis();
    draw_enabled = true;
  }

  if(draw_enabled && dobot1.available() && dobot2.available() && dobot3.available()){
    drawNext(draw_index);
    draw_index++;
  }
  

  //end of loop
  digitalWrite(STATUSLED,stateStartStop);
  //ask dobot for their command index
  float x = 0;
  float y = 0;
  float z = 0;
  int j = 0;

  dobot1.GetQueuedCmdCurrentIndex(0,&dobot1.queuedCmdIndex);
  dobot2.GetQueuedCmdCurrentIndex(0,&dobot2.queuedCmdIndex);
  dobot3.GetQueuedCmdCurrentIndex(0,&dobot3.queuedCmdIndex);
  //send message to the bus and process response
  dobot1.ProtocolProcess();
  dobot2.ProtocolProcess();
  dobot3.ProtocolProcess();

  delay(100);
  
}



//TODO : DO NOT MODIFY THIS CODE
bool digitalReadMaison(unsigned char pin) {
  return !digitalRead(pin);
}

void pinSwitchPullUp(unsigned char pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void drawNext(int index){
  if(index==0){
    dobot2.drawSegment(&A, &C);
    dobot2.idlePos();
  } else if(index==1){
    dobot3.drawSegment(&C, &E);
    dobot3.idlePos();
  } else if(index==2){
    dobot2.drawSegment(&B, &I);
    dobot2.idlePos();
  } else if(index==3){
    dobot3.drawSegment(&D, &J);
    dobot3.drawSegment(&D, &F);
    dobot3.ProtocolProcess();
    dobot3.idlePos();
  } else if( index==4){
    dobot2.drawSegment(&B, &H);
    dobot2.idlePos();
  } else if(index==5){
    dobot1.drawSegment(&E, &G);
    dobot1.drawSegment(&G, &A);
    dobot1.ProtocolProcess();
    dobot1.idlePos();
    draw_enabled = false;
  }

}