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

typedef struct tagDobotOrigin{
    float x;
    float y;
    float z;
    float theta;
}DobotOrigin;

typedef struct TagPoint2D{
  float x;
  float y;
  float z;
}Point2D;

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

        DobotOrigin origin;

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

        /*********************************************************************************************************
        ** COMPLEX MOVEMENT function
        *********************************************************************************************************/
        int firstMove();
        int joyStickMove(int posX, int posY);
        void idlePos();
        void danse();
        void drawSegment(Point2D *Start, Point2D *End);
        /*********************************************************************************************************
        ** G-CODE function
        *********************************************************************************************************/
       int nextGCodeInstruction();
       void GCodeInterpretation();


       void G0Command(float x, float y, float z, bool jump);
       void G0Command(Point2D *point, bool jump);
       void G1Command(float x, float y, float z);
       void G1Command(Point2D *point);

        /*********************************************************************************************************
        ** Compute function
        *********************************************************************************************************/
       void transformFcoordsToDobotCoords(float *x, float *y, float *z);
       

};