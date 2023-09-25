#ifndef LOADER
#define LOADER

#include <vector>
#include <fstream>
#include <sstream>
#include "pcb.h"

class Loader {
    std::ifstream file;

   public:
    Loader(std::string inputFile);

    // load processes from input file to vector array
    std::vector<pcb> load();

    ~Loader();
};

#endif