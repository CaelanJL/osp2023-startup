/* Includes */
#include "loader.h"
#include "simulator.h"

/* Import standard library stuff */

/* 
 * Function to check the argument count against the schedulor type
 * @return true if the argument count is correct, false otherwise
 */
bool checkArgCount(int argc, std::string schedulerType) {

    // Check that the number of arguments is correct for the scheduler type
    if (schedulerType == "rr" && argc != 3) {
        std::cout << "Error: Schedule type rr expects 2 arguments got " << argc - 1 << ", Usage: ./rr <quantum (time in ms)> <datafile>" << std::endl;
        return false;
    } else if (schedulerType != "rr" && argc != 2) {
        std::cout << "Error: Schedule type <fifo, sjr> expects 1 argument got " << argc - 1 << ", Usage: ./<fifo, sjf> <datafile>" << std::endl;
        return false;
    }
    return true;
}

/* 
 * Function to validate the given command line arguments
 * @return true if the arguments are valid, false otherwise
 */
bool validateArgs(int argc, char* argv[], std::string schedulerType) {

    // Check that the scheduler type is valid
    if (schedulerType != "rr" && schedulerType != "fifo" && schedulerType != "sjf") {
        std::cout << "Error: Invalid scheduler '" << argv[0] << "', expected fifo, sjf or rr" << std::endl;
        return false;
    }

    // Check arg count for the scheduler type
    if (!checkArgCount(argc, schedulerType)) {
        return false;
    }


    // Check that the file exists
    std::ifstream input_file(argv[argc - 1]);
    if (!input_file.is_open()) {
        std::cout << "Error: Cannot open file '" << argv[argc - 1] << "'." << std::endl;
        return false;
    }
    input_file.close();

    // Check that the quantum is valid
    if (argc == 3) {

        std::size_t pos;

        try {
            // Convert the quantum to an int
            int quantum = std::stoi(argv[1], &pos);

            // Check that the quantum is valid
            if (pos < std::string(argv[1]).size() || quantum < 1) {
                throw std::invalid_argument("");
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Error: Invalid quantum '" << argv[1] << "', expected positive integer" << std::endl;
            return false;
        }
    }

    return true;
}

/* Main function */
int main(int argc, char* argv[]) {

    // Get the scheduler type based on the program name
    std::string schedulerStr = std::string(argv[0]).substr(2);

    // Validate the command line arguments
    bool valid = validateArgs(argc, argv, schedulerStr);


    // Run the simulation if the arguments are valid
    if (valid) {

        // Grab the filename
        std::string filename = argv[argc - 1];

        // Load the processes
        Loader loader(filename);
        std::vector<pcb> processes = loader.load();
        
        // Create the simulator
        Simulator simulator(processes);

        // Run the simulation
        int quantum = 10;
        if (schedulerStr == "rr") {
            quantum = std::stoi(argv[1]);
        }
        simulator.run(schedulerStr, quantum);
    }


    // Return 0 if the arguments are valid, 1 if they are not
    return !valid;
}