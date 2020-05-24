/*
My solution beats 98% solutions in runtime 
Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
Return the intersection of these two interval lists.
(Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b. 
The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  
For example, the intersection of [1, 3] and [2, 4] is [2, 3].
*/
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> result;
        int i=0,j=0;
        while(i<A.size() && j<B.size())
        {
            int left=max(A[i][0],B[j][0]);
            int right=min(A[i][1],B[j][1]);
            if(right>=left)
            result.push_back({left,right});
            else
            {
                if(A[i][0]>B[j][1])
                {
                    j++;
                    continue;
                }
                else
                {
                    i++;
                    continue;
                }
            }
            if(A[i][1]>=B[j][1])
                j++;
            else
                i++;
        }
        return result;
    }
};
