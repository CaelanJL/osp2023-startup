#include "loader.h"

Loader::Loader(std::string inputFile) {
    file.open(inputFile);
}

std::vector<pcb> Loader::load() {

    // vector of pcb
    std::vector<pcb> processVector;

    std::string nextLine;
    while (std::getline(file, nextLine)) {

        // retrieve args into ID and burst time
        osp2023::id_type processID = std::stoi(nextLine.substr(0, nextLine.find(",")));
        osp2023::time_type burstTime = std::stoi(nextLine.substr(nextLine.find(",") + 1, nextLine.length()));

        // create pcb object and add to vector
        pcb process(processID, burstTime);
        processVector.push_back(process);
    }

    return processVector;
}

Loader::~Loader() {
    file.close();
}