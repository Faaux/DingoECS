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

		void AddComponentToEntity(DiComponent& component, const DiEntityId& id, const uint32_t componentId);

		bool IsValid(const DiEntityId& id);
		void RemoveComponentFromEntity(const DiEntityId& id, const uint32_t getComponentId);
		DiComponent& GetComponentForEntity(const DiEntityId& id, const uint32_t getComponentId);

		void AddSystem(DiSystem& system);
	private:
		uint32_t _nextEntityID = 0;
		uint32_t _chunkSize;

		std::vector<uint32_t> _idCounters;

		std::vector<DiEntityId> _freeIds;
		std::vector<DiEntityId> _addedEntites;
		std::vector<DiEntityId> _removedEntites;

		std::vector<DiComponentStorage> _componentStorage;
		std::vector<DiSystem*> _systems;
	};
}