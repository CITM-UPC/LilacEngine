#pragma once

#include "Globals.h"
#include "Graphic.h"

class GraphicObject
{
	glm::dmat4 _transform;
	std::set<GraphicObject*> _children;
	GraphicObject* _parent;
	std::shared_ptr<Graphic> _graphic;

public:
	GraphicObject();
	GraphicObject(std::shared_ptr<Graphic> graphic);

	inline glm::dvec3& pos() { return (glm::dvec3&)(_transform[3]); }
	inline void rotate(double rads, const glm::dvec3& axis) { _transform = glm::rotate(_transform, rads, axis); }

	void paint();

	void addChild(GraphicObject* child);
	void removeChild(GraphicObject* child);

	virtual ~GraphicObject();

private:
	GraphicObject(const GraphicObject&);
	GraphicObject& operator=(const GraphicObject&);

};
