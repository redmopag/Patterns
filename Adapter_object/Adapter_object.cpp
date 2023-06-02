#include <iostream>

class IArray
{
public:
    virtual int getCount() = 0;
    virtual int getValue(int index) = 0;
};
class CArray : public IArray
{
private:
    int* array;
    int size;
public:
    CArray(int size) : size(size), array(new int[size])
    {
        for (int i = 0; i < size; ++i)
            array[i] = rand();
    }
    int getCount() override { return size; }
    int getValue(int index) override { return array[index]; }
    virtual ~CArray()
    {
        delete[] array;
    }
};
class IList
{
public:
    virtual void first() = 0;
    virtual int currentValue() = 0;
    virtual void next() = 0;
    virtual bool isEnd() = 0;
};
class ListAdapter : public IList
{
private:
    int current;
    CArray* array;
public:
    ListAdapter(CArray* array) : array(array), current(0) {}
    void first() override { current = 0; }
    bool isEnd() override
    {
        return current == array->getCount();
    }
    int currentValue() override
    {
        if (!isEnd())
            return array->getValue(current);
        else
            return NULL;
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
    CArray array(size);

    IList* list = new ListAdapter(&array);
    for (list->first(); !list->isEnd(); list->next())
        std::cout << list->currentValue() << '\t';
    std::cout << "\n";

    list->first();
    for (int i = 0; i < 10; ++i)
    {
        std::cout << list->currentValue() << '\t';
        list->next();
    }

    delete list;
}