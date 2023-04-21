#include "Dobot.h"
#include "Packet.h"
#include "ProtocolID.h"
#include "Message.h"

#include <stdio.h>
#include <string.h>
#include <math.h>


#define NB_BLOCKS_MAX 3

#define ERR_OUT_OF_BOUND 2
#define ERR_TOO_DEEP 3


#define DEBUG_TEST 0


float degToRad(float deg){
    return deg * M_PI / 180;
}

Dobot::Dobot(DobotNumber number){
    if(number == DOBOT_1){
        _number = number;
        _serial = &Serial1;
        origin.x = 160 - 61;
        origin.y = -105;
        #if DEBUG_TEST
        origin.z = -36;
        #else
        origin.z = -56;
        #endif
        origin.theta = degToRad(0);
    }
    if(number == DOBOT_2){
        _number = number;
        _serial = &Serial2; 
        origin.x = 270 - 61;
        origin.y = 177;
        #if DEBUG_TEST
        origin.z = -36.5;
        #else
        origin.z = -56.5;
        #endif
        origin.theta = degToRad(-120);
    }
    if(number == DOBOT_3){
        _number = number;
        _serial = &Serial3;
        origin.x = 456 - 61;
        origin.y = -76;
        #if DEBUG_TEST
        origin.z = -33;
        #else
        origin.z = -53;
        #endif
        origin.theta = degToRad(120);
    }
    idPrecedent = 0;
    param246Precedent = 0;
    actualProgIndex = 0;
    nb_new_instruction = 0;
    posPrecedente.x = 1000;
    posPrecedente.x = 1000;
    posPrecedente.x = 60;

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
            if(message.id==0) return; 
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
                }
                Serial.println(F("]"));
            }
            if(message.id == 245){
                //clear queue
                for(size_t i =0;i<instructionsQueue.size();i++){
                    instructionsQueue.pop_back();
                }
            }

            if(message.id == 246) {
                queuedCmdIndex = param;

                
                int index=-1;
                for(size_t i=0; i<instructionsQueue.size(); i++){
                    if(instructionsQueue[i] == param) index = i;
                }
                for (int i = 0; i <= index; i++)
                {
                    Serial.print(F("*Instruction "));
                    printf("%08x", instructionsQueue[0]);
                    Serial.println(F(" termine"));
                    instructionsQueue.erase(instructionsQueue.begin());
                    if(available()) {
                        Serial.print(F("=> DOBOT "));
                        Serial.print(_number+1);
                        Serial.println(F(" PRET"));
                    }
                }
                
                
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
    //facteurCorrectif(&gPTPCmd.x , &gPTPCmd.y);
    CorrectY(&gPTPCmd.y);

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

void Dobot::ForceStopQueueExec(){
   Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdForceStopExec;
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


uint8_t Dobot::G0Command(float x, float y, float z, bool jump){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    if(jump)
        gPTPCmd.ptpMode = JUMP_XYZ;
    else
        gPTPCmd.ptpMode = MOVJ_XYZ;
        

    uint8_t accessible = isAccessible(x ,y, z);
    if(accessible>0){
        return accessible;
    }

    SetPTPCmd(1);

    posPrecedente.x = x;
    posPrecedente.y = y;
    posPrecedente.z = z;

    return 0;


}
uint8_t Dobot::G0Command(Point3D *point, bool jump){
    float x = point->x;
    float y = point->y;
    float z = point->z;

    transformFcoordsToDobotCoords(&x,&y,&z);

    return G0Command(x,y ,z , jump);
}

uint8_t Dobot::G1Command(float x, float y, float z){
    gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    //printf("x: %f  y : %f  z: %f",x,y,z);
    gPTPCmd.ptpMode = MOVL_XYZ;

    #if 1
        Serial.print("X :");
        Serial.print(x);
        Serial.print(" Y :");
        Serial.print(y);
        Serial.print(" Z :");
        Serial.println(z);
    #endif

    uint8_t accessible = isAccessible(x ,y, z);
    if(accessible>0){
        return accessible;
    }


    SetPTPCmd(1);

    posPrecedente.x = x;
    posPrecedente.y = y;
    posPrecedente.z = z;

    return 0;
}
uint8_t Dobot::G1Command(Point3D *point){
    float x = point->x;
    float y = point->y;
    float z = point->z;

    transformFcoordsToDobotCoords(&x,&y,&z);

    return G1Command(x,y,z);
}

uint8_t Dobot::G3Command(Point3D *point, Point3D *offset_centre){
    float x = point->x;
    float y = point->y;
    float z = point->z;

    transformFcoordsToDobotCoords(&x,&y,&z);
    
    return G3Command(x, y, z, offset_centre->x, offset_centre->y, offset_centre->z);
}


uint8_t Dobot::G3Command(float x, float y, float z, float i, float j, float k){
    ARCCmd arc;
    arc.cirPoint.x = x;
    arc.cirPoint.x = y;
    arc.cirPoint.x = z;
    arc.cirPoint.r = 0;

    float distAO = sqrt(i*i+j*j+k*k);
    float distOM = sqrt(pow((-posPrecedente.x+x)/2-i, 2) + pow((-posPrecedente.y+y)/2-j, 2) + pow((-posPrecedente.z+z)/2-k, 2));
    float l = distAO / distOM;

    arc.toPoint.x = l * ((-posPrecedente.x+x)/2-i) + (posPrecedente.x + i);
    arc.toPoint.y = l * ((-posPrecedente.y+y)/2-j) + (posPrecedente.y + j);
    arc.toPoint.z = l * ((-posPrecedente.z+z)/2-k) + (posPrecedente.z + k);
    arc.toPoint.r = 0;
#if 0
    Serial.print(F("pos precedente "));
    Serial.print(F(" X "));
    Serial.print(posPrecedente.x);
    Serial.print(F(" Y "));
    Serial.print(posPrecedente.y);
    Serial.print(F(" Z "));
    Serial.println(posPrecedente.z);

    Serial.print(F("to point "));
    Serial.print(F(" X "));
    Serial.print(x);
    Serial.print(F(" Y "));
    Serial.print(y);
    Serial.print(F(" Z "));
    Serial.println(z);

    Serial.print(F("circ point "));
    Serial.print(F(" X "));
    Serial.print(arc.cirPoint.x);
    Serial.print(F(" Y "));
    Serial.print(arc.cirPoint.y);
    Serial.print(F(" Z "));
    Serial.println(arc.cirPoint.z);
#endif
    SetARCCmd(&_gSerialProtocolHandler, &arc, true);
}

uint8_t Dobot::isAccessible(float x, float y, float z){
    Serial.print("X : ");
    Serial.print(x);
    Serial.print("Y : ");
    Serial.println(y);
    if(sqrt(x*x + y*y) > 270){ //on peut surement avoir une valeur plus precise
        return ERR_OUT_OF_BOUND;
    }
    if(z < origin.z){
        return ERR_TOO_DEEP;
    }
    return 0;

}

uint8_t Dobot::nextGCodeInstruction(){
    
    if(actualProgIndex<prog.num_blocks()){
        uint8_t err = GCodeInterpretation();
        actualProgIndex++;
        return err;
    } else {
        //programme terminé
        return 1;
    }
    
}

uint8_t Dobot::GCodeInterpretation(){
    float x=1000;
    float y=1000;
    float z=1000;
    float i=0;
    float j=0;
    float k=0;


    gcode::block b = prog.get_block(actualProgIndex);
    switch (b.get_add(0).letter)
    {
    case 'G':
        switch ((int) b.get_add(0).val)
        {
        case 0:
            for(char i = 1;i<b.size();i++){
                if(b.get_add(i).letter == 'X'){
                    x = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Y'){
                    y = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Z'){
                    z = b.get_add(i).val;
                }
            }
            //si inchangé (ex : G00 X164.687046 Y-43.752380 ;; z est inchangé)
            if(x >= 950) {
                x = posPrecedente.x;
                Serial.println(F("pas de X dans ce block"));
            }
            if(y >= 950){
                y = posPrecedente.y;
                Serial.println(F("pas de Y dans ce block"));
            }
            if(z >= 950){
                z = posPrecedente.z;
                Serial.println(F("pas de Z dans ce block"));
            }

            
            #if 1
                Serial.println(F("avant matrice transfo :"));
                Serial.print("X :");
                Serial.print(x);
                Serial.print(" Y :");
                Serial.print(y);
                Serial.print(" Z :");
                Serial.println(z);
            #endif

            transformFcoordsToDobotCoords(&x, &y, &z);

            #if 1
            Serial.println(F("apres matrice transfo :"));
                Serial.print("X :");
                Serial.print(x);
                Serial.print(" Y :");
                Serial.print(y);
                Serial.print(" Z :");
                Serial.println(z);
            #endif

            return G0Command(x, y, z, true);

            break;
        case 1:
            for(char i = 1;i<b.size();i++){
                if(b.get_add(i).letter == 'X'){
                    x = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Y'){
                    y = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Z'){
                    z = b.get_add(i).val;
                }
            }
            if(x == 1000) x = posPrecedente.x;
            if(y == 1000) x = posPrecedente.y;
            if(z == 1000) x = posPrecedente.z;

            transformFcoordsToDobotCoords(&x, &y, &z);


            return G1Command(x, y, z);
            break;
        case 2: //pas fonctionnel
        case 3:
            for(char i = 1;i<b.size();i++){
                if(b.get_add(i).letter == 'X'){
                    x = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Y'){
                    y = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'Z'){
                    z = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'I'){
                    i = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'J'){
                    j = b.get_add(i).val;
                }
                if(b.get_add(i).letter == 'K'){
                    k = b.get_add(i).val;
                }
            }
            if(x == 1000) x = posPrecedente.x;
            if(y == 1000) x = posPrecedente.y;
            if(z == 1000) x = posPrecedente.z;

            transformFcoordsToDobotCoords(&x, &y, &z);

            return G3Command(x ,y, z, i, j, k);
        
        default:
            break;
        }
        break;
    
    default:
        //pas implementé pour le moment
        break;
    }
    return 0;
}

void Dobot::updateProg(const char * program_text, uint16_t *index_program_text){
    //verifier qu'il reste des carateres a parser
    Serial.print(F("Valeur de actualprogindex :"));
    Serial.println(actualProgIndex);
    if(*index_program_text >= strlen_P(program_text)) return;
    while (actualProgIndex > 0)
    {
        actualProgIndex--;
        prog.removeFirstBlock();
    }
    //verifier que le programme a moins de NB_BLOCKS_MAX
    if(prog.num_blocks() >= NB_BLOCKS_MAX) return;
    
    gcode::parseNextN(&prog, program_text, index_program_text, NB_BLOCKS_MAX - prog.num_blocks());
    Serial.println(F("Nouveau bloc parse"));
    
}

void Dobot::drawSegment(Point3D *Start, Point3D *End){
    G0Command(Start, true);
    G1Command(End);
}



void Dobot::idlePos(){
    gPTPCmd.x = 75;
    gPTPCmd.y = 140;
    gPTPCmd.z = 35;
    gPTPCmd.ptpMode = MOVJ_XYZ;
    SetPTPCmd(1);
}

void Dobot::idleSafe(){
    gPTPCmd.x = 70;
    gPTPCmd.y = 0;
    gPTPCmd.z = 0;
    gPTPCmd.ptpMode = MOVJ_XYZ;
    SetPTPCmd(1);
    idlePos();
}

void Dobot::CorrectY(float *y){
    *y = *y * 0.886567;
}

void Dobot::transformFcoordsToDobotCoords(float *x, float *y, float *z){
    float new_x = cos(origin.theta) * (*x) - sin(origin.theta) * (*y) + origin.x;
    float new_y = sin(origin.theta) * (*x) + cos(origin.theta) * (*y) + origin.y;
    float new_z = 1* (*z) + origin.z;

    *x = new_x;
    *y = new_y;
    *z = new_z;
}

void Dobot::facteurCorrectif(float *x, float *y){
    //non fonctionnel
    Serial.print(F("ancieenne valeurs : x: "));
    Serial.print(*x);
    Serial.print(F(" y: "));
    Serial.println(*y);
    
    float new_x = 0;
    float new_y = 0;
    if(_number == 0){
        float a_x = *x * 0.0009 + 1.0014;
        float b_x = *x * 0.0001 - 0.1267;

        float a_y = *y * -0.0009 + 1.4419;
        float b_y = *y * -0.0009 - 0.0599;

        new_x = (*x-b_y)/a_y;
        new_y = (*y-b_x)/a_x;
    }

    if(_number == 1){
        float a_x = *x * 0.0008 + 0.9907;
        float b_x = *x * -0.0013 - 0.0933;

        float a_y = *y * -0.0009 + 1.6117;
        float b_y = *y * 0.0012 + -0.3111;

        new_x = (*x-b_y)/a_y;
        new_y = (*y-b_x)/a_x;
    }

    if(_number == 2){
        float a_x = *x * 0.0018 + 0.9214;
        float b_x = *x * -0.0033 + 0.2333;

        float a_y = *y * -0.0009 + 1.4434;
        float b_y = *y * -0.0001 - 0.0978;

        new_x = (*x-b_y)/a_y;
        new_y = (*y-b_x)/a_x;
    }
    *x = new_x;
    *y = new_y;
    Serial.print(F("nouvelles valeurs : x: "));
    Serial.print(*x);
    Serial.print(F(" y: "));
    Serial.println(*y);
}

void Dobot::danse() {

    G0Command(164, 107, 97, false);
    G0Command(158, -52, 154, false);
    G0Command(142, -197, 16, false);
    G0Command(14, -119, 61, false);
    ProtocolProcess();
    G0Command(150, -157, 96, false);
    G0Command(141, 0, 78, false);
    G0Command(182, 148, 118, false);
    idlePos();
    ProtocolProcess();

}



uint8_t Dobot::goToPreviousPos(){
    //si pas de pos precedente
    if(posPrecedente.x >= 950 || posPrecedente.y >= 950 || posPrecedente.z >= 950)
        return 0;

    float x = posPrecedente.x;
    float y = posPrecedente.y;
    float z = posPrecedente.z;

    transformFcoordsToDobotCoords(&x ,&y, &z);

    return G0Command(x, y ,z , true);
}
