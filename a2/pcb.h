#ifndef PCB
#define PCB

#include <iostream>
#include "types.h"

#pragma once  // tells the compiler to only include this file once
              /**
 * the process control block - represents a process that needs to be executed in
 * our simulator. Please note the I used some custom types of osp2023::time_type
 * and osp2023::id_type. these are just aliases to long integers but they are
 * more meaningful type names, hinting at how they will be used. Please see
 * their definitions in types.h.
 **/
class pcb {
    public:
    // the unique process ID
    osp2023::id_type processID;

    // the total time that a process / job should run for
    osp2023::time_type burstTime;

    // the time that has been used so far for this process
    osp2023::time_type timeUsed;

    // the priority level for this process

    
    // how much time has this process spent waiting for the cpu?
    osp2023::time_type totalWaitTime;

    // what time was this process last on the cpu?
    osp2023::time_type completionTime;

    // what was the first time this process was on the cpu?
    osp2023::time_type firstCpuTime;

   
    // constructor
    pcb(osp2023::id_type processId, osp2023::time_type totalTime);

    // max and min duration for a process in our system.
    static constexpr osp2023::time_type MAX_DURATION = 100;
    static constexpr osp2023::time_type MIN_DURATION = 10;
};

#endif