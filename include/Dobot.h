#include <HardwareSerial.h>
#include "ProtocolDef.h"
#include "command.h"

#include <vector>

typedef enum  tagDobotNumber{
    DOBOT_1,
    DOBOT_2,
    DOBOT_3,
}DobotNumber;

#define RAW_BYTE_BUFFER_SIZE    256
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

        HOMECmd homeCmd;
        
        Dobot(DobotNumber number);
        void ProtocolInit(void);//(dans protocol.cpp)
        void ProtocolProcess(void);//(dans protocol.cpp) faire les ringbuffer
        void InitRam(void);
        //mettre toutes les commandes possibles dedans (command.cpp + commandExented.cpp et faire this.gSerialProtocolHandler)
        //...


        /*********************************************************************************************************
        ** End effector function
        *********************************************************************************************************/
        int SetEndEffectorParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetEndEffectorLaser(bool on, bool isQueued, uint64_t *queuedCmdIndex);
        int SetEndEffectorSuctionCup(bool suck, bool isQueued, uint64_t *queuedCmdIndex);
        int SetEndEffectorGripper(bool grip, bool isQueued, uint64_t *queuedCmdIndex);

        /*********************************************************************************************************
        ** JOG function
        *********************************************************************************************************/
        int SetJOGJointParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetJOGCoordinateParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetJOGCommonParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetJOGCmd(bool isQueued, uint64_t *queuedCmdIndex);

        /*********************************************************************************************************
        ** PTP function
        *********************************************************************************************************/
        int SetPTPJointParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetPTPCoordinateParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetPTPJumpParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetPTPCommonParams(bool isQueued, uint64_t *queuedCmdIndex);
        int SetPTPCmd(bool isQueued, uint64_t *queuedCmdIndex);


        /*********************************************************************************************************
        ** EXTENDED function
        *********************************************************************************************************/
        int ClearDobotBuffer(bool isQueued, uint64_t *queuedCmdIndex);
        int GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex);
        int SetQueuedCmdStopExec(uint64_t *queuedCmdIndex);
        int SetHOMECmd(bool isQueued, uint64_t *queuedCmdIndex);
        int ClearAllAlarms();
        int StartQueueExec();
        int StopQueueExec();


};