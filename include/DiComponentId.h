#pragma once
#include <cstdint>
#include <cassert>
#include "DiWorld.h"
namespace decs
{
	class DiComponentId
	{
	public:
		template <typename T>
		static uint32_t GetComponentId();


	private:
		static uint32_t _nextComponentId;
	};

	template <typename T>
	uint32_t DiComponentId::GetComponentId()
	{
		static uint32_t componentId = _nextComponentId++;
		assert(componentId < Di_MAX_COMPONENTS);
		return componentId;
	}
}