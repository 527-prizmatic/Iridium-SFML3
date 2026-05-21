#ifndef PROJECT_EDITOR_CONTEXT_HPP_
#define PROJECT_EDITOR_CONTEXT_HPP_

#include "Iridium/rendering/model.hpp"

namespace vmf {
	struct Context {
		float zoomFactor { 10.f };
		ir::Vector posOffset { 0.f, 0.f };

		std::vector<ir::render::Vertex> vertexList;
	};
}

#endif // PROJECT_EDITOR_CONTEXT_HPP_