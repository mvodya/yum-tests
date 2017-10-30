#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include <ctime>

const int WINDOW_SIZE = 800; // Размер окна
const int PIXEL_QUANTITY = 4; // Плотность пикселей
const int STARS_QUANTITY = 50000; // Количество звезд
// Вычисление количества пикселей (не общее, общее = sqrt(PIXEL_AMOUNT))
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;

// Отрисовка одного пикселя
void drawPixel(float x, float y, float color) {
	// Костыль. Смещаем пиксели в центр
	x += PIXEL_AMOUNT / 2;
	y += PIXEL_AMOUNT / 2;
	// Вычисляем размер пикселя
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

class SpaceStar {
private:
	float x_, y_; // Координаты точки (для отображения)
	float speed; // Скорость
	float progress_; // Текущий прогресс для функции отображения
	float angle; // Угол (для функции отображения, абстрактен)
	bool side;
public:
	SpaceStar() { // Конструктор 
		x_ = 0, y_ = 0, progress_ = 0; 
		angle = std::rand() % 360; 
		side = std::rand() % 2; 
		speed = 100.0f / (std::rand() % 600 + 200); 
	};
	void draw() { drawPixel(x_, y_, 1.0f); } // Отрисовываем звезду
	void update() {
		// Обновляем координаты звезды
		if (side)
			progress_ -= speed;
		else
			progress_ += speed;
		x_ = progress_;
		y_ = progress_ * tan(angle);
		if (x_ > PIXEL_AMOUNT || y_ > PIXEL_AMOUNT) {
			x_ = 0, y_ = 0, progress_ = 0;
			angle = std::rand() % 360;
			side = std::rand() % 2;
			speed = 100.0f / (std::rand() % 600 + 200);
		}
	};
}; 