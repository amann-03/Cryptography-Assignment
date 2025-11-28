#include <iostream>   // cin, cout, cerr
#include <climits>    // LLONG_MAX

using namespace std;

// ---------- Prime detector: trial division ----------
bool is_prime(long long x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;

    // Check odd divisors up to sqrt(x)
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

// ---------- nth-prime computer using the detector ----------
bool nth_prime(long long n, long long &result) {
    if (n <= 0) return false;                // invalid request

    long long count = 0;
    long long x = 1;

    // Use upper bound of signed 64-bit integers
    const long long LIMIT = LLONG_MAX;

    while (true) {
        if (x == LIMIT) return false;        // would overflow going further
        ++x;

        if (is_prime(x)) {
            ++count;
            if (count == n) {
                result = x;
                return true;
            }
        }
    }
}

// ---------- Driver / test harness ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cout << "Enter n to compute the nth prime number : " << endl;

    if (!(cin >> n)) {
        cerr << "Error: failed to read n.\n";
        return 1;
    }

    long long p;
    bool ok = nth_prime(n, p);

    if (!ok) {
        cerr << "Error: could not compute the " << n
             << "-th prime within 64-bit limits.\n";
        return 1;
    }

    cout << "The " << n << "th prime number is : " << p << "\n";
    return 0;
}
