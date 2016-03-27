#pragma once
namespace decs
{
    class DiComponent
    {
      public:
        DiComponent() = default;
        virtual ~DiComponent() = default;

      private:
        DiComponent(DiComponent const &) = delete;
        void operator=(DiComponent const &) = delete;
    };
}