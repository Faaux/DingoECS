#include "DiWorld.h"
#include "DiEntity.h"
#include <cassert>
namespace decs
{
    DiWorld::DiWorld(uint32_t chunkSize) : _chunkSize(chunkSize), _idCounters(chunkSize), _componentStorage(chunkSize)
    {
    }

    DiWorld::~DiWorld()
    {
        // Cleanup Components
        for (auto &comps : _componentStorage)
        {
            comps.reset();
        }
    }

    DiEntity DiWorld::CreateEntity()
    {
        DiEntityId nextId;
        if (_freeIds.size() > 0)
        {
            nextId = _freeIds.back();
            _freeIds.pop_back();
        }
        else
        {
            nextId._id = _nextEntityID++;

            // Check if _idCounters is big enough
            if (_idCounters.size() <= nextId._id)
            {
                _idCounters.resize(_idCounters.size() + _chunkSize);
                _componentStorage.resize(_componentStorage.size() + _chunkSize);
            }

            _idCounters[nextId._id] = nextId._counter = 1;
        }
        _addedEntites.push_back(nextId);

        return DiEntity(*this, nextId);
    }

    void DiWorld::RemoveEntity(uint32_t entityId)
    {
        _removedEntites.push_back(entityId);
    }

    void DiWorld::Refresh()
    {
        // Update System with added entites
        for (auto &id : _addedEntites)
        {
            assert(IsValid(id._id));
            auto &storage = _componentStorage[id._id];
            storage._isInUse = true;

            for (auto &system : _systems)
            {
                if (!system)
                    continue;
                if ((system->_filter.GetFilter() & storage._usedComponents) == system->_filter.GetFilter())
                {
                    system->AddEntity(DiEntity(*this, id));
                }
            }

            for (auto &pair : _entityWithComponentsEvent)
            {
                DiFilter &filter = pair.first;
                bool *boolToChange = pair.second;

                if ((filter.GetFilter() & storage._usedComponents) == filter.GetFilter())
                {
                    *boolToChange = true;
                }
            }
        }
        _addedEntites.clear();

        for (auto &id : _removedEntites)
        {
            ++_idCounters[id._id];
            auto &currentComponentStorage = _componentStorage[id._id];
            for (auto &pair : _entityWithComponentsEvent)
            {
                DiFilter &filter = pair.first;
                bool *boolToChange = pair.second;

                if ((filter.GetFilter() & currentComponentStorage._usedComponents) == filter.GetFilter())
                {
                    *boolToChange = true;
                }
            }

            currentComponentStorage.reset();
        }
        _removedEntites.clear();
    }

    void DiWorld::AddComponentToEntity(DiComponent &component, const DiEntityId &id, const uint32_t componentId)
    {
        assert(IsValid(id));
        _componentStorage[id._id].AddComponent(component, componentId);
    }

    bool DiWorld::IsValid(const DiEntityId &id)
    {
        return id._counter == _idCounters[id._id];
    }

    void DiWorld::RemoveComponentFromEntity(const DiEntityId &id, const uint32_t componentId)
    {
        assert(IsValid(id));
        _componentStorage[id._id].RemoveComponent(componentId);
    }

    DiComponent &DiWorld::GetComponentForEntity(const DiEntityId &id, const uint32_t componentId)
    {
        assert(IsValid(id));
        return _componentStorage[id._id].GetComponent(componentId);
    }

    void DiWorld::AddSystem(DiSystem &system)
    {
        _systems.push_back(&system);

        // Push Entities to system

        for (uint32_t i = 0; i < _componentStorage.size(); i++)
        {
            auto &storage = _componentStorage[i];
            if (!storage._isInUse)
                continue;

            if ((system._filter.GetFilter() & storage._usedComponents) == system._filter.GetFilter())
            {
                auto id = DiEntityId(i);
                id._counter = _idCounters[i];
                system.AddEntity(DiEntity(*this, id));
            }
        }
    }

    bool DiWorld::RegisterComponentList(DiFilter filter, bool *boolToChange)
    {
        _entityWithComponentsEvent.push_back(std::pair<DiFilter, bool *>(filter, boolToChange));
        return true;
    }
}
