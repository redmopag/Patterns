#include <iostream>
#include <vector>

class Shape
{
public:
	virtual void draw() = 0;
	virtual ~Shape() {}
};
class Circle : public Shape
{
public:
	void draw() override
	{
		std::cout << "Draw Circle\n";
	}
};
class Composite : public Shape
{
private:
	std::vector<Shape*> shapes;
public:
	void addShape(Shape* shape)
	{
		shapes.push_back(shape);
	}
	void draw() override
	{
		std::cout << "Draw Composite\n";
		for (const auto& item : shapes)
			item->draw();
	}
	~Composite()
	{
		for (const auto& item : shapes)
			delete item;
	}
};

int main()
{
	int count = 5;
	Shape* shape;
	Composite* shapes = new Composite;
	Composite* child = new Composite;

	child->addShape(new Circle());
	child->addShape(new Circle());

	for (int i = 0; i < count; ++i)
	{
		shape = new Circle;
		shapes->addShape(shape);
	}
	shapes->addShape(child);

	shapes->draw();

	delete shapes;
}