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
#include "parser.h" 
#include <string> 

#include "instruction.h"


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
#define ORDO_PIN -1

#define TESTGCODE 29

#define DRAW 33

#define STATUSLED 12



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
unsigned long previousActivation8=0;
unsigned long previousHomeActivation=0;
unsigned long previousStartStopActivation=0;
unsigned long previousClearAlarm=0;

const unsigned int securityTime=1000;

bool draw_enabled = false;
int draw_index=0;

Point3D A;
Point3D B;
Point3D C;
Point3D D;
Point3D E;
Point3D F;
Point3D G;
Point3D H;
Point3D I;
Point3D J;


JOGJointParams gJOGJointParams;
JOGCoordinateParams gJOGCoordinateParams;
JOGCommonParams gJOGCommonParams;
PTPCoordinateParams gPTPCoordinateParams;
PTPCommonParams gPTPCommonParams;
//PTPJumpParams gptpJumpParams;


bool digitalReadMaison(unsigned char pin);
void pinSwitchPullUp(unsigned char pin);
void ActionSimple();
void drawNext(int index);
void InitRam(void);

Dobot dobot1(DOBOT_1);
Dobot dobot2(DOBOT_2);
Dobot dobot3(DOBOT_3);


int test=0;
bool demo = false;
uint8_t semaphore = 1;
Dobot *dobots[] = {&dobot1, &dobot2, &dobot3};
uint16_t index_ordo = 0;



