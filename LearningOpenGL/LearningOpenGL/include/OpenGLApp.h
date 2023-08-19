#pragma once

#include <GL_Lib.h>
#include <Window.h>
#include <iostream>
//#include <TriangleBuffer.h>
#include <Cube.h>
//#include <DynamicMesh.h>
//#include <Texture.h>

void Draw();

namespace FOGrP
{
	class OpenGLApp
	{
        Window mWindow;

        //TriangleBuffer mTris;
        Cube mCube;
        //DynamicMesh mesh;
        //Texture mTex;

        int keyCode;
        glm::vec3 eyePos;
        glm::vec3 forwardDir;

        /// <summary>
        /// Model View Projection matrices
        /// </summary>
        static MVP mvp;

    public:

        OpenGLApp(int width = 640, int height = 480);

        static MVP& MVP();

        Window& Window();

        ~OpenGLApp();

        void Start();

        virtual void OnDraw();

        virtual void OnInput();

        virtual void OnMouseMove(int x, int y);

        virtual void OnMouseDown(int button, int action);

        virtual void OnKeyDown(int key, int action);
	};
}