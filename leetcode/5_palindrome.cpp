#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    static string longestPalindrome(string s)
    {
        if ( s.size() == 1 )
        {
            return s;
        }
        else if ( s.size() == 0 )
        {
            return "";
        }

        int maxLeft = 0;
        int maxSize = 0;

        for ( int i = 0; i < s.size() - 1; ++i )
        {
            auto size = findPalindromes( s, i, i );

            if ( maxSize < size )
            {
                maxSize = size;
                maxLeft = i - ( size / 2 );
            }

            size = findPalindromes( s, i, i + 1 );

            if ( maxSize <= size )
            {
                maxSize = size;
                maxLeft = i - ( size / 2 ) + 1;
            }
        }

        std::cout << "maxLeft: " << maxLeft << ", maxSize: " << maxSize << std::endl;

        return s.substr( maxLeft, maxSize );
    }

    static int findPalindromes( string const & s, int left, int right )
    {
        while ( left >= 0 && right < s.size() && s[ left ] == s[ right ] )
        {
            --left;
            ++right;
        }

        return right - left - 1;
    }
};

int main ()
{
    // string s = "kasttsarbraddaror";
    // string s = "acb";
    string s = "babad";

    std::cout << "String: " << s << std::endl;

    // auto size = Solution::findPalindromes( s, 3, 3 );

    // std::cout << "left, right: " << left << ", " << right << std::endl;
    // std::cout << "Size of palindrome: " << size << std::endl;

    auto longest = Solution::longestPalindrome( s );

    std::cout << "Longest palindrome: " << longest << std::endl;


    return 0;
}

