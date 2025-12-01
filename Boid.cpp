#include "stdafx.h"
#include "Boid.h"
#include <cmath>

// Constructor to initialize a boid at a given position with default parameters
Boid::Boid(Vector3 pos)
    : position(pos), velocity(0, 0, 0), acceleration(0, 0, 0),
    maxSpeed(2.0f), maxForce(0.05f), bankAngle(0.0f), bankFactor(1.0f) {
    // position: initial location in 3D space
    // velocity: initial movement vector
    // acceleration: initially zero, accumulates forces
    // maxSpeed: upper limit for velocity magnitude
    // maxForce: upper limit for steering forces
    // bankAngle/bankFactor: used for banking/tilting behavior
}

// Apply a steering force to the boid, accumulating into acceleration
void Boid::applyForce(const Vector3& force) {
    acceleration += force;
}

// Update the boid's position and velocity based on acceleration and dt
void Boid::update(float dt) {
    velocity += acceleration * dt;              // Integrate acceleration into velocity
    if (velocity.length() > maxSpeed)           // Clamp velocity to maxSpeed
        velocity = velocity.normalized() * maxSpeed;
    position += velocity * dt;                  // Update position
    acceleration = Vector3(0, 0, 0);           // Reset acceleration for next frame
}

// Compute and apply flocking forces (separation, alignment, cohesion)
void Boid::flock(const std::vector<Boid>& boids) {
    float sepWeight = 1.5f;   // Weight for separation force
    float aliWeight = 1.0f;   // Weight for alignment force
    float cohWeight = 1.0f;   // Weight for cohesion force

    // Apply weighted forces to acceleration
    applyForce(separation(boids) * sepWeight);
    applyForce(alignment(boids) * aliWeight);
    applyForce(cohesion(boids) * cohWeight);
}

// Separation: steer to avoid crowding neighbors
Vector3 Boid::separation(const std::vector<Boid>& boids) {
    Vector3 steer(0, 0, 0);
    int count = 0;
    float desiredSeparation = 1.0f; // Minimum desired distance from neighbors

    for (auto& other : boids) {
        float d = (position - other.position).length();
        if (&other != this && d < desiredSeparation) {
            Vector3 diff = (position - other.position).normalized() / d;
            steer += diff;
            count++;
        }
    }
    if (count > 0) steer /= (float)count;       // Average steering
    if (steer.length() > 0) {
        steer = steer.normalized() * maxSpeed - velocity;  // Desired velocity change
        if (steer.length() > maxForce) steer = steer.normalized() * maxForce; // Clamp force
    }
    return steer;
}

// Alignment: steer towards the average heading of neighbors
Vector3 Boid::alignment(const std::vector<Boid>& boids) {
    Vector3 sum(0, 0, 0);
    int count = 0;
    float neighborDist = 3.0f; // Radius to consider neighbors

    for (auto& other : boids) {
        float d = (position - other.position).length();
        if (&other != this && d < neighborDist) {
            sum += other.velocity;
            count++;
        }
    }
    if (count > 0) {
        sum /= (float)count;             // Average velocity
        sum = sum.normalized() * maxSpeed;
        Vector3 steer = sum - velocity;  // Steering adjustment
        if (steer.length() > maxForce) steer = steer.normalized() * maxForce; // Clamp
        return steer;
    }
    return Vector3(0, 0, 0); // No neighbors: no alignment force
}

// Cohesion: steer towards the average position of neighbors
Vector3 Boid::cohesion(const std::vector<Boid>& boids) {
    Vector3 sum(0, 0, 0);
    int count = 0;
    float neighborDist = 3.0f; // Radius to consider neighbors

    for (auto& other : boids) {
        float d = (position - other.position).length();
        if (&other != this && d < neighborDist) {
            sum += other.position;
            count++;
        }
    }
    if (count > 0) {
        sum /= (float)count;                     // Average neighbor position
        Vector3 desired = (sum - position).normalized() * maxSpeed; // Desired velocity
        Vector3 steer = desired - velocity;      // Steering adjustment
        if (steer.length() > maxForce) steer = steer.normalized() * maxForce; // Clamp
        return steer;
    }
    return Vector3(0, 0, 0); // No neighbors: no cohesion force
}

// Apply forces to keep boids within the 3D world boundaries
void Boid::borders(float width, float height, float depth) {
    float margin = 1.0f;     // Distance from boundary to start turning
    float turnFactor = 0.05f; // Force magnitude for turning

    if (position.x < margin) applyForce(Vector3(turnFactor, 0, 0));
    if (position.y < margin) applyForce(Vector3(0, turnFactor, 0));
    if (position.z < margin) applyForce(Vector3(0, 0, turnFactor));

    if (position.x > width - margin) applyForce(Vector3(-turnFactor, 0, 0));
    if (position.y > height - margin) applyForce(Vector3(0, -turnFactor, 0));
    if (position.z > depth - margin) applyForce(Vector3(0, 0, -turnFactor));
}

// Predictive obstacle avoidance for cube-shaped obstacles
void Boid::avoidObstacles(const std::vector<Obstacle>& obstacles, float lookAhead) {
    // Calculate future position along velocity vector
    Vector3 futurePos = position + velocity.normalized() * lookAhead;

    // Check collision with each obstacle
    for (auto& obs : obstacles) {
        if (obs.containsPoint(futurePos)) {
            Vector3 diff = futurePos - obs.position;  // Vector away from obstacle center
            Vector3 steer = diff.normalized() * maxForce * 2.0f; // Strong avoidance force
            applyForce(steer);
        }
    }
}
