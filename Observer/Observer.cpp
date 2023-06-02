#include <iostream>
#include <vector>

class Subject;
class Observer
{
public:
    virtual void onSubjectChange(Subject* who) = 0;
    virtual ~Observer() {}
};
class Subject
{
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer)
    {
        observers.push_back(observer);
    }
    void notify()
    {
        for (const auto& item : observers)
            item->onSubjectChange(this);
    }
    ~Subject()
    {
        for (auto& item : observers)
            delete item;
    }
};

class Cat : public Subject
{
private:
    std::string name;
    bool isHangry;
public:
    Cat(const std::string& name) : name(name), isHangry(true) {}
    void wantToEat()
    {
        std::cout << "Cat " << name << " want to eat\n";
        notify();
    }
    const std::string& getName() { return name; }
    bool Hagnry() { return isHangry; }
    void setHangry(bool isHangry) { this->isHangry = isHangry; }
};
class Owner : public Observer
{
private:
    std::string name;
public:
    Owner(const std::string& name) : name(name) {}

    void onSubjectChange(Subject* who) override
    {
        std::cout << "Owner " << name << " fed cat " << static_cast<Cat*>(who)->getName() << "\n";
        static_cast<Cat*>(who)->setHangry(false);
    }
};

int main()
{
    char num;
    std::cout << "Will the cat have a owner? 1 - yes, 0 - no: ";
    std::cin >> num;

    Observer* observer = new Owner("Mike");
    Cat* cat = new Cat("Jack");
    switch (num)
    {
    case '1':
        cat->addObserver(observer);
        break;
    default:
        break;
    }
    cat->wantToEat();
    if (cat->Hagnry())
        std::cout << "Cat Jack will find food itself\n";
    else
        std::cout << "Cat Jack has eaten\n";
}