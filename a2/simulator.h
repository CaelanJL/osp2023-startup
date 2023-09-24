#ifndef SIMULATOR
#define SIMULATOR

#include <vector>
#include "pcb.h"


class Simulator
{
    public:
        Simulator(std::vector<pcb> processes);
        pcb* getNextFIFO();
        pcb* getNextSJF();
        pcb* getNextRR();
        void run(std::string scheduler, int quantum = 10);
        void printResults();

    private:
        std::vector<pcb>* processes;
        std::vector<pcb> completedProcesses;
        int timePassed;
};

#endif