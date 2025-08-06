#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    static int lengthOfLongestSubstring(string s)
    {
        unordered_map< char, int > seq;

        // int leftLongest = 0, rightLongest = 0;
        int maxLength = 0;

        for ( int left = 0, right = 0; right < s.size(); ++right )
        {
            auto current = s[ right ];

            if ( seq.find( current ) != seq.end() && seq[ current ] >= left )
            {
                left = seq[ current ] + 1;
            }

            seq[ current ] = right;

            maxLength = max( maxLength, right - left + 1 );
        }


        return maxLength;
    }

    static int lengthOfLongestSubstring_Vector(const string& s)
    {
        int lastIndex[256];
        for (int i = 0; i < 256; ++i)
        {
            lastIndex[i] = -1;
        }


        int maxLength = 0;
        int left = 0;

        for (int right = 0; right < s.size(); ++right)
        {
            left = max(left, lastIndex[s[right]] + 1);

            maxLength = max(maxLength, right - left + 1);

            lastIndex[s[right]] = right;
        }

        return maxLength;
    }
};

int main ()
{
    auto const length = Solution::lengthOfLongestSubstring( "abcabcdab" );
    cout << length << endl;
    auto const length2 = Solution::lengthOfLongestSubstring_Vector( "abcabcdab" );
    cout << length2 << endl;
    return 0;
}
