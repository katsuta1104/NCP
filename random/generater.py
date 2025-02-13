class XORshift:
    def __init__(self, seed):
        self.state = seed & 0xffffffffffffffff
        if self.state == 0:
            self.state = 88172645463325252

    def next(self):
        x = self.state
        x ^= (x << 13) & 0xffffffffffffffff
        x ^= (x >> 7)
        x ^= (x << 17) & 0xffffffffffffffff
        self.state = x & 0xffffffffffffffff
        return self.state

    def randint(self, min_n, max_n):
        range_size = max_n - min_n + 1
        max_val = 0xffffffffffffffff
        threshold = (max_val+1) - ((max_val+1) % range_size)
        while True:
            r = self.next()
            if r < threshold:
                return min_n + (r % range_size)
    
    def sequence(self, N, min_n, max_n):
        #長さNの各要素がmin_n以上max_n以下の数列を生成する
        return [self.randint(min_n, max_n) for _ in range(N)]

# 使用例
seed = 3156431638
xs = XORshift(seed)

min_n = 1
max_n = 10**9

N = 100
A = xs.sequence(N, min_n, max_n)
print(A)
