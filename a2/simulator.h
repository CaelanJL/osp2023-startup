#ifndef SIMULATOR
#define SIMULATOR

#include <vector>
#include "pcb.h"


class Simulator
{
    public:
        Simulator(std::vector<pcb>& processes);
        pcb* retrieveFIFO();
        pcb* retrieveSJF();
        pcb* retrieveRR();
        void simulate(std::string scheduler, int quantum = 10);

    private:
        std::vector<pcb>* processes;
        std::vector<pcb> completedProcesses;
        int timePassed;
};

#endif