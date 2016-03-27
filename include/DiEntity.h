#pragma once
#include <cstdint>
#include <type_traits>
#include <utility>
#include "DiWorld.h"
#include "DiEntityId.h"
#include "DiComponent.h"
#include "DiComponentId.h"
namespace decs
{
	class DiEntity
	{
		friend class DiWorld;
	public:

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template <typename T>
		void RemoveComponent();

		template <typename T>
		T& GetComponent();

		void Release() const;
	private:

		DiEntity(DiWorld& world, DiEntityId id);
		DiWorld& _world;
		DiEntityId _id;
	};

	template <typename T, typename ... Args>
	T& DiEntity::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
		auto component = new T{ std::forward<Args>(args)... };
		_world.AddComponentToEntity(*component, _id, DiComponentId::GetComponentId<T>());
		return *component;
	}

	template <typename T>
	void DiEntity::RemoveComponent()
	{
		static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
		_world.RemoveComponentFromEntity(_id, DiComponentId::GetComponentId<T>());
	}

	template <typename T>
	T& DiEntity::GetComponent()
	{
		static_assert(std::is_base_of<DiComponent, T>(), "T is not a component, cannot retrieve T from entity");
		return static_cast<T&>(_world.GetComponentForEntity(_id, DiComponentId::GetComponentId<T>()));
	}
}