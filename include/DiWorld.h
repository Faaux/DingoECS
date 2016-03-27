#pragma once
#include <cstdint>
#include <vector>

#include "DiComponentStorage.h"
#include "DiEntityId.h"
#include "DiSystem.h"
namespace decs
{
    class DiEntity;
    class DiWorld
    {
      public:
        DiWorld(uint32_t chunkSize = 256);
        ~DiWorld();

        DiEntity CreateEntity();
        void RemoveEntity(uint32_t entityId);

        void Refresh();

        void AddComponentToEntity(DiComponent &component, const DiEntityId &id, const uint32_t componentId);

        bool IsValid(const DiEntityId &id);
        void RemoveComponentFromEntity(const DiEntityId &id, const uint32_t getComponentId);
        DiComponent &GetComponentForEntity(const DiEntityId &id, const uint32_t getComponentId);

        void AddSystem(DiSystem &system);

        template <class... Components>
        std::vector<DiEntity> &GetEntitiesWithComponents();

        bool RegisterComponentList(DiFilter filter, bool *boolToChange);

      private:
        uint32_t _nextEntityID = 0;
        uint32_t _chunkSize;

        std::vector<uint32_t> _idCounters;

        std::vector<DiEntityId> _freeIds;
        std::vector<DiEntityId> _addedEntites;
        std::vector<DiEntityId> _removedEntites;

        std::vector<DiComponentStorage> _componentStorage;
        std::vector<DiSystem *> _systems;

        std::vector<std::pair<DiFilter, bool *>> _entityWithComponentsEvent;
    };

    template <class... Components>
    std::vector<DiEntity> &DiWorld::GetEntitiesWithComponents()
    {
        static std::vector<DiEntity> component_entities;
        static bool changed = true;
        static bool registered = false;

        if (!registered)
        {
            auto filter = DiFilter::CreateFilter<Components...>();
            bool success = RegisterComponentList(filter, &changed);
            registered = success;
        }
        if (!changed || !registered)
            return component_entities;

        changed = false;
        component_entities.clear();
        component_entities.reserve(_componentStorage.size());

        auto filter = DiFilter::CreateFilter<Components...>();

        for (uint32_t i = 0; i < _componentStorage.size(); i++)
        {
            auto &storage = _componentStorage[i];
            if (!storage._isInUse)
                continue;

            if ((filter.GetFilter() & storage._usedComponents) == filter.GetFilter())
            {
                auto id = DiEntityId(i);
                id._counter = _idCounters[i];
                component_entities.push_back(DiEntity(*this, id));
            }
        }
        return component_entities;
    }
}
