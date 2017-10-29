#pragma once

class SpaceStart {
private:
	float x_, y_; // Координаты точки (для отображения)
	float progress_; // Текущий прогресс для функции отображения
	float angle; // Угол (для функции отображения, абстрактен)
public:
	void draw() { drawPixel(x_, y_, 1.0f); } // Отрисовываем звезду
	void update() { // Обновляем координаты звезды
		progress_ += 0.01f;
		x_ = progress_;
		y_ = progress_ * tan(angle);
	};
}; 