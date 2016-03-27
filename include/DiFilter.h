#pragma once
#include "DiDefines.h"
#include <bitset>
namespace decs
{
    class DiFilter
    {
      public:
        template <class... Components>
        static DiFilter CreateFilter();

        const std::bitset<Di_MAX_COMPONENTS> &GetFilter() const
        {
            return _components;
        }

      private:
        template <typename C>
        void SetBitMask();

        template <typename C1, typename C2, typename... Components>
        void SetBitMask();

        DiFilter() = default;

        std::bitset<Di_MAX_COMPONENTS> _components;
    };

    template <class... Components>
    DiFilter DiFilter::CreateFilter()
    {
        DiFilter result;
        result.SetBitMask<Components...>();
        return result;
    }

    template <typename C>
    void DiFilter::SetBitMask()
    {
        _components.set(DiComponentId::GetComponentId<C>(), true);
    }

    template <typename C1, typename C2, typename... Components>
    void DiFilter::SetBitMask()
    {
        SetBitMask<C1>();
        SetBitMask<C2, Components...>();
    }
}