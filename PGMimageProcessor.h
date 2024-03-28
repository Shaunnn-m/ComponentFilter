//
// Created by Thabang Mokoena on 2024/03/14.
//

#ifndef ASSIGNMENT_3_PGMIMAGEPROCESSOR_H
#define ASSIGNMENT_3_PGMIMAGEPROCESSOR_H

#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include "ConnectedComponent.h"

namespace MKNTHA093 {


    class PGMimageProcessor {
    public:
        // Constructors and Destructor
        PGMimageProcessor(const std::string& filename);
        ~PGMimageProcessor();

        // Rule of Five: Copy Constructor, Move Constructor, Copy Assignment Operator, and Move Assignment Operator
        PGMimageProcessor(const PGMimageProcessor& other) = delete; // Prevent copy
        PGMimageProcessor(PGMimageProcessor&& other) noexcept = delete; // Prevent move
        PGMimageProcessor& operator=(const PGMimageProcessor& other) = delete; // Prevent copy assignment
        PGMimageProcessor& operator=(PGMimageProcessor&& other) noexcept = delete; // Prevent move assignment

        // Core functionalities
        bool readImage();
        bool writeComponents(const std::string& outFileName) const;
        int extractComponents(unsigned char threshold, int minValidSize);
        int filterComponentsBySize(int minSize, int maxSize);
        int getComponentCount() const;
        int getLargestSize() const;
        int getSmallestSize() const;
        const std::vector<std::shared_ptr<ConnectedComponent>>& getComponents() const;
        void printComponentData(const std::shared_ptr<ConnectedComponent>& component) const;





    private:
        std::string inputFileName;
        std::vector<unsigned char> imageData;

        int width;
        int height;
        std::vector<std::shared_ptr<ConnectedComponent>> components;
    };


} // MKNTHA093

#endif //ASSIGNMENT_3_PGMIMAGEPROCESSOR_H
