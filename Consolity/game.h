#pragma once

#include <ctime>
#include <map>
#include "renderSystem.h"
#include "screen.h"

namespace consolity
{
    typedef int Exception;

    static Exception Exception_ScreenNotFound = 999;
    
    class Game
    {
    public:
        virtual void setup();
        virtual void shutdown();

        void addScreen(Screen* screen);
        void setScreen(ScreenType screenType);
        void run();
        int getFps() { return m_fps; }
        void setWorld(World* world) { m_world = world; }

    protected:
        void initialize();

    private:
        clock_t m_clockLastFrame;
        int m_framesCounter;
        float m_framesTimeCounter;
        int m_fps;

        World* m_world;
        RenderSystem* m_renderSystem;
        std::map<ScreenType, Screen*> m_screens;
        std::map<ScreenType, bool> m_screensCheck;
        Screen* m_currentScreen;
    };
}
