import math

data_X = []
data_Y = []
for l in open('hw5_X.txt'):
	data_X.append([int(j) for j in l.split()])
for l in open('hw5_Y.txt'):
	data_Y.append(l)
prob = []
# initial value
for i in range(10):
	prob.append(0.5)

def denom(X):
	total = 1.0
	for i in range(len(X)):
		total *= ((1.0 - prob[i])**X[i])
	return 1.0 - total

def p(X, Y, i):
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

def main():
	print ll(data_X, data_Y)

if __name__ == '__main__':
	main()
