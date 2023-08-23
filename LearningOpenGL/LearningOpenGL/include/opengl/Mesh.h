#pragma once

#include <Window.h>
#include <TextureBuffer.h>
#include <vector>

namespace FOGrP
{
    struct MeshVertex {
        glm::vec3 position;                     //<-- An xyz coordinate of the vertex
        glm::vec3 normal;                       //<-- A normal at the vertex
        glm::vec4 color;                        //<-- A color at the vertex
        glm::vec2 textureCoordinate;            //<-- A texture coordinate of the vertex

        //Offsets into memory
        static size_t offsetNormal() { return sizeof(glm::vec3); }
        static size_t offsetColor() { return sizeof(glm::vec3) * 2; }
        static size_t offsetTextureCoordinate() { return sizeof(glm::vec3) * 2 + sizeof(glm::vec4); }
    };

	class Mesh
	{
        Shader* mShader;

        std::vector<MeshVertex> vertices;
        std::vector<GLushort> indices;

        //ID of Vertex Attribute
        GLuint positionID, normalID, colorID, textureCoordinateID;          //<-- Attribute IDS
        //A buffer ID and elementID
        GLuint bufferID, elementID;
        //An array object ID
        GLuint arrayID;

        Window* mWindow;

        MVP mvp;
        TextureBuffer* texture;
        float timer = 0.0;

    public:

        //ID of Vertex Attribute
        glm::vec3 mPos;
        //orientation in world space
        glm::quat mRot;
        //scale
        float mScale;

        Mesh();

        void Init(Window* window, MVP& _mvp);

        void BindVertexData();

        void Draw();
        void SubBuffer(); 
        void Buffer();
        void Bind();
        void Unbind(); 
        void DrawArrays(GLuint mode); 
        
        void GetAttributes(GLuint shaderID);

        void DrawElements(GLuint mode);


        ~Mesh();
	};
}

