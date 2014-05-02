/*
 * AERenderer.h
 *
 *  Created on: Apr 23, 2014
 *      Author: ross
 */

#ifndef AERENDERER_H_
#define AERENDERER_H_

#include "AEShader.h"
#include "../libaem/mat4x4.hpp"

class AERenderer {
public:
	AERenderer();
	virtual ~AERenderer();

	virtual void init() = 0;
	virtual void release() = 0;

	virtual void setCurrentShader(aeg::AEShader *shader) = 0;
	virtual void resize(int x, int y) = 0;
	virtual void clearScreen() = 0;
	virtual void renderScene() = 0;
	virtual void updateScene() = 0;

protected:

	aem::mat4 projMatrix;
	aem::mat4 modelMatrix;
	aem::mat4 viewMatrix;
	aem::mat4 textureMatrix;

	int width;
	int height;

	bool hasInitialized;
	aeg::AEShader *currentShader;
};

#endif /* AERENDERER_H_ */
