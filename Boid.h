#pragma once
#include "Vector3.h"
#include <vector>
#include "Obstacle.h"

// Class representing an individual boid in 3D space
class Boid {
public:
    Vector3 position;      // Current position of the boid
    Vector3 velocity;      // Current velocity vector
    Vector3 acceleration;  // Accumulated steering forces applied per update

    float maxSpeed;        // Maximum allowed speed for the boid
    float maxForce;        // Maximum steering force applied per frame

    float bankAngle;       // Current banking angle for visual tilting
    float bankFactor;      // Factor to control banking intensity

    // Constructor to initialize a boid at a specific position with default parameters
    Boid(Vector3 pos = Vector3(0, 0, 0));

    // Apply an external force to the boid, accumulated into acceleration
    void applyForce(const Vector3& force);

    // Update the boid's velocity and position based on current acceleration and delta time
    void update(float dt);

    // Compute and apply flocking forces: separation, alignment, and cohesion
    void flock(const std::vector<Boid>& boids);

    // Apply forces to keep the boid within the world boundaries
    void borders(float width, float height, float depth);

    // Separation: compute a steering force to avoid crowding nearby boids
    Vector3 separation(const std::vector<Boid>& boids);

    // Alignment: compute a steering force to align with nearby boids' average heading
    Vector3 alignment(const std::vector<Boid>& boids);

    // Cohesion: compute a steering force to move toward the average position of neighbors
    Vector3 cohesion(const std::vector<Boid>& boids);

    // Predictive obstacle avoidance for cube obstacles
    void avoidObstacles(const std::vector<Obstacle>& obstacles, float lookAhead = 1.0f);

    // Update banking angle based on turning and velocity changes (visual effect)
    void updateBanking(float dt);
};
