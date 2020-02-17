#ifndef PHYSICS_LAYER_MASK_H
#define PHYSICS_LAYER_MASK_H
#include "../Common.h"

namespace Physics {

	typedef unsigned int Layer;

	struct LayerMask {

		LayerMask();
		LayerMask(const uint& mask_);
		~LayerMask();

		/// getters

		bool GetLayer(const Layer& layer_);
		QUICK_GETTER(uint, mask, Mask);
		
		/// setters

		void SetLayer(const Layer& layer, const bool& value);
		QUICK_SETTER(uint, mask, Mask);

		/// operators

		bool operator==(const LayerMask& other);
		bool operator!=(const LayerMask& other);
		bool operator&&(const LayerMask& other);

	private:
		// a 32 bit binary value 
		// stores info on layers (1 if active, 0 if inactive)
		uint mask;
	};

}

#endif // !PHYSICS_LAYER_MASK_H