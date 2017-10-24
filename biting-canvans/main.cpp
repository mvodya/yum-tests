#include <iostream>

#include <GL/freeglut.h>

const int WINDOW_SIZE = 800; // ������ ����
const int PIXEL_QUANTITY = 4; // ��������� ��������
// ���������� ���������� �������� (�� �����, ����� = sqrt(PIXEL_AMOUNT))
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

int **pixelStorage; // ������ ���� ������������ ��������

// ��������� ������ �������
void DrawPixel(float x, float y, float alpha) {
	float pixelSize = (1.0f / PIXEL_AMOUNT) * 2;
	// ��������� ����
	glColor3f(alpha, alpha, alpha);
	// ������������ �������
	glBegin(GL_QUADS);
		glVertex2f(-1.0f + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 0 1
		glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - pixelSize - (pixelSize * y)); // 1 1
		glVertex2f(-1.0f + pixelSize + (pixelSize * x), 1.0f - (pixelSize * y)); // 1 0
		glVertex2f(-1.0f + (pixelSize * x), 1.0f - (pixelSize * y)); // 0 0
	glEnd();
}

// ��������� �������
void graphicsLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < PIXEL_AMOUNT; i++)
	{
		for (size_t j = 0; j < PIXEL_AMOUNT; j++)
		{
			DrawPixel(i, j, pixelStorage[i][j]);
		}
	}
	glutSwapBuffers();
}

// ��������� ����� � ����������
void keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "Key detected: " << key << std::endl;
	if (key == 27) // ����� �� ESC
		exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	std::cout << "Biting canvans test\n";

	// �������� ������ ������� ��������
	pixelStorage = new int*[PIXEL_AMOUNT];
	for (size_t i = 0; i < PIXEL_AMOUNT; i++)
	{
		pixelStorage[i] = new int[PIXEL_AMOUNT];
		for (size_t j = 0; j <PIXEL_AMOUNT; j++)
		{
			pixelStorage[i][j] = 1;
		}
	}

	// ������������� �������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Yum - Biting canvans");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDisplayFunc(graphicsLoop);
	glutKeyboardFunc(keyboardHandler);

	// ��������� �����
	glutMainLoop();

	return 0;
}