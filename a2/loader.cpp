/* Includes */
#include "loader.h"

/* Constructor */
Loader::Loader(std::string filename) {
    file.open(filename);
}

// Function to load processes from a file
std::vector<pcb> Loader::load() {

    // Vector to store processes
    std::vector<pcb> processes;

    // Loop through file until there is no more lines
    std::string line;
    while (std::getline(file, line)) {

        // Init pcb values
        osp2023::id_type id;
        osp2023::time_type total_time;

        // Split the line by commas
        std::stringstream ss(line);
        std::string token;

        // Get the id
        std::getline(ss, token, ',');
        id = std::stol(token);

        // Get the total time
        std::getline(ss, token, ',');
        total_time = std::stoi(token);

        // Create the pcb
        pcb process(id, total_time);
        processes.push_back(process);
    }

    return processes;
}

/* Destructor */
Loader::~Loader() {
    file.close();
}