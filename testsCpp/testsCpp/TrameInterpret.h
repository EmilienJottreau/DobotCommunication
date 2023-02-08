#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
//---------------------------------
typedef struct tagMessage {
	uint8_t id;
	uint8_t rw;
	uint8_t isQueued;
	uint8_t paramsLen;
	uint8_t params[62];
}Message;
//--------------------------------
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

typedef struct tagJOGJointParams {
	float velocity[4];//Joint velocity of 4 axis
	float acceleration[4]; //Joint acceleration of 4 axis
}JOGJointParams;

typedef struct tagJOGCoordinateParams {
	float velocity[4];//Coornite velocity of 4 axis(x,y,z,r)
	float acceleration[4];//Coordinate acceleration of 4 zxis(x,y,z,r)
} JOGCoordinateParams;

typedef struct tagJOGLParams {
	float velocity; // Joint velocity of JOGL
	float acceleration; // Joint acceleration of JOGL
}JOGLParams;

typedef struct tagPTPJointParams {
	float velocity[4]; //In PTP mode, joint velocity of 4 axis
	float acceleration[4]; // In PTP mode, joint acceleration of 4 axis
} PTPJointParams;

typedef struct tagPTPCoordinateParams {
	float xyzVelocity; //In PTP mode, coordinate velocity of xyz 3 axis
	float rVelocity; //In PTP mode, end-effector velocity
	float xyzAcceleration;//In PTP mode, coordinate acceleration of xyz 3 axis
	float rAccleration; // In PTP mode, end-effector acceleration
} PTPCoordinateParams;

typedef struct tagPTPJumpParams {
	float jumpHeight; //Movement rising distance in Jump mode
	float zLimit; //Movement of the maximum rising height limitation in Jump mode
} PTPJumpParams;

typedef struct tagPTPCommonParams {
	float velocityRatio; //Velocity ratio in PTP mode, share joint and coordinate mode
	float accelerationRatio; //Acceleration ratio in PTP mode, share joint and coordinate mode
} PTPCommonParams;

typedef struct tagPTPLParams {
	float velocity; // In PTP mode, joint velocity of 4 axis
	float acceleration; // In PTP mode, joint acceleration of 4 axis
} PTPLParams;

typedef struct tagPTPJump2Params {
	float startjumpHeight;//Movement of the starting lifting height in Jump mode
	float endJumpHeight; //Movement of the end lifting height in Jump mode
	float zLimit; //Movement of the maximum lifting height in Jump mode
} PTPJump2Params;

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

class TrameInterpret
{
private:
	std::vector<uint8_t> _vect;
public:
	TrameInterpret(Message a);
	uint32_t bytes_to_uint32_t(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
};

