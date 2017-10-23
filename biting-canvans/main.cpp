#include <iostream>

#include <GL/freeglut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int **pixelStorage;

void DrawPixel(float x, float y) {
	glBegin(GL_QUADS);
		glVertex2f(-1.0f + (x / WINDOW_WIDTH), -1.0f + (y / WINDOW_WIDTH));
		glVertex2f(1.0f + (x / WINDOW_WIDTH), -1.0f + (x / WINDOW_WIDTH));
		glVertex2f(0.1f, 0.1f);
		glVertex2f(-0.1f, 0.1f);
	glEnd();
}

// Обработка графики
void graphicsLoop() 
{
	// Графический цикл
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor4f(0.0f, 0.0f, 0.0f, 0.1f);

	DrawPixel(0, 0);

	glutSwapBuffers();
}

// Обработка ввода с клавиатуры
void keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "Key detected: " << key << std::endl;
	if (key == 27) // Выход по ESC
		exit(EXIT_SUCCESS);
}

// Закрашиваем все окно белым цветом
void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	std::cout << "Biting canvans test\n";

	// Выделяем память и обнуляем хранилище пикселей
	pixelStorage = new int*[WINDOW_HEIGHT];
	for (size_t i = 0; i < WINDOW_HEIGHT; i++)
	{
		pixelStorage[i] = new int[WINDOW_WIDTH];
		for (size_t j = 0; j < WINDOW_WIDTH; j++)
		{
			pixelStorage[i][j] = 0;
		}
	}

	// Инициализация графики
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Yum - Biting canvans");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutDisplayFunc(graphicsLoop);
	glutKeyboardFunc(keyboardHandler);

	// Закрашиваем окно
	init(); init();
	// Запускаем циклы
	glutMainLoop();

	return 0;
}