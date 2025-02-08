#include "World.h"
#include "Ray.h"

World::World() {
	return;
}

void World::Add(Object* obj) {
	this->objects.push_back(obj);
}

//void World::transform(Object obj) {
//	return;
//}

void World::transformAll() {
	//TODO IMPLEMENT
	return;
}

Object* World::spawn(Ray r) {
	//loop through objects in objects array.
	//if object intersects with ray, return object
	//else return NULL
	for (Object* obj : this->objects) {
		if (obj->Intersect(r)) {
			return obj;
		}
	}
	return nullptr;
}