import os
import random
import shutil
def run(os_path):
    image_paths = os.listdir(os_path)
    random.seed(1)
    for paths in image_paths:
        cur_path = os_path + "/" + paths
        if random.randint(0, 9) < 5:
            shutil.rmtree(path=cur_path)
            # os.removedirs(cur_path)
            print("Delete files: ", cur_path)


if __name__ == '__main__':
    path = "./datasets"
    run(path)