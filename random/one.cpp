#include <iostream>
#include <cstdint>

class XORshift {
public:
    uint64_t state;

    XORshift(uint64_t seed) {
        state = seed & 0xffffffffffffffffULL;
        if(state == 0) {
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
        __uint128_t full = (__uint128_t)1 << 64;
        __uint128_t mod = full % range_size;
        __uint128_t threshold = full - mod;
        while (true) {
            uint64_t r = next();
            if ((__uint128_t)r < threshold) {
                return min_n + (r % range_size);
            }
        }
    }
};

int main(){
    // 任意のシード値
    uint64_t seed = 3156431638ULL;
    XORshift xs(seed);

    uint64_t min_n = 1;
    uint64_t max_n = 1000000000ULL;

    uint64_t num = xs.randint(min_n, max_n);
    std::cout << num << std::endl;
    return 0;
}
