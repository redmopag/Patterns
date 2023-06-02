#include <iostream>
#include <map>
#include <stack>
#include <conio.h>

class Shape
{
public:
    virtual void move(int x, int y) = 0;
    virtual ~Shape() {}
};
class Point : public Shape
{
private:
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}
    void move(int x, int y) override
    {
        std::cout << "Point::move(" << x << "," << y << ")\n";
        this->x += x;
        this->y += y;
    }
};
class Command
{
public:
    virtual void execute(Shape* sel) = 0;
    virtual void unexecute() = 0;
    virtual Command* clone() = 0;
    virtual ~Command() {}
};
class MoveCommand : public Command
{
private:
    Shape* sel;
    int dx, dy;
public:
    MoveCommand(int dx, int dy) : dx(dx), dy(dy), sel(nullptr) {}
    virtual void execute(Shape* sel) override
    {
        std::cout << "MoveCommand::execute(sel)\n";
        this->sel = sel;
        if (sel != nullptr)
            sel->move(dx, dy);
    }
    
    virtual void unexecute() override
    {
        std::cout << "MoveCommand::unexecute()\n";
        if (this->sel != nullptr)
            this->sel->move(-dx, -dy);
    }

    virtual Command* clone() override
    {
        return new MoveCommand(dx, dy);
    }
};

int main()
{
    std::map<char, Command*> commands;
    commands['a'] = new MoveCommand(-10, 0);
    commands['d'] = new MoveCommand(10, 0);
    commands['w'] = new MoveCommand(0, 10);
    commands['s'] = new MoveCommand(0, -10);

    Shape* shape = new Point(10, 10);
    std::stack<Command*> comhis;

    char key;
    do
    {
        key = _getch();
        Command* com = commands[key];

        if (com != nullptr)
        {
            Command* newCom = com->clone();
            newCom->execute(shape);
            comhis.push(newCom);
        }
        if (key == 'z' && !comhis.empty())
        {
            Command* lastCom = comhis.top();
            lastCom->unexecute();
            delete lastCom;
            comhis.pop();
        }
    } while (key != 27);

    while (!comhis.empty())
    {
        delete comhis.top();
        comhis.pop();
    }

    delete commands['a'];
    delete commands['d'];
    delete commands['w'];
    delete commands['s'];
    delete shape;
}