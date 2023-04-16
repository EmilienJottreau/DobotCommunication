#ifndef COMMAND_H
#define COMMAND_H

/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           command.h
** Latest modified Date:
** Latest Version:      V1.0.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          LiYi
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:        Data definition
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include <stdint.h>
#include "ProtocolDef.h"
#include "ProtocolID.h"

/*********************************************************************************************************
** Data structure
*********************************************************************************************************/
#pragma pack(push)
#pragma pack(1)

enum
{
    JUMP_XYZ,
    MOVJ_XYZ,
    MOVL_XYZ,
    JUMP_ANGLE,
    MOVJ_ANGLE,
    MOVL_ANGLE,
    MOVJ_INC,
    MOVL_INC,
};

enum {
    IDEL,       //Invalid status
    AP_DOWN,    // X+/Joint1+
    AN_DOWN,    // X-/Joint1-
    BP_DOWN,    // Y+/Joint2+
    BN_DOWN,    // Y-/Joint2-
    CP_DOWN,    // Z+/Joint3+
    CN_DOWN,    // Z-/Joint3-
    DP_DOWN,    // R+/Joint4+
    DN_DOWN     // R-/Joint4-
};
enum{
    COORDINATE_MODEL,  
    JOINT_MODEL  
};
//(size 12o)
typedef struct tagEndEffectorParams {
    float xBias;
    float yBias;
    float zBias;
}EndEffectorParams;

//(size 64o)
typedef struct tagJOGJointParams {
    float velocity[4];
    float acceleration[4];
}JOGJointParams;

//(size 64o)
typedef struct tagJOGCoordinateParams {
    float velocity[4];
    float acceleration[4];
}JOGCoordinateParams;

//(size 8o)
typedef struct tagJOGCommonParams {
    float velocityRatio;
    float accelerationRatio;
}JOGCommonParams;

//(size 2o)
typedef struct tagJOGCmd {
    uint8_t isJoint;
    uint8_t cmd;
}JOGCmd;

//(size 64o)
typedef struct tagPTPJointParams {
    float velocity[4];
    float acceleration[4];
}PTPJointParams;

//(size 16o)
typedef struct tagPTPCoordinateParams {
    float xyzVelocity;
    float rVelocity;
    float xyzAcceleration;
    float rAcceleration;
}PTPCoordinateParams;

//(size 8o)
typedef struct tagPTPJumpParams {
    float jumpHeight;
    float maxJumpHeight;
}PTPJumpParams;

//(size 8o)
typedef struct tagPTPCommonParams {
    float velocityRatio;
    float accelerationRatio;
}PTPCommonParams;

//(size 17o)
typedef struct tagPTPCmd {
uint8_t ptpMode;
    float x;
    float y;
    float z;
    float r;
}PTPCmd;

//(size 4o)
typedef struct tagHOMECmd {
uint32_t reserved; // Reserved for future use
} HOMECmd;


//(size 17o)
typedef struct tagCPCmd {
    uint8_t cpMode; //CP mode, 0: Relative mode 1: Absolute mode
    float x; //x-coordinate increment(Relative mode) / x-coordinate(Absolute mode)
    float y; //y-coordinate increment(Relative mode)/ y-coordinate(Absolute mode)
    float z; // z-coordinate increment(Relative mode) / z-coordinate(Absolute mode)
union {
    float velocity; // Reserved
    float power; //Laser power
 };
} CPCmd;


typedef struct tagARCCmd {
    struct{
        float x;
        float y;
        float z;
        float r;
    } cirPoint; //Any circular point
    struct {
        float x;
        float y;
        float z;
        float r;
    } toPoint; //Circular ending point
} ARCCmd;


/*********************************************************************************************************
** End effector function
*********************************************************************************************************/
void SetEndEffectorParams(ProtocolHandler *_gSerialProtocolHandler, EndEffectorParams *gEndEffectorParams, bool isQueued);
void SetEndEffectorLaser(ProtocolHandler *_gSerialProtocolHandler, bool on, bool isQueued);
void SetEndEffectorSuctionCup(ProtocolHandler *_gSerialProtocolHandler, bool suck, bool isQueued);
void SetEndEffectorGripper(ProtocolHandler *_gSerialProtocolHandler, bool grip, bool isQueued);

/*********************************************************************************************************
** JOG function
*********************************************************************************************************/
void SetJOGJointParams(ProtocolHandler *_gSerialProtocolHandler, JOGJointParams *gJOGJointParams, bool isQueued);
void SetJOGCoordinateParams(ProtocolHandler *_gSerialProtocolHandler, JOGCoordinateParams *gJOGCoordinateParams, bool isQueued);
void SetJOGCommonParams(ProtocolHandler *_gSerialProtocolHandler, JOGCommonParams *gJOGCommonParams, bool isQueued);

/*********************************************************************************************************
** PTP function
*********************************************************************************************************/
void SetPTPJointParams(ProtocolHandler *_gSerialProtocolHandler, PTPJointParams *gPTPJointParams, bool isQueued);
void SetPTPCoordinateParams(ProtocolHandler *_gSerialProtocolHandler, PTPCoordinateParams *gPTPCoordinateParams, bool isQueued);
void SetPTPJumpParams(ProtocolHandler *_gSerialProtocolHandler, PTPJumpParams *gptpJumpParams, bool isQueued);
void SetPTPCommonParams(ProtocolHandler *_gSerialProtocolHandler, PTPCommonParams *gPTPCommonParams, bool isQueued);

/*********************************************************************************************************
** ARC function
*********************************************************************************************************/
void SetARCCmd(ProtocolHandler *_gSerialProtocolHandler, ARCCmd *arccmd, bool isQueued);

#pragma pack(pop)

#endif

