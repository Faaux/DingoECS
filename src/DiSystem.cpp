#include "DiSystem.h"
#include "DiEntity.h"
#include <algorithm>
namespace decs
{
    DiSystem::DiSystem(DiWorld &world, DiFilter filter) : _world(world), _filter(filter)
    {
    }

    DiWorld &DiSystem::GetWorld() const
    {
        return _world;
    }

    std::vector<DiEntity> &DiSystem::GetEntities()
    {
        return _entities;
    }

    void DiSystem::AddEntity(DiEntity id)
    {
        _entities.push_back(id);
    }

    void DiSystem::RemoveEntity(DiEntity id)
    {
        _entities.erase(std::remove(_entities.begin(), _entities.end(), id), _entities.end());
    }
}