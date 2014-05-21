/*
 * AEDebugDraw.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: ross
 */

#include <cmath>
#include "libgraphics/libdebug/AEDebugDraw.h"
#include "../../libfoundation/Common.h"

AEDebugDraw::AEDebugDraw() {
	// TODO Auto-generated constructor stub

}

AEDebugDraw::~AEDebugDraw() {
	// TODO Auto-generated destructor stub
}

void AEDebugDraw::addDebugLine(const aem::vec3 &fromPos, const aem::vec3 &toPos,
		aeg::AEColor color, float lineWidth) {

	addLine(fromPos, toPos, color);
}

void AEDebugDraw::addDebugCross(const aem::vec3 &pos, aeg::AEColor color, float size) {

	addLine(pos, pos - aem::vec3(size, 0, 0), color);
	addLine(pos, pos - aem::vec3(-size, 0, 0), color);

	addLine(pos, pos - aem::vec3(0, -size, 0), color);
	addLine(pos, pos - aem::vec3(0, size, 0), color);

	addLine(pos, pos - aem::vec3(0, 0, -size), color);
	addLine(pos, pos - aem::vec3(0, 0, size), color);
}

//Currently incorrect.
//Trouble determing smallest axis.. also, need to implement ability to ^ matrices or make a nasty hack
//A nasty hack is looking likely....
//Brendan would be proud lol
void AEDebugDraw::addDebugCircle(const aem::vec3 &centerPos, const aem::vec3 &planeNormal, float radius, aeg::AEColor color) {

	int smallestAxis = 0;
	if(std::abs(planeNormal.y) < std::abs(planeNormal.x)) smallestAxis = 1;

	aem::vec3 base1(0, 0, 0);
	aem::vec3 ortho1;
	ortho1.normalize();
	aem::vec3 ortho2;
	ortho2.normalize();
	unsigned int numPoints = 32;

	for(unsigned int i = 0; i < numPoints; ++i) {

		float angle = (static_cast<float>(i) / static_cast<float>(numPoints)) * PI * 2;
		aem::vec3 v = centerPos + ortho1 * std::sin(angle) * -1 * radius + ortho2 * std::cos(angle) * radius;

	}
}

void AEDebugDraw::addDebugTriangle(const aem::vec3 &v0, const aem::vec3 &v1, const aem::vec3 &v2, aeg::AEColor color, float lineWidth) {

	addLine(v0, v1, color);
	addLine(v1, v2, color);
	addLine(v2, v0, color);
}

void AEDebugDraw::addDebugAxes(const aem::mat4 &transform, aeg::AEColor color, float size) {

	float arrowHead = 0.1f;
	aem::vec3 v0(0, 0, 0);
	aem::vec3 v1(0, 0, size);
	aem::vec3 v2(0, size, 0);
	aem::vec3 v3(size, 0, 0);

	aem::vec3 v1a(arrowHead, 0, size - arrowHead);
	aem::vec3 v1b(-arrowHead, 0, size - arrowHead);

	aem::vec3 v2a(arrowHead, size - arrowHead, 0);
	aem::vec3 v2b(-arrowHead, size - arrowHead, 0);

	aem::vec3 v3a(size - arrowHead, 0, arrowHead);
	aem::vec3 v3b(size - arrowHead, 0, -arrowHead);

	addLine(transform * v0, transform * v1, color);
	addLine(transform * v0, transform * v2, color);
	addLine(transform * v0, transform * v3, color);

	addLine(transform * v1, transform * v1a, color);
	addLine(transform * v1, transform * v1b, color);

	addLine(transform * v2, transform * v2a, color);
	addLine(transform * v2, transform * v2b, color);

	addLine(transform * v3, transform * v3a, color);
	addLine(transform * v3, transform * v3b, color);
}

void AEDebugDraw::addDebugOBB(const aem::mat4 &centerTransform,
		const aem::vec3 &scaleXYZ, aeg::AEColor color, float lineWidth) {

	aem::vec3 v000(-scaleXYZ.x * 0.5f, -scaleXYZ.y * 0.5f, -scaleXYZ.z * 0.5f);
	aem::vec3 v001(-scaleXYZ.x * 0.5f, scaleXYZ.y * 0.5f, -scaleXYZ.z * 0.5f);
	aem::vec3 v010(scaleXYZ.x * 0.5f, scaleXYZ.y * 0.5f, -scaleXYZ.z * 0.5f);
	aem::vec3 v011(scaleXYZ.x * 0.5f, -scaleXYZ.y * 0.5f, -scaleXYZ.z * 0.5f);

	aem::vec3 v100(-scaleXYZ.x * 0.5f, -scaleXYZ.y * 0.5f, scaleXYZ.z * 0.5f);
	aem::vec3 v101(-scaleXYZ.x * 0.5f, scaleXYZ.y * 0.5f, scaleXYZ.z * 0.5f);
	aem::vec3 v110(scaleXYZ.x * 0.5f, scaleXYZ.y * 0.5f, scaleXYZ.z * 0.5f);
	aem::vec3 v111(scaleXYZ.x * 0.5f, -scaleXYZ.y * 0.5f, scaleXYZ.z * 0.5f);

	v000 = centerTransform * v000;
	v001 = centerTransform * v001;
	v010 = centerTransform * v010;
	v011 = centerTransform * v011;
	v100 = centerTransform * v100;
	v101 = centerTransform * v101;
	v110 = centerTransform * v110;
	v111 = centerTransform * v111;

	addLine(v000, v001, color);
	addLine(v001, v010, color);
	addLine(v010, v011, color);
	addLine(v011, v000, color);

	addLine(v100, v101, color);
	addLine(v101, v110, color);
	addLine(v110, v111, color);
	addLine(v111, v100, color);

	addLine(v000, v100, color);
	addLine(v001, v101, color);
	addLine(v010, v110, color);
	addLine(v011, v111, color);

}

void AEDebugDraw::addDebugAABB(const aem::vec3 &minCoords,
		const aem::vec3 &maxCoords, aeg::AEColor color, float lineWidth) {

	aem::vec3 v000 = minCoords;
	aem::vec3 v111 = maxCoords;
	aem::vec3 v001(minCoords.x, minCoords.y, maxCoords.z);
	aem::vec3 v010(minCoords.x, maxCoords.y, maxCoords.z);
	aem::vec3 v100(maxCoords.x, minCoords.y, minCoords.z);
	aem::vec3 v011(minCoords.x, maxCoords.y, maxCoords.z);
	aem::vec3 v101(maxCoords.x, minCoords.y, maxCoords.z);
	aem::vec3 v110(maxCoords.x, maxCoords.y, minCoords.z);

	addLine(v000, v100, color);
	addLine(v100, v101, color);
	addLine(v101, v001, color);
	addLine(v001, v000, color);

	addLine(v001, v011, color);
	addLine(v101, v111, color);
	addLine(v100, v110, color);
	addLine(v000, v010, color);

	addLine(v011, v111, color);
	addLine(v010, v011, color);
	addLine(v111, v110, color);
	addLine(v010, v110, color);
}

//Needs Implementation.
//Holding off until font classes and manager have been implemented.
void AEDebugDraw::addDebugString(const aem::vec3 &pos, const char* text, aeg::AEColor color) {


}

inline void AEDebugDraw::addLine(const aem::vec3 &fromPos, const aem::vec3 &toPos, aeg::AEColor color) {

	lines.push_back(fromPos);
	lines.push_back(toPos);

	colors.push_back(color);
}

inline void AEDebugDraw::clear() {

	lines.clear();
	colors.clear();
}



