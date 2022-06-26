import random
from typing import List
import numpy as np

N = 64
M = 128

random.seed(1)
inputs = np.array([[random.randint(-1, 1) for _ in range(N)] for _ in range(M)])

random.seed(2)
weight = np.array([random.randint(-1, 1) for _ in range(N)])

result = []
for idx in range(M):
    result.append([1 if inputs[idx] @ weight.T > 0 else 0])

input_file_name = "inputs.txt"
output_file_name = "outputs.txt"
weight_file_name = "weight.txt"

weight = weight.tolist()
inputs = inputs.tolist()


def writeFile(fileName, datas: List):
    with open(fileName, 'w') as f:
        if type(datas[0]) is int:
            line = list(map(lambda x: str(x) + " ", datas))
            f.writelines(line)
        else:
            for idx in range(len(datas)):
                line = list(map(lambda x: str(x) + " ", datas[idx]))
                f.writelines(line)
                f.write('\n')


writeFile(input_file_name, inputs)
writeFile(weight_file_name, weight)
writeFile(output_file_name, result)
