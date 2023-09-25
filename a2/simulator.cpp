#include "simulator.h"

Simulator::Simulator(std::vector<pcb>& processes) {
    this->processes = &processes;
}

pcb* Simulator::getNextFIFO() {
    return &processes->front();
}

pcb* Simulator::getNextSJF() {
    pcb* shortestProcess = &processes->front();

    // Iterate through the processes to find the shortest
    for (size_t i = 0; i < processes->size(); i++) {
        if (processes->at(i).burstTime < shortestProcess->burstTime) {
            shortestProcess = &processes->at(i);
        }
    }

    return shortestProcess;
}

pcb* Simulator::getNextRR() {
    return &processes->front();
}

void Simulator::run(std::string scheduler, int quantum) {

    int timePassed = 0;

    std::vector<pcb> completedProcesses;

    while (!processes->empty()) {

        pcb* nextProcess;
        if (scheduler == "fifo") {
            nextProcess = getNextFIFO();
        } else if (scheduler == "sjf") {
            nextProcess = getNextSJF();
        } else if (scheduler == "rr") {
            nextProcess = getNextRR();
        } else {
            std::cout << "Error: Invalid scheduler '" << scheduler << "'" << std::endl;
            return;
        }

        int executionTime = quantum;
        if (scheduler != "rr") {
            executionTime = nextProcess->burstTime;
        }

        int remainingTime = nextProcess->burstTime - nextProcess->timeUsed;
        if (remainingTime < executionTime) {
            executionTime = remainingTime;
        }

        if (nextProcess->firstCpuTime == -1) {
            nextProcess->firstCpuTime = timePassed;
        }

        timePassed += executionTime;

        nextProcess->timeUsed = nextProcess->timeUsed + executionTime;

        nextProcess->totalWaitTime = timePassed - nextProcess->timeUsed;

        int processIndex = 0;
        for (size_t i = 0; i < processes->size(); i++) {
            if (processes->at(i).processID == nextProcess->processID) {
                processIndex = i;
                break;
            }
        }

        
        auto processIterator = processes->begin() + processIndex;

        pcb processCopy = *nextProcess;
        processes->erase(processIterator);

        if (processCopy.timeUsed < processCopy.burstTime) {            
            processes->push_back(processCopy);
        } else {
            processCopy.completionTime = timePassed;
            completedProcesses.push_back(processCopy);
        }
    }

    int aggregatedWaitTime = 0;
    int aggregatedTurnaroundTime = 0;
    int aggregatedResponseTime = 0;

    for (size_t i = 0; i < completedProcesses.size(); i++) {
        std::cout << "Process ID: " << completedProcesses.at(i).processID << std::endl;
        std::cout << "Burst time: " << completedProcesses.at(i).burstTime << std::endl;
        std::cout << "TAT: " << completedProcesses.at(i).completionTime << std::endl;
        std::cout << "Waiting time: " << completedProcesses.at(i).totalWaitTime << std::endl;
        std::cout << "Response time: " << completedProcesses.at(i).firstCpuTime << std::endl << std::endl;

        // add this processes time to a running total to later be divided by count for address
        aggregatedWaitTime += completedProcesses.at(i).totalWaitTime;

        // in this case all processes arrived at time 0, therefore turnaround time = completion time
        aggregatedTurnaroundTime += completedProcesses.at(i).completionTime; 

        // response time is time from when process arrived (0) to when process got cpu
        aggregatedResponseTime += completedProcesses.at(i).firstCpuTime;
    }

    int numProcesses = completedProcesses.size();

    std::cout << "AVERAGES: " << std::endl;
    // must convert ints to float such that division returns a float
    std::cout << "wait time: " << aggregatedWaitTime / static_cast<float>(numProcesses) << std::endl;
    std::cout << "TAT: " << aggregatedTurnaroundTime / static_cast<float>(numProcesses) << std::endl;
    std::cout << "response time: " << aggregatedResponseTime / static_cast<float>(numProcesses) << std::endl;

}