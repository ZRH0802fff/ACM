from abc import ABC, abstractmethod
import math

class Activation(ABC):
    @abstractmethod
    def forward(self, x):
        pass

class ReLU(Activation):
    def forward(self, x):
        return max(0, x)

class Sigmoid(Activation):
    def forward(self, x):
        return 1 / (1 + math.exp(-x))

class Tanh(Activation):
    def forward(self, x):
        return math.tanh(x)

def apply_activation(act, x):
    return act.forward(x)

relu = ReLU()
sigmoid = Sigmoid()
tanh = Tanh()

for x in [-1, 0, 1]:
    print(apply_activation(relu, x))
    print(apply_activation(sigmoid, x))
    print(apply_activation(tanh, x))