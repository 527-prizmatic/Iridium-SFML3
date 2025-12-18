/*
#ifndef IRIDIUM_RESOURCES_HPP_
#define IRIDIUM_RESOURCES_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	template <typename T>
	concept LoadableFromFile = requires(T _a) {
		_a.loadFromFile(std::filesystem::path{});
	};

	class Resource {
	public:
		bool LoadFromFile(std::filesystem::path _path) {
			return this->m_resource->LoadFromFile(_path);
		}

		[[nodiscard]] const auto Get() {
			return this->m_resource->Get();
		}

	private:
		class ResourceConcept {
		public:
			virtual bool LoadFromFile(std::filesystem::path _path) = 0;
		};

		template <LoadableFromFile T>
		class ResourceModel : public ResourceConcept {
		public:
			ResourceModel() : m_resource { std::make_unique<T>(); } {}

			/// @note To be specialized for each available resource type
			bool LoadFromFile(std::filesystem::path _path) {
				if (!this->m_resource)
					this->m_resource = std::make_unique<T>();
					
				return this->m_resource->loadFromFile(_path);
			}

			[[nodiscard]] const std::weak_ptr<T> Get() {
				return this->m_resource;
			}

		private:
			std::shared_ptr<T> m_resource;
		};

		std::unique_ptr<ResourceConcept> m_resource;	
	};
}




#endif // IRIDIUM_RESOURCES_HPP_
*/