/*
* Name: Simon Fliegel
  s-Nummer: s85344
  Matr.-Nr: 53043
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glew.h>
#include <freeglut.h>

#include "models/base_models/Shape.h";
#include "models/base_models/Cube.h";
#include "models/base_models/Sphere.h";
#include "models/base_models/Plain.h"
#include "models/SolarSystem.h";

#include "util/FlyCamera.h";
#include "util/Shader.h";

const char* VERTEX_SHADER = "shaders/vertexShader.vs";
const char* FRAGMENT_SHADER = "shaders/fragmentShader.fs";

std::shared_ptr<Shader> shader;

GLint windowWidth = 800;
GLint windowHeight = 600;

auto flyCamera = FlyCamera();
bool mouseMovedByUser = true;

// Objects
Cube cube = Cube();
Sphere sphere = Sphere();
Plain plain = Plain();
std::unique_ptr<SolarSystem> solarSystem;

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;





void init(void)
{
	shader = std::make_shared<Shader>(VERTEX_SHADER, FRAGMENT_SHADER); // needs to be here, because of glewInit
	shader->use();
	flyCamera = FlyCamera();

	lastFrame = glutGet(GLUT_ELAPSED_TIME);

	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	solarSystem = std::make_unique<SolarSystem>(*shader);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);
	
	// maybe extract to method?
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = flyCamera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(flyCamera.getZoom()), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	// draw solar system
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader->setMat4("model", model);
	solarSystem->draw();

	glFlush();
}

void reshape(int w, int h) 
{
	windowWidth = w;
	windowHeight = h;
}

void idle(void)
{
	deltaTime = ((float) glutGet(GLUT_ELAPSED_TIME) - lastFrame) / 1000; // in seconds
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
		flyCamera.processKeyboardInput(ECameraMovementDirection::FORWARD, deltaTime);
	if (key == 's')
		flyCamera.processKeyboardInput(ECameraMovementDirection::BACKWARD, deltaTime);
	if (key == 'a')
		flyCamera.processKeyboardInput(ECameraMovementDirection::LEFT, deltaTime);
	if (key == 'd')
		flyCamera.processKeyboardInput(ECameraMovementDirection::RIGHT, deltaTime);

	// @TODO toggle light source

	glutPostRedisplay();
}

void mouseMovement(int x, int y)
{
	flyCamera.processMouseInput(x, y);
	//glutWarpPointer(windowWidth / 2, windowHeight / 2); TODO: fix this
	glutPostRedisplay();
}

void scroll(int button, int dir, int x, int y)
{
	flyCamera.processScrollInput(dir);

	glutPostRedisplay();
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 5);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
	//glutSetCursor(GLUT_CURSOR_NONE);
	glutMouseWheelFunc(scroll);
	glutMainLoop();
}
