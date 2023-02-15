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

//Set Serial TX&RX Buffer Size
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 256

#define DEBUG 1
#define ENSEMBLE_PIN 40
#define SIMPLE_PIN1 48
#define SIMPLE_PIN2 44
#define HOME_PIN 52
#define START_STOP_PIN 36


//#define JOG_STICK
#define JOYSTICKX 0 //care it's analog pin
#define JOYSTICKY 1 //care it's analog pin
#define JOYSTICKBUTTON 27
#define ENABLEJOYSTICK 29

bool joyStickDobot = 0;
unsigned long previousActivationJoyStickButton=0;

bool stateStartStop = 1; //Start=1, Stop=0

/*********************************************************************************************************
** Global parameters
*********************************************************************************************************/
//EndEffectorParams gEndEffectorParams;
//
//JOGJointParams gJOGJointParams;
//JOGCoordinateParams gJOGCoordinateParams;
//JOGCommonParams gJOGCommonParams;
//JOGCmd gJOGCmd;
//
//PTPCoordinateParams gPTPCoordinateParams;
//PTPCommonParams gPTPCommonParams;
//PTPCmd gPTPCmd;
//
//HOMECmd homeCmd;
//
//uint64_t gQueuedCmdIndex;

int count;
unsigned long previousActivation1=0;
unsigned long previousActivation2=0;
unsigned long previousActivation3=0;
unsigned long previousHomeActivation=0;
unsigned long previousStartStopActivation=0;

const unsigned int securityTime=1000;


bool digitalReadMaison(unsigned char pin);
void pinSwitchPullUp(unsigned char pin);
void ActionSimple();

Dobot dobot1(DOBOT_1);
Dobot dobot2(DOBOT_2);


void clearQueue() {
  //printf("==Debut Interuption\n");
  //dobot1.ClearAllAlarms();
  printf("#STOP & CLEAR QUEUE\n");
  dobot1.StopQueueExec(); // ca marche
  dobot1.ClearDobotBuffer(0);
  dobot1.StartQueueExec();
  dobot1.ProtocolProcess();
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
}
/*********************************************************************************************************
** Function name:       Serial_putc
** Descriptions:        Remap Serial to Printf
** Input parametersnone:
** Output parameters:   
** Returned value:      
*********************************************************************************************************/
//TODO trouver l'utilité de cette fonction
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
//TODO trouver l'utilité de cette fonction
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
//deplacée dans dobot.cpp
/*
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
*/

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

  count = 0;
  attachInterrupt(digitalPinToInterrupt(2), clearQueue, RISING);
  dobot1.ProtocolInit();
  dobot1.SetJOGJointParams(true);
  dobot1.SetJOGCommonParams(true);
  dobot1.SetJOGCoordinateParams(true);
  dobot1.ProtocolProcess();
  printf("FIN SETUP DOBOT 1! \n");
  dobot2.ProtocolInit();
  dobot2.SetJOGJointParams(true);
  dobot2.SetJOGCommonParams(true);
  dobot2.SetJOGCoordinateParams(true);
  dobot2.ProtocolProcess();
  printf("FIN SETUP DOBOT 2! \n");
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
    previousHomeActivation = millis();
  }

  if(digitalReadMaison(START_STOP_PIN) && millis() - previousStartStopActivation > securityTime){
    if(stateStartStop==1){
      printf("@STOP Queue\n");
      dobot1.StopQueueExec();
    }
    else{
      printf("@START Queue\n");
      dobot1.StartQueueExec();
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
  }

  if(digitalReadMaison(ENSEMBLE_PIN) && millis() - previousActivation3 > securityTime){
    previousActivation3 = millis();
    dobot1.firstMove();
    dobot2.firstMove();
  }


  //change dobot beeing controlled by joystick
  if(digitalRead(JOYSTICKBUTTON) && millis() - previousActivationJoyStickButton > 200){
    joyStickDobot ^= 1;  
    previousActivationJoyStickButton = millis();
  } 
/*
  if(digitalRead(ENABLEJOYSTICK)){
    int posX = analogRead(JOYSTICKX);
    int posY = analogRead(JOYSTICKY);
    if(joyStickDobot){
      dobot1.joyStickMove(posX,posY);
    }
    else{
      dobot2.joyStickMove(posX,posY);
    }
  }
*/
  //end of loop

  //ask dobot for their command index
  dobot1.GetQueuedCmdCurrentIndex(0,&dobot1.queuedCmdIndex);
  dobot2.GetQueuedCmdCurrentIndex(0,&dobot2.queuedCmdIndex);
  //send message to the bus and process response
  dobot1.ProtocolProcess();
  dobot2.ProtocolProcess();

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
