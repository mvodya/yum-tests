#pragma once
#include <ctime>

const int WINDOW_SIZE = 800;  // Размер окна
const int PIXEL_QUANTITY = 4; // Плотность пикселей
// Вычисление количества пикселей по одной стороне
const float PIXEL_AMOUNT = (float)WINDOW_SIZE / (float)PIXEL_QUANTITY;
const int RAIN_DROPS_COUNT = 200; // Количесвто капель

// Отрисовка одного пикселя
void drawPixel(float x, float y, float color) {
	float pixelSize = (1.0f / PIXEL_AMOUNT) * 2;
	// Указываем цвет
	glColor4f(0.43f, 0.65f, 1.0f, color);
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
	int length_, speed_;
public:
	// Регенерация
	void reSpawn() {
		x_ = std::rand() % (int)PIXEL_AMOUNT; // Рандомная горизонтальная позиция
		y_ = 0;
		length_ = std::rand() % 40 + 20; // Рандомная длинна
		speed_ = std::rand() % 3 + 1; // Рандомная скорость
	}

	// Конструктор
	RainDrop() {
		reSpawn();
	};

	// Отрисовываем
	void draw() {
		drawPixel(x_, y_, 1.0f);
		for (size_t i = 1; i < length_; i++)
		{
			drawPixel(x_, y_ - i, 1.0f - ((1.0f / (float)length_) * i));
		}
	};
	
	// Обновление
	void update() {
		y_ = y_ + 1 * speed_;
		if (y_ > PIXEL_AMOUNT + length_) // Если вышла за пределы экрана
			reSpawn(); // Регенерируем каплю
	};
};