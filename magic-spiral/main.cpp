/*
	Magic spiral
	Рисует спираль из пикселей и вращает ее.
	Каждый такт отрисовывает i-ое количество точек A = (a;b), где
		a = cos(i + q) * i
		b = cos(i + q) * i
	где q - смещение для вращения, а i - номер точки (т.е. шаг)

	by @mvodya 2017
*/
#include <iostream>

#include <GL/freeglut.h>

const int WINDOW_SIZE = 800; // Размер окна
const int PIXEL_QUANTITY = 4; // Плотность пикселей
// Вычисление количества пикселей (не общее, общее = sqrt(PIXEL_AMOUNT))
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

const int SPIRAL_PIXELS = 100; // Количесво пикселей для спирали
const float SPIRAL_ANGLE_OFFSET_STEP = 0.05f; // Смещение угла спирали за такт
const float SPIRAL_STEP = 0.01f; // Шаг отрисовки спирали
const float Pi = 3.14159f; // Число Pi

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

float AngleOffset = 0.0f; // Итератор смещения спирали

// Обработка графики
void graphicsLoop()
{
	AngleOffset += SPIRAL_ANGLE_OFFSET_STEP; // Смещаем спираль
	if (AngleOffset > 2*Pi) AngleOffset = 0; // Обнуляем смещение, при достижении 2Pi 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (float i = 0; i < SPIRAL_PIXELS; i+=SPIRAL_STEP)
	{
		drawPixel(PIXEL_AMOUNT/2 + cos(i + AngleOffset) * i, PIXEL_AMOUNT/2 + sin(i + AngleOffset) * i, i);
	}

	glutSwapBuffers();
}

// Таймер для обновления графики (раз в 1ms)
void glutTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, glutTimer, 1);
}

// Обработка ввода с клавиатуры
void keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "Key detected: " << key << std::endl;
	if (key == 27) // Выход по ESC
		exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	std::cout << "Magic spiral test\n";

	// Инициализация графики
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Yum - Magic spiral test");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDisplayFunc(graphicsLoop);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(1, glutTimer, 1);

	// Запускаем циклы
	glutMainLoop();

	return 0;
}