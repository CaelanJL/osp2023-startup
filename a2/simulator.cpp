#include "simulator.h"

// Constructor
Simulator::Simulator(std::vector<pcb>* processes) {
    this->processes = processes;
}

/// Scheduler algorithms
/*
 * Function to get the next process using FIFO
 * @returns An iterator to the next process
 */
pcb* Simulator::getNextFIFO() {
    return &processes->front();
}

/*
 * Function to get the next process using SJF
 * @returns An iterator to the next process
 */
pcb* Simulator::getNextSJF() {
    pcb* shortestProcess = &processes->front();

    // Iterate through the processes to find the shortest
    for (int i = 0; i < processes->size(); i++) {
        if (processes->at(i).burstTime < shortestProcess->burstTime) {
            shortestProcess = &processes->at(i);
        }
    }

    return shortestProcess;
}

/*
 * Function to get the next process using round robin
 * @returns An iterator to the next process
 */
pcb* Simulator::getNextRR() {
    return &processes->front();
}

/*
 * Function to run the simulation
 * @param scheduler The scheduler algorithm to use
 * @param quantum The quantum to use for round robin
 * Defaults to round robin with a quantum of 10
 * Prints the results to stdout
 * @returns nothing
 */
void Simulator::run(std::string scheduler, int quantum) {

    // Keep track of the time
    int timePassed = 0;

    // Completed processes
    std::vector<pcb> completedProcesses;

    // Loop until all processes are done
    while (!processes->empty()) {

        // Call the scheduler to get the next process
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

        /*
         * Calculate the execution time for the process
         * If the scheduler is round robin, the execution time is the quantum
         * If the scheduler is not round robin, the execution time is the total time of the process
         */
        int executionTime = quantum;
        if (scheduler != "rr") {
            executionTime = nextProcess->burstTime;
        }

        // Set the execution time to the remaining time if it is less than the execution time
        int remainingTime = nextProcess->burstTime - nextProcess->timeUsed;
        if (remainingTime < executionTime) {
            executionTime = remainingTime;
        }

        // If this is the first time the process is running on the CPU, set the first time CPU
        if (nextProcess->firstCpuTime == -1) {
            nextProcess->firstCpuTime = timePassed;
        }

        // Increment the time passed
        timePassed += executionTime;

        // Run the process for the execution time
        nextProcess->timeUsed += executionTime;

        // Set the total wait time
        nextProcess->totalWaitTime = timePassed - nextProcess->timeUsed;

        // remove nextProcess from processes
        processes->erase(std::remove(processes->begin(), processes->end(), *nextProcess), processes->end());

        // Add the process back to the end of vector if it is not done
        if (nextProcess->timeUsed < nextProcess->burstTime) {
            processes->push_back(*nextProcess);
        } else {
            nextProcess->completionTime = timePassed;
            completedProcesses.push_back(*nextProcess);
        }
    }

    // Totals
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    // Print the results of each process in the order they were completed
    for (const auto& process : completedProcesses) {

        // Calculate the totals
        total_wait_time += process.totalWaitTime;
        total_turnaround_time += process.completionTime; // in this case all processes arrived at time 0, therefore turnaround time = completion time
        total_response_time += process.firstCpuTime;

        // Print the process information
        std::cout << "ID: " << process.processID << ",";
        std::cout << "burst time: " << process.burstTime << ",";
        std::cout << "turnaround time: " << process.completionTime << ",";
        std::cout << "total waiting time: " << process.totalWaitTime << ",";
        std::cout << "response time" << process.firstCpuTime << std::endl;
    }

    // Print the Averages
    float totalProcesses = completedProcesses.size(); // Convert to float to avoid integer division
    std::cout << "Average,";
    std::cout << completedProcesses.size() << ",";
    std::cout << total_turnaround_time / totalProcesses << ",";
    std::cout << total_wait_time / totalProcesses << ",";
    std::cout << total_response_time / totalProcesses << std::endl;

}