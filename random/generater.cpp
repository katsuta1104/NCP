#include <iostream>
#include <vector>
#include <cstdint>
#include <utility> // for std::pair

using namespace std;

class XORshift {
private:
    uint64_t state;
public:
    XORshift(uint64_t seed) {
        state = seed & 0xffffffffffffffffULL;
        if (state == 0) {
            state = 88172645463325252ULL;
        }
    }

    uint64_t next() {
        uint64_t x = state;
        x ^= (x << 13);
        x ^= (x >> 7);
        x ^= (x << 17);
        state = x;
        return state;
    }

    uint64_t randint(uint64_t min_n, uint64_t max_n) {
        uint64_t range_size = max_n - min_n + 1;
        __uint128_t full = ((__uint128_t)1 << 64);
        __uint128_t mod = full % range_size;
        __uint128_t threshold = full - mod;
        while (true) {
            uint64_t r = next();
            if ((__uint128_t)r < threshold) {
                return min_n + (r % range_size);
            }
        }
    }

    // 長さ N の各要素が [min_n, max_n] の数列を生成
    vector<uint64_t> sequence(uint64_t N, uint64_t min_n, uint64_t max_n) {
        vector<uint64_t> seq;
        seq.reserve(N);
        for (uint64_t i = 0; i < N; i++) {
            seq.push_back(randint(min_n, max_n));
        }
        return seq;
    }
};

pair<uint64_t, vector<uint64_t>> generate(uint64_t seed) {
    XORshift xs(seed);
    uint64_t N, min_n, max_n;
    
    if (seed < 100ULL) {
        N = xs.randint(1, 10);
        min_n = 1;
        max_n = 10;
    }
    else if (seed < 1000ULL) {
        N = xs.randint(1, 50);
        min_n = 1;
        max_n = 100;
    }
    // 以下、ジャッジ想定
    else if (seed < 10000ULL) {
        N = xs.randint(1, 1000);
        min_n = 1;
        max_n = 1000000000ULL; // 10^9
    }
    else if (seed < 100000ULL) {
        N = xs.randint(1, 3000);
        min_n = 1;
        max_n = 1000000000ULL;
    }
    else if (seed < 1000000ULL) {
        N = xs.randint(1, 50000);
        min_n = 1;
        max_n = 1000000000ULL;
    }
    else if (seed < 10000000000ULL) { // 10^10
        N = xs.randint(1, 200000);
        min_n = 1;
        max_n = 1000000000ULL;
    }
    else {
        N = xs.randint(1, 1000000);
        min_n = 1;
        max_n = 1000000000ULL;
    }
    
    vector<uint64_t> A = xs.sequence(N, min_n, max_n);
    return make_pair(N, A);
}

int main() {
    uint64_t seed = 97ULL;
    auto result = generate(seed);
    uint64_t N = result.first;
    vector<uint64_t> A = result.second;
    return 0;
}
