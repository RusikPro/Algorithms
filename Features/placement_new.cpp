#include <cstdlib>
#include <iostream>

class MyClass {

public:
    int m_setVar;

    MyClass()  {
        m_setVar = 10;
        std::cout << "Constructor called.\n"; }
    ~MyClass() { std::cout << "Destructor called.\n"; }
};

int main()
{
    void * raw = std::malloc( sizeof(MyClass) );

    std::cout << "Var before placement-new: " << static_cast< MyClass * >(raw)->m_setVar << std::endl;

    // Making constructor to be called with placement-new
    new (raw) MyClass();
    // Or: MyClass * obj = ...

    std::cout << "Var after placement-new: " << static_cast< MyClass * >(raw)->m_setVar << std::endl;

    static_cast< MyClass * >(raw)->~MyClass();

    // Manually call the destructor
    // obj->~MyClass();

    std::free( raw );

    std::cout << "--------" << std::endl;

    auto * raw2 = new MyClass();

    delete raw2;

    return 0;
}
