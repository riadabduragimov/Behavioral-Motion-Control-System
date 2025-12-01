#pragma once
#include <vector>
#include "Boid.h"
#include "Obstacle.h"

// BoidEngine class manages the simulation of all boids within a 3D environment
class BoidEngine {
public:
    std::vector<Boid> boids;   // Container holding all boids in the simulation
    float width, height, depth; // Dimensions of the 3D world

    // Constructor to initialize the engine with world dimensions
    BoidEngine(float w, float h, float d);

    // Add a new boid to the simulation
    void addBoid(const Boid& b);

    // Update all boids in the simulation
    // Applies flocking behavior, obstacle avoidance, and enforces boundaries
    void update(float dt, const std::vector<Obstacle>& obstacles);
};
