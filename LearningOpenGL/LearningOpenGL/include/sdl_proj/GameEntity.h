#pragma once

#include <MathHelper.h>

namespace FOGrP
{
    class GameEntity
    {
    private:
        Vector2 mPosition;
        float mRotation;
        Vector2 mScale;
        bool mActive;
        GameEntity* mParent;
    public:
        enum Space { Local = 0, World = 1 };

        GameEntity(float x = 0.0f, float y = 0.0f);
        GameEntity(const Vector2& pos);
        ~GameEntity();

        void Position(float x, float y);
        void Position(const Vector2& pos);
        Vector2 Position(Space space = World);
        void Rotation(float rot);
        float Rotation(Space space = World);
        void Scale(Vector2 scale);
        Vector2 Scale(Space space = World);
        void Active(bool active); bool Active();
        void Parent(GameEntity* parent);
        GameEntity* Parent();
        void Translate(Vector2 vec, Space space = Local);
        void Rotate(float amount);

        virtual void Update() {};
        virtual void Render() {};
    };
}