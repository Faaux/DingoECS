#include "DiSystem.h"
#include <algorithm>
namespace decs
{
	DiSystem::DiSystem(DiWorld& world, DiFilter filter) : _world(world), _filter(filter)
	{
	}

	DiWorld& DiSystem::GetWorld() const
	{
		return _world;
	}

	const std::vector<DiEntityId>& DiSystem::GetEntities() const
	{
		return _entities;
	}

	void DiSystem::AddEntity(DiEntityId id)
	{
		_entities.push_back(id);
	}

	void DiSystem::RemoveEntity(DiEntityId id)
	{
		_entities.erase(std::remove(_entities.begin(), _entities.end(), id), _entities.end());
	}
}