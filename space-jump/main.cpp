/*
	Space jump
*/
#include "spacestar.h"

SpaceStar *stars; // Массив звезд

// Обработка графики
void graphicsLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Чистим буфер
	for (size_t i = 0; i < STARS_QUANTITY; i++)
	{
		stars[i].update();
		stars[i].draw();
	}
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

int main(int argc, char **argv) {
	std::cout << "Space jump test\n";

	stars = new SpaceStar[STARS_QUANTITY];

	// Генерируем новое семя дял генератора
	std::srand(unsigned(std::time(0)));

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