#ifndef OBJECTS_ENTITY_H
#define OBJECTS_ENTITY_H
#include "../Common.h"
#include "../Math.h"
#include "../Physics/Box.h"

namespace Objects {

	class Entity {

		vec2 position;
		Physics::Box box;

	public:

		Entity() : position(0.0f), box() { }
		virtual ~Entity() { }

		/// getters

		QUICK_GETTER(vec2, position, Position);
		QUICK_GETTER(Physics::Box, box, Box);

		/// setters

		QUICK_SETTER(vec2, position, Position);
		QUICK_SETTER(Physics::Box, box, Box);

		/// virtual events

		virtual void OnCreate() { }
		virtual void OnDestroy() { }
		virtual void Update(const float& delta) { }
		virtual void Draw(const mat4& view, const mat4& proj) { }

		/// functions



		// TODO: add physics related functions

	};

}

#endif // !OBJECTS_ENTITY_H