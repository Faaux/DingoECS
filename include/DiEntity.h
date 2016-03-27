#pragma once
#include "DiComponent.h"
#include "DiComponentId.h"
#include "DiEntityId.h"
#include "DiWorld.h"
#include <cstdint>
#include <type_traits>
#include <utility>
namespace decs
{
    class DiEntity
    {
        friend class DiWorld;

      public:
        template <typename T, typename... Args>
        T &AddComponent(Args &&... args) const;

        template <typename T>
        void RemoveComponent() const;

        template <typename T>
        T &GetComponent() const;

        void Release() const;

        friend bool operator==(const DiEntity &lhs, const DiEntity &rhs)
        {
            return lhs._id == rhs._id;
        }

        friend bool operator!=(const DiEntity &lhs, const DiEntity &rhs)
        {
            return !(lhs == rhs);
        }

        DiEntity(const DiEntity &other) : _world(other._world), _id(other._id)
        {
        }

        DiEntity(DiEntity &&other) : _world(other._world), _id(std::move(other._id))
        {
        }

        DiEntity &operator=(const DiEntity &other)
        {
            if (this == &other)
                return *this;
            _world = other._world;
            _id = other._id;
            return *this;
        }

        DiEntity &operator=(DiEntity &&other)
        {
            if (this == &other)
                return *this;
            _world = other._world;
            _id = std::move(other._id);
            return *this;
        }

        const DiEntityId &GetId()
        {
            return _id;
        }

      private:
        DiEntity(DiWorld &world, DiEntityId id);
        DiWorld &_world;
        DiEntityId _id;
    };

    template <typename T, typename... Args>
    T &DiEntity::AddComponent(Args &&... args) const
    {
        static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
        auto component = new T{std::forward<Args>(args)...};
        _world.AddComponentToEntity(*component, _id, DiComponentId::GetComponentId<T>());
        return *component;
    }

    template <typename T>
    void DiEntity::RemoveComponent() const
    {
        static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
        _world.RemoveComponentFromEntity(_id, DiComponentId::GetComponentId<T>());
    }

    template <typename T>
    T &DiEntity::GetComponent() const
    {
        static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
        return static_cast<T &>(_world.GetComponentForEntity(_id, DiComponentId::GetComponentId<T>()));
    }
}