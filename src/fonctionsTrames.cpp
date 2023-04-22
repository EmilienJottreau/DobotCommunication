#include<stdio.h>
#include<iostream>
#include<vector>

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

uint32_t bytes_to_uint32_t(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	return (a << 24) | (b << 16) | (c << 8) | d;
}

void interpretMessage(Message message){
    std::vector<uint8_t> _vect;
    switch (message.id)
	{
	case GetPose:
		Pose p;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		p.x = reinterpret_cast<float&>(_vect[0]);
		p.y = reinterpret_cast<float&>(_vect[1]);
		p.z = reinterpret_cast<float&>(_vect[2]);
		p.r = reinterpret_cast<float&>(_vect[3]);

		for (unsigned char j = 0; j < 4; j++)
		{
			p.jointAngle[j] = reinterpret_cast<float&>(_vect[4 + j]);
		}
		break;

	case GetHOMEParams:
		HOMEParams hp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		hp.x = reinterpret_cast<float&>(_vect[0]);
		hp.y = reinterpret_cast<float&>(_vect[1]);
		hp.z = reinterpret_cast<float&>(_vect[2]);
		hp.r = reinterpret_cast<float&>(_vect[3]);
		break;

	case GetPTPJumpLParams:
		PTPJumpParams ptpjp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		ptpjp.jumpHeight = reinterpret_cast<float&>(_vect[0]);
		ptpjp.zLimit = reinterpret_cast<float&>(_vect[1]);
		break;

	case GetJOGLParams:
		JOGLParams jp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		jp.velocity = reinterpret_cast<float&>(_vect[0]);
		jp.acceleration = reinterpret_cast<float&>(_vect[1]);
		break;

	case GetJOGJointParams:
		JOGJointParams jjp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			jjp.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			jjp.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetJOGCoordinateParams:
		JOGCoordinateParams jgp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			jgp.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			jgp.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetPTPJointParams:
		PTPJointParams pjp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			pjp.velocity[j] = reinterpret_cast<float&>(_vect[j]);
			pjp.acceleration[j] = reinterpret_cast<float&>(_vect[j + 4]);
		}
		break;

	case GetPTPCoordinateParams:
		PTPCoordinateParams pcp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		pcp.xyzVelocity = _vect[0];
		pcp.rVelocity = _vect[1];
		pcp.xyzAcceleration = _vect[2];
		pcp.rAccleration = _vect[3];
		break;

	case GetPTPJumpParams:
		PTPJumpParams pjpa;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		pjpa.jumpHeight = _vect[0];
		pjpa.zLimit = _vect[1];
		break;

	case GetPTPLParams:
		PTPLParams plp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		plp.velocity = _vect[0];
		plp.acceleration = _vect[1];
		break;
        
	case GetARCParams:
		ARCParams arcp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		arcp.xyzVelocity = _vect[0];
		arcp.rVelocity = _vect[1];
		arcp.xyzAcceleration = _vect[2];
		arcp.rAcceleration = _vect[3];
		break;

	default:
		break;
	}
}