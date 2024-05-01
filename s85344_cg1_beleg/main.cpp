/*
* Name: Simon Fliegel
  s-Nummer: s85344
  Matr.-Nr: 53043
*/

#include <iostream>
#include <memory>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glew.h>
#include <freeglut.h>

#include "models/base_models/Cube.h";
#include "models/base_models/Sphere.h";
#include "models/base_models/Plain.h"
#include "models/SolarSystem.h";
#include "models/RoomWithLamp.h";

#include "util/cams/FlyCamera.h";
#include "util/cams/FixedCamera.h";
#include "util/Shader.h";


// settings
const GLuint FPS = 60; // only in idle
// true fps measurement
double lastTime = 0;
unsigned int frameCounter = 0;

GLint windowWidth = 1000;
GLint windowHeight = 600;

// shaders
const char* const ROOM_WITH_LAMP_VS = "shaders/roomWithLamp.vs";
const char* const ROOM_WITH_LAMP_FS = "shaders/roomWithLamp.fs";
const char* const SOLARSYSTEM_VS= "shaders/solarSystem.vs";
const char* const SOLARSYSTEM_FS = "shaders/solarSystem.fs";

std::unique_ptr<Shader> roomWithLampShader;
std::unique_ptr<Shader> solarSystemShader;
Cylinder cylinder;

// camera
FlyCamera flyCamera;
FixedCamera fixedCamera;

//bool mouseMovedByUser = true;

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// models
std::unique_ptr<SolarSystem> solarSystem;
std::unique_ptr<RoomWithLamp> roomWithLamp;

// function declarations
void drawViewPort(AbstractCamera& cam, int x, int y, int width, int height);
void drawScene(float deltaTime, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& camPos);


/// <summary>
/// displays the fps in the window title
/// </summary>
/// <param name="updateInterval">interval in seconds to update the fps</param>
static void displayFps(unsigned int updateInterval)
{
	double delta = (glutGet(GLUT_ELAPSED_TIME) - lastTime) / 1000;
	if (delta > updateInterval)
	{
		auto fps = int(frameCounter / delta);
		std::string windowTitle = "s85344_cg1_beleg - FPS: " + std::to_string(fps);
		glutSetWindowTitle(windowTitle.c_str());
		lastTime = glutGet(GLUT_ELAPSED_TIME);
		frameCounter = 0;
	}
	else
	{
		frameCounter++;
	}
}

/// <summary>
/// initializes glut
/// </summary>
void init(void)
{
	displayFps(0.0f); // initial call to update window title

	roomWithLampShader = std::make_unique<Shader>(ROOM_WITH_LAMP_VS, ROOM_WITH_LAMP_FS); // needs to be here, because of glewInit
	solarSystemShader = std::make_unique<Shader>(SOLARSYSTEM_VS, SOLARSYSTEM_FS);

	// camera setup
	flyCamera.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	fixedCamera.setPosition(glm::vec3(0.0f, 0.8f, 0.3f));
	fixedCamera.setFront(glm::vec3(0.0f, -1.0f, 0.0f));
	fixedCamera.setFov(60.0f);

	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	solarSystem = std::make_unique<SolarSystem>(*solarSystemShader);
	roomWithLamp = std::make_unique<RoomWithLamp>(*roomWithLampShader);
}

/// <summary>
/// glut callback for displaying the scene
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	deltaTime = (glutGet(GLUT_ELAPSED_TIME) - lastFrame) / 1000; // in seconds, in theory 1/FPS in idle
	lastFrame = glutGet(GLUT_ELAPSED_TIME);

	int widthMainWindow = 3 * (windowWidth / 5);
	int widthSecondaryWindow = 2 * (windowWidth / 5);

	drawViewPort(flyCamera, 0, 0, widthMainWindow, windowHeight);
	drawViewPort(fixedCamera, widthMainWindow, 0, widthSecondaryWindow, windowHeight);

	displayFps(1.0f);

	glFlush();
}

/// <summary>
/// draws the view port with given camera and dimensions
/// </summary>
void drawViewPort(AbstractCamera& cam, int x, int y, int width, int height)
{
	glViewport(x, y, width, height);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = cam.getViewMatrix();
	glm::mat4 projection = cam.getProjectionMatrix(width, height);
	glm::vec3 pos = cam.getPosition();

	drawScene(deltaTime, model, view, projection, pos);
}

/// <summary>
/// draws the entire scene with given model, view and projection matrix and camera position
/// </summary>
/// <param name="deltaTime">for constant animantion speed independent of fps</param>
/// <param name="model">for transformation of the scene</param>
/// <param name="view">camera view matrix</param>
/// <param name="projection">camera projection matrix</param>
/// <param name="pos">camera position</param>
void drawScene(float deltaTime, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& pos) {

	// ####################### draw solar system #######################
	solarSystemShader->use();
	solarSystemShader->setMat4("view", view);
	solarSystemShader->setMat4("projection", projection);

	glm::mat4 modelSolarSystem = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	modelSolarSystem = glm::rotate(modelSolarSystem, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.5f));
	solarSystemShader->setMat4("model", modelSolarSystem);
	solarSystem->draw(modelSolarSystem, deltaTime);
	// update light position
	solarSystemShader->setVec3("lightPos", solarSystem->getLightPosition());


	// ####################### draw room with lamp #######################
	roomWithLampShader->use();
	roomWithLampShader->setMat4("view", view);
	roomWithLampShader->setMat4("projection", projection);

	glm::mat4 modelRoom = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	roomWithLampShader->setMat4("model", modelRoom);
	// add sun as external light source to room
	roomWithLamp->setExternalLightSource(solarSystem->getLightPosition(), solarSystem->getExternalLightColorOfSun());
	roomWithLamp->draw(modelRoom);
	// update light position
	roomWithLampShader->setVec3("primaryLightPos", roomWithLamp->getLightPosition());
	roomWithLampShader->setVec3("viewPos", pos);
}

/// <summary>
/// glut callback when window is resized
/// </summary>
void reshape(int w, int h) 
{
	windowWidth = w;
	windowHeight = h;
}

/// <summary>
/// glut callback when key is pressed
/// </summary>
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
	if (key == 32) // ASCII for space
		roomWithLamp->toggleLight();
	if (key == 27) // ASCII for escape
		glutLeaveMainLoop();

	glutPostRedisplay();
}

/// <summary>
/// glut callback when mouse is moved
/// </summary>
void mouseMovement(int x, int y)
{
	flyCamera.processMouseInput(x, y);
	//glutWarpPointer(windowWidth / 2, windowHeight / 2); TODO: fix this
	glutPostRedisplay();
}

/// <summary>
/// glut callback when mouse wheel is scrolled
/// </summary>
void scroll(int, int dir, int, int)
{
	flyCamera.processScrollInput(dir);
	glutPostRedisplay();
}

/// <summary>
/// glut callback for updating the display
/// </summary>
void updateDisplay(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, updateDisplay, 0);
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
	
	if (glewInit())
	{
		printf("Error");
	}
	
	init();

	// settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// callbacks
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
	//glutSetCursor(GLUT_CURSOR_NONE);
	glutMouseWheelFunc(scroll);
	glutTimerFunc(1000 / FPS, updateDisplay, 0);

	glutMainLoop();
}


