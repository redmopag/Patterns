#include <iostream>

class Shape
{
public:
	virtual void draw() = 0;
	virtual ~Shape() {}
};

class Point : public Shape
{
private:
	int x, y;
public:
	void draw() override
	{
		std::cout << "Point(" << x << "," << y << ")\n";
	}
};
class Decorator : public Shape
{
private:
	Shape* shape;
public:
	Decorator(Shape* shape) : shape(shape) {}

	void draw() override
	{
		std::cout << "***\n";
		shape->draw();
		std::cout << "***\n";
	}
	~Decorator()
	{
		delete shape;
	}
};

int main()
{
	char num;
	std::cout << "Beautiful draw? 0 - no, 1 - yes: ";
	std::cin >> num;

	Shape* shape = new Point();

	switch (num)
	{
	case '1':
		shape = new Decorator(shape);
		break;
	default:
		break;
	}

	shape->draw();
	delete shape;
}