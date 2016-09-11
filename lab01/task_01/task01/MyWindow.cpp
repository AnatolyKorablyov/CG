#include "MyWindow.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Definition.h"

namespace
{
	void DrawCoordinateSystem(const glm::ivec2 & size)
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, size.y / 2);
		glVertex2f(size.x, size.y / 2);

		glVertex2f(size.x / 2, 0.0f);
		glVertex2f(size.x / 2, size.y);
		glEnd();
	}

	float GetYcoordFromParabola(float xCoord)
	{
		return ARGUMENT_A * xCoord * xCoord + ARGUMENT_B * xCoord + ARGUMENT_C;
	}

	void DrawParabola(float step, float xCentre, float yCentre)
	{
		glBegin(GL_LINE_STRIP);
		
		float y = 0.0f;
		for (float x = INTERVAL_MIN; x <= INTERVAL_MAX; x += STEP_ERROR)
		{
			y = GetYcoordFromParabola(x);
			glVertex2f(xCentre + x * step, yCentre - y * step);
		}
		glEnd();
	}

}

CMyWindow::CMyWindow()
{
}


CMyWindow::~CMyWindow()
{
}

void CMyWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CMyWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	glColor3f(1, 0, 1);
	DrawCoordinateSystem(size);

	glColor3f(1, 1, 1);
	DrawParabola(10.0f, size.x / 2, size.y / 2);
}

void CMyWindow::OnWindowEvent(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_r:
			SetBackgroundColor({ 1, 0, 0, 1 });
			break;
		case SDLK_g:
			SetBackgroundColor({ 0, 1, 0, 1 });
			break;
		case SDLK_b:
			SetBackgroundColor({ 0, 0, 1, 1 });
			break;
		}
	}
}

void CMyWindow::SetupView(const glm::ivec2 & size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}
