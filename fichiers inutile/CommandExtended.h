#ifndef COMMAND_EXTENDED_H
#define COMMAND_EXTENDED_H

typedef struct tagHOMECmd {
uint32_t reserved; // Reserved for future use
} HOMECmd;

extern int ClearDobotBuffer(bool isQueued, uint64_t *queuedCmdIndex);
extern int GetQueuedCmdCurrentIndex(bool isQueued, uint64_t *queuedCmdIndex);
extern int SetQueuedCmdStopExec(uint64_t *queuedCmdIndex);
extern int SetHOMECmd(HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex);


#endif