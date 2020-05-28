/*
Given a non negative integer number num. 
For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.
Input 5:
Output: [0,1,1,2,1,2]
Beats 83% in runtime
*/
class Solution {
public:
    int countOnes(int n)
    {
        int count=0;
        while(n)
        {
            count+=(n&1);
            n>>=1;
        }
        return count;
    }
    vector<int> countBits(int num) {
        vector<int> count;
        for(int i=0;i<=num;i++)
        {
            count.push_back(countOnes(i));
        }
        return count;
    }
};
