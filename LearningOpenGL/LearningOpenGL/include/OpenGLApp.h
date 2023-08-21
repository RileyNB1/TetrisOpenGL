#pragma once

#include <GL_Lib.h>
#include <Window.h>
#include <iostream>
//#include <TriangleBuffer.h>
#include <Cube.h>
//#include <DynamicMesh.h>
//#include <Texture.h>

namespace FOGrP
{
	class OpenGLApp// : public MouseListener
	{
        Window mWindow;

        //TriangleBuffer mTris;
        Cube mCube;
        //DynamicMesh mesh;
        //Texture mTex;

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

        static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void OnMouseMove(GLFWwindow* window, double x, double y);

        static void OnMouseDown(GLFWwindow* window, int button, int action, int mods);
	};
}