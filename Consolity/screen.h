#pragma once

#include <ctime>
#include "renderSystem.h"
#include "world.h"

namespace consolity
{
    typedef int ScreenType;

    static const int ScreenType_None = -1;

    class Screen
    {
    public:
        Screen(ScreenType type)
        {
            m_type = type;
        }

        virtual void onFirstOpen(RenderSystem* rs, World* world) {}
        virtual void onReopen(RenderSystem* rs, World* world) {}
        virtual void onDestroy() {}

        virtual void render(RenderSystem* rs, World* world);
        virtual void update(float dt, World* world);
        virtual ScreenType openNext() { return ScreenType_None; }

        ScreenType getType() { return m_type; }

    private:
        ScreenType m_type;

    };
}
