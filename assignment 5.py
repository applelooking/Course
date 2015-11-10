import math

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
def main():
	update()
	print ("% .4f" % ll(data_X, data_Y))

if __name__ == '__main__':
	main()
