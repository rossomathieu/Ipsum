/*
 * GLRenderer.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: ross
 */

#include "GLRenderer.h"

GLRenderer::GLRenderer() {
	// TODO Auto-generated constructor stub

}

GLRenderer::~GLRenderer() {
	// TODO Auto-generated destructor stub
}

void GLRenderer::init(AERenderWindow &window) {

	init = false;
	renderWindow = window;

	std::string version = glGetString(GL_VERSION);

	//Check to make sure we support the minimum requirement of OpenGL 3.3.
	int major = version[0] - '0';
	int minor = version[2] - '0';

	if(major < 3) {
		//GPU/Driver does not support OpenGL 3.x
		std::runtime_error(std::string("GLRenderer::init(): Device does not support OpenGL 3.x!"));
	}

	if(major == 3 && minor < 3) {
		//GPU/Driver does not support OpenGL 3.3
		std::runtime_error(std::string("GLRenderer::init(): Device does not support OpenGL 3.3!"));
	}

	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK) {
		//GLEW did not initialize properly
		std::runtime_error(std::string("GLRenderer::init(): Cannot initialize GLEW!"));
	}
}

void GLRenderer::release() {

	delete currentShader;
	delete debugDrawShader;
}

bool GLRenderer::hasInitialized() const {

	return init;
}

void GLRenderer::swapBuffers() {

	renderWindow->swapBuffers();
}

void GLRenderer::resize(int x, int y) {

	width = std::max(x, 1);
	height = std::max(y, 1);
	glViewport(0, 0, width, height);
}

void GLRenderer::updateScene(float deltaTime) {


}

void GLRenderer::updateShaderMatrices() {

	if(currentShader) {

		glUniformMatrix4fv(glGetUniformLocation(currentShader), "modelMatrix"), 1, false, (float*)&modelMatrix);

	}
}

