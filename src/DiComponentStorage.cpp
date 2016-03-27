#include "DiComponentStorage.h"
#include <cassert>
namespace decs
{
	DiComponentStorage::DiComponentStorage()
		: _isInUse(false)
	{
	}

	DiComponentStorage::~DiComponentStorage()
	{
	}

	void DiComponentStorage::reset()
	{
		_isInUse = false;
		_usedComponents.reset();
		for (auto* component : _components)
		{
			if (component)
				delete component;
			component = nullptr;
		}
	}

	void DiComponentStorage::AddComponent(DiComponent& component, const uint32_t componentId)
	{
		_components[componentId] = &component;
		_usedComponents.set(componentId, true);
	}

	void DiComponentStorage::RemoveComponent(const uint32_t componentId)
	{
		assert(_usedComponents[componentId]);
		delete _components[componentId];
		_components[componentId] = nullptr;
		_usedComponents.set(componentId, false);
	}

	DiComponent& DiComponentStorage::GetComponent(const uint32_t componentId)
	{
		assert(_usedComponents[componentId]);
		return *_components[componentId];
	}
}