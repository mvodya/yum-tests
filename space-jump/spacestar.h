#pragma once

class SpaceStar {
private:
	float x_, y_; // Координаты точки (для отображения)
	float progress_; // Текущий прогресс для функции отображения
	float angle; // Угол (для функции отображения, абстрактен)
public:
	SpaceStar() { x_ = 0, y_ = 0; progress_ = 0; angle = 1; }; // Конструктор
	void draw() { drawPixel(x_, y_, 1.0f); } // Отрисовываем звезду
	void update() { // Обновляем координаты звезды
		progress_ += 0.01f;
		x_ = progress_;
		y_ = progress_ * tan(angle);
	};
}; 