#include <iostream>

template <
        typename _ValT
    ,   typename _ArgT
>
static constexpr bool OR (
        _ValT && _val
    ,   _ArgT && _arg
)
{
    return _val == _arg;
}


template <
        typename _ValT
    ,   typename _ArgT
    ,   typename... _ArgsT
>
static constexpr bool OR (
        _ValT && _val
    ,   _ArgT && _arg
    ,   _ArgsT && ... _args
)
{
    return ( _val == _arg || OR( std::forward< _ValT >( _val ), std::forward< _ArgsT >( _args )... ) );
}

int main()
{
    std::cout << "OR( 1, 10, 11, 0, 1, 3, 4 ): " << std::boolalpha << OR( 1, 10, 11, 0, 1, 3, 4 ) << std::endl;
    std::cout << "OR( 2, 10, 11, 0, 1, 3, 4 ): " << std::boolalpha << OR( 2, 10, 11, 0, 1, 3, 4 ) << std::endl;

    return 0;
}
