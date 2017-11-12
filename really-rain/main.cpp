/*
	Really rain
	
	by @mvodya 2017
*/

#include <iostream>
#include <ctime>

#include <GL/freeglut.h>

const int WINDOW_SIZE = 800;  // Размер окна
const int PIXEL_QUANTITY = 4; // Плотность пикселей
// Вычисление количества пикселей по одной стороне
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

// Отрисовка одного пикселя
void drawPixel(float x, float y, float color) {
	float pixelSize = (1.0f / PIXEL_AMOUNT) * 2;
	// Указываем цвет
	glColor3f(color, color, color);
	// Отрисовываем квадрат
	glBegin(GL_QUADS);
	glVertex2f(-1.0f + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 0 1
	glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 1 1
	glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - (pixelSize * y)); // 1 0
	glVertex2f(-1.0f + (pixelSize * x), 1.0f - (pixelSize * y)); // 0 0
	glEnd();
}

// Обработка графики
void graphicsLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Чистим буфер

	// TODO: Все самое основное
	drawPixel(1, 1, 1);

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
