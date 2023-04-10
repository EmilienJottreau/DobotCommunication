/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ProtocolDef.h
** Latest modified Date:2016-06-01
** Latest Version:      V1.0.0
** Descriptions:        Protocol definition
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef PROTOCOLDEF_H
#define PROTOCOLDEF_H

#include "RingBuffer.h"

#define SYNC_BYTE   0xAA

#define MAX_PAYLOAD_SIZE 64  
                           // Minus 1 for not larger than SYNC_BYTE

#pragma pack(push)
#pragma pack(1)


#define GetPose 10
#define GetPTPJumpLParams 87
#define GetHOMEParams 30
#define GetJOGJointParams 70
#define GetJOGCoordinateParams 71
#define GetJOGLParams 74	//vitesse de chaque joint
#define GetPTPJointParams 80
#define GetPTPCoordinateParams 81
#define GetPTPJumpParams 82
#define GetPTPLParams 85
#define GetCPParams 90
#define GetARCParams 100

// Just for easy use of this protocol
typedef struct tagMessage {
    uint8_t id;
    uint8_t rw;
    uint8_t isQueued;
    uint8_t paramsLen;
    uint8_t params[MAX_PAYLOAD_SIZE - 2];
}Message;

// Packet header
typedef struct tagPacketHeader {
    uint8_t syncBytes[2];
    uint8_t payloadLen;
}PacketHeader;

typedef struct tagPacketPayload {
    uint8_t id;
    uint8_t ctrl;
    uint8_t params[MAX_PAYLOAD_SIZE - 2];
}PacketPayload;

typedef struct tagPacket {
    PacketHeader header;
    PacketPayload payload;
    uint8_t checksum;
}Packet;

typedef void (*SendFunc)(void);

typedef struct tagProtocolHandler {
    // For hardware
    RingBuffer txRawByteQueue;
    RingBuffer rxRawByteQueue;

    Packet txAppPacket;
    Packet rxAppPacket;
    Packet rxDLPacket;

    // For application
    RingBuffer txPacketQueue;
    RingBuffer rxPacketQueue;
}ProtocolHandler;

typedef struct tagPTPJump2Params {
	float startjumpHeight;//Movement of the starting lifting height in Jump mode
	float endJumpHeight; //Movement of the end lifting height in Jump mode
	float zLimit; //Movement of the maximum lifting height in Jump mode
} PTPJump2Params;

typedef struct tagPose
{
	float x;             // Robotic arm coordinate system x
	float y;             // Robotic arm .
	float z;             // Robotic arm coordinate system z
	float r;             // Robotic arm coordinate system r
	float jointAngle[4]; // Robotic arm 4 axis(The basement, rear arm, forearm,EndEffector) angles
} Pose;

typedef struct tagHOMEParams {
	float x;
	float y;
	float z;
	float r;
} HOMEParams;





typedef struct tagJOGLParams {
	float velocity; // Joint velocity of JOGL
	float acceleration; // Joint acceleration of JOGL
}JOGLParams;









typedef struct tagPTPLParams {
	float velocity; // In PTP mode, joint velocity of 4 axis
	float acceleration; // In PTP mode, joint acceleration of 4 axis
} PTPLParams;


typedef struct tagCPParams {
	float planAcc; // Maximum planned accelerations
	float junctionVel; // Maximum junction acceleration
	union {
		float acc; //Maximum actual acceleration,used in non-real-time mode
		float period; //Interpolation cycle, used in real-time mode
	};
	uint8_t realTimeTrack; //0: Non-real time mode; 1: Real time mode
} CPParams;

typedef struct tagARCParams {
	float xyzVelocity; // Cartesian coordinate axis (X,Y,Z) velocity
	float rVelocity; // Cartesian coordinate axis (R) velocity
	float xyzAcceleration; // Cartesian coordinate axis (X,Y,Z) acceleration
	float rAcceleration; // Cartesian coordinate axis (R) acceleration
} ARCParams;

#pragma pack(pop)

#endif

