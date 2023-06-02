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
private:
    int x, y, r;
public:
    Circle(int x, int y, int r) : x(x), y(y), r(r) {}
    ~Circle() {}

    void draw() override
    {
        std::cout << "Circle::draw() at " << x << " " << y << " with radius " << r << "\n";
    }
};
class ProxyCircle : public Shape
{
private:
    int x, y, r;
    Circle* circle;
public:
    ProxyCircle(int x, int y, int r) : x(x), y(y), r(r), circle(nullptr) {}
    void draw() override
    {
        std::cout << "ProxyCircle::draw()\n";
        if (circle == nullptr)
            circle = new Circle(x, y, r);
        
        circle->draw();
    }
    ~ProxyCircle()
    {
        delete circle;
    }
};

int main()
{
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(1, 2, 3));
    shapes.push_back(new ProxyCircle(4, 5, 6));
    shapes.push_back(new Circle(2, 3, 4));

    for (auto& item : shapes)
        item->draw();

    for (auto& item : shapes)
        delete item;
}