#include "Mesh.h"

namespace FOGrP
{
    Mesh::Mesh() : mScale(1), mRot(1, 0, 0, 0), mPos(0, 0, 0)
    {
    }

    void FOGrP::Mesh::Init(Window* window, MVP& _mvp)
	{
        mWindow = window;
        mvp = _mvp;
        timer = 0.0;
        srand(0);

        mShader = new Shader();

        mvp.updateUniformLocId(mShader);

        texture = new Texture(32, 32);
        glm::vec4 data[32 * 32];
        for (int i = 0; i < 32 * 32; ++i) {
            data[i] = glm::vec4(RAND, RAND, RAND, 1.0);
        }
        texture->Update(data);


        /*-----------------------------------------------------------------------------
         *  A Cylindrical MESH
         *-----------------------------------------------------------------------------*/

        int slices = 50;
        int stacks = 5;
        for (int i = 0; i < slices; ++i) {
            float tu = (float)i / slices;
            float rad = 2 * PI * tu;
            for (int j = 0; j < stacks; ++j) {
                float tv = (float)j / stacks;
                glm::vec3 pos(cos(rad), -1 + 2 * tv, sin(rad));
                glm::vec4 col(tu, .5, .5, 1);
                glm::vec2 tex(tu, tv);
                MeshVertex v = { pos, pos, col, tex };
                vertices.push_back(v);
            }
        }

        for (int i = 0; i < slices; ++i) {
            int a, b;
            for (int j = 0; j < stacks; ++j) {
                a = i * stacks + j;
                b = i < (slices - 1) ? a + stacks : j;
                indices.push_back(a);
                indices.push_back(b);
            }
            indices.push_back(b);
            if (i < slices - 1) indices.push_back((i + 1) * stacks);
        }
        GetAttributes(mShader->Id());
        Buffer();
	}

	void FOGrP::Mesh::BindVertexData()
	{
	}

	void FOGrP::Mesh::Draw()
	{
        timer += .01;

        //Randomize Texture
        glm::vec4 data[32 * 32];
        for (int i = 0; i < 32 * 32; ++i) {
            data[i] = glm::vec4(RAND, RAND, RAND, 1.0);
        }
        texture->Update(data);

        glUseProgram(mShader->Id());
        texture->Bind();

        //Eye and Projection Matrices 
        mvp.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        mvp.proj = glm::perspective(3.14f / 3.0f, (float)mWindow->AspectRatio(), 0.1f, -10.0f);
        glUniformMatrix4fv(mvp.viewID, 1, GL_FALSE, glm::value_ptr(mvp.view));
        glUniformMatrix4fv(mvp.projectionID, 1, GL_FALSE, glm::value_ptr(mvp.proj));


        /* Model and Normal Matrix for Mesh */
        glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(mScale));
        glm::mat4 rotate = glm::toMat4(mRot);
        glm::mat4 translate = glm::translate(glm::mat4(1), mPos);
        
        mvp.model = translate * rotate * scale;

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(mvp.view * mvp.model)));
        glUniformMatrix4fv(mvp.modelID, 1, GL_FALSE, glm::value_ptr(mvp.model));
        glUniformMatrix3fv(mvp.normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        Bind();
        DrawElements(GL_TRIANGLE_STRIP);
        Unbind();

        texture->Unbind();
        glUseProgram(0);
	}

    void Mesh::Buffer() {

        /*-----------------------------------------------------------------------------
        *  CREATE THE VERTEX ARRAY OBJECT
        *-----------------------------------------------------------------------------*/
        GENVERTEXARRAYS(1, &arrayID);
        BINDVERTEXARRAY(arrayID);

        /*-----------------------------------------------------------------------------
         *  CREATE THE VERTEX BUFFER OBJECT
         *-----------------------------------------------------------------------------*/
         // Generate one buffer
        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &(vertices[0]), GL_DYNAMIC_DRAW); //<-- Prep for frequent updates

        /*-----------------------------------------------------------------------------
        *  CREATE THE ELEMENT ARRAY BUFFER OBJECT
        *-----------------------------------------------------------------------------*/
        glGenBuffers(1, &elementID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &(indices[0]), GL_STATIC_DRAW); //<-- Update infrequently, if ever

        /*-----------------------------------------------------------------------------
         *  ENABLE VERTEX ATTRIBUTES
         *-----------------------------------------------------------------------------*/
        glEnableVertexAttribArray(positionID);
        glEnableVertexAttribArray(colorID);
        glEnableVertexAttribArray(normalID);   //<-- Enable normalID attribute
        glEnableVertexAttribArray(textureCoordinateID);

        // Tell OpenGL how to handle the buffer of data that is already on the GPU
        //                      attrib    num   type     normalize   stride     offset
        glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), 0);
        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)MeshVertex::offsetColor());
        glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)MeshVertex::offsetNormal());
        glVertexAttribPointer(textureCoordinateID, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)MeshVertex::offsetTextureCoordinate());

        // Unbind Everything (NOTE: unbind the vertex array object first)
        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Mesh::SubBuffer() {
        Bind();
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(MeshVertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        Unbind();
    }

    void Mesh::Bind()
    {
        BINDVERTEXARRAY(arrayID);
    }

    void Mesh::Unbind()
    {
        BINDVERTEXARRAY(0);
    }
    
    void Mesh::DrawArrays(GLuint mode) 
    { 
        glDrawArrays(mode, 0, vertices.size()); }

    void Mesh::DrawElements(GLuint mode) 
    { 
        glDrawElements(mode, indices.size(), GL_UNSIGNED_SHORT, 0); 
    }

    void Mesh::GetAttributes(GLuint shaderID)
    {

        // Get attribute locations from SHADER (if these attributes do not exist in shader, ID=-1)
        positionID = glGetAttribLocation(shaderID, "position");
        colorID = glGetAttribLocation(shaderID, "color");
        normalID = glGetAttribLocation(shaderID, "normal");
        textureCoordinateID = glGetAttribLocation(shaderID, "textureCoordinate");
    }

	FOGrP::Mesh::~Mesh()
	{
	}
}
