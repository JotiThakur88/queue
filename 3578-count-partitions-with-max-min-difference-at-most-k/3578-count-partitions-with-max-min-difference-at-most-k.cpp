#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        const int MOD = 1e9 + 7;

        vector<long long> dp(n + 1, 0), prefix(n + 1, 0);
        dp[0] = 1;
        prefix[0] = 1;

        deque<int> maxD, minD;
        int left = 0;

        for (int right = 0; right < n; right++) {
            // Maintain decreasing deque for max
            while (!maxD.empty() && nums[maxD.back()] <= nums[right])
                maxD.pop_back();
            maxD.push_back(right);

            // Maintain increasing deque for min
            while (!minD.empty() && nums[minD.back()] >= nums[right])
                minD.pop_back();
            minD.push_back(right);

            // Shrink window if invalid
            while (nums[maxD.front()] - nums[minD.front()] > k) {
                if (maxD.front() == left) maxD.pop_front();
                if (minD.front() == left) minD.pop_front();
                left++;
            }

            // Compute dp[right+1]
            long long ways = prefix[right];
            if (left > 0) ways = (ways - prefix[left - 1] + MOD) % MOD;

            dp[right + 1] = ways;
            prefix[right + 1] = (prefix[right] + dp[right + 1]) % MOD;
        }

        return dp[n];
    }
};