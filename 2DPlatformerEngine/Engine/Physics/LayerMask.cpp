#include "LayerMask.h"

namespace Physics {

	LayerMask::LayerMask() : mask(0) { }

	LayerMask::LayerMask(const uint& mask_) : mask(mask_) { }

	LayerMask::~LayerMask() { }

	bool LayerMask::GetLayer(const Layer& layer_) {
		return false;
	}

	void LayerMask::SetLayer(const Layer& layer, const bool& value) {
		// sets the layer to true
		if (value) mask |= 1 << layer;
		// sets the layer to false
		else	   mask &= ~(1 << layer);
	}

	bool LayerMask::operator==(const LayerMask& other) {
		return mask == other.mask;
	}

	bool LayerMask::operator!=(const LayerMask& other) {
		return mask != other.mask;
	}

	bool LayerMask::operator&&(const LayerMask& other) {
		return mask & other.mask;
	}

}