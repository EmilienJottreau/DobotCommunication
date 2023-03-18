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
#define ENSEMBLE_PIN 40
#define SIMPLE_PIN1 48
#define SIMPLE_PIN2 44
#define HOME_PIN 52
#define START_STOP_PIN 36
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
unsigned long previousHomeActivation=0;
unsigned long previousStartStopActivation=0;

const unsigned int securityTime=1000;


bool digitalReadMaison(unsigned char pin);
void pinSwitchPullUp(unsigned char pin);
void ActionSimple();

Dobot dobot1(DOBOT_1);
Dobot dobot2(DOBOT_2);

gpr::gcode_program p;
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



  ////PARSE G CODE PROGRAMME

  p = gpr::parse_gcode(hardcoded_prog);
  printf("programme gcode parsé\n");
  Serial.println(atof("9876.98765"), 5);
  printf("%f\n", atof("9876.98765"));
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
    //dobot2.firstMove();
    test = 1;
    printf("activation boutton 3\n");
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



  if(digitalReadMaison(ENABLEJOYSTICK)){
    int posX = analogRead(JOYSTICKX);
    int posY = analogRead(JOYSTICKY);
    printf("joystick mode\n");
    dobot1.joyStickMove(posX,posY);
  }

  

  //end of loop
  digitalWrite(STATUSLED,stateStartStop);
  //ask dobot for their command index
  float x = 0;
  float y = 0;
  float z = 0;
  int j = 0;
  if(test==1){
  Dobot *chosenDobot = &dobot1;
  
  for (int i = 0; i < p.num_blocks(); i++) {
        gpr::block b = p.get_block(i);
        if (b.get_chunk(0).tp() != gpr::CHUNK_TYPE_WORD_ADDRESS) {
            //commentaire ou autre
            continue;
        }
        char letter = b.get_chunk(0).get_word();

        switch (letter)
        {
        case 'G': //changed to see debug
            switch (b.get_chunk(0).get_address().int_value())
            {
                //implementer tout les G
                //  G00	Déplacement rapide               (MOVJ)
                //  G01	Interpolation linéaire           (MOVL)
                //  G02	Interpolation circulaire (sens horaire, anti-trigo) (ARC à implementer id 100 communication protocol)
                //  G03	Interpolation circulaire (sens anti-horaire, trigo) (ARC à implementer)
                    
            case 0:
                for (j = 1; j < b.size(); j++) {
                    switch (b.get_chunk(j).get_word()) {
                    case 'X':
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            x = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            x = b.get_chunk(j).get_address().double_value();
                        }
                        break;
                    case 'Y':
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            y = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            y = b.get_chunk(j).get_address().double_value();
                        }
                        break;
                    case 'Z':
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            z = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            z = b.get_chunk(j).get_address().double_value();
                        }
                        break;
                    case 'F':
                        //commande vitesse
                        break;

                    }
                    //appel de la commande G0 avec nos fonctions speciales
                    //debug
                    //cout << "Commande G0 X " << x << " Y " << y << " Z " << z << " Somme : " << x+y+z << " Produit : " << x * y  << endl;
                    chosenDobot->G0Command((float)x,(float)y,(float)z);
                }
                break;
            case 1:
                for (j = 1; j < b.size(); j++) {
                    switch (b.get_chunk(j).get_word()) {
                    case 'X':
                    printf("type %d\n",b.get_chunk(j).get_address().tp());
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            x = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            x = b.get_chunk(j).get_address().double_value();
                            printf("x en d %g\n",b.get_chunk(j).get_address().double_value());
                        }
                        Serial.print("x value ");
                        Serial.println(x);
                        break;
                    case 'Y':
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            y = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            y = b.get_chunk(j).get_address().double_value();
                        }
                        break;
                    case 'Z':
                        if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                            z = b.get_chunk(j).get_address().int_value();
                        }
                        else {
                            z = b.get_chunk(j).get_address().double_value();
                        }
                        break;
                    case 'F':
                        //commande vitesse
                        break;

                    }
                }
                //cout << "Commande G1 X " << x << " Y " << y << " Z " << z << " Somme : " << x+y+z << " Produit : " << x * y  << endl;
                //printf("dans le main 7 x: %f\n",x);
                chosenDobot->G1Command(x,y,z);
                printf("gcode action i:%d, j:%d\n",i,j);
                break;
            case 2:
                break;
            case 3:
                break;

            default:
                break;
                
            }
            break;
        case 'F':
            break;
        case 'M':
            break;
        default:
            break;
        }
        //dobot1.ProtocolProcess();
    }
  }
  test=0;
  dobot1.GetQueuedCmdCurrentIndex(0,&dobot1.queuedCmdIndex);
  dobot2.GetQueuedCmdCurrentIndex(0,&dobot2.queuedCmdIndex);
  //send message to the bus and process response
  dobot1.ProtocolProcess();
  dobot2.ProtocolProcess();


  char * str = "100\0";

  std::string s2= "100";

/*
  double valeur;
  valeur = strtod(s2.c_str(),(char**)0);

  printf("val de f dans le main %lf, %f, %f\n", valeur, (float)valeur, valeur);
  Serial.println(valeur);

  Serial.println(valeur *5.2294);
*/
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


/* code joystick loop

*/