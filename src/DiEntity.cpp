#include "DiEntity.h"
namespace decs
{
    void DiEntity::Release() const
    {
        _world.RemoveEntity(_id._id);
    }

    DiEntity::DiEntity(DiWorld &world, DiEntityId id) : _world(world), _id(id)
    {
    }
}