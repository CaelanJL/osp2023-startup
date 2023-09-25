#ifndef PCB
#define PCB

#include <iostream>
#include "types.h"

#pragma once  
class pcb {
    public:
    // the unique process ID
    osp2023::id_type processID;

    // the total time that a process / job should run for
    osp2023::time_type burstTime;

    // the time that has been used so far for this process
    osp2023::time_type timeUsed;

    // how much time has this process spent waiting for the cpu?
    osp2023::time_type totalWaitTime;

    // what time was this process last on the cpu?
    osp2023::time_type completionTime;

    // what was the first time this process was on the cpu?
    osp2023::time_type firstCpuTime;

    // constructor
    pcb(osp2023::id_type processId, osp2023::time_type totalTime);
};

#endif