#include <iostream>
#include <vector>

class Point;
class Group;

class Handler
{
public:
    virtual void handlePoint(Point* p) = 0;
    virtual void handleGroup(Group* g) = 0;
};

class Shape
{
public:
    virtual void apply(Handler* handler) = 0;
    virtual ~Shape() {}
};
class Point : public Shape
{
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
    void apply(Handler* handler) override
    {
        handler->handlePoint(this);
    }
};
class Group : public Shape
{
public:
    std::vector<Shape*> array;
    void addShape(Shape* shape)
    {
        array.push_back(shape);
    }
    ~Group()
    {
        for (auto& item : array)
            delete item;
    }
    void apply(Handler* handler) override
    {
        handler->handleGroup(this);
    }
};

class Drawer : public Handler
{
public:
    void handlePoint(Point* p) override
    {
        std::cout << "Point drawed at " << p->x << "," << p->y << "\n";
    }
    void handleGroup(Group* g) override
    {
        for (const auto& item : g->array)
            item->apply(this);
    }
};
class Mover : public Handler
{
private:
    int dx, dy;
public:
    Mover(int x, int y) : dx(x), dy(y) {}

    void handlePoint(Point* p) override
    {
        std::cout << "Point moved on " << dx << "," << dy << "\n";
        p->x += dx;
        p->y += dy;
    }
    void handleGroup(Group* g) override
    {
        for (const auto& item : g->array)
            item->apply(this);
    }
};

int main()
{
    Group* shapes = new Group();
    shapes->addShape(new Point(1, 1));
    shapes->addShape(new Point(2, 2));
    Group* childShapes = new Group();
    childShapes->addShape(new Point(3, 3));
    childShapes->addShape(new Point(4, 4));
    shapes->addShape(childShapes);

    Drawer dr;
    Mover mv(10, 10);

    shapes->apply(&dr);
    std::cout << "\n";
    shapes->apply(&mv);
    std::cout << "\n";
    shapes->apply(&dr);

    delete shapes;
}