#pragma once
#include "DiFilter.h"
#include <vector>
namespace decs
{
    class DiSystem
    {
        friend class DiWorld;
        friend class DiEntity;

      public:
        DiSystem(DiWorld &world, DiFilter filter);
        virtual ~DiSystem() = default;
        DiWorld &GetWorld() const;
        std::vector<DiEntity> &GetEntities();
        virtual void Update(float deltaTime){};

      private:
        void AddEntity(DiEntity entity);
        void RemoveEntity(DiEntity entity);

        DiWorld &_world;
        DiFilter _filter;
        std::vector<DiEntity> _entities;
    };
}