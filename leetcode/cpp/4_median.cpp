#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto s1 = nums1.size();
        auto s2 = nums2.size();

        int i = 0, j = 0;

        int medianCounter = 0;
        double median = 0;

        int globalSize = s1 + s2;
        int target = globalSize / 2;
        bool oneMore = globalSize % 2 == 0;

        if ( !oneMore )
        {
            ++target;
        }
        while ( i < s1 && j < s2 )
        {
            if ( nums1[ i ] <= nums2[ j ] )
            {
                ++medianCounter;
                if ( medianCounter == target )
                {
                    median += nums1[ i ];

                    if ( oneMore )
                    {
                        ++target;
                        oneMore = false;
                    }
                    else
                    {
                        break;
                    }
                }


                ++i;
            }
            else if ( nums1[ i ] > nums2[ j ] )
            {
                ++medianCounter;
                if ( medianCounter == target )
                {
                    median += nums2[ j ];

                    if ( oneMore )
                    {
                        ++target;
                        oneMore = false;
                    }
                    else
                    {
                        break;
                    }
                }

                ++j;
            }
        }
        if ( i == s1 )
        {
            while ( j < s2 )
            {
                ++medianCounter;
                if ( medianCounter == target )
                {
                    median += nums2[ j ];

                        if ( oneMore )
                    {
                        ++target;
                        oneMore = false;
                    }
                    else
                    {
                        break;
                    }
                }

                ++j;
            }
        }

        if ( j == s2 )
        {
            while ( i < s1 )
            {
                ++medianCounter;
                if ( medianCounter == target )
                {
                    median += nums1[ i ];

                    if ( oneMore )
                    {
                        ++target;
                        oneMore = false;
                    }
                    else
                    {
                        break;
                    }
                }

                ++i;
            }
        }

        if ( globalSize % 2 == 0 )
        {
            median /= 2;
        }

        return median;
    }
};

int main ()
{
    vector< int > v1 = { 1, 3 };
    vector< int > v2 = { 2 };

    auto median = Solution::findMedianSortedArrays( v1, v2 );
    std::cout << "Median: " << median << std::endl;

    return 0;
}
