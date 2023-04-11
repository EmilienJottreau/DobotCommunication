#include "command.h"
#include <string.h>
#include "Message.h"

/****************************************************************************************************Point2DD*****
** Function name:       SetEndEffectorParams
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
*********************************************************************************************************/
void SetEndEffectorParams(ProtocolHandler *_gSerialProtocolHandler, EndEffectorParams *gEndEffectorParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(EndEffectorParams);
    memcpy(tempMessage.params, (uint8_t *)gEndEffectorParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);
}

/*********************************************************************************************************
** Function name:       SetEndEffectorLaser
** Descriptions:        Set the laser output
** Input parameters:    on,isQueued
*********************************************************************************************************/
void SetEndEffectorLaser(ProtocolHandler *_gSerialProtocolHandler, bool on, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorLaser;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = on;

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetEndEffectorSuctionCup
** Descriptions:        Set the suctioncup output
** Input parameters:    suck,isQueued
*********************************************************************************************************/
void SetEndEffectorSuctionCup(ProtocolHandler *_gSerialProtocolHandler, bool suck, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorSuctionCup;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = suck;
    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetEndEffectorGripper
** Descriptions:        Set the gripper output
** Input parameters:    grip,isQueued
*********************************************************************************************************/
void SetEndEffectorGripper(ProtocolHandler *_gSerialProtocolHandler, bool grip, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorGripper;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = grip;
    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetJOGJointParams
** Descriptions:        Sets the joint jog parameter
** Input parameters:    jogJointParams,isQueued
*********************************************************************************************************/
void SetJOGJointParams(ProtocolHandler *_gSerialProtocolHandler, JOGJointParams *gJOGJointParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGJointParams);
    memcpy(tempMessage.params, (uint8_t *)gJOGJointParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetJOGCoordinateParams
** Descriptions:        Sets the axis jog parameter
** Input parameters:    jogCoordinateParams,isQueued
*********************************************************************************************************/
void SetJOGCoordinateParams(ProtocolHandler *_gSerialProtocolHandler, JOGCoordinateParams *gJOGCoordinateParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)gJOGCoordinateParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetJOGCommonParams
** Descriptions:        Sets the jog common parameter
** Input parameters:    jogCommonParams,isQueued
*********************************************************************************************************/
void SetJOGCommonParams(ProtocolHandler *_gSerialProtocolHandler, JOGCommonParams *gJOGCommonParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCommonParams);
    memcpy(tempMessage.params, (uint8_t *)gJOGCommonParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetPTPJointParams
** Descriptions:        Sets the articulation point parameter
** Input parameters:    ptpJointParams,isQueued
*********************************************************************************************************/
void SetPTPJointParams(ProtocolHandler *_gSerialProtocolHandler, PTPJointParams *gPTPJointParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJointParams);
    memcpy(tempMessage.params, (uint8_t *)gPTPJointParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetPTPCoordinateParams
** Descriptions:        Sets the coordinate position parameter
** Input parameters:    ptpCoordinateParams,isQueued
*********************************************************************************************************/
void SetPTPCoordinateParams(ProtocolHandler *_gSerialProtocolHandler, PTPCoordinateParams *gPTPCoordinateParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)gPTPCoordinateParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetPTPJumpParams
** Descriptions:        Set the gate type parameter
** Input parameters:    ptpJumpParams,isQueued
*********************************************************************************************************/
void SetPTPJumpParams(ProtocolHandler *_gSerialProtocolHandler, PTPJumpParams *gptpJumpParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJumpParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJumpParams);
    memcpy(tempMessage.params, (uint8_t *)gptpJumpParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}

/*********************************************************************************************************
** Function name:       SetPTPCommonParams
** Descriptions:        Set point common parameters
** Input parameters:    ptpCommonParams,isQueued
*********************************************************************************************************/
void SetPTPCommonParams(ProtocolHandler *_gSerialProtocolHandler, PTPCommonParams *gPTPCommonParams, bool isQueued)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCommonParams);
    memcpy(tempMessage.params, (uint8_t *)gPTPCommonParams, tempMessage.paramsLen);

    MessageWrite(_gSerialProtocolHandler, &tempMessage);

    
}
