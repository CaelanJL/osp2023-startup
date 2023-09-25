#include "loader.h"
#include "simulator.h"

int main(int argc, char* argv[]) {

    // retrieve commandline args
    std::string schedulerStr = std::string(argv[0]).substr(2);
    std::string inputFile = argv[argc - 1];

    // construct loader and retrieve process vector
    Loader loader(inputFile);
    std::vector<pcb> processes = loader.load();

    // construct simulator
    Simulator simulator(processes);

    // ensure quantum is type int
    int quantum = 10;
    if (schedulerStr == "rr") {
        try
        {
            quantum = std::stoi(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return EXIT_FAILURE;
        }
    }

    // file error checking
    std::ifstream file(argv[argc - 1]);
    if (!file.is_open()) {
        std::cerr << "Invalid file name: '" << argv[argc - 1] << std::endl;
        return EXIT_FAILURE;
    }
    file.close();

    // run simulating code
    simulator.run(schedulerStr, quantum);


    return EXIT_SUCCESS;
}