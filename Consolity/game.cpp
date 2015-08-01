#include "game.h"

namespace consolity
{
    void Game::setup()
    {
        srand(time(0));
        m_world = new World(SCREEN_WIDTH, SCREEN_HEIGHT);
        m_renderSystem = new RenderSystem();
        m_currentScreen = NULL;
        m_renderSystem->initialize();
    }

    void Game::shutdown()
    {
        m_renderSystem->forceClear();
        m_world->destroy();

        delete m_currentScreen;
        delete m_world;
        delete m_renderSystem;
        
    }

    void Game::addScreen(Screen* screen)
    {
        m_screens[screen->getType()] = screen;
        m_screensCheck[screen->getType()] = false;
    }

    void Game::setScreen(ScreenType screenType)
    {
        m_renderSystem->forceClear();
        if (m_currentScreen != NULL)
        {
            //todo
        }

        m_currentScreen = m_screens[screenType];
        if (m_currentScreen == nullptr)
        {
            throw Exception_ScreenNotFound;
        }
        initialize();
        if (m_screensCheck[screenType]) {
            m_currentScreen->onReopen(m_renderSystem, m_world);
        }
        else
        {
            m_currentScreen->onFirstOpen(m_renderSystem, m_world);
            m_screensCheck[screenType] = true;
        }
    }

    void Game::run()
    {
        initialize();
        while (m_world->isExists())
        {
            clock_t clockNow = clock();
            clock_t deltaClock = clockNow - m_clockLastFrame;
            float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
            m_clockLastFrame = clockNow;

            m_framesCounter++;
            m_framesTimeCounter += deltaTime;
            if (m_framesTimeCounter >= 1.0)
            {
                m_framesTimeCounter -= 1.0;
                m_fps = m_framesCounter;
                m_framesCounter = 0;
            }

            m_renderSystem->clear();
            if (m_currentScreen != NULL)
            {
                ScreenType next = m_currentScreen->openNext();
                if (ScreenType_None == next)
                {
                    m_currentScreen->render(m_renderSystem, m_world);
                    m_currentScreen->update(deltaTime, m_world);
                }
                else
                {
                    setScreen(next);
                }
            }
            else
            {
                char buffer[SCREEN_WIDTH];
                int length = sprintf_s(buffer, "SCREEN NOT SET!");
                int x = SCREEN_WIDTH / 2 - length / 2;
                m_renderSystem->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
            }
            m_world->postUpdate(deltaTime);

            char buffer[SCREEN_WIDTH];
            int length = sprintf_s(buffer, "FPS: %d", getFps());
            m_renderSystem->drawText(SCREEN_WIDTH - length, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
            m_renderSystem->flush();
        }
    }

    void Game::initialize()
    {
        m_clockLastFrame = clock();
        m_framesCounter = 0;
        m_framesTimeCounter = 0;
        m_fps = 0;
    }
}
