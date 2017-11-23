/*
	Really rain
	Рисует пиксельный дождик

	by @mvodya 2017
*/

#include <iostream>

#include <GL/freeglut.h>
#include "raindrop.h"

const int RAIN_DROPS_COUNT = 100; // Количесвто

RainDrop *rainDrops;

// Обработка графики
void graphicsLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Чистим буфер

	for (size_t i = 0; i < RAIN_DROPS_COUNT; i++)
	{
		rainDrops[i].draw();
		rainDrops[i].update();
	}

	// TODO: Все самое основное

	glutSwapBuffers();
}

// Таймер для обновления графики (раз в 1ms)
void glutTimer(int value)
{
	glutPostRedisplay(); // Обновляем экран (тик)
	glutTimerFunc(1, glutTimer, 1); // Снова запускаем таймер
}

// Обработка ввода с клавиатуры
void keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "Key detected: " << key << std::endl; // Выводим ввод с клавиатуры (просто так)
	if (key == 27) // Выход по ESC
		exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	std::cout << "Really rain\n";

	// Выделяем память каплям дождя
	rainDrops = new RainDrop[RAIN_DROPS_COUNT];
	 
	// Инициализация графики
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Yum - Really rain test");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDisplayFunc(graphicsLoop);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(1, glutTimer, 1);

	// Запускаем циклы
	glutMainLoop();
}
