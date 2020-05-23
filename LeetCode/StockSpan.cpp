/*
My solution beats 92% of other solutions in runtime and 100% in memory usage
Write a class StockSpanner which collects daily price quotes for some stock, and returns the span of that stock's price for the current day.

The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backwards) for which the price of the stock was less than or equal to today's price.

For example, if the price of a stock over the next 7 days were [100, 80, 60, 70, 60, 75, 85], then the stock spans would be [1, 1, 1, 2, 1, 4, 6].

1.Calls to StockSpanner.next(int price) will have 1 <= price <= 10^5.
2.There will be at most 10000 calls to StockSpanner.next per test case.
3.There will be at most 150000 calls to StockSpanner.next across all test cases.
4.The total time limit for this problem has been reduced by 75% for C++, and 50% for all other languages.
*/
class StockSpanner {
    private:
    vector<pair<int,int>> prices;
    public:
    StockSpanner() {}
    int next(int price) {
    prices.push_back({price,1});
        if(prices.size()==1)
            return 1;
        int count=0;
        for(int i=prices.size()-1;i>=0;i--)
        {
            if(prices[i].first<=price)
            {
                count+=prices[i].second;
                i-=(prices[i].second-1);
                continue;
            }
            if(prices[i].first>price)
                break;
        }
        prices[prices.size()-1].second=count;
        return count;
    }
};
