#include <bits/stdc++.h>

using namespace std;

vector<int> primes;

void prime_sieve(int n = 100) {
    vector<bool> is_prime(n + 1, true);
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (int i = p * 2; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }
}

vector<int> count_prime_factors(int N) {
    vector<int> counts;

    for (int i = 0, n = N; i < primes.size() && primes[i] <= N; i++) {
        int p = primes[i];
        int count = 0;
        for (int j = p; j <= n; j *= p) {
            count += n / j;
        }
        counts.push_back(count);
    }

    return counts;
}

int main() {
    prime_sieve();
    
    int N;
    while (cin >> N && N != 0) {
        vector<int> prime_counts = count_prime_factors(N);
        cout << setw(3) << N << "! =";
        
        for (int i = 0; i < prime_counts.size(); i++) {
            if (i > 0 && i % 15 == 0) {
                cout << endl << "      ";
            }
            cout << setw(3) << prime_counts[i];
        }
        cout << endl;
    }
    return 0;
}