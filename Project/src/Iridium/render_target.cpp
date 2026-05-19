#include "Iridium/render_target.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	void RenderTarget::expectValid() {
		if (!isValid()) {
			throw ir::Exceptions::InvalidRenderTarget{};
		}
	}
}