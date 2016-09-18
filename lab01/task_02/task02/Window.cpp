#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

CColor NormalizeColor(size_t r, size_t g, size_t b)
{
	CColor color;
	color.R = r / 255.f;
	color.G = g / 255.f;
	color.B = b / 255.f;
	return color;
}

const CColor BLACK_COLOR = NormalizeColor(0, 0, 0);
const CColor DARK_BLUE_COLOR = NormalizeColor(30, 15, 72);
const CColor BLUE_COLOR = NormalizeColor(39, 97, 196);
const CColor PINK_COLOR = NormalizeColor(172, 21, 91);
const CColor YELLOW_COLOR = NormalizeColor(236, 190, 33);
const CColor WHITE_COLOR = NormalizeColor(255, 255, 255);


void StrokeEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
{
    const float step = float(2 * M_PI / pointCount);

    // Эллипс представлен в виде незамкнутой ломаной линии, соединяющей
    // pointCount точек на его границе с шагом 2*PI/pointCount
    glBegin(GL_LINE_STRIP);
    for (float angle = 0; angle < float(2 * M_PI); angle += step)
    {
        const float dx = rx * cosf(angle);
        const float dy = ry * sinf(angle);
        glVertex2f(dx + xCenter, dy + yCenter);
    }
    glEnd();
}

/**/
// Рисуем закрашенный эллипс
void FillEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
{
    const float step = float(2 * M_PI) / pointCount;

    // Эллипс представлет в виде "веера" из треугольников
    glBegin(GL_TRIANGLE_FAN);
    // Начальная точка веера располагается в центре эллипса
    glVertex2f(xCenter, yCenter);
    // Остальные точки - равномерно по его границе
    for (float angle = 0; angle <= float(2 * M_PI); angle += step)
    {
        float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
        const float dx = rx * cosf(a);
        const float dy = ry * sinf(a);
        glVertex2f(dx + xCenter, dy + yCenter);
    }
    glEnd();
}

void FillSector(float xCenter, float yCenter, float rx, float ry, int s_angle, int e_angle)
{
	const float step = float(2 * M_PI) / 360;

	// Эллипс представлет в виде "веера" из треугольников
	glBegin(GL_TRIANGLE_FAN);
	// Начальная точка веера располагается в центре эллипса
	glVertex2f(xCenter, yCenter);
	// Остальные точки - равномерно по его границе
	for (float angle = (s_angle * M_PI / 180); angle <= float(e_angle * M_PI / 180); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}




void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}


CWindow::CWindow()
{
    SetBackgroundColor({1.0f, 1.0f, 1.0f, 1.0f});
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
}			  

