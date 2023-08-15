#pragma once

#include <GL_Lib.h>
#include <Window.h>
#include <iostream>

void Draw();

namespace FOGrP
{
	class OpenGLApp
	{
        Window mWindow;

    public:

        OpenGLApp(int width = 640, int height = 480);

        Window& Window();

        ~OpenGLApp();

        void Start();

        virtual void OnDraw();

        virtual void OnMouseMove(int x, int y);

        virtual void OnMouseDown(int button, int action);

        virtual void OnKeyDown(int key, int action);
	};
}