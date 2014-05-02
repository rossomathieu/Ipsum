/*
 * AEDebugDraw.h
 *
 *  Created on: Apr 26, 2014
 *      Author: ross
 */

#ifndef AEDEBUGDRAW_H_
#define AEDEBUGDRAW_H_

#include <vector>
#include "../../libaem/vec3.hpp"
#include "../../libaem/mat4x4.hpp"
#include "../AEColor.hpp"

class AEDebugDraw {

public:

	AEDebugDraw();
	virtual ~AEDebugDraw();

	//Adds a line segment to the debug drawing queue.
	void addDebugLine(const aem::vec3 &fromPos, const aem::vec3 &toPos,
			aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float lineWidth = 1.0f);

	//Adds an axis-aligned cross to the debug drawing queue.
	void addDebugCross(const aem::vec3 &pos, aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float size = 1.0f);

	//Adds a circle to the debug drawing queue
	void addDebugCircle(const aem::vec3 &centerPos, const aem::vec3 &planeNormal,
			float radius, aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f));

	//Adds a wireframe sphere to the debug drawing queue.
	void addDebugSphere(const aem::vec3 &pos, aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float size = 1.0f);

	//Adds a set of coordinate axes depicting the position and orientation of the given transformation to the debug drawing queue
	void addDebugAxes(const aem::mat4 &transform, aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float size = 1.0f);

	//Adds a wireframe traingle to the debug drawing queue.
	void addDebugTriangle(const aem::vec3 &v0, const aem::vec3 &v1, const aem::vec3 &v2,
			aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float lineWidth = 1.0f);

	//Adds an axis-aligned bounding box to the debug draw queue.
	void addDebugAABB(const aem::vec3 &minCoords, const aem::vec3 &maxCoords,
			aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float lineWidth = 1.0f);

	//Adds an orientated bounding box to the debug draw queue.
	void addDebugOBB(const aem::mat4 &centerTransform, const aem::vec3 &scaleXYZ,
			aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f), float lineWidth = 1.0f);

	//Adds a text string to the debug draw queue.
	void addDebugString(const aem::vec3 &pos, const char* text, aeg::AEColor color = aeg::AEColor(1.0f, 1.0f, 1.0f, 1.0f));


	inline void clear();

private:

	std::vector<aem::vec3> lines;
	std::vector<aeg::AEColor> colors;

	inline void addLine(const aem::vec3 &fromPos, const aem::vec3 &toPos, aeg::AEColor color);
};

#endif /* AEDEBUGDRAW_H_ */
