import numpy as np
import re
from collections import Counter
from typing import List
import math

# 超参数
laplace = 0.1

# 过滤词
stopwords = "about all along also although among and any anyone anything are around because " \
            "been before being both but came come coming could did each else every for from get getting going got gotten had has have having her here hers him his how " \
            "however into its like may most next now only our out particular same she " \
            "should some take taken taking than that the then there these they this those " \
            "throughout too took very was went what when which while who why will with " \
            "without would yes yet you your" \
            "com doc edu encyclopedia fact facts free home htm html http information " \
            "internet net new news official page pages resource resources pdf site " \
            "sites usa web wikipedia www " \
            "one ones two three four five six seven eight nine ten tens eleven twelve " \
            "dozen dozens thirteen fourteen fifteen sixteen seventeen eighteen nineteen " \
            "twenty thirty forty fifty sixty seventy eighty ninety hundred hundreds " \
            "thousand thousands million millions "


# --------------------------------Step0-------------------------------

# 使用正则表达式将英文单词切割
def textParse(strings):
    # 替换标点符号
    # strings.replace("'", " ")
    # strings.replace(",", " ")
    # strings.replace(".", " ")
    # 编译正则表达式引擎
    listOfWords = re.split(r"\W", strings)
    # 返回小写形式
    return [word.lower() for word in listOfWords if len(word) > 1]


# 测试testParse
def Test_testParse():
    stopLists = textParse(stopwords)
    print(stopLists)


# 全局参数
stopwords_set = set(textParse(stopwords))


# 人物信息
class person:
    def __init__(self, name, category, description):
        self.name = name
        self.category = category
        self.description = description
        self.wordList = []  # 去除过滤词的不重复单词列表

    def __str__(self):
        return "name:{}\ncategory:{}\ndescription:{}\nwordList:{}\n". \
            format(self.name, self.category, self.description, self.wordList)


# 根据person的description去除重复单词和过滤词汇
def filter_persons(p: person):
    p.wordList = sorted(set(textParse(p.description)) - stopwords_set)


# 读取txt文件，返回人物信息列表
def readTxt(path):
    persons = []
    with open(path, 'r', encoding='utf8') as f:
        file = f.read().splitlines()
        index = 0
        p = person('', '', '')
        for lines in file:
            if len(lines) > 0:  # 此行数据有效
                if index == 0:  # 表示这是人物的姓名
                    p.name = lines
                    index += 1
                elif index == 1:  # 人物分类
                    p.category = lines
                    index += 1
                else:  # 人物描述
                    p.description += lines + ' '
                    index += 1
            else:  # 遇到空行
                index = 0
                if len(p.name) > 0:  # person有效
                    persons.append(p)
                p = person('', '', '')  # 清空
        if len(p.name) > 0:
            persons.append(p)
        for p in persons:
            filter_persons(p)
        return persons


# 根据题目要求，需要将读入的文件划分为训练集和测试集
def split_persons(persons, N):
    return persons[:N], persons[N:]


# 读取txt然后将其划分为数据集和测试集
def prework(path, N):
    persons = readTxt(path)
    return split_persons(persons, N)


# 测试readTxt
def Test_readTxt():
    path = "./bioCorpus.txt"
    persons = readTxt(path)
    for p in persons:
        print(p)


# 建立一个包含在所有文档出现的不重复单词列表
def createVocabList(persons: List[person]):
    vocabSet = set([])  # 使用set去重
    for p in persons:
        vocabSet = vocabSet | set(p.wordList)
    return sorted(list(vocabSet))  # 返回list形式


# --------------------------------Step1-------------------------------

# 将训练样本中标签按字典序排序，然后计算先验概率FreqT (C) = OccT (C)/|T|
def categoryFreq(persons_train: List[person]):
    category = sorted([p.category for p in persons_train])
    # print("category: ", category)
    category_counter = Counter(category)
    # print("Counter: ", category_counter)
    # 去重
    category_list = list(set(category))
    # print("list: ", category_list)
    # 计算概率,使用字典保存
    category_freq = {}
    for category_name in category_list:
        category_freq[category_name] = category_counter[category_name] / len(category)
    # print("prob: ", category_prob)
    return category_freq


# 测试函数
def Test_categoryFreq():
    path = "./bioCorpus.txt"
    persons = readTxt(path)
    person_train, _ = split_persons(persons, 5)
    prob = categoryFreq(person_train)
    print(prob)


# 创建词向量矩阵，横轴词汇表，纵轴分类category，计算训练集中每个词在这个分类中出现的概率
# 即计算 FreqT (W|C)
def word2categoryFreq(persons_train: List[person]):
    # 获取横轴
    vocabList = createVocabList(persons_train)
    # 纵轴
    categoryOrigin = [p.category for p in persons_train]
    categoryList = sorted(list(set(categoryOrigin)))
    # 使用二维字典保存 FreqT (W|C)，初始化为0
    word2category = {}
    for vocab in vocabList:
        word2category[vocab] = {}
        for c in categoryList:
            word2category[vocab][c] = 0

    categoryNum = Counter(categoryOrigin)
    # 使用Counter计算每个单词在每个分类中出现的次数
    categoryCounter = {}
    for c in categoryList:
        categoryCounter[c] = Counter()
    for p in persons_train:
        categoryCounter[p.category] += Counter(p.wordList)
    # 计算 FreqT (W|C)
    for vocab in vocabList:
        for c in categoryList:
            if categoryCounter[c].get(vocab) is not None:
                word2category[vocab][c] = categoryCounter[c][vocab] / categoryNum[c]
            else:
                word2category[vocab][c] = 0.0
    return vocabList, categoryList, word2category


