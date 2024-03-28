//
// Created by Thabang Mokoena on 2024/03/14.
//

#ifndef ASSIGNMENT_3_CONNECTEDCOMPONENT_H
#define ASSIGNMENT_3_CONNECTEDCOMPONENT_H


#include <vector>
#include <utility> // For std::pair

namespace MKNTHA093 {




    class ConnectedComponent {
    public:
        // Default constructor
        ConnectedComponent();

        // Destructor
        ~ConnectedComponent();

        // Copy constructor
        ConnectedComponent(const ConnectedComponent& other);

        // Move constructor
        ConnectedComponent(ConnectedComponent&& other) noexcept;

        // Copy assignment operator
        ConnectedComponent& operator=(const ConnectedComponent& other);

        // Move assignment operator
        ConnectedComponent& operator=(ConnectedComponent&& other) noexcept;

        // Additional methods and members as needed
        void addPixel(int x, int y);
        int getPixelCount() const;
        int getID() const;
        // Provides read-only access to the pixels vector
        const std::vector<std::tuple<int, int>>& getPixels() const;


    private:
        int id; // Unique identifier
        std::vector<std::tuple<int, int>> pixels; // Pixels in the component

        static int nextID; // Static member to generate unique IDs
    };



} // MKNTHA093

#endif //ASSIGNMENT_3_CONNECTEDCOMPONENT_H
