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

#include "SolidCube.h"
#include "Timer.h"



Renderer *g_Renderer = NULL;
vector<CSolidCube*> Cube;
CGameTimer gametimer;

int v = 0;
Vector2i pos;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	for (auto elem : Cube) {
		elem->Render();
	}
	
	
	glutSwapBuffers();
}

void Idle(void)
{

	gametimer.Tick(0.0f);

	for (auto elem : Cube) {
		elem->Update(gametimer.GetTimeElapsed() );
	}

	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	Cube.push_back(new CSolidCube(g_Renderer,
		{ x - CLIENT_WIDTH/2,CLIENT_HEIGHT / 2 - y,0 },
		{ 1,0,0 },
		150, 
		50,
		{ 1,0,0,1 }
	));
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}


	Cube.push_back(new CSolidCube(g_Renderer, { 0,0,0 }, { 1,0,0 }, 50, 10, {1,0,0,1}));

	gametimer.Reset();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
    return 0;
}

