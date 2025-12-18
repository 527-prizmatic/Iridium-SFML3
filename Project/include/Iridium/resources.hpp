/*
#ifndef IRIDIUM_RESOURCES_HPP_
#define IRIDIUM_RESOURCES_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/exceptions.hpp"

namespace Ir {
	namespace Resources {
		template <typename T>
		concept LoadableFromFile = requires(T _a) {
			_a.loadFromFile(std::filesystem::path{});
		};

		class ResourceBase {};

		template <typename T>
		class Resource : public ResourceBase {
		public:
			using ResourceType = T;

			Resource() : m_resource { std::make_shared<T>() } {}

			Resource(std::weak_ptr<T>&& _resource) : m_resource { std::move(_resource) } {}

			bool Load(std::filesystem::path _path) {
				return this->m_resource->loadFromFile(_path);
			}

			[[nodiscard]] const std::weak_ptr<T> Get() { return this->m_resource; }
		
		private:
			std::shared_ptr<T> m_resource;
		};

		template <> inline bool Resource<sf::Font>::Load(std::filesystem::path _path) {
				return this->m_resource->openFromFile(_path);
		}

		class ResourceManager {
		public:
			template <typename T>
			[[nodiscard]] bool Load(std::filesystem::path _path, std::string _name) {
				Resource<T> resource {};
				if (resource.Load(_path)) {
					this->g_resourceMap[_name].reset();
					this->g_resourceMap[_name] = std::make_shared<Resource<T>>(std::move(resource));
					return true;
				}
				else
					return false;
			}

			template <typename T>
			[[nodiscard]] auto Get(std::string_view _name) {
				if (std::weak_ptr<ResourceBase> res = this->g_resourceMap[_name.data()]; res.lock()) {
					auto lock = res.lock();
					return std::static_cast<std::shared_ptr<T>>(lock)->Get();
				}
				else {
					throw Ir::Exceptions::BadResourceID{_name};
				}
			}

			void Clear() {
				this->g_resourceMap.clear();
			}

		private:
			std::unordered_map<std::string, ResourceBase> g_resourceMap;
		};
	}
}


#endif // IRIDIUM_RESOURCES_HPP_
*/