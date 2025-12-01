#include "stdafx.h"
#include "BoidEngine.h"

// Constructor to initialize the BoidEngine with the given world dimensions
BoidEngine::BoidEngine(float w, float h, float d) : width(w), height(h), depth(d) {}

// Add a new boid to the simulation
void BoidEngine::addBoid(const Boid& b) {
    boids.push_back(b);
}

// Update all boids in the simulation
// For each boid, compute flocking behavior, avoid obstacles, update position and velocity,
// and enforce world boundaries
void BoidEngine::update(float dt, const std::vector<Obstacle>& obstacles) {
    for (auto& b : boids) {
        b.flock(boids);                  // Apply separation, alignment, and cohesion
        b.avoidObstacles(obstacles);     // Avoid collisions with obstacles
        b.update(dt);                    // Update position and velocity
        b.borders(width, height, depth); // Keep boid within the world boundaries
    }
}
