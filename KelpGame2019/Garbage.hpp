#pragma once



class Garbage
{
private:
	int m_x;
	int m_y;

	int mD_garbage;


public:
	Garbage(const int& t_x, const int& t_y);
	~Garbage();


	void Draw();

	void Process(const int& t_speed);

	const int& GetX() const;
	const int& GetY() const;
};

