#pragma once
#include "Vector3.h"

// Obstacle class represents a simple 3D axis-aligned bounding box (AABB) obstacle
class Obstacle {
public:
    Vector3 position; // Center position of the obstacle
    Vector3 size;     // Half-size of the obstacle along each axis (x, y, z)

    // Constructor with default position at origin and default half-size of 1 in each axis
    Obstacle(Vector3 pos = Vector3(0, 0, 0), Vector3 sz = Vector3(1, 1, 1))
        : position(pos), size(sz) {
    }

    // Checks if a given point is inside the obstacle using AABB collision detection
    bool containsPoint(const Vector3& point) const {
        return (point.x >= position.x - size.x && point.x <= position.x + size.x) &&
            (point.y >= position.y - size.y && point.y <= position.y + size.y) &&
            (point.z >= position.z - size.z && point.z <= position.z + size.z);
    }
};
