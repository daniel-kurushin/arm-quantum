# -*- coding: utf-8 -*-
# 
# Лабораторная работа №3
# Сеть обратного распространения ошибки.
# Сформировать обучающий вектор, обучить cеть и протестировать.
# Подобрать оптимальное число элементов скрытого слоя.
#   
# Сеть обратного распространения ошибки.
# Обучающий должен быть описан в файле D.py. Там-же определяются входные
# денные для тестирования.
# n = NN(nX, nH, nY) - Создание сети.
# n.train(d)         - Обучение сети.
# n.test(test)       - Проверка сети.
# daniel.kurushin@gmail.com
import math
import random
import string

random.seed(0)

# calculate a random number where:  a <= rand < b
def rand(a, b):
    return (b-a)*random.random() + a

# Make a matrix (we could use NumPy to speed this up)
def makeMatrix(I, J, fill=0.0):
    m = []
    for i in range(I):
        m.append([fill]*J)
    return m

# our sigmoid function, tanh is a little nicer than the standard 1/(1+e^-x)
def sigmoid(x):
    try:
        return math.tanh(x)
    except Exception as e:
        print(x)
        raise e

# derivative of our sigmoid function, in terms of the output (i.e. y)
def dsigmoid(y):
    return 1.0 - y**2

class NN:
    def __init__(self, ni, nh, no):
        # number of input, hidden, and output nodes
        self.ni = ni + 1 # +1 for bias node
        self.nh = nh
        self.no = no

        # activations for nodes
        self.ai = [1.0]*self.ni
        self.ah = [1.0]*self.nh
        self.ao = [1.0]*self.no

        # create weights
        self.wi = makeMatrix(self.ni, self.nh)
        self.wo = makeMatrix(self.nh, self.no)
        # set them to random vaules
        for i in range(self.ni):
            for j in range(self.nh):
                self.wi[i][j] = rand(-0.2, 0.2)
        for j in range(self.nh):
            for k in range(self.no):
                self.wo[j][k] = rand(-2.0, 2.0)

        # last change in weights for momentum   
        self.ci = makeMatrix(self.ni, self.nh)
        self.co = makeMatrix(self.nh, self.no)
        

    def update(self, inputs):
        if len(inputs) != self.ni-1:
            raise ValueError('wrong number of inputs')

        # input activations
        for i in range(self.ni-1):
            self.ai[i] = sigmoid(inputs[i])
            # self.ai[i] = inputs[i]

        # hidden activations
        for j in range(self.nh):
            summ = 0.0
            for i in range(self.ni):
                summ = summ + self.ai[i] * self.wi[i][j]
            self.ah[j] = sigmoid(summ)

        # output activations
        for k in range(self.no):
            summ = 0.0
            for j in range(self.nh):
                summ = summ + self.ah[j] * self.wo[j][k]
            self.ao[k] = sigmoid(summ)

        # print self.ao[:]
        return self.ao[:]


    def backPropagate(self, targets, N, M):
        if len(targets) != self.no:
            raise ValueError('wrong number of target values')

        # calculate error terms for output
        output_deltas = [0.0] * self.no
        for k in range(self.no):
            error = targets[k]-self.ao[k]
            output_deltas[k] = dsigmoid(self.ao[k]) * error

        # calculate error terms for hidden
        hidden_deltas = [0.0] * self.nh
        for j in range(self.nh):
            error = 0.0
            for k in range(self.no):
                error = error + output_deltas[k]*self.wo[j][k]
            hidden_deltas[j] = dsigmoid(self.ah[j]) * error

        # update output weights
        for j in range(self.nh):
            for k in range(self.no):
                change = output_deltas[k]*self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N*change + M*self.co[j][k]
                self.co[j][k] = change
                #print N*change, M*self.co[j][k]

        # update input weights
        for i in range(self.ni):
            for j in range(self.nh):
                change = hidden_deltas[j]*self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N*change + M*self.ci[i][j]
                self.ci[i][j] = change

        # calculate error
        error = 0.0
        for k in range(len(targets)):
            error = error + 0.5*(targets[k]-self.ao[k])**2
        return error


    def test(self, patterns):
        for p in patterns:
            x, y = [ round(x*1000) for x in self.update(p)]
            r1, r2, r3 = [ round(x*1000) for x in p ]
            print("\t (%s, %s):[%s, %s, %s], " % (x, y, r1, r2, r3))

    def weights(self):
        print('Input weights:')
        for i in range(self.ni):
            print(self.wi[i])
        print()
        print('Output weights:')
        for j in range(self.nh):
            print(self.wo[j])

    def train(self, patterns, iterations=10000, N=0.5, M=0.01):
        # N: learning rate
        # M: momentum factor
        for i in range(iterations):
            error = 0.0
            for p in patterns:
                inputs = p[0]
                targets = p[1]
                self.update(inputs)
                error = error + self.backPropagate(targets, N, M)


def demo():
    from D import D, test, nX, nH, nY
    n = NN(nX, nH, nY)   
    n.train(D)
    # print n.wi
    # print n.wo
    # print n.ci
    n.test(test)

if __name__ == '__main__':
    demo()
    
