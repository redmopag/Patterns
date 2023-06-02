#include <iostream>
#include <vector>

class Animal
{
public:
	virtual Animal* clone() = 0;
	~Animal() {}
};
class Cat : public Animal
{
public:
	Animal* clone() override
	{
		std::cout << "Cat::clone()\n";
		return new Cat(*this);
	}
	~Cat()
	{
		std::cout << "~Cat()\n";
	}
};
class Dog : public Animal
{
public:
	Animal* clone() override
	{
		std::cout << "Dog::clone()\n";
		return new Dog(*this);
	}
	~Dog()
	{
		std::cout << "~Dog()\n";
	}
};


void main()
{
	std::vector<Animal*> animals{ new Cat(), new Dog() };
	Animal* newAnimal = animals[0]->clone();
	delete newAnimal;

	newAnimal = animals[1]->clone();
	delete newAnimal;

	for (const auto& item : animals)
		delete item;
}