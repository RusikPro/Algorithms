#include <memory>
#include <iostream>

namespace custom {

template < typename _T >
class shared_ptr
{
    int * m_pCounter;
    _T * m_pData;
public:

    shared_ptr ()
        :   m_pData( nullptr )
        ,   m_pCounter( new int( 0 ) )
    {
    }

    shared_ptr ( _T * _pData )
        :   m_pData( _pData )
        ,   m_pCounter( new int( 1 ) )
    {
    }

    shared_ptr ( shared_ptr const & _other )
        :   m_pData( _other.m_pData )
        ,   m_pCounter( _other.m_pCounter )
    {
        ++*m_pCounter;
    }

    shared_ptr< _T > & operator = ( shared_ptr< _T > const & _other )
    {
        if ( this != &_other )
        {
            if ( --*m_pCounter == 0 )
            {
                delete m_pData;
                delete m_pCounter;
            }

            m_pData = _other.m_pData;
            m_pCounter = _other.m_pCounter;
            ++*m_pCounter;
        }

        return *this;
    }

    shared_ptr< _T > & operator = ( shared_ptr< _T > && _other )
    {
        if ( this != &_other )
        {
            if ( --*m_pCounter == 0 )
            {
                delete m_pData;
                delete m_pCounter;
            }

            m_pData = _other.m_pData;
            m_pCounter = _other.m_pCounter;
            _other.m_pData = nullptr;
            _other.m_pCounter = nullptr;
        }
        return *this;
    }

    ~shared_ptr ()
    {
        if ( m_pCounter && --*m_pCounter <= 0 )
        {
            delete m_pData;
            delete m_pCounter;
        }
    }
};

}

class Test {
    int i_{0};

public:
    Test() {
        std::cout << "Test()" << std::endl;
    }
    Test(int i): i_{i} {
        std::cout << "Test(" << i_ << ")" << std::endl;
    }
    ~Test() {
        std::cout << "~Test(" << i_ << ")" << std::endl;
    }
    Test(const Test& other): i_{other.i_} {
        std::cout << "Test(const&)" << std::endl;
    }
    Test(Test&& other): i_{other.i_} {
        std::cout << "Test(&&)" << std::endl;
    }
    Test& operator=(const Test& other) {
        std::cout << "operator=(const&)" << std::endl;
        i_ = other.i_;
        return *this;
    }
    Test& operator=(Test&& other) {
        std::cout << "operator=(&&)" << std::endl;
        i_ = other.i_;
        return *this;
    }
};

int main(){
    custom::shared_ptr<Test> ptr0;
    custom::shared_ptr<Test> ptr1{new Test{1}};

    {
        custom::shared_ptr<Test> ptr2{new Test{2}};

        ptr0 = ptr2;

        ptr1 = custom::shared_ptr<Test>{new Test{3}};
    }

    custom::shared_ptr<Test> ptr3 = ptr1;
    custom::shared_ptr<Test> ptr4 = ptr1;

    ptr1 = ptr1;
}

