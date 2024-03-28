//
// Created by Thabang Mokoena on 2024/03/14.
//

#include "PGMimageProcessor.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>

namespace MKNTHA093 {

    PGMimageProcessor::PGMimageProcessor(const std::string& filename) : inputFileName(filename), width(0), height(0) {}

    PGMimageProcessor::~PGMimageProcessor() {}

    bool PGMimageProcessor::readImage() {
        std::ifstream file(inputFileName, std::ios::binary);
        if (!file) {
            std::cerr << "Unable to open file: " << inputFileName << std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line); // Read magic number
        bool isPGM = (line == "P5");

        // Skip comments
        while (file.peek() == '#') std::getline(file, line);

        file >> width >> height;
        int maxVal;
        file >> maxVal;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the binary data

        if (isPGM) {

            imageData.resize(width * height);
            file.read(reinterpret_cast<char*>(imageData.data()), imageData.size());

        }

        return true;
    }



    bool PGMimageProcessor::writeComponents(const std::string& outFileName) const {
        // Initialize new image data with all pixels set to background (0)
        std::vector<unsigned char> newImageData(width * height, 0);

        // For each component, set its pixels to foreground (255)
        for (const auto& component : components) {
            const auto& pixels = component->getPixels(); // Assuming ConnectedComponent has a method getPixels()
            for (const auto& pixel : pixels) {
                int x = std::get<0>(pixel);
                int y = std::get<1>(pixel);
                newImageData[y * width + x] = 255;
            }
        }

        // Write the new image data to a PGM file
        std::ofstream outFile(outFileName, std::ios::binary);
        if (!outFile) {
            std::cerr << "Unable to open file for writing: " << outFileName << std::endl;
            return false;
        }

        // Write PGM header
        outFile << "P5\n" << width << " " << height << "\n255\n";

        // Write new image data
        outFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());

        return true;
    }


    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize) {


        std::vector<bool> visited(width * height, false);


        for (auto& pixel : imageData) {
            pixel = (pixel >= threshold) ? 255 : 0;
        }


        // Directions for N, E, S, W
        std::vector<int> dx = {-1, 0, 1, 0};
        std::vector<int> dy = {0, -1, 0, 1};

        // Clear previous components
        components.clear();

        // Component detection using BFS
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (imageData[y * width + x] == 255 && !visited[y * width + x]) {
                    std::queue<std::pair<int, int>> q;
                    q.push({x, y});
                    visited[y * width + x] = true;
                    auto component = std::make_shared<ConnectedComponent>();;

                    while (!q.empty() && imageData[y * width + x] == 255) {
                        auto [cx, cy] = q.front(); q.pop();
                        component->addPixel(cx, cy);

                        for (int i = 0; i < 4; ++i) {
                            int nx = cx + dx[i], ny = cy + dy[i];
                            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny * width + nx] && imageData[ny * width + nx] == 255) {
                                q.push({nx, ny});
                                visited[ny * width + nx] = true;
                            }
                        }
                    }

                    if (component->getPixelCount() >= static_cast<int>(minValidSize)) {
                        // Create and store the component if it meets the size criteria
                        components.push_back(std::move(component));
                    }
                    else{
                        continue;
                    }
                }
            }
        }

        return components.size();
    }

    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize) {
        std::vector<std::shared_ptr<ConnectedComponent>> filteredComponents;

        for (auto& component : components) {
            int size = component->getPixelCount(); // Assuming ConnectedComponent has a method getPixelCount()
            if (size >= minSize && size <= maxSize) {
                filteredComponents.push_back(component);
            }
        }

        // Replace the original components with the filtered list
        components.swap(filteredComponents);

        return components.size();
    }

    int PGMimageProcessor::getLargestSize() const {
        int largestSize = 0;
        for (const auto& component : components) {
            int componentSize = component->getPixelCount(); // Assuming getPixelCount() exists and returns the size.
            if (componentSize > largestSize) {
                largestSize = componentSize;
            }
        }
        return largestSize;
    }

    void PGMimageProcessor::printComponentData(const std::shared_ptr<ConnectedComponent> & theComponent) const {
        // Assuming theComponent has getID() and getPixelCount() methods
        std::cout << "Component ID: " << theComponent->getID()
                  << ", Number of pixels: " << theComponent->getPixelCount() << std::endl;
    }

    int PGMimageProcessor::getSmallestSize() const {
        if (components.empty()) {
            return 0; // Or -1 to indicate no components.
        }

        int smallestSize = components.front()->getPixelCount(); // Initialize with the size of the first component.
        for (const auto& component : components) {
            int componentSize = component->getPixelCount(); // Assuming getPixelCount() returns the number of pixels in the component.
            if (componentSize < smallestSize) {
                smallestSize = componentSize;
            }
        }
        return smallestSize;
    }

    const std::vector<std::shared_ptr<ConnectedComponent>>& PGMimageProcessor::getComponents() const {
        return components;
    }



    int PGMimageProcessor::getComponentCount() const {
        return components.size();
    }


} // MKNTHA093