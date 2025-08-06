#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum_n2(vector<int>& nums, int target)
    {
        auto n = nums.size();
        for ( int left = 0; left < n - 1; ++left )
        {
            for ( int right = left + 1; right < n; ++right )
            {
                if ( nums[ left ] + nums[ right ] == target )
                {
                    vector< int > result{ left, right };
                    return result;
                }
            }
        }

        return {};
    }

    vector<int> twoSum(vector<int>& nums, int target)
    {
        auto n = nums.size();

        vector< pair< int, int > > numsSorted; // value, initial index

        for ( int i = 0; i < n; ++i )
        {
            numsSorted.emplace_back( nums[ i ], i );
        }

        sort( numsSorted.begin(), numsSorted.end() );

        auto left = 0;
        auto right = n - 1;

        while ( left < right )
        {
            auto sum = numsSorted[ left ].first + numsSorted[ right ].first;
            if ( sum == target )
            {
                return { numsSorted[ left ].second, numsSorted[ right ].second };
            }
            else if ( sum < target )
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return {};
    }

    vector<int> twoSum_n(vector<int>& nums, int target)
    {
        unordered_map<int, int> numMap;
        for (int i = 0; i < nums.size(); ++i)
        {
            int diff = target - nums[i];
            if (numMap.find(diff) != numMap.end())
            {
                return { numMap[ diff ], i };
            }
            numMap[ nums[ i ] ] = i;
        }
        return {};
    }
};