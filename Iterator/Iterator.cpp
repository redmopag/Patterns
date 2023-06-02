#include <iostream>

template <class Item> class Iterator;
template<class Item>
class Container
{
public:
    virtual Iterator<Item>* createIterator() = 0;
    virtual ~Container() {}
};
template<class Item>
class Iterator
{
public:
    virtual void first() = 0;
    virtual Item& getCurrent() = 0;
    virtual void setCurrent(const Item& item) = 0;
    virtual bool isEnd() = 0;
    virtual void next() = 0;

    virtual ~Iterator() {}
};

template<class Item> class ArrayIterator;
template<class Item>
class Array : public Container<Item>
{
private:
    int size;
    Item* array;
public:
    Array(int size) : size(size), array(new Item[size]) {}

    virtual int getSize() { return size; }
    virtual Item& getValue(int index) { return array[index]; }
    virtual void setValue(int index, Item item) { array[index] = item; }
    Iterator<Item>* createIterator() override
    {
        return new ArrayIterator<Item>(this);
    }

    virtual ~Array() {}
};
template <class Item>
class ArrayIterator : public Iterator<Item>
{
public:
    int current;
    Array<Item>* array;
public:
    ArrayIterator(Array<Item>* array) : array(array), current(0) {}
    void first() override
    {
        current = 0;
    }
    Item& getCurrent() override
    {
        if (!isEnd())
            return array->getValue(current);
    }
    bool isEnd() override
    {
        return current == array->getSize();
    }
    void setCurrent(const Item& item) override
    {
        if (!isEnd())
            array->setValue(current, item);
    }
    void next() override
    {
        if (!isEnd())
            ++current;
    }
};

int main()
{
    const int size = 10;
    Array<int> array(size);

    Iterator<int>* it = array.createIterator();
    for (it->first(); !it->isEnd(); it->next())
        it->setCurrent(rand());

    for (it->first(); !it->isEnd(); it->next())
        std::cout << it->getCurrent() <<"\t";

    delete it;
}