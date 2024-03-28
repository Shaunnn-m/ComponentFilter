#include "PGMimageProcessor.h"
#include <iostream>
#include <limits.h>
#include <string>

using namespace MKNTHA093;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputPGMfile> [options]\n";
        return 1;
    }

    std::string inputFileName = argv[1];
    int minSize = 3;
    int maxSize = INT_MAX;
    unsigned char threshold = 127;
    std::string outFileName;
    bool printComponentDataFlag = false;

    // Example of simple command-line argument parsing
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-s" && i + 2 < argc) {
            minSize = std::stoi(argv[++i]);
            maxSize = std::stoi(argv[++i]);
        } else if (arg == "-t" && i + 1 < argc) {
            threshold = static_cast<unsigned char>(std::stoi(argv[++i]));
        } else if (arg == "-p") {
            printComponentDataFlag = true;
        } else if (arg == "-w" && i + 1 < argc) {
            outFileName = argv[++i];
        }
    }

    PGMimageProcessor processor(inputFileName);
    if (!processor.readImage()) {
        std::cerr << "Failed to read the image.\n";
        return 1;
    }



    if (printComponentDataFlag) {
        int componentCount = processor.extractComponents(threshold, minSize);
        std::cout << "Total components detected: " << componentCount << std::endl;
        int filteredCount = processor.filterComponentsBySize(minSize, maxSize);
        std::cout << "Components after filtering: " << filteredCount << std::endl;
        int largest = processor.getLargestSize();
        std::cout << "The Largest component has: " << largest << " pixels"<<std::endl;
        int smallest = processor.getSmallestSize();
        std::cout << "The smallest component has: " << smallest << " pixels"<<std::endl;
        for (const auto& component : processor.getComponents()) { // Assume there's a getComponents() method
            processor.printComponentData(component);
        }
    }

    if (!outFileName.empty()) {
        if (processor.writeComponents(outFileName)) {
            std::cout << "Components written to " << outFileName << std::endl;
        } else {
            std::cerr << "Failed to write components to file.\n";
        }
    }

    return 0;
}

