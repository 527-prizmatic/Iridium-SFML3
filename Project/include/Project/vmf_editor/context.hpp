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
		COMPONENT_VALIDATE,
		CONFIRM_MODEL_SAVE,
		CANCEL_MODEL_SAVE,
	};

	struct Context {
		float zoomFactor { 10.f };
		ir::Vector posOffset { 0.f, 0.f };

		std::vector<ir::render::Vertex> vertexList;
		std::list<vmf::UserEvent> events;

		ir::render::Component::Type drawingType { ir::render::Component::Type::TRIANGLE };

		sf::Color drawColor { sf::Color::White };

		bool saveMode { false };

		void registerEvent(vmf::UserEvent evt) { events.push_back(evt); }

		vmf::UserEvent popFirstEvent() {
			vmf::UserEvent evt = *events.begin();
			events.pop_front();
			return evt;
		}

		ir::render::Component inputToComponent() {
			using namespace ir::render;
			Component cmp {};

			cmp.type = drawingType;
			cmp.vertices.clear();
			for (auto& v : vertexList) {
				cmp.vertices.push_back(v);
			}

			return cmp;
		}
	};
}

#endif // PROJECT_EDITOR_CONTEXT_HPP_