void CWindow::DrawWings()
{
	// обводка правое крыло
	glColor3f(DARK_BLUE_COLOR.R, DARK_BLUE_COLOR.G, DARK_BLUE_COLOR.B);
	FillEllipse(556, 320, 20, 80);
	FillEllipse(543, 365, 32, 47);

	// правое крыло
	glColor3f(BLUE_COLOR.R, BLUE_COLOR.G, BLUE_COLOR.B);
	FillEllipse(556, 320, 18, 78);
	FillEllipse(543, 365, 30, 45);

	// обводка левое крыло
	glColor3f(DARK_BLUE_COLOR.R, DARK_BLUE_COLOR.G, DARK_BLUE_COLOR.B);
	FillEllipse(240, 320, 20, 80);
	FillEllipse(250, 365, 32, 47);

	// левое крыло
	glColor3f(BLUE_COLOR.R, BLUE_COLOR.G, BLUE_COLOR.B);
	FillEllipse(240, 320, 18, 78);
	FillEllipse(250, 365, 30, 45);

	// пальцы левой руки
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2f(236.0, 365.0);
	glVertex2f(236.0, 406.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(255.0, 365.0);
	glVertex2f(263.0, 406.0);
	glEnd();

	// пальцы правой руки
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2f(538.0, 366.0);
	glVertex2f(525.0, 402.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(553.0, 365.0);
	glVertex2f(554.0, 408.0);
	glEnd();
}

void CWindow::DrawFoots()
{
	// левая нога - обводка
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	glBegin(GL_QUADS);
	glVertex2f(307, 508);
	glVertex2f(330, 536);
	glVertex2f(376, 512);
	glVertex2f(360, 480);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(357, 438);
	glVertex2f(394, 438);
	glVertex2f(394, 552);
	glVertex2f(357, 552);
	glEnd();

	// левая нога
	glColor3f(PINK_COLOR.R, PINK_COLOR.G, PINK_COLOR.B);
	glBegin(GL_QUADS);
	glVertex2f(359, 440);
	glVertex2f(392, 440);
	glVertex2f(392, 550);
	glVertex2f(359, 550);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(310, 510);
	glVertex2f(330, 534);
	glVertex2f(374, 510);
	glVertex2f(360, 484);
	glEnd();


	// правая нога - обводка
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	glBegin(GL_QUADS);
	glVertex2f(504, 508);
	glVertex2f(492, 538);
	glVertex2f(424, 514);
	glVertex2f(408, 470);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(407, 438);
	glVertex2f(444, 438);
	glVertex2f(444, 552);
	glVertex2f(407, 552);
	glEnd();

	// правая нога
	glColor3f(PINK_COLOR.R, PINK_COLOR.G, PINK_COLOR.B);
	glBegin(GL_QUADS);
	glVertex2f(409, 440);
	glVertex2f(442, 440);
	glVertex2f(442, 550);
	glVertex2f(409, 550);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(500, 510);
	glVertex2f(490, 534);
	glVertex2f(424, 510);
	glVertex2f(410, 474);
	glEnd();
}

void CWindow::DrawBody()
{
	// темно-синяя обводка шара
	glColor3f(DARK_BLUE_COLOR.R, DARK_BLUE_COLOR.G, DARK_BLUE_COLOR.B);
	FillEllipse(400, 300, 150, 150);

	// тело шара
	glColor3f(BLUE_COLOR.R, BLUE_COLOR.G, BLUE_COLOR.B);
	FillEllipse(400, 300, 140, 140);

	// бабочка
	glColor3f(DARK_BLUE_COLOR.R, DARK_BLUE_COLOR.G, DARK_BLUE_COLOR.B);
	FillTriangle(362, 340, 356, 400, 410, 370);
	FillTriangle(400, 370, 450, 340, 445, 400);
}

void CWindow::DrawFace()
{
	// клюв
	glColor3f(YELLOW_COLOR.R, YELLOW_COLOR.G, YELLOW_COLOR.B);
	FillEllipse(400, 275, 80, 60);
	FillEllipse(400, 200, 20, 20);

	// разрез рта 
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2f(319.0, 275.0);
	glVertex2f(332.0, 268.0);
	glVertex2f(342.0, 275.0);
	glVertex2f(362.0, 296.0);
	glVertex2f(386.0, 308.0);
	glVertex2f(401.0, 308.0);
	glVertex2f(426.0, 301.0);
	glVertex2f(455.0, 274.0);
	glVertex2f(465.0, 267.0);
	glVertex2f(478.0, 268.0);
	glEnd();

	// левый глаз - обводка
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	FillEllipse(350, 175, 50, 60);

	// левый глаз - белок
	glColor3f(WHITE_COLOR.R, WHITE_COLOR.G, WHITE_COLOR.B);
	FillEllipse(350, 175, 45, 55);

	// левый глаз - зрачок
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	FillEllipse(380, 185, 13, 20);


	// левый глаз - веко
	glColor3f(PINK_COLOR.R, PINK_COLOR.G, PINK_COLOR.B);
	FillSector(350, 175, 45, 55, 170, 350);

	// правый глаз - обводка			   
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	FillEllipse(446, 175, 50, 60);

	// правый глаз - белок				   
	glColor3f(WHITE_COLOR.R, WHITE_COLOR.G, WHITE_COLOR.B);
	FillEllipse(446, 175, 45, 55);


	// правый глаз - зрачок			   
	glColor3f(BLACK_COLOR.R, BLACK_COLOR.G, BLACK_COLOR.B);
	FillEllipse(415, 185, 13, 20);

	// правый глаз - веко				  
	glColor3f(PINK_COLOR.R, PINK_COLOR.G, PINK_COLOR.B);
	FillSector(446, 175, 45, 55, 200, 380);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);
	glEnable(GL_POINT_SMOOTH);

	DrawWings();
	DrawFoots();
	DrawBody();
	DrawFace();
	
}


void CWindow::SetupView(const glm::ivec2 &size)
{
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
