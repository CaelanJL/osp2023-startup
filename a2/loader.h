#ifndef LOADER
#define LOADER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "pcb.h"

class Loader {
    // the file to load from
    std::ifstream file;

   public:
    // constructor
    Loader(std::string filename);

    // function to load processes from a file
    std::vector<pcb> load();

    // destructor
    ~Loader();
};

#endif