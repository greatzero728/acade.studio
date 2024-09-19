#include <iostream>
#include <cmath>
using namespace std;

//return total lenght of d-digits numbers from first block up to n-th block
long long count(int d, int n) {
    // blocks that fully contains all d-digit numbers (blocks that start from 10^d up to n).
    long long greater_cnt = n - pow(10, d) + 1;
    long long ans = greater_cnt * 9 * pow(10, d - 1) * d;

    // blocks that partially contains d-digit numbers:

    // in case n is less than 10^d, count only d-digit numbers from 10^(d-1) block up to n-th block
    if (ans < 0) {
        long long first = 1, last = n - pow(10LL, d-1) + 1;
        ans = (last - first + 1) * (last + first) / 2;
        ans *= d;
    }
    // in case n is greater or equal to 10^d, all d-digit numbers from block 10^{d-1) to 10^d will be included
    else {
        long long first = 1, last = pow(10LL, d) - pow(10LL, d-1);
        ans += ((last - first + 1) * (last + first) / 2) * d;
    }
    return ans;
}

// return total lenght of numbers from first block up to the n-th block
long long check(int n) {
    long long total_lenght = 0;
    for(int d = 1; d <= 1 + floor(log10(n)); d++) {
        total_lenght += count(d, n);
    }
    return total_lenght;
}

// function that find k-th digit in the block (12345....)
void find_digit(long long k)
{
    long long res = -1;
    int digits_lenght = 1;
    long long left = 1, right = 9;   // range of 1 digit numbers
    while (1)
    {
        long long tot = (right - left + 1) * digits_lenght;
        // check if k-th digit is in this range
        if (k <= tot)
        {
            long long oleft = left, oright = right;
            while (left <= right)
            {
                long long mid = left + (right - left) / 2;
                long long passedDigits = (mid - oleft + 1) * digits_lenght;
                if (k <= passedDigits)
                {
                    res = mid;
                    right = mid - 1;
                }
                else left = mid + 1;
            }
            string ans = to_string(res);
            cout << ans[(k - 1) % digits_lenght] << '\n';
            return ;
        }
        // not in this range
        else k -= tot;
        // increment the digits count;
        digits_lenght++;
        left = right + 1, right = (right * 10 + 9);   // range of 'digits_lenght' digit numbers; 
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long k;
        cin >> k;
        long long block = 0;
        long long l = 1, r = 1;
        while (check(r) < k)
            r *= 2;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(mid) >= k)
            {
                block = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        k -= check(block - 1);
        find_digit(k);
    }
}