import math
import matplotlib.pyplot as plt

# question 5.2 code
data_X = []
data_Y = []
for l in open('hw5_X.txt'):
	data_X.append([int(j) for j in l.split()])
for l in open('hw5_Y.txt'):
	data_Y.append(int(l))
prob = []
# initial value
for i in range(10):
	prob.append(0.5)

def denom(X):
	total = 1.0
	for i in range(len(X)):
		total *= ((1.0 - prob[i])**X[i])
	return 1.0 - total

def pr(X, Y, i):
	return Y * 1.0 * X[i] * prob[i] / denom(X)

def p(X, Y):
	tmp = denom(X)
	if Y == 1:
		return tmp
	else :
		return 1.0 - tmp

def ll(X_list, Y_list):
	total = 0.0
	for i in range(len(Y_list)):
		total += math.log(p(X_list[i], Y_list[i]))
	return total / len(Y_list)

def update():
	global prob
	tmp = list(prob)
	for i in range(len(tmp)):
		total = 0.0
		counter = 0
		for j in range(len(data_Y)):
			total += pr(data_X[j], data_Y[j], i)
			if data_X[j][i] == 1:
				counter += 1
		tmp[i] = total / counter
	prob = tmp


def main2():
	update()
	print ("% .4f" % ll(data_X, data_Y))


# question 5.3 code
x = 0.0
def derived_f(x):
	return math.tanh(x)

def update_3_f():
	global x
	x = x - derived_f(x)

def main_3_f():
	global x
	x = 3
	x_axis = []
	y_axis = []
	for i in range(50):
		x_axis.append(i)
		y_axis.append(x)
		update_3_f()
	plt.figure().canvas.set_window_title('the figure of 5.3 f')
	plt.plot(x_axis, y_axis)
	plt.ylabel('the number of x')
	plt.xlabel('number of iteration')
	plt.axis([0,60,-3, 3])
	plt.show()

def derived_derived_f(x):
	total = math.cosh(x) * math.cosh(x)
	return 1 / total

def update_3_g():
	global x
	x = x - derived_f(x) / derived_derived_f(x)

def main_3_g():
	global x
	x = 1
	x_axis = []
	y_axis = []
	for i in range(50):
		x_axis.append(i)
		y_axis.append(x)
		update_3_g()
	plt.figure().canvas.set_window_title('the figure of 5.3 g')
	plt.plot(x_axis, y_axis)
	plt.ylabel('the number of x')
	plt.xlabel('number of iteration')
	plt.axis([0,60,-3, 3])
	plt.show()

def derived_g(x):
	total = 0.0
	for k in range(1, 11):
		total += math.tanh(x + 1/ math.sqrt(k))
	return total / 10.0

def update_3_k():
	global x
	x = x - derived_g(x)

def g(x):
	total = 0.0
	for k in range(1, 11):
		total += math.log(math.cosh(x + 1 / math.sqrt(k)))
	return total / 10

def main_3_k():
	global x
	x = 1
	x_axis = []
	y_axis = []
	for i in range(50):
		x_axis.append(i)
		y_axis.append(x)
		update_3_k()
	plt.figure().canvas.set_window_title('the figure of 5.3 k')
	plt.plot(x_axis, y_axis)
	plt.ylabel('the number of x')
	plt.xlabel('number of iteration')
	plt.axis([0,60,-3, 3])
	plt.show()
	print y_axis[-1]
	print g(y_axis[-1])

if __name__ == '__main__':
	# main_3_g()
	main_3_k()