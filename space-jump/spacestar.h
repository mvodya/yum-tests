#pragma once

class SpaceStart {
private:
	float x_, y_; // ���������� ����� (��� �����������)
	float progress_; // ������� �������� ��� ������� �����������
	float angle; // ���� (��� ������� �����������, ����������)
public:
	void draw() { drawPixel(x_, y_, 1.0f); } // ������������ ������
	void update() { // ��������� ���������� ������
		progress_ += 0.01f;
		x_ = progress_;
		y_ = progress_ * tan(angle);
	};
}; 