#pragma once
#include <bitset>
#include <cstdint>

#include "DiComponent.h"
#include "DiDefines.h"
namespace decs
{
    class DiComponentStorage
    {
        friend class DiWorld;

      public:
        DiComponentStorage();
        ~DiComponentStorage();

        void AddComponent(DiComponent &component, const uint32_t componentId);
        void RemoveComponent(const uint32_t componentId);
        DiComponent &GetComponent(const uint32_t componentId);

      private:
        void reset();
        bool _isInUse;
        std::bitset<Di_MAX_COMPONENTS> _usedComponents;
        DiComponent *_components[Di_MAX_COMPONENTS] = {nullptr};
    };
}