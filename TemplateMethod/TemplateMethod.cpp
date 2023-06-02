#include <iostream>

class Template
{
public:
    virtual void doSpecific() = 0;
    void foo()
    {
        std::cout << "D1\n";
        std::cout << "D2\n";
        doSpecific();
        std::cout << "D4\n";
    }
    virtual ~Template() {}
};
class TemplateA : public Template
{
public:
    void doSpecific() override
    {
        std::cout << "DX\n";
    }
};
class TemplateB : public Template
{
public:
    void doSpecific() override
    {
        std::cout << "DY\n";
    }
};

int main()
{
    TemplateA a;
    TemplateB b;
    a.foo();
    std::cout << "\n";
    b.foo();
}