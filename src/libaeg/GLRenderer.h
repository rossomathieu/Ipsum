/*
 * GLRenderer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: ross
 */

#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "AERenderer.h"

class GLRenderer : public AERenderer {
public:
	GLRenderer();
	~GLRenderer();

	void init() = 0;
	void release() = 0;
	void clearScreen() = 0;
};

#endif /* GLRENDERER_H_ */
