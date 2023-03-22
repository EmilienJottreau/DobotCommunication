#include "Dobot.h"
#include "Packet.h"
#include "ProtocolID.h"
#include "Message.h"

#include <stdio.h>
#include <string.h>


#define NEUTRAL 255

Dobot::Dobot(DobotNumber number){
    if(number == DOBOT_1){
        _number = number;
        _serial = &Serial1;
    }
    if(number == DOBOT_2){
        _number = number;
        _serial = &Serial2;
    }
    if(number == DOBOT_3){
        _number = number;
        _serial = &Serial3;
    }
    idPrecedent = 0;
    param246Precedent = 0;
    joystickXState = 0;
    joystickYState = 0;
    actualProgIndex = 0;
}

void Dobot::ProtocolInit(){
        // Init Serial protocol
    RingBufferInit(&_gSerialProtocolHandler.txRawByteQueue, gSerialTXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&_gSerialProtocolHandler.rxRawByteQueue, gSerialRXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&_gSerialProtocolHandler.txPacketQueue, gSerialTXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
    RingBufferInit(&_gSerialProtocolHandler.rxPacketQueue, gSerialRXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
}

void Dobot::ProtocolProcess(){
    Message message;


    MessageProcess(&_gSerialProtocolHandler);

    if (RingBufferGetCount(&_gSerialProtocolHandler.txRawByteQueue)) {
        uint8_t data;
        while (RingBufferIsEmpty(&_gSerialProtocolHandler.txRawByteQueue) == false) {
            RingBufferDequeue(&_gSerialProtocolHandler.txRawByteQueue, &data);
            (*_serial).write(data);
        }
        if(MessageRead(&_gSerialProtocolHandler, &message)==ProtocolNoError){
            #if 1
            if(message.id==0) return; //ca bug si on fait pas return potentielmement probleme reglé / on peut l'enlever
            if(    message.id == 246 
                || message.id == ProtocolJOGCommonParams 
                || message.id == ProtocolJOGCoordinateParams
                || message.id == ProtocolJOGJointParams
                || message.id == ProtocolJOGCmd
                || message.id == ProtocolPTPCmd
                || message.id == ProtocolHOMECmd){
                    param = message.params[7] << 56 | message.params[6] << 48 | message.params[5] << 40 | message.params[4] << 32 | message.params[3] << 24 | message.params[2] << 16 | message.params[1] << 8 | message.params[0];
            }

            if((message.id==246 && param246Precedent != param) || message.id!=246) {
                printf("Dobot %d Rx : [id : %d, param : ", _number, message.id);
                for(int i=0; i<message.paramsLen; i++)
                {
                    printf("%02x ", message.params[i]);
                    if(i>20) printf("message param len : %d + message.id : %d\n", message.paramsLen, message.id);
                }
                printf("]\n");
            }

            if(message.id == 246) {
                int index=-1;
                for(int i=0; i<instructionsQueue.size(); i++){
                    if(instructionsQueue[i] == param) index = i;
                }
                for (int i = 0; i <= index; i++)
                {
                    //printf("  instruction queue len : %d\n", instructionsQueue.size());
                    printf("*Instruction %08x termine\n",instructionsQueue[0]);
                    instructionsQueue.erase(instructionsQueue.begin());
                    if(available()) printf("=> DOBOT %d PRET\n",_number);
                }
                
                
            } else{
                instructionsQueue.push_back(param);
            }

            param246Precedent = param;
            #endif
        }
    }
}



void Dobot::InitRam(){
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

    gJOGCmd.cmd = AP_DOWN;
    //gJOGCmd.isJoint = JOINT_MODEL;
    gJOGCmd.isJoint = COORDINATE_MODEL;



    //Set PTP Model
    gPTPCoordinateParams.xyzVelocity = 100;
    gPTPCoordinateParams.rVelocity = 100;
    gPTPCoordinateParams.xyzAcceleration = 80;
    gPTPCoordinateParams.rAccleration = 80;

    gPTPCommonParams.velocityRatio = 50;
    gPTPCommonParams.accelerationRatio = 50;

    gPTPCmd.ptpMode = MOVL_XYZ;
    gPTPCmd.x = 200;
    gPTPCmd.y = 0;
    gPTPCmd.z = 0;
    gPTPCmd.r = 0;

    homeCmd.reserved = 0;
    


    gCPCmd.cpMode = 0;
    gCPCmd.x = 0;
    gCPCmd.y = 0;
    gCPCmd.z = 0;


}


/*********************************************************************************************************
** Function name:       SetEndEffectorParams
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetEndEffectorParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(EndEffectorParams);
    memcpy(tempMessage.params, (uint8_t *)&gEndEffectorParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorLaser
** Descriptions:        Set the laser output
** Input parameters:    on,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetEndEffectorLaser(bool on, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorLaser;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = on;

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorSuctionCup
** Descriptions:        Set the suctioncup output
** Input parameters:    suck,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetEndEffectorSuctionCup(bool suck, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorSuctionCup;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = suck;
    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorGripper
** Descriptions:        Set the gripper output
** Input parameters:    grip,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetEndEffectorGripper(bool grip, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorGripper;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = grip;
    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGJointParams
** Descriptions:        Sets the joint jog parameter
** Input parameters:    jogJointParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetJOGJointParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGJointParams);
    memcpy(tempMessage.params, (uint8_t *)&gJOGJointParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCoordinateParams
** Descriptions:        Sets the axis jog parameter
** Input parameters:    jogCoordinateParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetJOGCoordinateParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)&gJOGCoordinateParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCommonParams
** Descriptions:        Sets the jog common parameter
** Input parameters:    jogCommonParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetJOGCommonParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCommonParams);
    memcpy(tempMessage.params, (uint8_t *)&gJOGCommonParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCmd
** Descriptions:        Execute the jog function
** Input parameters:    jogCmd,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetJOGCmd(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCmd);
    memcpy(tempMessage.params, (uint8_t *)&gJOGCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJointParams
** Descriptions:        Sets the articulation point parameter
** Input parameters:    ptpJointParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetPTPJointParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJointParams);
    memcpy(tempMessage.params, (uint8_t *)&gPTPJointParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCoordinateParams
** Descriptions:        Sets the coordinate position parameter
** Input parameters:    ptpCoordinateParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetPTPCoordinateParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)&gPTPCoordinateParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJumpParams
** Descriptions:        Set the gate type parameter
** Input parameters:    ptpJumpParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetPTPJumpParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJumpParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJumpParams);
    memcpy(tempMessage.params, (uint8_t *)&gptpJumpParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCommonParams
** Descriptions:        Set point common parameters
** Input parameters:    ptpCommonParams,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetPTPCommonParams(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCommonParams);
    memcpy(tempMessage.params, (uint8_t *)&gPTPCommonParams, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCmd
** Descriptions:        Execute the position function
** Input parameters:    ptpCmd,isQueued
** Returned value:      true
*********************************************************************************************************/
int Dobot::SetPTPCmd(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCmd);
    memcpy(tempMessage.params, (uint8_t *)&gPTPCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}


int Dobot::SetHOMECmd(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolHOMECmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(homeCmd);
    memcpy(tempMessage.params, (uint8_t *)&homeCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}








int Dobot::ClearDobotBuffer(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdClear;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}




int Dobot::GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdCurrentIndex;
    tempMessage.rw = false;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(queuedCmdIndex);
    memcpy(tempMessage.params, (uint8_t *)queuedCmdIndex, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}



int Dobot::ClearAllAlarms(){
  Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolClearAlarms;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

int Dobot::StartQueueExec(){
   Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdStartExec;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

int Dobot::StopQueueExec(){
   Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdStopExec;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}


int Dobot::available(){
    if(instructionsQueue.size()==0) return true;
    else return false;
}

int Dobot::firstMove(){
    gPTPCmd.ptpMode = MOVJ_XYZ;
    gPTPCmd.x = 84;
    gPTPCmd.y = 127;
    gPTPCmd.z = -8;
    SetPTPCmd(1);

    gPTPCmd.x = 158;
    gPTPCmd.y = 100;
    gPTPCmd.z = 38;
    SetPTPCmd(1);

    gPTPCmd.x = 163;
    gPTPCmd.y = -21;
    gPTPCmd.z = 122;
    SetPTPCmd(1);

    gPTPCmd.x = 91;
    gPTPCmd.y = -196;
    gPTPCmd.z = 68;
    SetPTPCmd(1);
    return true;
}


//fonction a refaire, neutral x=494 from 0 to 1023,  neutral y=500, from 0 to 1023
int Dobot::joyStickMove(int posX, int posY){//range analogRead() = 0:1023
    int actualXState;
    int actualYState;
    
    int increment = 3;

    if(posX <= 100){
        gCPCmd.x = increment;
        actualXState = 1;
    }else if(posX >= 950){
        gCPCmd.x = -increment;
        actualXState = -1;
    } else {
        gCPCmd.x = 0;
        actualXState = 0;
    }

    if(posY <= 100){
        gCPCmd.y = increment;
        actualYState = 1;
    } else if(posY >= 950){
        gCPCmd.y = -increment;
        actualYState = -1;
    }
    else {
        gCPCmd.y = 0;
        actualYState = 0;
    }
    //if(actualXState != joystickXState || actualYState != joystickYState)
    SetCPCmd();




    /*
    posX -= 494;
    posY -= 500;
    printf("DEBUG : X=%d, Y=%d\n");
    //X axis
    if(posX > 0){
        printf("X UP ");
        gJOGCmd.cmd = AP_DOWN;
    } else if (posX == 0) {
        printf("X NEUTRAL ");
        gJOGCmd.cmd = IDEL;
    } else {
        printf("X DOWN ");
        gJOGCmd.cmd = AN_DOWN;
    }
    if(posX!=0){
        gJOGJointParams.velocity[0] = 0,1519 * abs(posX) + 24,996;//find regression y = 0,1519x + 24,996
        printf("changed velocity x : %f ", gJOGJointParams.velocity[0]);
    }
    if(posY!=0){
        gJOGJointParams.velocity[1] = 0,15 * abs(posY) + 25,005;//find regression y = 0,15x + 25,005
        printf("changed velocity y : %f ", gJOGJointParams.velocity[0]);
    }
    
    SetJOGCommonParams(1);
    SetJOGCmd(1);
    //Y axis
    if(posY > 0){
        printf("Y UP ");
        gJOGCmd.cmd = BP_DOWN;
    } else if (posY == 0) {
        printf("Y NEUTRAL ");
        gJOGCmd.cmd = IDEL;
    } else {
        printf("Y DOWN ");
        gJOGCmd.cmd = BN_DOWN;
    }
    SetJOGCmd(1);
*/
    return true;
}


int Dobot::SetCPCmd(){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolCPCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = 1;
    tempMessage.paramsLen = sizeof(CPCmd);
    memcpy(tempMessage.params, (uint8_t *)&gCPCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;


}


void Dobot::G0Command(float x, float y, float z){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    gPTPCmd.ptpMode = JUMP_XYZ;
    SetPTPCmd(1);

}
void Dobot::G1Command(float x, float y, float z){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    //printf("x: %f  y : %f  z: %f",x,y,z);
    gPTPCmd.ptpMode = MOVL_XYZ;
    SetPTPCmd(1);
}

int Dobot::nextGCodeInstruction(){
    //temporaire
    if(actualProgIndex==0){
        actualProgIndex++;
        G0Command(100,100,100);
    } else if(actualProgIndex==1) {
        actualProgIndex++;
        G1Command(150,100,150);
    } else if(actualProgIndex==2) {
        actualProgIndex++;
        G1Command(100,150,100);
    } else if(actualProgIndex==3) {
        actualProgIndex++;
        G1Command(200,100,100);
    }
    /*
    if(actualProgIndex<prog.num_blocks()){
        GCodeInterpretation();
        actualProgIndex++;
        return 0;
    } else {
        //programme terminé
        return 1;
    }
    */
}

void Dobot::GCodeInterpretation(){
    int j=0;
    double x=0, y=0, z=0;

    
    gpr::block b = prog.get_block(actualProgIndex);
    if (b.get_chunk(0).tp() != gpr::CHUNK_TYPE_WORD_ADDRESS) {
        //commentaire ou autre
        nextGCodeInstruction();
        return;
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
                this->G0Command(x,y,z);
            }
            break;
        case 1:
            for (j = 1; j < b.size(); j++) {
                switch (b.get_chunk(j).get_word()) {
                case 'X':
                //printf("type %d\n",b.get_chunk(j).get_address().tp());
                    if (b.get_chunk(j).get_address().tp() == gpr::ADDRESS_TYPE_INTEGER) {
                        x = b.get_chunk(j).get_address().int_value();
                    }
                    else {
                        x = b.get_chunk(j).get_address().double_value();
                        printf("x en d %g\n",b.get_chunk(j).get_address().double_value());
                    }
                    //Serial.print("x value ");
                    //Serial.println(x);
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

            this->G1Command(x,y,z);

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
}


void Dobot::getPose(Pose *PoseParam){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolGetPose;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = sizeof(PoseParam);
    memcpy(tempMessage.params, (uint8_t *)PoseParam, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);
}

void Dobot::InitPos(){
   G0Command(initPos.x, initPos.y, initPos.z); 
}

void Dobot::goToPreviousPos(){
    G0Command(pose.x, pose.y, pose.z);
}