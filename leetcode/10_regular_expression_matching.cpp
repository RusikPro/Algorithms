#include <iostream>
#include <vector>

using namespace std;

// Returns true if _s matches _p, where _p may contain:
//  '.' — matches any single character
//  '*' — matches zero or more of the preceding element
bool isMatch ( std::string const & _s, std::string const & _p )
{
    int m = _s.size(), n = _p.size();
    // dp[i][j] = whether _s[i..m-1] matches _p[j..n-1]
    std::vector< std::vector< bool > > dp(
            m + 1
        ,   std::vector< bool >( n + 1, false )
    );

    // Base case: empty pattern matches empty string
    dp[ m ][ n ] = true;

    // Fill table backwards
    for ( int i = m; i >= 0; --i )
    {
        for ( int j = n - 1; j >= 0; --j )
        {
            // Does the first character match?
            bool firstMatch = ( i < m ) && ( _p[j] == '.' || _p[j] == _s[i] );

            // If there's a '*' following _p[j]
            if ( j + 1 < n && _p[j+1] == '*' )
            {
                // Two cases:
                // 1) Skip "x*" entirely -> dp[i][j+2]
                // 2) If firstMatch, consume one _s[i] and stay on _p[j]
                dp[i][j] = dp[i][j+2] || ( firstMatch && dp[i+1][j] );
            }
            else
            {
                // No '*' -> must match one char and advance both
                dp[i][j] = firstMatch && dp[i+1][j+1];
            }
        }
    }

    // Our answer is: does _s[0..] match _p[0..] ?
    return dp[0][0];
}

int main()
{


    bool ans = isMatch("aa", "a*");
    std::cout << (ans ? "true\n" : "false\n");
    return 0;
}
