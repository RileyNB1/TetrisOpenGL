#pragma once

#include <GLTexture.h>

namespace FOGrP
{
    class Collider : public GameEntity 
    {
    public: 
        enum class ColliderType { Box, Circle }; // type safety 

        Collider(ColliderType type); 
        
        virtual ~Collider(); 
        
        virtual Vector2 GetFurthestPoint() = 0; 
        
        ColliderType GetType(); 
        
        virtual void Render() override;

    protected: 
        ColliderType mType;

        static const bool DEBUG_COLLIDERS = true; 
        
        GLTexture* mDebugTexture;
        
        void SetDebugTexture(GLTexture* tex);
    };
}