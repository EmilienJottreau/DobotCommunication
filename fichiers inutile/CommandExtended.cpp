#include <stdio.h>
#include <string.h>
#include "commandExtended.h"
#include "Protocol.h"
#include "ProtocolID.h"




int SetHOMECmd(HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolHOMECmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(homeCmd);
    memcpy(tempMessage.params, (uint8_t *)homeCmd, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}








int ClearDobotBuffer(bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdClear;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}




int GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdCurrentIndex;
    tempMessage.rw = false;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(queuedCmdIndex);
    memcpy(tempMessage.params, (uint8_t *)queuedCmdIndex, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

int SetQueuedCmdStopExec(uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolQueuedCmdStopExec;
    tempMessage.rw = true;
    tempMessage.isQueued = 0;
    tempMessage.paramsLen = 0;
    memcpy(tempMessage.params, NULL, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}