#include "pcb.h"

// Constructor
pcb::pcb(osp2023::id_type processID, osp2023::time_type burstTime) {
    this->processID = processID;
    this->burstTime = burstTime;
    this->timeUsed = 0;
    this->totalWaitTime = 0;
    this->firstCpuTime = -1;
    this->completionTime = -1;
}