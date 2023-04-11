#include <HardwareSerial.h>
#include "ProtocolDef.h"
#include "command.h"

#include "parser.h"

#include <vector>



//(size 1o?)
typedef enum  tagDobotNumber{
    DOBOT_1,
    DOBOT_2,
    DOBOT_3,
}DobotNumber;

//(size 16o)
typedef struct tagDobotOrigin{
    float x;
    float y;
    float z;
    float theta;
}DobotOrigin;

//(size 12o)
typedef struct TagPoint3D{
  float x;
  float y;
  float z;
}Point3D;

#define RAW_BYTE_BUFFER_SIZE 256
#define PACKET_BUFFER_SIZE  4

//(size 1488+)
class Dobot{


    private:
        DobotNumber _number;//1

        // Serial
        uint8_t gSerialTXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];//256
        uint8_t gSerialRXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];//256
        Packet gSerialTXPacketBuffer[PACKET_BUFFER_SIZE];//272
        Packet gSerialRXPacketBuffer[PACKET_BUFFER_SIZE];//272
        uint8_t idPrecedent;//1
        uint64_t param;//8
        uint64_t param246Precedent;//8

        DobotOrigin origin;//16


        uint8_t nb_new_instruction;//1

        

    public:
        std::vector<uint64_t> instructionsQueue;//inconnue
        HardwareSerial* _serial;//4?
        ProtocolHandler _gSerialProtocolHandler;//336

        //attributes related to movement


        PTPCmd gPTPCmd;//17
        JOGCmd gJOGCmd;//2
        CPCmd gCPCmd;//17


        uint64_t queuedCmdIndex;//8
        gcode::gcode_program prog;//inconnue
        uint8_t actualProgIndex;//1

        Point3D posPrecedente;//12 (position en repere dobot)
        
        Dobot(DobotNumber number);
        void ProtocolInit(void);
        void ProtocolProcess(void);


        void setUp(JOGJointParams *gJOGJointParams, JOGCommonParams *gJOGCommonParams, JOGCoordinateParams *gJOGCoordinateParams);

        

        void serialRead(void);



        /*********************************************************************************************************
        ** JOG function
        *********************************************************************************************************/
        void SetJOGCmd(bool isQueued);

        /*********************************************************************************************************
        ** PTP function
        *********************************************************************************************************/
        void SetPTPCmd(bool isQueued);
        void SetCPCmd();
        
        /*********************************************************************************************************
        ** EXTENDED function
        *********************************************************************************************************/
        void ClearDobotBuffer(bool isQueued);
        void GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex);
        void SetHOMECmd(bool isQueued);
        void ClearAllAlarms();
        void StartQueueExec();
        void StopQueueExec();

        void storePreviousPos(void);



        /*********************************************************************************************************
        ** SYNCHRONIZATION function
        *********************************************************************************************************/
        bool available();
        void goToPreviousPos();

        /*********************************************************************************************************
        ** COMPLEX MOVEMENT function
        *********************************************************************************************************/
        void firstMove();
        void idlePos();
        void danse();
        void drawSegment(Point3D *Start, Point3D *End);
        /*********************************************************************************************************
        ** G-CODE function
        *********************************************************************************************************/
       int nextGCodeInstruction();
       //void GCodeInterpretation();


       void G0Command(float x, float y, float z, bool jump);
       void G0Command(Point3D *point, bool jump);
       void G1Command(float x, float y, float z);
       void G1Command(Point3D *point);

        /*********************************************************************************************************
        ** Compute function
        *********************************************************************************************************/
       void transformFcoordsToDobotCoords(float *x, float *y, float *z);


};