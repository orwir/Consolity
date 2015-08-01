#include "world.h"
#include <algorithm>

using namespace consolity;

GameObject::GameObject()
{
    m_type = GameObjectType_None;

    m_x = 0;
    m_y = 0;

    m_xSpeed = 0;
    m_ySpeed = 0;

    m_symbol = '?';
    m_color = ConsoleColor_White;
    m_backgroundColor = ConsoleColor_Black;
}

void GameObject::render(RenderSystem* rs)
{
    int row = (m_y);
    int col = (m_x);

    rs->drawChar(col, row, m_symbol, m_color, m_backgroundColor);
}

void GameObject::update(float dt, World* world)
{
    m_x += m_xSpeed * dt;
    m_y += m_ySpeed * dt;

    if (m_x < 0)
    {
        m_x = 0;
    }
    else if (m_x > world->getWidth()-1)
    {
        m_x = world->getWidth()-1;
    }
    if (m_y < 0)
    {
        m_y = 0;
    }
    else if (m_y > world->getHeight()-1)
    {
        m_y = world->getHeight()-1;
    }
}

bool GameObject::intersects(GameObject* object)
{
    int row1 = int(m_y);
    int col1 = int(m_x);

    int row2 = int(object->m_y);
    int col2 = int(object->m_x);

    return row1 == row2 && col1 == col2;
}

void World::postUpdate(float dt)
{
    if (m_subjectsForDeletion.size() > 0)
    {
        for (int i = 0; i < m_subjectsForDeletion.size(); i++)
        {
            destroyObject(m_subjectsForDeletion[i]);
        }
        m_subjectsForDeletion.clear();
    }
}

GameObject* World::initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor)
{
    m_objects.push_back(object);

    object->setType(type);
    object->setX(x);
    object->setY(y);
    object->setSymbol(symbol);
    object->setColor(color);
    object->setBackgroundColor(backgroundColor);

    return object;
}

void World::destroyObject(GameObject* object)
{
    m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void World::destroy()
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        destroyObject(m_objects[i]);
    }
}
