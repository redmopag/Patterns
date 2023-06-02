#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>

class Shape
{
protected:
	int x, y;
public:
	Shape(int x, int y) : x(x), y(y) {}

	virtual void save(FILE *stream) = 0;
	virtual void load(FILE *stream) = 0;
	virtual ~Shape() {};
};
class AbstractFactory
{
public:
	virtual Shape* createShape(char code) = 0;
	virtual ~AbstractFactory() {};
};
class ShapeArray
{
private:
	std::vector<Shape*> array;
public:
	void loadShapes(std::string fileName, AbstractFactory& factory)
	{
		FILE* stream;
		int count;
		if ((stream = fopen(fileName.c_str(), "r")) != nullptr)
		{
			char code;
			Shape* shape;
			fscanf(stream, " %d\n", &count);
			for (int i = 0; i < count; ++i)
			{
				fscanf(stream, " %c\n", &code);
				shape = factory.createShape(code);
				if (shape != nullptr)
				{
					shape->load(stream);
					array.push_back(shape);
				}
			}
		}
		fclose(stream);
	}
	virtual ~ShapeArray()
	{
		for (const auto& shape : array)
			delete shape;
	}
};

class Circle : public Shape
{
private:
	int radius;
public:
	Circle(int x, int y, int radius) : Shape(x, y), radius(radius) {}

	void save(FILE* stream) override
	{
		fprintf(stream, "C\n");
		fprintf(stream, "x=%d y=%d rad=%d\n", x, y, radius);
	}
	void load(FILE* stream) override
	{
		fscanf(stream, "%d %d %d\n", &x, &y, &radius);
	}
};
class Square : public Shape
{
private:
	int bone;
public:
	Square(int x, int y, int bone) : Shape(x, y), bone(bone) {}
	void save(FILE* stream) override
	{
		fprintf(stream, "S\n");
		fprintf(stream, "x=%d y=%d bone=%d\n", x, y, bone);
	}
	void load(FILE* stream) override
	{
		fscanf(stream, "%d %d %d\n", &x, &y, &bone);
	}
};
class ShapeFactory : public AbstractFactory
{
public:
	Shape* createShape(char code) override
	{
		Shape* shape = nullptr;
		switch (code)
		{
		case 'C':
			shape = new Circle(0,0, 0);
			break;
		case 'S':
			shape = new Square(0, 0, 0);
			break;
		default:
			break;
		}
		return shape;
	}
};

void main()
{
	std::string fileName = "data.txt";
	FILE* stream;
	Shape* shape;

	if ((stream = fopen(fileName.c_str(), "w")) != nullptr)
	{
		fprintf(stream, "%d\n", 2);
		shape = new Circle(2, 1, 2);
		shape->save(stream);
		delete shape;

		shape = new Square(2, 2, 2);
		shape->save(stream);
		delete shape;

		fclose(stream);
	}

	ShapeFactory factory;
	ShapeArray array;
	array.loadShapes(fileName, factory);
}