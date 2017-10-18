/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"

#include <iostream>
#include <vector>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"


#include "Timer.h"
#include "SceneMgr.h"



CGameTimer gametimer;
CSceneMgr SceneMgr;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	SceneMgr.Render();

	glutSwapBuffers();
}

void Idle(void)
{

	gametimer.Tick(0.0f);

	SceneMgr.Update(gametimer.GetTimeElapsed());

	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	
	SceneMgr.Input_MouseButton(button,state,x,y);
	
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	SceneMgr.Input_Key(key, x, y);
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	SceneMgr.Input_SpecialKey(key,x,y);
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	
	SceneMgr.Initialize();

	gametimer.Reset();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

    return 0;
}

