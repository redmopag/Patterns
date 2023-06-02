#include <iostream>

template<class Item>
class MultStrategy
{
public:
    virtual Item multiply(Item* arr, int cnt) = 0;
};
template<class Item>
class ForwardMultStrategy : public MultStrategy<Item>
{
public:
    Item multiply(Item* arr, int cnt) override
    {
        Item res = 1;
        for (int i = 0; i < cnt; ++i)
            res = res * arr[i];
        return res;
    }
};
template<class Item>
class TwiceMultStrategy : public MultStrategy<Item>
{
public:
    Item multiply(Item* arr, int cnt) override
    {
        Item res = 1;
        for (int i = 0; i < cnt - 3; i = i + 4)
            res = res * arr[i];
        return res;
    }
};
template<class Item>
class MyArray
{
private:
    int cnt;
    Item* array;
public:
    MultStrategy<Item>* strategy;
    MyArray(int cnt) : cnt(cnt), array(new Item[cnt]), strategy(nullptr)
    {
        for (int i = 0; i < cnt; ++i)
            array[i] = (Item)rand();
    }
    Item getCalculation()
    {
        if (strategy != nullptr)
            return strategy->multiply(array, cnt);
        else
            return NULL;
    }
    ~MyArray()
    {
        delete[] array;
    }
};

int main()
{
    MyArray<int> array(10);

    array.strategy = new ForwardMultStrategy<int>();
    std::cout << "Res: " << array.getCalculation();
    delete array.strategy;

    array.strategy = new TwiceMultStrategy<int>();
    std::cout << "\nRes: " << array.getCalculation();
    delete array.strategy;
}