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

#define HOME_PIN 33
#define IDLE_SAFE  41
#define IDLE_PIN  37
#define START_STOP_PIN 53
#define SIMPLE_PIN1 52
#define SIMPLE_PIN2 48
#define SIMPLE_PIN3 44
#define DANSE_PIN 40


#define ORDO_PIN 45

#define DRAW_PIN 36
#define DRAW_PIN_RANDOM 32

#define STATUSLED 49

#define SEMAPHORE_LIBRE 5



bool stateStartStop = 1; //Start=1, Stop=0

/*********************************************************************************************************
** Global parameters
*********************************************************************************************************/


unsigned long previousActivationSimple1=0;
unsigned long previousActivationSimple2=0;
unsigned long previousActivationSimple3=0;
unsigned long previousDanseActivation=0;
unsigned long previousIdleActivation=0;
unsigned long previousDrawActivation=0;
unsigned long previousOrdoActivation=0;
unsigned long previousHomeActivation=0;
unsigned long previousStartStopActivation=0;


const unsigned int securityTime=1000;

bool draw_enabled = false;
bool draw_enabled_random = false;
int draw_index=0;

uint8_t r1;
uint8_t r2;

uint8_t done =0;

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


bool demo = false;
uint8_t semaphore = 1;
Dobot *dobots[] = {&dobot1, &dobot2, &dobot3};
uint16_t index_ordo = 0;



void clearQueue() {
  Serial.println(F("#STOP & CLEAR QUEUE"));
  dobot1.ForceStopQueueExec();
  dobot1.ClearDobotBuffer(0);
  dobot1.ClearAllAlarms();
  dobot1.StartQueueExec();
  dobot1.ProtocolProcess();
  dobot2.ForceStopQueueExec();
  dobot2.ClearDobotBuffer(0);
  dobot2.ClearAllAlarms();
  dobot2.StartQueueExec();
  dobot2.ProtocolProcess();
  dobot3.ForceStopQueueExec();
  dobot3.ClearDobotBuffer(0);
  dobot3.ClearAllAlarms();
  dobot3.StartQueueExec();
  dobot3.ProtocolProcess();
  stateStartStop = 1;

  draw_enabled = false;
  draw_enabled_random = false;
  demo = false;

}



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
  randomSeed(millis());
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
  pinSwitchPullUp(DANSE_PIN);
  pinSwitchPullUp(HOME_PIN);
  pinSwitchPullUp(START_STOP_PIN);
  pinSwitchPullUp(IDLE_PIN);
  pinSwitchPullUp(IDLE_SAFE);
  pinMode(STATUSLED, OUTPUT);

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

  r1 = random(0, 2);
  r2 = random(0, 2);
  
  Serial.println(F("Test coords"));

  //points pour l'etoile
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

  if(digitalReadMaison(SIMPLE_PIN1) && millis() - previousActivationSimple1 > securityTime){
    previousActivationSimple1 = millis();
    dobot1.firstMove();
  }

  if(digitalReadMaison(SIMPLE_PIN2) && millis() - previousActivationSimple2 > securityTime){
    previousActivationSimple2 = millis();
    dobot2.firstMove();
  }
  if(digitalReadMaison(SIMPLE_PIN3) && millis() - previousActivationSimple3 > securityTime){
    previousActivationSimple3 = millis();
    dobot3.firstMove();
  }

  if(digitalReadMaison(DANSE_PIN) && millis() - previousDanseActivation > securityTime){
    previousDanseActivation = millis();
    dobot1.danse();
    dobot2.danse();
    dobot3.danse();
  }

  if(digitalReadMaison(IDLE_PIN) && millis() - previousIdleActivation > securityTime){
    previousIdleActivation = millis();
    dobot1.idlePos();
    dobot2.idlePos();
    dobot3.idlePos();
  }

  if(digitalReadMaison(IDLE_SAFE) && millis() - previousIdleActivation > securityTime){
    previousIdleActivation = millis();
    dobot1.idleSafe();
    dobot2.idleSafe();
    dobot3.idleSafe();
  }

  if(digitalReadMaison(DRAW_PIN_RANDOM) && millis() - previousDrawActivation > securityTime){
    previousDrawActivation = millis();
    draw_enabled_random = true;
  }

  if(digitalReadMaison(DRAW_PIN) && millis() - previousDrawActivation > securityTime){
    previousDrawActivation = millis();
    draw_enabled = true;
  }


  if(draw_enabled_random && dobot1.available() && dobot2.available() && dobot3.available()){
    do{
      draw_index = random(0, 8);
    } while(((done >> draw_index) & 1) == 1);
    done = done | (1 << draw_index);
    Serial.print(done);
    drawNext(draw_index);
    if(done == 0xFF) {
      draw_enabled_random = false;
      draw_index=0;
      done = 0;
    }




    Serial.print(F("Mermoire restante : "));
    Serial.println(freeMemory());
  }
  if(draw_enabled && dobot1.available() && dobot2.available() && dobot3.available()){

    drawNext(draw_index);
    draw_index++;

    if(draw_index == 8){
      draw_index=0;
      draw_enabled=false;
    }

    Serial.print(F("Mermoire restante : "));
    Serial.println(freeMemory());
  }

  /********************************NON FONCTIONNEL*******************************************************/
  r1 = 2;//index 2 pour dobot 3
  r2 = 2;
  uint8_t err=0;
  if (digitalReadMaison(ORDO_PIN) && millis() - previousOrdoActivation > securityTime)
  {
    previousOrdoActivation = millis();
    demo ^= 1;
    Serial.print(F("demo : "));
    Serial.println(demo);
    dobot1.idlePos();

  }
  if(demo){
    if(semaphore != SEMAPHORE_LIBRE){
      //occupé
      if(dobots[semaphore]->available()) semaphore = SEMAPHORE_LIBRE;
    }
    if(semaphore == SEMAPHORE_LIBRE){
        //dobot1.updateProg(robot_3, &index_robot_3);
        Serial.print(F("Memory free :"));
        Serial.println(freeMemory());
        //revenir a la position precedente
        err = dobots[r1]->goToPreviousPos();
        Serial.print("previous pos : ");
        Serial.println(err);
        //continuer le programme
        err = dobots[r1]->nextGCodeInstruction();
        Serial.print("next gcode : ");
        Serial.println(err);
        //verrouille la semaphore
        dobots[r1]->ProtocolProcess(); 
        semaphore = r1;
        if(r1 != r2){
          dobots[r1]->idlePos();
        }

        r1 = r2;
        r2 = random(0, 2);
    }
    if(err>0) demo=false;
  }
  /*******************************************************************************************************/

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

}



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
    dobot1.drawSegment(&E, &G);
    dobot1.idlePos();
  } else if(index==3){
    dobot2.drawSegment(&B, &I);
    dobot2.idlePos();
  } else if( index==4){
    dobot3.drawSegment(&J, &D);
    dobot3.idlePos();
  } else if(index==5){
    dobot2.drawSegment(&H, &B);
    dobot2.idlePos();
  } else if(index==6){
    dobot1.drawSegment(&G, &A);
    dobot1.idlePos();
  } else if(index==7) {
    dobot3.drawSegment(&D, &F);
    dobot3.idlePos();
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