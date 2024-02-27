/*
* Name: Simon Fliegel
  s-Nummer: s85344
  Matr.-Nr: 53043
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

#include "models/Shape.h";
#include "models/Cube.h";
#include "models/Sphere.h";

GLuint loadShaders(const char* vertexFilePath,
	const char* fragmentFilePath,
	const char* geometryFilePath,
	const char* tesscontrolFilePath,
	const char* tessevaluationFilePath,
	const char* computeFilePath);
GLint windowWidth = 800, windowHeight = 600;

// Objects
Cube cube;
Sphere sphere;

const float anglestep = 0.0001f;
float theta = 0.0f;


GLuint program;

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("shader.vs", "fragmentShader.fs", "", "", "", "");
	glUseProgram(program);

	sphere.createShape();
	sphere.bind();

}

void display(void)
{
	// render loop
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);

	auto center = glm::vec3(0.0f, 0.0f, 0.0f);

	const GLfloat scale = 0.4;
	GLint modelLoc = glGetUniformLocation(program, "model");

	GLfloat radius = 0.6f;
	auto model = glm::mat4(1.0f);
	
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	sphere.draw();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f + radius * cos(theta), 0.0f + radius * sin(theta), 0.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	sphere.draw();


	glFlush();
}

void reshape(int w, int h) 
{
	windowWidth = w;
	windowHeight = h;
}

void idle(void)
{
	theta += anglestep;
	if (theta > PI) theta = -PI;
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
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
}
