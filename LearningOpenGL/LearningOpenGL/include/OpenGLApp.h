#pragma once

#include <Macros.h>
#include <Window.h>
#include <iostream>
#include <Mesh.h>

namespace FOGrP
{
	class OpenGLApp
	{
        static Window mWindow;

        //TriangleBuffer mTris;
        //Cube mCube;
        Mesh mesh;
        //Texture mTex;

        /// <summary>
        /// Model View Projection matrices
        /// </summary>
        static MVP mvp;

        static OpenGLApp* Instance;

        static Mouse mouse;

    public:

        OpenGLApp(int width = 640, int height = 480);

        static MVP& MVP();

        static Window& Window();

        ~OpenGLApp();

        void Start();

        virtual void OnDraw();

        virtual void OnInput();

        static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void OnMouseMove(GLFWwindow* window, double x, double y);

        static void OnMouseDown(GLFWwindow* window, int button, int action, int mods);

        static void OnMouseDrag(int x, int y);
	};
}