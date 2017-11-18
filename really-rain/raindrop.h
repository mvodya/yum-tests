#pragma once
#include <ctime>

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

class RainDrop {
private:
	int size_;
	int x_, y_;
public:
	void reSpawn() {
		x_ = std::rand() % (int)PIXEL_AMOUNT;
		y_ = 0;
	}
	RainDrop() { // Конструктор
		reSpawn();
	};
	void draw() { // Отрисовываем
		drawPixel(x_, y_, 1.0f); 
	};
	void update() { // Обновляем каплю
		y_ = y_ - 1;
		if (y_ > PIXEL_AMOUNT)
			reSpawn();
	};
};