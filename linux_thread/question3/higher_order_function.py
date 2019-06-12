#coding:utf-8

def bar():
		print("in the bar.")
		return bar


def func(foo):
		print("in the func.")
		print(hex(id(foo)))
		print(foo)
		print(foo())

if __name__ == "__main__":
		func(bar)
