#include <HardwareSerial.h>
#include "ProtocolDef.h"
#include "command.h"

#include "parser.h"

#include <vector>

typedef enum  tagDobotNumber{
    DOBOT_1,
    DOBOT_2,
    DOBOT_3,
}DobotNumber;

#define RAW_BYTE_BUFFER_SIZE 256
#define PACKET_BUFFER_SIZE  4

class Dobot{


    private:
        DobotNumber _number;
        // Serial
        uint8_t gSerialTXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
        uint8_t gSerialRXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
        Packet gSerialTXPacketBuffer[PACKET_BUFFER_SIZE];
        Packet gSerialRXPacketBuffer[PACKET_BUFFER_SIZE];
        int idPrecedent;
        uint64_t param;
        uint64_t param246Precedent;
        Pose previousPose;
        Pose initPos;   //POSITION DE REPOS DU ROBOT (en dehors de la zone de travail)

        int joystickXState;
        int joystickYState;

        

    public:
        std::vector<uint64_t> instructionsQueue;
        HardwareSerial* _serial;
        ProtocolHandler _gSerialProtocolHandler;
        EndEffectorParams gEndEffectorParams;
        //attributes related to movement
        JOGJointParams gJOGJointParams;
        JOGCoordinateParams gJOGCoordinateParams;
        JOGCommonParams gJOGCommonParams;
        JOGCmd gJOGCmd;

        PTPJointParams gPTPJointParams;
        PTPCoordinateParams gPTPCoordinateParams;
        PTPCommonParams gPTPCommonParams;
        PTPCmd gPTPCmd;
        PTPJumpParams gptpJumpParams;
        uint64_t queuedCmdIndex;
        Pose pose;

        CPCmd gCPCmd;

        HOMECmd homeCmd;

        gpr::gcode_program prog;
        int actualProgIndex;
        
        Dobot(DobotNumber number);
        void ProtocolInit(void);
        void ProtocolProcess(void);
        void InitRam(void);
        //mettre toutes les commandes possibles dedans (command.cpp + commandExented.cpp et faire this.gSerialProtocolHandler)
        //...


        /*********************************************************************************************************
        ** End effector function
        *********************************************************************************************************/
        int SetEndEffectorParams(bool isQueued);
        int SetEndEffectorLaser(bool on, bool isQueued);
        int SetEndEffectorSuctionCup(bool suck, bool isQueued);
        int SetEndEffectorGripper(bool grip, bool isQueued);

        /*********************************************************************************************************
        ** JOG function
        *********************************************************************************************************/
        int SetJOGJointParams(bool isQueued);
        int SetJOGCoordinateParams(bool isQueued);
        int SetJOGCommonParams(bool isQueued);
        int SetJOGCmd(bool isQueued);

        /*********************************************************************************************************
        ** PTP function
        *********************************************************************************************************/
        int SetPTPJointParams(bool isQueued);
        int SetPTPCoordinateParams(bool isQueued);
        int SetPTPJumpParams(bool isQueued);
        int SetPTPCommonParams(bool isQueued);
        int SetPTPCmd(bool isQueued);
        int SetCPCmd();
        
        /*********************************************************************************************************
        ** EXTENDED function
        *********************************************************************************************************/
        int ClearDobotBuffer(bool isQueued);
        int GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex);
        int SetHOMECmd(bool isQueued);
        int ClearAllAlarms();
        int StartQueueExec();
        int StopQueueExec();



        /*********************************************************************************************************
        ** SYNCHRONIZATION function
        *********************************************************************************************************/
        int available();
        void getPose(Pose *PoseParam);
        void InitPos();
        void goToPreviousPos();
        /*********************************************************************************************************
        ** COMPLEX MOVEMENT function
        *********************************************************************************************************/
        int firstMove();
        int joyStickMove(int posX, int posY);
        /*********************************************************************************************************
        ** G-CODE function
        *********************************************************************************************************/
       int nextGCodeInstruction();
       void GCodeInterpretation();


       void G0Command(float x, float y, float z);
       void G1Command(float x, float y, float z);

};