#include "stdafx.h"
#include "BoidEngine.h"
#include <GL/glut.h>
#include <cstdlib>

// Initialize the Boid engine with a 3D space of size 10x10x10
BoidEngine engine(10.0f, 10.0f, 10.0f);

// Time step for updating the simulation
float dt = 0.05f;

// Container for obstacles in the environment
std::vector<Obstacle> obstacles;

// Initialize the scene by creating boids and obstacles
void initScene() {
    // Generate 50 boids with random positions in the 10x10x10 space
    for (int i = 0; i < 50; i++) {
        engine.addBoid(Boid(Vector3(rand() % 10, rand() % 10, rand() % 10)));
    }

    // Add cube-shaped obstacles with specified center positions and half-sizes
    obstacles.push_back(Obstacle(Vector3(5, 5, 5), Vector3(1, 1, 1)));
    obstacles.push_back(Obstacle(Vector3(2, 2, 7), Vector3(0.8f, 0.8f, 0.8f)));
}

// Set up OpenGL lighting for the scene
void setupLighting() {
    glEnable(GL_LIGHTING);      // Enable lighting calculations
    glEnable(GL_LIGHT0);        // Enable the first light source
    glEnable(GL_COLOR_MATERIAL); // Allow colors to affect material properties

    // Define light properties
    GLfloat lightPos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };

    // Apply the light properties
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
}

// Configure the camera perspective and position
void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.1, 50.0); // 60-degree FOV, aspect ratio, near/far planes
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 25, 5, 5, 0, 0, 1, 0); // Camera at (5,5,25) looking at (5,5,0), up along Z
}

// Draw a boid as a cone oriented along its velocity vector
void drawCone(const Vector3& position, const Vector3& velocity) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z); // Move to boid position

    // Determine orientation based on velocity
    Vector3 dir = velocity.normalized();
    float angle = atan2(dir.z, dir.x) * 180.0 / 3.14159f;
    glRotatef(-90, 1, 0, 0); // Align cone along X-axis
    glRotatef(angle, 0, 0, 1); // Rotate around Z to match velocity direction

    glColor3f(0.2f, 0.5f, 1.0f); // Set boid color
    glutSolidCone(0.1f, 0.3f, 8, 2); // Draw the cone
    glPopMatrix();
}

// Draw all obstacles in the scene as scaled cubes
void drawObstacles() {
    for (auto& obs : obstacles) {
        glPushMatrix();
        glTranslatef(obs.position.x, obs.position.y, obs.position.z);
        glColor3f(1.0f, 0.2f, 0.2f); // Obstacle color
        glScalef(obs.size.x * 2, obs.size.y * 2, obs.size.z * 2); // Scale to full size
        glutSolidCube(1.0f); // Draw a unit cube scaled to obstacle dimensions
        glPopMatrix();
    }
}

// Display callback for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
    glLoadIdentity();
    gluLookAt(5, 5, 25, 5, 5, 0, 0, 1, 0); // Set camera position and orientation

    drawObstacles(); // Render obstacles first

    // Render all boids in the scene
    for (auto& b : engine.boids) {
        drawCone(b.position, b.velocity);
    }

    glutSwapBuffers(); // Swap buffers for double buffering
}

// Timer callback to update simulation
void update(int value) {
    engine.update(dt, obstacles); // Update boids' positions and velocities
    glutPostRedisplay();           // Request a redraw
    glutTimerFunc(16, update, 0); // Call update roughly every 16 ms (~60 FPS)
}

// Entry point of the program
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Double-buffered RGB window with depth
    glutInitWindowSize(800, 600); // Window size
    glutCreateWindow("CS6555 Assignment 4 - Boids with Cube Obstacles");

    glEnable(GL_DEPTH_TEST);       // Enable depth testing for proper 3D rendering
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Background color

    setupLighting(); // Set up lights
    setupCamera();   // Set up camera
    initScene();     // Initialize boids and obstacles

    glutDisplayFunc(display);      // Set the display callback
    glutTimerFunc(16, update, 0);  // Start the simulation timer
    glutMainLoop();                // Enter the main event loop
    return 0;
}
