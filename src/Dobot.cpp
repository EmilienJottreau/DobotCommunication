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
    //TODO : remplacer les "#define GetPose", "#define GetHOMEParams", etc... par les procolos dans ProtocolID 
    //----------------------------------------------------------------------------------------------
    
	switch (message.id)
	{
	case GetPose:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		pose.x = reinterpret_cast<float&>(_vect[0]);
		pose.y = reinterpret_cast<float&>(_vect[1]);
		pose.z = reinterpret_cast<float&>(_vect[2]);
		pose.r = reinterpret_cast<float&>(_vect[3]);

		for (unsigned char j = 0; j < 4; j++)
		{
			pose.jointAngle[j] = reinterpret_cast<float&>(_vect[4 + j]);
		}
		break;

	case GetHOMEParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		homeParams.x = reinterpret_cast<float&>(_vect[0]);
		homeParams.y = reinterpret_cast<float&>(_vect[1]);
		homeParams.z = reinterpret_cast<float&>(_vect[2]);
		homeParams.r = reinterpret_cast<float&>(_vect[3]);
		break;

	case GetPTPJumpLParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		PtpJumpParams.jumpHeight = reinterpret_cast<float&>(_vect[0]);
		PtpJumpParams.maxJumpHeight = reinterpret_cast<float&>(_vect[1]);
		break;

	case GetJOGLParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		JogLParams.velocity = reinterpret_cast<float&>(_vect[0]);
		JogLParams.acceleration = reinterpret_cast<float&>(_vect[1]);
		break;

	case GetJOGJointParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			JogJointParams.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			JogJointParams.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetJOGCoordinateParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			JogCoordinateParams.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			JogCoordinateParams.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetPTPJointParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			PtpJointParams.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			PtpJointParams.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetPTPCoordinateParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		PtpCoordinateParams.xyzVelocity = _vect[0];
		PtpCoordinateParams.rVelocity = _vect[1];
		PtpCoordinateParams.xyzAcceleration = _vect[2];
		PtpCoordinateParams.rAcceleration = _vect[3];
		break;

	/*case GetPTPJumpParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		PtpJumpParams.jumpHeight = _vect[0];
		PtpJumpParams.maxJumpHeight = _vect[1];
		break;*/

	case GetPTPLParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		PtpLParams.velocity = _vect[0];
		PtpLParams.acceleration = _vect[1];
		break;

	case GetARCParams:
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		ArcParams.xyzVelocity = _vect[0];
		ArcParams.rVelocity = _vect[1];
		ArcParams.xyzAcceleration = _vect[2];
		ArcParams.rAcceleration = _vect[3];
		break;

	default:
		break;
	}
    //----------------------------------------------------------------------------------------------
    

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
/*-------------------------------------------
NOUVELLES FONCTIONS------------------------*/
int Dobot::getPose(){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolGetPose;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;         
}

int Dobot::getJOGParams(){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolFunctionJOGBase;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;        
}

int Dobot::getHomeParams(){
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolHOMEParams;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);

    return true;
}

int Dobot::getPTPJumpLParams(){
    
    
    return true;
}

int Dobot::getParams(int ID_command){   //FONCTION CAPABLE D'EXEC TOUTES LES FONCTIONS GET
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ID_command;
    tempMessage.rw = false;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&_gSerialProtocolHandler, &tempMessage);


    return true;
}

/*----------------------------------------------
----------------------------------------------*/

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
    if(abs(posX)>NEUTRAL){
        //change speed, proportional to joystick position, find regression
        //gJOGCoordinateParams.velocity[0] = 100;
        //gJOGCoordinateParams.velocity[1] = 100;
        //gJOGCoordinateParams.velocity[2] = 100;
        //gJOGCoordinateParams.velocity[3] = 100;
        //SetJOGCoordinateParams(1);
        if(posX>0)  gJOGCmd.cmd = AP_DOWN;
        else gJOGCmd.cmd = AN_DOWN;
    } else {
        gJOGCmd.cmd = IDEL;
    }
    SetJOGCmd(1);
    if(abs(posY)>NEUTRAL){
        //change speed, proportional to joystick position, find regression
        //gJOGCoordinateParams.velocity[0] = 100;
        //gJOGCoordinateParams.velocity[1] = 100;
        //gJOGCoordinateParams.velocity[2] = 100;
        //gJOGCoordinateParams.velocity[3] = 100;
        //SetJOGCoordinateParams(1);
        if(posX>0)  gJOGCmd.cmd = BP_DOWN;
        else gJOGCmd.cmd = BN_DOWN;
    } else {
        gJOGCmd.cmd = IDEL;
    }
    SetJOGCmd(1);
    return true;
}

uint32_t Dobot::bytes_to_uint32_t(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	return (a << 24) | (b << 16) | (c << 8) | d;
}