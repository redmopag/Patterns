#include <iostream>

class Handler
{
public:
    virtual bool handler(int req) = 0;
    virtual ~Handler() {}
};
class DefaultHandler : public Handler
{
public:
    bool handler(int req) override
    {
        std::cout << req << " is prime\n";
        return false;
    }
};
class DivisionHandler : public Handler
{
private:
    int num;
    Handler* nextHandler;
public:
    DivisionHandler(int num, Handler* nextHandler) : num(num), nextHandler(nextHandler) {}
    bool handler(int req) override
    {
        if (req % num == 0)
            return true;
        else
            return nextHandler->handler(req);
    }
    ~DivisionHandler()
    {
        delete nextHandler;
    }
};

int main()
{
    Handler* queue = new DefaultHandler();
    for (int i = 2; i < 100; ++i)
        if (queue->handler(i) == false)
            queue = new DivisionHandler(i, queue);
    delete queue;
}