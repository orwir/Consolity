#pragma once

#include <vector>
#include "renderSystem.h"

namespace consolity
{
    typedef int GameObjectType;

    const GameObjectType GameObjectType_None = -1;

    class World;

    class GameObject
    {
    public:
        GameObject();

        virtual void render(RenderSystem* rs);
        virtual void update(float dt, World* world);
        virtual bool intersects(GameObject* object);

        void setType(GameObjectType type) { m_type = type; }
        GameObjectType getType() { return m_type; }

        void setX(float x) { m_x = x; }
        float getX() { return m_x; }

        void setY(float y) { m_y = y; }
        float getY() { return m_y; }

        void setXSpeed(float speed) { m_xSpeed = speed; }
        float getXSpeed() { return m_xSpeed; }

        void setYSpeed(float speed) { m_ySpeed = speed; }
        float getYSpeed() { return m_ySpeed; }

        void setSymbol(unsigned char symbol) { m_symbol = symbol; }
        unsigned char getSymbol() { return m_symbol; }

        void setColor(ConsoleColor color) { m_color = color; }
        ConsoleColor getColor() { return m_color; }

        void setBackgroundColor(ConsoleColor color) { m_backgroundColor = color; }
        ConsoleColor getBackgroundColor() { return m_backgroundColor; }

    private:
        GameObjectType m_type;

        float m_x;
        float m_y;
        float m_xSpeed;
        float m_ySpeed;

        unsigned char m_symbol;
        ConsoleColor m_color;
        ConsoleColor m_backgroundColor;
    };

    class World
    {
    public:
        World(int width, int height)
        {
            m_width = width;
            m_height = height;
            m_isExists = true;
        }

        void postUpdate(float dt);
        void destroy();

        int getWidth() { return m_width; }
        int getHeight() { return m_height; }

        GameObject* initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor);
        void destroyObject(GameObject* object);

        const std::vector<GameObject*> getObjects() { return m_objects; }
        void planDelete(GameObject* object) { m_subjectsForDeletion.push_back(object); }
        bool isDeleted(GameObject* object) { return std::find(m_subjectsForDeletion.begin(), m_subjectsForDeletion.end(), object) != m_subjectsForDeletion.end(); }

        void planDestroy() { m_isExists = false; }
        bool isExists() { return m_isExists; }

    private:
        bool m_isExists;
        int m_width;
        int m_height;
        std::vector<GameObject*> m_objects;
        std::vector<GameObject*> m_subjectsForDeletion;
    };
}