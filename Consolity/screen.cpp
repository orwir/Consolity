#include "screen.h"
#include <cstdio>

using namespace consolity;

void Screen::render(RenderSystem* rs, World* world)
{
    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "SCREEN PLACEHOLDER");
    int x = SCREEN_WIDTH / 2 - length / 2;
    rs->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_White, ConsoleColor_Black);
}

void Screen::update(float dt, World* world)
{

}
