#include "Dobot.h"
#include "Packet.h"
#include "ProtocolID.h"
#include "Message.h"

#include <stdio.h>
#include <string.h>
#include <math.h>


#define NEUTRAL 255





float degToRad(float deg){
    return deg * M_PI / 180;
}

Dobot::Dobot(DobotNumber number){
    if(number == DOBOT_1){
        _number = number;
        _serial = &Serial1;
        origin.x = 160 - 61;
        origin.y = -105;
        origin.z = -56;
        origin.theta = degToRad(0);
    }
    if(number == DOBOT_2){
        _number = number;
        _serial = &Serial2; 
        origin.x = 270 - 61;
        origin.y = 177;
        origin.z = -56.5;
        origin.theta = degToRad(-120);
    }
    if(number == DOBOT_3){
        _number = number;
        _serial = &Serial3;
        origin.x = 456 - 61;
        origin.y = -76;
        origin.z = -53;
        origin.theta = degToRad(120);
    }
    idPrecedent = 0;
    param246Precedent = 0;
    actualProgIndex = 0;
    nb_new_instruction = 0;
}

void Dobot::ProtocolInit(){
    // Init Serial protocol
    RingBufferInit(&_gSerialProtocolHandler.txRawByteQueue, gSerialTXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&_gSerialProtocolHandler.rxRawByteQueue, gSerialRXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&_gSerialProtocolHandler.txPacketQueue, gSerialTXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
    RingBufferInit(&_gSerialProtocolHandler.rxPacketQueue, gSerialRXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
}

/*void Dobot::ProtocolProcess(){
    return;
}
*/

void Dobot::ProtocolProcess(){
    Message message;


    MessageProcess(&_gSerialProtocolHandler);

    for(int i=0; i<nb_new_instruction; i++){
        instructionsQueue.push_back(queuedCmdIndex+nb_new_instruction);
    }
    nb_new_instruction=0;

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
                printf("Dobot %d Rx : [id : %d, param : ", _number+1, message.id);
                for(int i=0; i<message.paramsLen; i++)
                {
                    printf("%02x ", message.params[i]);
                    //if(i>20) printf("message param len : %d + message.id : %d\n", message.paramsLen, message.id);
                }
                Serial.println(F("]"));
            }
            if(message.id == 245){
                //clear queue
                instructionsQueue.clear();
            }

            if(message.id == 246) {
                queuedCmdIndex = param;

                //for(int i=0; i<message.paramsLen; i++)
                //{
                //    printf("%02x ", queuedCmdIndex >> 8*i);
                //}
                //printf("\n");

                //a virer apres le debug
                Serial.print(F("Dobot "));
                Serial.print(_number+1);
                Serial.print(F(" instruction queue len : "));
                Serial.println(instructionsQueue.size());
                //printf("Dobot %d  instruction queue len : %d\n", _number+1, instructionsQueue.size());

                int index=-1;
                for(int i=0; i<instructionsQueue.size(); i++){
                    if(instructionsQueue[i] == param) index = i;
                }
                for (int i = 0; i <= index; i++)
                {
                    //printf("  instruction queue len : %d\n", instructionsQueue.size());
                    //printf("*Instruction %08x termine\n",instructionsQueue[0]);
                    Serial.print(F("*Instruction "));
                    printf("%08x", instructionsQueue[0]);
                    Serial.println(F(" termine"));
                    instructionsQueue.erase(instructionsQueue.begin());
                    if(available()) {
                        Serial.print(F("=> DOBOT "));
                        Serial.print(_number+1);
                        Serial.println(F(" PRET"));
                        //printf("=> DOBOT %d PRET\n",_number+1);
                    }
                }
                
                
            } else{
                //instructionsQueue.push_back(param);
            }

            param246Precedent = param;
            #endif
        }
    }
}



void Dobot::setUp(JOGJointParams *gJOGJointParams, JOGCommonParams *gJOGCommonParams, JOGCoordinateParams *gJOGCoordinateParams){
    SetJOGJointParams(&_gSerialProtocolHandler, gJOGJointParams, true);
    SetJOGCommonParams(&_gSerialProtocolHandler, gJOGCommonParams, true);
    SetJOGCoordinateParams(&_gSerialProtocolHandler, gJOGCoordinateParams, true);

    gJOGCmd.cmd = AP_DOWN;
    gJOGCmd.isJoint = COORDINATE_MODEL;

    gPTPCmd.ptpMode = MOVL_XYZ;
    gPTPCmd.x = 200;
    gPTPCmd.y = 0;
    gPTPCmd.z = 0;
    gPTPCmd.r = 0;

    gCPCmd.cpMode = 0;
    gCPCmd.x = 0;
    gCPCmd.y = 0;
    gCPCmd.z = 0;

}


