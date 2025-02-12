class XORshift:
	def __init__(self,seed1,seed2,seed3):
		self.state1 = seed1
		self.state2 = seed2
		self.state3 = seed3
	
	def next(self):
		x1 = self.state1
		x2 = self.state2
		x3 = self.state3
		
		x1 ^= (x1<<21) & 0xFFFFFFFFFFFFFFFF
		x1 ^= (x1>>35) & 0xFFFFFFFFFFFFFFFF
		x1 ^= (x1<<4) & 0xFFFFFFFFFFFFFFFF
		
		x2 ^= (x2<<21) & 0xFFFFFFFFFFFFFFFF
		x2 ^= (x2>>35) & 0xFFFFFFFFFFFFFFFF
		x2 ^= (x2<<4) & 0xFFFFFFFFFFFFFFFF
		
		x3 ^= (x3<<21) & 0xFFFFFFFFFFFFFFFF
		x3 ^= (x3>>35) & 0xFFFFFFFFFFFFFFFF
		x3 ^= (x3<<4) & 0xFFFFFFFFFFFFFFFF
		
		self.state1 = x1
		self.state2 = x2
		self.state3 = x3
		
		res = (x1^x2^x3) & 0xFFFFFFFFFFFFFFFF
		return res
	
	def next_int(self,min_value,max_value):
		return min_value + self.next() % (max_value-min_value)

import os
seed = os.urandom(8)
print(seed)
seed1 = int.from_bytes(seed,byteorder="big")
seed2 = int.from_bytes(seed,byteorder="big")
seed3 = int.from_bytes(seed,byteorder="big")

rng = XORshift(seed1,seed2,seed3)

N = rng.next_int(1,50000)
M = rng.next_int(1,int(2e5))
print(N,M)
