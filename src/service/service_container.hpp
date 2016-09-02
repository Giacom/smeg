#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "service.hpp"

typedef std::unordered_map<std::type_index, std::unique_ptr<Service>> ServiceMap;

struct ServiceContainer {

    private:
        ServiceMap services;

    public:
        template<typename T>
        void Provide(std::unique_ptr<Service> &service) {
            auto type = std::type_index(typeid(T));
            services[type] = std::move(service);
        }

        template<typename T>
        T* Get() {
		    return dynamic_cast<T*>(services[std::type_index(typeid(T))].get());
        }
};