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

//Set Serial TX&RX Buffer Size
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 256

#define DEBUG 1
#define DEBUG_PIN 35
#define RESET_PIN 39
#define SIMPLE_PIN 24
//#define JOG_STICK
/*********************************************************************************************************
** Global parameters
*********************************************************************************************************/
EndEffectorParams gEndEffectorParams;

JOGJointParams gJOGJointParams;
JOGCoordinateParams gJOGCoordinateParams;
JOGCommonParams gJOGCommonParams;
JOGCmd gJOGCmd;

PTPCoordinateParams gPTPCoordinateParams;
PTPCommonParams gPTPCommonParams;
PTPCmd gPTPCmd;

HOMECmd homeCmd;

uint64_t gQueuedCmdIndex;

int count;
unsigned long previousActivation=0;


bool digitalReadMaison(unsigned char pin);
void pinSwitchPullUp(unsigned char pin);
void ActionSimple();

Dobot dobot1(DOBOT_2);

void clearQueue() {
  printf("==Debut Interuption\n");
  //dobot1.ClearAllAlarms();
  //dobot1.SetQueuedCmdStopExec(&gQueuedCmdIndex);
  //dobot1.ClearDobotBuffer(0, &gQueuedCmdIndex);
  dobot1.SetHOMECmd(1, &gQueuedCmdIndex);
  dobot1.StartQueueExec();
  dobot1.ProtocolProcess();
  printf("==Fin Interuption (Clear Alarm 21, Stop command exec 241, clear dobot buffer 245, home 31)\n");
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
  while (Serial2.available()) {
    uint8_t data = Serial2.read();
    if (RingBufferIsFull(&dobot1._gSerialProtocolHandler.rxRawByteQueue) == false) {
      RingBufferEnqueue(&dobot1._gSerialProtocolHandler.rxRawByteQueue, &data);
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
** Function name:       InitRAM
** Descriptions:        Initializes a global variable
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void InitRAM(void) {
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

  gJOGCommonParams.velocityRatio = 50;
  gJOGCommonParams.accelerationRatio = 50;

  gJOGCmd.cmd = AP_DOWN;
  gJOGCmd.isJoint = JOINT_MODEL;



  //Set PTP Model
  gPTPCoordinateParams.xyzVelocity = 100;
  gPTPCoordinateParams.rVelocity = 100;
  gPTPCoordinateParams.xyzAcceleration = 80;
  gPTPCoordinateParams.rAcceleration = 80;

  gPTPCommonParams.velocityRatio = 50;
  gPTPCommonParams.accelerationRatio = 50;

  gPTPCmd.ptpMode = MOVL_XYZ;
  gPTPCmd.x = 200;
  gPTPCmd.y = 0;
  gPTPCmd.z = 0;
  gPTPCmd.r = 0;

  homeCmd.reserved = 0;
  
  gQueuedCmdIndex = 0;
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
  pinSwitchPullUp(DEBUG_PIN);
  pinSwitchPullUp(RESET_PIN);
  pinSwitchPullUp(SIMPLE_PIN);
  count = 0;
  attachInterrupt(digitalPinToInterrupt(2), clearQueue, RISING);
  dobot1.ProtocolInit();
  dobot1.SetJOGJointParams(true, &gQueuedCmdIndex);
  dobot1.SetJOGCommonParams(true, &gQueuedCmdIndex);
  dobot1.SetJOGCoordinateParams(true, &gQueuedCmdIndex);
  dobot1.ProtocolProcess();
  printf("Fin SETUP ! \n");
}
/*********************************************************************************************************
** Function name:       loop
** Descriptions:        Program entry
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/

void loop() {
  //InitRAM();

/*
  SetJOGJointParams(&gJOGJointParams, true, &gQueuedCmdIndex);

  SetJOGCoordinateParams(&gJOGCoordinateParams, true, &gQueuedCmdIndex);

  SetJOGCommonParams(&gJOGCommonParams, true, &gQueuedCmdIndex);
*/
  //printf("\r\n======Enter demo application======\r\n");

  //SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);


  if (digitalReadMaison(DEBUG_PIN) == HIGH && 0) {
    printf("===PIN ACTIVATED, %d, millis : %d ===\n", count, millis());
    if (DEBUG) {
      /*if(count & 0x01){
        gPTPCmd.x = 100;
        SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);
      } else {
      gPTPCmd.y = 100;
      SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);

      }*/
      static uint32_t timer = millis();
      if (millis() - timer > 1000) {
      count++;
        timer = millis();

        switch (count) {
          case 1:
          printf("avance\n");
            dobot1.gJOGCmd.cmd = AP_DOWN;
            dobot1.gJOGCmd.isJoint = COORDINATE_MODEL;
            dobot1.SetJOGCmd(true, &gQueuedCmdIndex);
            break;
          case 2:
            dobot1.gJOGCmd.cmd = IDEL;
            dobot1.gJOGCmd.isJoint = COORDINATE_MODEL;
            dobot1.SetJOGCmd(true, &gQueuedCmdIndex);
            break;
          case 3:
          printf("recule\n");
            dobot1.gJOGCmd.cmd = AN_DOWN;
            dobot1.gJOGCmd.isJoint = COORDINATE_MODEL;
            dobot1.SetJOGCmd(true, &gQueuedCmdIndex);
            break;
          case 4:
            dobot1.gJOGCmd.cmd = IDEL;
            dobot1.gJOGCmd.isJoint = COORDINATE_MODEL;
            dobot1.SetJOGCmd(true, &gQueuedCmdIndex);
            break;
          default:
            count = 0;
            break;
        }
      }
    }
  }
  //dobot1.GetQueuedCmdCurrentIndex(1,&gQueuedCmdIndex);
  if(digitalReadMaison(RESET_PIN)) dobot1.ClearAllAlarms(); //marche pas

  if(digitalReadMaison(SIMPLE_PIN) && millis() - previousActivation > 2000){
    previousActivation = millis();
    ActionSimple();
  }
  dobot1.GetQueuedCmdCurrentIndex(0,&gQueuedCmdIndex);

  Serialread();
  //printf("rien\n");
  dobot1.ProtocolProcess();
  delay(100);
  
}


void ActionSimple(){
  dobot1.gPTPCmd.ptpMode = MOVJ_XYZ;
  dobot1.gPTPCmd.x = 84;
  dobot1.gPTPCmd.y = 127;
  dobot1.gPTPCmd.z = -8;
  dobot1.SetPTPCmd(1,&gQueuedCmdIndex);

  dobot1.gPTPCmd.x = 158;
  dobot1.gPTPCmd.y = 100;
  dobot1.gPTPCmd.z = 38;
  dobot1.SetPTPCmd(1,&gQueuedCmdIndex);

  dobot1.gPTPCmd.x = 163;
  dobot1.gPTPCmd.y = -21;
  dobot1.gPTPCmd.z = 122;
  dobot1.SetPTPCmd(1,&gQueuedCmdIndex);

  dobot1.gPTPCmd.x = 91;
  dobot1.gPTPCmd.y = -196;
  dobot1.gPTPCmd.z = 68;
  dobot1.SetPTPCmd(1,&gQueuedCmdIndex);
}







//TODO : DO NOT MODIFY THIS CODE
bool digitalReadMaison(unsigned char pin) {
  return !digitalRead(pin);
}

void pinSwitchPullUp(unsigned char pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}
