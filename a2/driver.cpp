/* Includes */
#include "loader.h"
#include "simulator.h"

/* Import standard library stuff */
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stoi;

/* 
 * Function to check the argument count against the schedulor type
 * @return true if the argument count is correct, false otherwise
 */
bool checkArgCount(int argc, std::string schedulerType) {

    // Check that the number of arguments is correct for the scheduler type
    if (schedulerType == "rr" && argc != 4) {
        cout << "Error: Schedule type rr expects 2 arguments got " << argc - 1 << ", Usage: ./rr <quantum (time in ms)> <datafile>" << endl;
        return false;
    } else if (schedulerType != "rr" && argc != 3) {
        cout << "Error: Schedule type <fifo, sjr> expects 1 argument got " << argc - 1 << ", Usage: ./<fifo, sjf> <datafile>" << endl;
        return false;
    }
    return true;
}

/* 
 * Function to validate the given command line arguments
 * @return true if the arguments are valid, false otherwise
 */
bool validateArgs(int argc, char* argv[], std::string schedulerType) {
    cout << schedulerType << std::endl;

    // Check that the scheduler type is valid
    if (schedulerType != "rr" && schedulerType != "fifo" && schedulerType != "sjf") {
        cout << "Error: Invalid scheduler '" << argv[1] << "', expected fifo, sjf or rr" << endl;
        return false;
    }

    // Check arg count for the scheduler type
    if (!checkArgCount(argc, schedulerType)) {
        return false;
    }

    // Check that the file exists
    ifstream input_file(argv[argc - 1]);
    if (!input_file.is_open()) {
        cout << "Error: Cannot open file '" << argv[argc - 1] << "'." << endl;
        return false;
    }
    input_file.close();

    // Check that the quantum is valid
    if (argc == 4) {

        std::size_t pos;

        try {
            // Convert the quantum to an int
            int quantum = stoi(argv[2], &pos);

            // Check that the quantum is valid
            if (pos < std::string(argv[2]).size() || quantum < 1) {
                throw std::invalid_argument("");
            }
        } catch (const std::invalid_argument&) {
            cout << "Error: Invalid quantum '" << argv[2] << "', expected positive integer" << endl;
            return false;
        }
    }

    return true;
}

/* Main function */
int main(int argc, char* argv[]) {

    // Get the scheduler type based on the program name
    string schedulerStr = string(argv[1]);

    // Validate the command line arguments
    bool valid = validateArgs(argc, argv, schedulerStr);

    // Run the simulation if the arguments are valid
    if (valid) {

        // Grab the filename
        string filename = argv[argc - 1];

        // Load the processes
        Loader loader(filename);
        std::vector<pcb> processes = loader.load();
        
        // Create the simulator
        Simulator simulator(processes);

        // Run the simulation
        int quantum = 10;
        if (schedulerStr == "rr") {
            quantum = stoi(argv[2]);
        }
        simulator.run(schedulerStr, quantum);
    }

    // Return 0 if the arguments are valid, 1 if they are not
    return !valid;
}