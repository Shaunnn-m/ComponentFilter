//
// Created by Thabang Mokoena on 2024/03/14.
//

#include <vector>
#include <tuple>
#include"ConnectedComponent.h"

namespace MKNTHA093 {

// Initialize static member
    int ConnectedComponent::nextID = 0;

// Default constructor
    ConnectedComponent::ConnectedComponent() : id(nextID++) {}

// Destructor
    ConnectedComponent::~ConnectedComponent() {}

// Copy constructor
    ConnectedComponent::ConnectedComponent(const ConnectedComponent& other)
            : id(other.id), pixels(other.pixels) {}

// Move constructor
    ConnectedComponent::ConnectedComponent(ConnectedComponent&& other) noexcept
            : id(other.id), pixels(std::move(other.pixels)) {
        other.id = 0; // Reset the other's ID
    }

// Copy assignment operator
    ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other) {
        if (this != &other) { // Protect against self-assignment
            id = other.getID();
            pixels = other.getPixels();
        }
        return *this;
    }

// Move assignment operator
    ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other) noexcept {
        if (this != &other) {
            id = other.id;
            pixels = std::move(other.pixels);
            other.id = 0; // Reset the other's ID
        }
        return *this;
    }

// Additional method implementations
    void ConnectedComponent::addPixel(int x, int y) {
        pixels.push_back(std::make_tuple(x, y));
    }

    const std::vector<std::tuple<int, int>>& ConnectedComponent::getPixels() const {
        return pixels;
    }

    int ConnectedComponent::getPixelCount() const {
        return pixels.size();
    }

    int ConnectedComponent::getID() const {
        return id;
    }

} // MKNTHA093