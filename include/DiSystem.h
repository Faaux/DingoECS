#pragma once
#include <vector>
#include "DiEntityId.h"
#include "DiFilter.h"
namespace decs
{
	class DiSystem
	{
		friend class DiWorld;
	public:
		DiSystem(DiWorld& world, DiFilter filter);
		virtual ~DiSystem() = default;
		DiWorld& GetWorld() const;
		const std::vector<DiEntityId>& GetEntities() const;
		virtual void Update(float deltaTime) {};

	private:
		void AddEntity(DiEntityId id);
		void RemoveEntity(DiEntityId id);

		DiWorld& _world;
		DiFilter _filter;
		std::vector<DiEntityId> _entities;
	};
}