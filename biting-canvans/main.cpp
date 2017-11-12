/*
	Biting Canvans
	Отрисовывает массив пикселей. У каждого пикселя есть вес, который визуализируется цветом от черного (0) до белого (1)
	Раз в такт (1ms) от рандомного пикселя отнимается 0.2 веса. Таким образом холст деградирует.
	Постепенно холст пропадает и начинает выглядить как космос :3

	by @mvodya 2017
*/

#include <iostream>
#include <ctime>

#include <GL/freeglut.h>

const int WINDOW_SIZE = 800; // Размер окна
const int PIXEL_QUANTITY = 4; // Плотность пикселей
// Вычисление количества пикселей по одной стороне
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

float **pixelStorage; // Массив всех отображаемых пикселей

// Отрисовка одного пикселя
void drawPixel(float x, float y, float alpha) {
	float pixelSize = (1.0f / PIXEL_AMOUNT) * 2;
	// Указываем цвет
	glColor3f(alpha, alpha, alpha);
	// Отрисовываем квадрат
	glBegin(GL_QUADS);
		glVertex2f(-1.0f + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 0 1
		glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 1 1
		glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - (pixelSize * y)); // 1 0
		glVertex2f(-1.0f + (pixelSize * x), 1.0f - (pixelSize * y)); // 0 0
	glEnd();
}

// Рандомное пожирание пикселей
void canvansDegradation() {
	int x = std::rand() % (int)PIXEL_AMOUNT;
	int y = std::rand() % (int)PIXEL_AMOUNT;

	if (pixelStorage[x][y] > 0.0f) {
		pixelStorage[x][y] = pixelStorage[x][y] - 0.2f; // Убиваем немного (на 0.2) пиксель
	}
}

// Обработка графики
void graphicsLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < PIXEL_AMOUNT; i++)
	{
		for (size_t j = 0; j < PIXEL_AMOUNT; j++)
		{
			drawPixel(i, j, pixelStorage[i][j]); // Отрисовываем нужный пиксель
		}
	}

	canvansDegradation();

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
	std::cout << "Biting canvans test\n";

	// Генерируем новое семя дял генератора
	std::srand(unsigned(std::time(0)));

	// Выделяем память массиву пикселей
	pixelStorage = new float*[(int)PIXEL_AMOUNT];
	for (size_t i = 0; i < (int)PIXEL_AMOUNT; i++)
	{
		pixelStorage[i] = new float[(int)PIXEL_AMOUNT];
		for (size_t j = 0; j < (int)PIXEL_AMOUNT; j++)
		{
			pixelStorage[i][j] = 1.0f;
		}
	}

	// Инициализация графики
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Yum - Biting canvans");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDisplayFunc(graphicsLoop);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(1, glutTimer, 1);

	// Запускаем циклы
	glutMainLoop();

	return 0;
}