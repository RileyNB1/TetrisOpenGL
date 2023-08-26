#pragma once

#include <Collider.h>

namespace FOGrP
{
    enum BoxCorner
    {
        TopLeft = 0,
        TopRight,
        BottomLeft,
        BottomRight
    };

    class BoxCollider : public Collider
    {
    private:
        static const int MAX_VERTS = 4;

        GameEntity* mVerts[MAX_VERTS];

        void AddVert(int index, Vector2 pos);

    public:

        BoxCollider(Vector2 size);

        ~BoxCollider();

        Vector2 GetFurthestPoint() override;

        Vector2 GetVertexPos(BoxCorner index);
    };
}