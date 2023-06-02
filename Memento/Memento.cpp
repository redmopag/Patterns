#include <iostream>
#include <memory>

class Memento
{
private:
    virtual void setState(int x, int y) = 0;
    virtual void getState(int& x, int& y) = 0;
public:
    virtual ~Memento() {}
};
class PointMemento : public Memento
{
private:
    friend class Point;
    int x, y;
    void setState(int x, int y) override
    {
        this->x = x;
        this->y = y;
    }
    void getState(int& x, int& y) override
    {
        x = this->x;
        y = this->y;
    }
    PointMemento() : x(0), y(0) {}
};
class Point
{
private:
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}
    void move(int dx, int dy)
    {
        std::cout << "Point::move(" << dx << "," << dy << ")\n";
        x += dx;
        y += dy;
    }
    void report()
    {
        std::cout << "Point(" << x << "," << y << ")\n";
    }
    Memento* createMemento()
    {
        PointMemento* memento = new PointMemento();
        memento->setState(x, y);
        return memento;
    }
    void updateMemnto(Memento* memento)
    {
        PointMemento* ownMemento = dynamic_cast<PointMemento*>(memento);
        if (ownMemento != nullptr)
            ownMemento->getState(x, y);
    }
    virtual ~Point() {}
};

int main()
{
    Point point(10, 20);
    point.report();

    Memento* memento = point.createMemento();
    point.move(10, 20);
    point.report();

    point.updateMemnto(memento);
    point.report();

    delete memento;
}