def Test_word2categoryFreq():
    path = "./bioCorpus.txt"
    persons = readTxt(path)
    person_train, _ = split_persons(persons, 5)
    prob = word2categoryFreq(person_train)
    print(prob)


# --------------------------------Step2-------------------------------
# 计算概率 For each classification C and word W, compute the probabilities using the Laplacian correction. Let  = 0.1.
# 计算P(C),返回一维字典
def categoryProb(categoryFreq: dict):
    category_prob = {}
    for c, freq in categoryFreq.items():
        category_prob[c] = (freq + laplace) / (1 + len(categoryFreq) * laplace)
    return category_prob


# 计算P(W|C)，返回二维字典
def word2categoryProb(vocabList: List, categoryList: List, word2category: dict):
    word2category_prob = {}
    for vocab in vocabList:
        word2category_prob[vocab] = {}
        for c in categoryList:
            word2category_prob[vocab][c] = (word2category[vocab][c] + laplace) / (1 + 2 * laplace)
    return word2category_prob


# --------------------------------Step3-------------------------------
# 计算负对数 Compute negative log probabilities to avoid underflow
nlog = lambda x: -math.log(x, 2)  # 计算以2为底的对数


def categoryProbLog(categoryProb: dict):
    category_log = {}
    for c, prob in categoryProb.items():
        category_log[c] = nlog(prob)
    return category_log


# 计算P(W|C)，返回二维字典
def word2categoryProbLog(vocabList: List, categoryList: List, word2category_prob: dict):
    word2category_log = {}
    for vocab in vocabList:
        word2category_log[vocab] = {}
        for c in categoryList:
            word2category_log[vocab][c] = nlog(word2category_prob[vocab][c])
    return word2category_log


def Test_Log():
    path = "./bioCorpus.txt"
    persons = readTxt(path)
    person_train, _ = split_persons(persons, 5)
    vocabList, categoryList, word2category = word2categoryFreq(person_train)
    word2category_prob = word2categoryProb(vocabList, categoryList, word2category)
    print("prob: ", word2category_prob)
    word2category_log = word2categoryProbLog(vocabList, categoryList, word2category_prob)
    print("log: ", word2category_log)


def trainNativeBayes(persons_train: List[person]):
    """
    :param persons_train:
    :return:
    """
    # 计算L(C)
    category_freq = categoryFreq(persons_train)
    category_prob = categoryProb(category_freq)
    category_log = categoryProbLog(category_prob)

    # 计算L(W/C)
    vocabList, categoryList, word2category = word2categoryFreq(persons_train)
    word2category_prob = word2categoryProb(vocabList, categoryList, word2category)
    word2category_log = word2categoryProbLog(vocabList, categoryList, word2category_prob)

    return vocabList, categoryList, category_log, word2category_log


# --------------------------------Step4-------------------------------
# Applying the classifier to the test data
# 使用训练的分类器应用于测试数据集
# The prediction of the algorithm is the category C with the smallest value of L(C|B).
def classifyPerson(p: person, vocabList: List, categoryList: List, category_log: dict, word2category_log: dict):
    category_classify = {}
    p.wordList = set(p.wordList) & set(vocabList)  # 只保留训练集中的词汇
    for c in categoryList:
        category_classify[c] = category_log[c]
        for vocab in p.wordList:
            category_classify[c] += word2category_log[vocab][c]
    # 计算各个类别的概率
    m = min(list(category_classify.values()))  # 分类最小值
    classify_prob = {}
    for c in categoryList:
        ci = category_classify[c]
        if ci - m < 7:
            classify_prob[c] = 2 ** (ci - m)
        else:
            classify_prob[c] = 0
    s = sum(classify_prob.values())
    for c in categoryList:
        classify_prob[c] = classify_prob[c] / s
    return classify_prob


def output(p: person, categoryList: List, classify_prob: dict):
    prediction = ""
    prob = 0
    for c in categoryList:
        if classify_prob[c] > prob:
            prob = classify_prob[c]
            prediction = c
    flag = "Right." if prediction == p.category else "Wrong."
    print("{}\t Prediction:{}\t {}".format(p.name, prediction, flag))
    probility = ""
    for c in categoryList:
        probility += "%s:%.2f   " % (c, classify_prob[c])
    print(probility)


def Test_classify():
    path = "./bioCorpus.txt"
    N = 10
    persons_train, persons_test = prework(path, N)
    vocabList, categoryList, category_log, word2category_log = trainNativeBayes(persons_train)
    for p in persons_test:
        classify_prob = classifyPerson(p, vocabList, categoryList, category_log, word2category_log)
        output(p, categoryList, classify_prob)


if __name__ == "__main__":
    Test_classify()
