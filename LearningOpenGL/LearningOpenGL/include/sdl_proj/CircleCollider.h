#pragma once

#include <Collider.h>

namespace sdlFr
{
    const float DEBUG_IMAGE_SIZE = 50;

    class CircleCollider : public Collider 
    {
    private: 
        
        float mRadius; 
    
    public: 
        CircleCollider(float radius, bool broadPhase = false); 
        
        ~CircleCollider(); 
        
        Vector2 GetFurthestPoint() override; 
        
        float GetRadius();
    };
}