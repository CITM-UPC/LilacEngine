#include "GraphicObject.h"

GraphicObject::GraphicObject() : _transform(glm::identity<mat4d>()) {}
GraphicObject::GraphicObject(std::shared_ptr<Graphic> graphic) : _transform(glm::identity<mat4d>()), _graphic(graphic) {}

void GraphicObject::paint() const {
	glPushMatrix();
	glMultMatrixd(&_transform[0].x);
	if (_graphic.get()) _graphic->draw();
	for (auto& child : children()) ((GraphicObject&)child).paint();
	glPopMatrix();
}