void Dobot::serialRead(void){
    while (_serial->available()) {
        uint8_t data = _serial->read();
        if (RingBufferIsFull(&_gSerialProtocolHandler.rxRawByteQueue) == false) {
            RingBufferEnqueue(&_gSerialProtocolHandler.rxRawByteQueue, &data);
        }
    }
}




/*********************************************************************************************************
** Function name:       SetJOGCmd
** Descriptions:        Execute the jog function
** Input parameters:    jogCmd,isQueued
** Returned value:      true
*********************************************************************************************************/
void Dobot::SetJOGCmd(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCmd);
    memcpy(tempMessage.params, (uint8_t *)&gJOGCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}


/*********************************************************************************************************
** Function name:       SetPTPCmd
** Descriptions:        Execute the position function
** Input parameters:    ptpCmd,isQueued
** Returned value:      true
*********************************************************************************************************/
void Dobot::SetPTPCmd(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCmd);
    memcpy(tempMessage.params, (uint8_t *)&gPTPCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    nb_new_instruction++;

}


void Dobot::SetHOMECmd(bool isQueued)
{
    Message tempMessage;
    HOMECmd gHomeCmd;
    gHomeCmd.reserved=0;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolHOMECmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(gHomeCmd);
    memcpy(tempMessage.params, (uint8_t *)&gHomeCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}








void Dobot::ClearDobotBuffer(bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdClear;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    instructionsQueue.clear();
    if(available()) {
        Serial.print(F("=> DOBOT "));
        Serial.print(_number+1);
        Serial.println(F(" PRET"));
    }

}




void Dobot::GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdCurrentIndex;
    tempMessage.rw = false;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(queuedCmdIndex);
    memcpy(tempMessage.params, (uint8_t *)queuedCmdIndex, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}



void Dobot::ClearAllAlarms(){
  Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolClearAlarms;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}

void Dobot::StartQueueExec(){
   Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdStartExec;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}

void Dobot::StopQueueExec(){
   Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdStopExec;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

}


bool Dobot::available(){
    if(instructionsQueue.size()==0) return true;
    else return false;
}

void Dobot::firstMove(){
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

}





void Dobot::SetCPCmd(){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolCPCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = 1;
    tempMessage.paramsLen = sizeof(CPCmd);
    memcpy(tempMessage.params, (uint8_t *)&gCPCmd, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);



}


void Dobot::G0Command(float x, float y, float z, bool jump){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    if(jump)
        gPTPCmd.ptpMode = JUMP_XYZ;
    else
        gPTPCmd.ptpMode = MOVJ_XYZ;
    SetPTPCmd(1);

}
void Dobot::G0Command(Point3D *point, bool jump){
    float x = point->x;
    float y = point->y;
    float z = point->z;

    transformFcoordsToDobotCoords(&x,&y,&z);

    G0Command(x,y ,z , jump);
}

void Dobot::G1Command(float x, float y, float z){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    //printf("x: %f  y : %f  z: %f",x,y,z);
    gPTPCmd.ptpMode = MOVL_XYZ;
    SetPTPCmd(1);
}
void Dobot::G1Command(Point3D *point){
    float x = point->x;
    float y = point->y;
    float z = point->z;

    transformFcoordsToDobotCoords(&x,&y,&z);

    G1Command(x,y,z);
}

int Dobot::nextGCodeInstruction(){
    //temporaire
    if(actualProgIndex==0){
        actualProgIndex++;
        G0Command(100,100,100, false);
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

void Dobot::drawSegment(Point3D *Start, Point3D *End){
    G0Command(Start, true);
    G1Command(End);
}




void Dobot::idlePos(){
    G0Command(75, 140, 35, false);
}

void Dobot::transformFcoordsToDobotCoords(float *x, float *y, float *z){
    float new_x = cos(origin.theta) * (*x) - sin(origin.theta) * (*y) + origin.x;
    float new_y = sin(origin.theta) * (*x) + cos(origin.theta) * (*y) + origin.y;
    float new_z = 1* (*z) + origin.z;

    *x = new_x;
    *y = new_y;
    *z = new_z;
}

void Dobot::danse() {
    G0Command(160, 0, 128, false);
    G0Command(140, 0, 172, false);
    G0Command(140, 0, 100, false);
    G0Command(191, 134, 77, false);
    ProtocolProcess();
    G0Command(66, 223, 69, false);
    G0Command(26.5, 100, 26.7, false);
    G0Command(150, 0, 145, false);
    G0Command(190, -160, 94, false);
    ProtocolProcess();
    G0Command(188, -97, -8, false);
    idlePos();
}

/*
void getPose(Pose *PoseParam){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolGetPose;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = sizeof(PoseParam);
    memcpy(tempMessage.params, (uint8_t *)PoseParam, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);
}
*/


void Dobot::goToPreviousPos(){
    G0Command(posPrecedente.x, posPrecedente.y, posPrecedente.z, true);
}

void Dobot::storePreviousPos(void){
    //a implementer 
}