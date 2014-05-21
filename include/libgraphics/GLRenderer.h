/*
 * GLRenderer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: ross
 */

#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "AERenderer.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>

class GLRenderer : public AERenderer {
public:
	GLRenderer();
	~GLRenderer();

	void init(AERenderWindow &window);
	void resize(int x, int y);
	void release();
	void clearScreen();
	void updateScene(float deltaTime);
	void swapBuffers();
	void setCurrentShader(aeg::AEShader *shader);

	bool hasInitialized() const;
	void updateShaderMatrices();
};

#endif /* GLRENDERER_H_ */
