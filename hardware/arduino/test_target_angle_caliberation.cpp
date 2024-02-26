#include <iostream>
#include <vector>

float getTargetAngle(float currentAngle, int direction);
// Define some example values for cardinal directions
float southAngle = 330.0;
float eastAngle = 212;
float northAngle = 160;
float westAngle = 87;

int main() {

    // Test the function with different input values
    std::vector<float> currentAngles = {161, 213, 331, 212, 159, 86, 329, 211};
    std::vector<int> actions = {0, 0, 0, 0, 1, 1, 1, 1};
    for (size_t i = 0; i < currentAngles.size(); ++i) {
        std::cout << "Test - Current Angle: " << currentAngles[i] << ", Direction: ";
        if (actions[i] == 0) {
            std::cout << "Left\n";
        } else {
            std::cout << "Right\n";
        }
        std::cout << "Target Angle: " << getTargetAngle(currentAngles[i], actions[i]) << "\n\n";
    }

    // Add more test cases as needed

    return 0;
}

float getTargetAngle(float currentAngle, int direction) {
    // Implement the logic for the getTargetAngle function here
    // ...

    // For testing purposes, you can use the provided logic as-is
    // Replace southAngle, eastAngle, northAngle, and westAngle with actual values
    if ((southAngle >= currentAngle) && (eastAngle <= currentAngle)) {
        // in between south and east
        if (direction == 0) {
            // Left Turn
            return southAngle;
        } else {
            // Right Turn
            return eastAngle;
        }
    } else if ((eastAngle >= currentAngle) && (northAngle <= currentAngle)) {
        // in between North and West
        if (direction == 0) {
            // Left Turn
            return eastAngle;
        } else {
            // Right Turn
            return northAngle;
        }
    } else if ((northAngle >= currentAngle) && (westAngle <= currentAngle)) {
        // in between North and West
        if (direction == 0) {
            // Left Turn
            return northAngle;
        } else {
            // Right Turn
            return westAngle;
        }
    } else {
        // in between South and West
        if (direction == 0) {
            // Left Turn
            return westAngle;
        } else {
            // Right Turn
            return southAngle;
        }
    }
}
