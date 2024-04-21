#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <queue>
#include <set>

bool checkOne ( std::string const & _s1, std::string const & _s2 )
{
    bool oneNotEqual = false;

    std::size_t difference = std::abs(
        static_cast< int >( _s1.size() ) - static_cast< int >( _s2.size() )
    );

    if ( difference > 1 )
        return false;

    std::size_t minimun = std::min( _s1.size(), _s2.size() );

    for ( std::size_t i = 0; i < minimun; ++i )
    {
        if ( _s1[ i ] != _s2[ i ] )
        {
            if ( oneNotEqual )
            {
                return false;
            }
            oneNotEqual = true;
        }
    }

    if ( difference == 1 )
        return true;

    return oneNotEqual;
}

std::vector< std::string > bfsFindSequence (
        std::string const & _begin
    ,   std::string const & _end
    ,   std::set< std::string > const & _dict
)
{
    std::queue< std::vector< std::string > > paths;

    paths.push( { _begin } );


    while ( !paths.empty() )
    {
        auto chain = paths.front();
        paths.pop();

        auto lastWord = chain[ chain.size() - 1 ];

        if ( lastWord == _end )
        {
            return chain;
        }

        for ( auto const & word: _dict )
        {
            if (    checkOne( lastWord, word )
                &&  std::find( chain.begin(), chain.end(), word ) == chain.end()
            )
            {
                std::vector<std::string> newChain = chain;
                newChain.push_back( word );
                paths.push( newChain );
            }
        }
    }

    return {};
}

void print ( std::vector< std::string > const & _path )
{
    for ( std::size_t i{ 0 }; i < _path.size(); ++i )
    {
        std::cout << _path[ i ];
        if ( i < _path.size() - 1 )
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

void test (
        std::string const & _name
    ,   std::string const & _begin
    ,   std::string const & _end
    ,   std::set< std::string > const & _dict
)
{
    std::cout << _name << ":" << std::endl;

    auto seq = bfsFindSequence( _begin, _end, _dict );

    if ( seq.empty() )
        std::cout << "No path from " << _begin << " to " << _end << std::endl;
    else
        print( seq );
    std::cout << std::endl;
}

int main ()
{
    std::string s1 = "catoo";

    std::string s2 = "capoo";
    std::string s3 = "cogoo";
    std::string s4 = "capto";

    std::cout << checkOne( s1, s1 ) << std::endl;
    std::cout << checkOne( s1, s2 ) << std::endl;
    std::cout << checkOne( s1, s3 ) << std::endl;
    std::cout << checkOne( s1, s4 ) << std::endl;

    std::cout << checkOne( "cat", "cats" ) << std::endl;
    std::cout << checkOne( "cat", "catty" ) << std::endl;

    test( "Direct", "cat", "rat", { "cat", "rat" } );

    test( "Several steps",
        "cat", "bad", { "cat", "bat", "bit", "bar", "bad" }
    );

    test( "No path", "cat", "arc", { "cat", "pig", "rat", "arc" } );

    test( "Different lengths",
        "cats", "cots", { "cats", "cat", "cot", "cots" }
    );

    test( "Multi-optional chain",
        "cat", "fog", { "bat", "cat", "cot", "dog", "dot", "hat", "hot", "fog" }
    );
}