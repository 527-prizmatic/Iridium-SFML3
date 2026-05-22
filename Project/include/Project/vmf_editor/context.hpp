#ifndef PROJECT_EDITOR_CONTEXT_HPP_
#define PROJECT_EDITOR_CONTEXT_HPP_

#include "Project/ir_fwd.hpp"
#include "Iridium/rendering/model.hpp"
#include <list>

namespace vmf {
	enum class UserEvent {
		DEBUG,
		MODEL_SAVE,
		MODEL_DISCARD,
	};

	struct Context {
		float zoomFactor { 10.f };
		ir::Vector posOffset { 0.f, 0.f };

		std::vector<ir::render::Vertex> vertexList;
		std::list<vmf::UserEvent> events;
	};
}

#endif // PROJECT_EDITOR_CONTEXT_HPP_