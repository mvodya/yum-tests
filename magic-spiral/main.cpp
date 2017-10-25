#include <iostream>

#include <GL/freeglut.h>

const int WINDOW_SIZE = 800; // ������ ����
const int PIXEL_QUANTITY = 4; // ��������� ��������
// ���������� ���������� �������� (�� �����, ����� = sqrt(PIXEL_AMOUNT))
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

const int SPIRAL_PIXELS = 100; // ��������� �������� ��� �������
const float SPIRAL_ANGLE_OFFSET_STEP = 0.05f; // �������� ���� ������� �� ����
const float SPIRAL_STEP = 0.01f; // ��� ��������� �������
const float Pi = 3.14159f; // ����� Pi

// ��������� ������ �������
void drawPixel(float x, float y, float alpha) {
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

float AngleOffset = 0.0f; // �������� �������� �������

// ��������� �������
void graphicsLoop()
{
	AngleOffset += SPIRAL_ANGLE_OFFSET_STEP; // ������� �������
	if (AngleOffset > 2*Pi) AngleOffset = 0; // �������� ��������, ��� ���������� 2Pi 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (float i = 0; i < SPIRAL_PIXELS; i+=SPIRAL_STEP)
	{
		drawPixel(PIXEL_AMOUNT/2+ cos(i + AngleOffset) * i, PIXEL_AMOUNT/2 + sin(i + AngleOffset) * i, 1);
	}

	glutSwapBuffers();
}

// ������ ��� ���������� ������� (��� � 1ms)
void glutTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, glutTimer, 1);
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
	std::cout << "Magic spiral test\n";

	// ������������� �������
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

	// ��������� �����
	glutMainLoop();

	return 0;
}