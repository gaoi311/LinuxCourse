#coding:utf-8

import time

def decorator_time(func):
		def wrapper():
				start_time = time.time()
				func()
				end_time = time.time()
				print("Time:", end_time - start_time)
				print("wrapper done.")
		return wrapper


@decorator_time
def sum():
		sum = 0
		for i in range(1, 101):
				sum += i
		print("result:", sum)


if __name__ == "__main__":
		sum()
