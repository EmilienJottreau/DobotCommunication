#include "TrameInterpret.h"

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

TrameInterpret::TrameInterpret(Message message) {
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

	/*case GetCPParams:
		CPParams cpp;
		for (unsigned char i = 0; i < sizeof(message.params); i = i + 4) {
			_vect.push_back(bytes_to_uint32_t(message.params[i], message.params[i + 1], message.params[i + 2], message.params[i + 3]));
		}
		cpp.planAcc = _vect[0];
		cpp.junctionVel = _vect[1];

		break;
*/
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

uint32_t TrameInterpret::bytes_to_uint32_t(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	return (a << 24) | (b << 16) | (c << 8) | d;
}