void clearQueue() {
  //printf("==Debut Interuption\n");
  //dobot1.ClearAllAlarms();
  Serial.println(F("#STOP & CLEAR QUEUE"));
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
void Serialread() {
    dobot1.serialRead();
    dobot2.serialRead();
    dobot3.serialRead();
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
  pinSwitchPullUp(HOME_PIN);
  pinSwitchPullUp(START_STOP_PIN);
  pinSwitchPullUp(CLEAR_ALARM_PIN);
  pinMode(STATUSLED, OUTPUT);

  count = 0;
  attachInterrupt(digitalPinToInterrupt(2), clearQueue, RISING);
  InitRam();

  dobot1.ProtocolInit();
  dobot1.setUp(&gJOGJointParams, &gJOGCommonParams, &gJOGCoordinateParams);
  dobot1.ProtocolProcess();
  Serial.println(F("FIN SETUP DOBOT 1!"));

  dobot2.ProtocolInit();
  dobot2.setUp(&gJOGJointParams, &gJOGCommonParams, &gJOGCoordinateParams);
  dobot2.ProtocolProcess();
  Serial.println(F("FIN SETUP DOBOT 2!"));


  dobot3.ProtocolInit();
  dobot3.setUp(&gJOGJointParams, &gJOGCommonParams, &gJOGCoordinateParams);
  dobot3.ProtocolProcess();
  Serial.println(F("FIN SETUP DOBOT 3!"));
  clearQueue();
  
  Serial.println(F("Test coords"));

  
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

  /*Serial.print(F("memory free : "));
  Serial.println(freeMemory());
  
  Serial.println(F("debut parse gcode 1"));

  gcode::parseNext20(&dobot1.prog, robot_1, &index_robot_1);



  Serial.println(F("fin parse gcode 1"));*/

  Serial.print(F("taille du programme : "));
  Serial.println(dobot1.prog.num_blocks());


  Serial.print(F("memory free : "));
  Serial.println(freeMemory());
  
  Serial.println(F("FIN DU SETUP"));
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
      Serial.println(F("@STOP Queue"));
      dobot1.StopQueueExec();
      dobot2.StopQueueExec();
      dobot3.StopQueueExec();
    }
    else{
      Serial.println(F("@START Queue"));
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

  uint16_t nb_instruction[] = {dobot1.prog.num_blocks() + dobot2.prog.num_blocks() + dobot3.prog.num_blocks(), dobot1.prog.num_blocks(), dobot2.prog.num_blocks(), dobot3.prog.num_blocks()};
  /*------------------------------------------------------------------------------
  dobot1.prog.num_blocks(); //Total
  dobot1.actualProgIndex; //Index auquel on est 
  dobot1.prog.num_blocks() - dobot1.actualProgIndex;  //ce qu'il nous reste
  ------------------------------------------------------------------------------*/
  uint8_t ordo[nb_instruction[0]]; // tab de ordonnencement des dobots. Ex: [1,1,2,0,0,1,0,2,2,...]
  if (digitalReadMaison(ORDO_PIN) && millis() - previousActivation8 > securityTime)
  {
    previousActivation8 = millis();
    unsigned int i = 0;
    demo = true;
    index_ordo = 0;
    while (i < nb_instruction[0])
    {
      uint8_t r = random(0, 2); // Choisi un robot aléatoirement qui a encore des tâches à faire
      if (nb_instruction[r] > 0)
      {
        nb_instruction[r]--;
        ordo[i] = r;
        i++;
      }
    }
  }

  if (demo == true)
  {
    if (semaphore == 1)
    {
      semaphore = 0;
      dobots[ordo[index_ordo]]->goToPreviousPos();
      do
      {
        dobots[ordo[index_ordo]]->nextGCodeInstruction();
        index_ordo++;
      } while (ordo[index_ordo == ordo[index_ordo - 1]]);
      //dobots[ordo[index_ordo]].pose = dobots[ordo[index_ordo]].getPose(&dobot1.pose);
      dobots[ordo[index_ordo]]->storePreviousPos(); //On prend la nouvelle position du robot
      dobots[ordo[index_ordo]]->idlePos();
    }
    if(semaphore == 0 && dobots[ordo[index_ordo]]->available())
    {
      semaphore = 1;
      if(index_ordo == nb_instruction[0]){
        demo = false;
      }
    }
  }
  

  //end of loop
  digitalWrite(STATUSLED,stateStartStop);
 

  dobot1.GetQueuedCmdCurrentIndex(0,&dobot1.queuedCmdIndex);
  dobot2.GetQueuedCmdCurrentIndex(0,&dobot2.queuedCmdIndex);
  dobot3.GetQueuedCmdCurrentIndex(0,&dobot3.queuedCmdIndex);
  //send message to the bus and process response
  dobot1.ProtocolProcess();
  dobot2.ProtocolProcess();
  dobot3.ProtocolProcess();

  delay(100);
  
  //printf();
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


void InitRam(){
    //Set JOG Model
    gJOGJointParams.velocity[0] = 100;
    gJOGJointParams.velocity[1] = 100;
    gJOGJointParams.velocity[2] = 100;
    gJOGJointParams.velocity[3] = 100;
    gJOGJointParams.acceleration[0] = 80;
    gJOGJointParams.acceleration[1] = 80;
    gJOGJointParams.acceleration[2] = 80;
    gJOGJointParams.acceleration[3] = 80;

    gJOGCoordinateParams.velocity[0] = 100;
    gJOGCoordinateParams.velocity[1] = 100;
    gJOGCoordinateParams.velocity[2] = 100;
    gJOGCoordinateParams.velocity[3] = 100;
    gJOGCoordinateParams.acceleration[0] = 80;
    gJOGCoordinateParams.acceleration[1] = 80;
    gJOGCoordinateParams.acceleration[2] = 80;
    gJOGCoordinateParams.acceleration[3] = 80;

    gJOGCommonParams.velocityRatio = 100;
    gJOGCommonParams.accelerationRatio = 80;





    //Set PTP Model
    gPTPCoordinateParams.xyzVelocity = 100;
    gPTPCoordinateParams.rVelocity = 100;
    gPTPCoordinateParams.xyzAcceleration = 80;
    gPTPCoordinateParams.rAcceleration = 80;

    gPTPCommonParams.velocityRatio = 50;
    gPTPCommonParams.accelerationRatio = 50;




}