# CS6555 Assignment 4 - Behavioral Motion Control System

This project implements a behavioral motion control system inspired by Reynolds' flocking algorithm. Boids navigate a 3D environment and interact with both each other and environmental obstacles.

## Overview

Boids in the system compute their motion by combining three forces: separation, alignment, and cohesion. Separation prevents crowding, alignment steers a boid toward the average heading of its neighbors, and cohesion moves the boid toward the average position of nearby boids. These forces are combined in a weighted sum to produce smooth flocking behavior.

Boids move in a 3D space of configurable dimensions. Velocity is clamped to a maximum speed, and forces are limited by a maximum acceleration to maintain realistic motion. Environmental obstacles are implemented as axis-aligned cubes. Boids perform predictive collision detection by checking a point ahead along their velocity vector and steering away if a collision is likely. 

Boids are visually represented as cones using OpenGL, while obstacles are displayed as scaled cubes. The system uses GLUT to create a 3D scene with lighting, depth testing, and a perspective camera. The framework also includes variables for banking, allowing boids to rotate along turns according to their curvature, although this effect is not fully implemented.

## Project Structure

The project consists of the following key classes:

- **Vector3:** Provides basic 3D vector operations including addition, subtraction, normalization, and dot/cross products.
- **Boid:** Implements individual boid behavior, including flocking, movement updates, boundary handling, and obstacle avoidance.
- **Obstacle:** Represents environmental obstacles as cubes and provides point-containment checks.
- **BoidEngine:** Manages the collection of boids, updates their states each timestep, and applies flocking and obstacle forces.

The main program initializes the scene by creating a set number of boids and obstacles. OpenGL lighting, camera, and display callbacks are configured, and the simulation continuously updates the boids using `BoidEngine::update()` while rendering the scene each frame.

## Features Implemented

- Core flocking behaviors: separation, alignment, and cohesion
- 3D movement with speed and force limits
- Axis-aligned cube obstacles with predictive collision avoidance
- OpenGL rendering of boids and obstacles
- Basic framework for banking along turns

## Requirements

- C++ compiler supporting C++11 or later
- OpenGL and GLUT libraries

## How to Run

1. Compile all source files: `main.cpp`, `Boid.cpp`, `BoidEngine.cpp`, `Vector3.h`, `Boid.h`, `BoidEngine.h`, and `Obstacle.h`.
2. Run the executable.
3. Observe the boids flocking in 3D space while avoiding cube obstacles.

## Notes

- The banking effect is not fully implemented but can be extended using the `bankAngle` and `bankFactor` variables in the `Boid` class.
- Obstacles are cubes in this implementation, but the system can be extended to other shapes.
- The code is commented to help understand the logic of flocking behaviors and obstacle avoidance.

