import pandas as pd
import numpy as np

# 定义数据集， 也就是那个表格， 注意这里我们采用字典存放数据， 因为实际情况中数据是非常稀疏的， 很少有情况是现在这样
def loadData():
    items={'A': {1: 5, 2: 3, 3: 4, 4: 3, 5: 1},
           'B': {1: 3, 2: 1, 3: 3, 4: 3, 5: 5},
           'C': {1: 4, 2: 2, 3: 4, 4: 1, 5: 5},
           'D': {1: 4, 2: 3, 3: 3, 4: 5, 5: 2},
           'E': {2: 3, 3: 5, 4: 4, 5: 1}
          }
    users={1: {'A': 5, 'B': 3, 'C': 4, 'D': 4},
           2: {'A': 3, 'B': 1, 'C': 2, 'D': 3, 'E': 3},
           3: {'A': 4, 'B': 3, 'C': 4, 'D': 3, 'E': 5},
           4: {'A': 3, 'B': 3, 'C': 1, 'D': 5, 'E': 4},
           5: {'A': 1, 'B': 5, 'C': 5, 'D': 2, 'E': 1}
          }
    return items,users

items, users = loadData()
item_df = pd.DataFrame(items).T
user_df = pd.DataFrame(users).T

"""计算用户相似性矩阵"""
similarity_matrix = pd.DataFrame(np.zeros((len(users), len(users))), index=[1, 2, 3, 4, 5], columns=[1, 2, 3, 4, 5])

# 遍历每条用户-物品评分数据
for userID in users:
    for otheruserId in users:
        vec_user = []
        vec_otheruser = []
        if userID != otheruserId:
            for itemId in items:   # 遍历物品-用户评分数据
                itemRatings = items[itemId]        # 这也是个字典  每条数据为所有用户对当前物品的评分
                if userID in itemRatings and otheruserId in itemRatings:  # 说明两个用户都对该物品评过分
                    vec_user.append(itemRatings[userID])
                    vec_otheruser.append(itemRatings[otheruserId])
            # 这里可以获得相似性矩阵(共现矩阵)
            similarity_matrix[userID][otheruserId] = np.corrcoef(np.array(vec_user), np.array(vec_otheruser))[0][1]
            #similarity_matrix[userID][otheruserId] = cosine_similarity(np.array(vec_user), np.array(vec_otheruser))[0][1]


"""计算前n个相似的用户"""
n = 2
similarity_users = similarity_matrix[1].sort_values(ascending=False)[:n].index.tolist()    # [2, 3]   也就是用户1和用户2


"""计算最终得分"""
base_score = np.mean(np.array([value for value in users[1].values()]))
weighted_scores = 0.
corr_values_sum = 0.
for user in similarity_users:  # [2, 3]
    corr_value = similarity_matrix[1][user]            # 两个用户之间的相似性
    mean_user_score = np.mean(np.array([value for value in users[user].values()]))    # 每个用户的打分平均值
    weighted_scores += corr_value * (users[user]['E']-mean_user_score)      # 加权分数
    corr_values_sum += corr_value
final_scores = base_score + weighted_scores / corr_values_sum
print('用户Alice对物品5的打分: ', final_scores)
user_df.loc[1]['E'] = final_scores

print(user_df)

# 基于物品的协同过滤
similarity_matrix = pd.DataFrame(np.zeros((len(items), len(items))), index=['A', 'B', 'C', 'D', 'E'], columns=['A', 'B', 'C', 'D', 'E'])

# 基于物品的协同过滤
for itemId in items:
    for otherItemId in items:
        if itemId != otherItemId:
            item_vec = []
            otherItem_vec = []
            for userId in users:
                userRatings = users[userId]
                if itemId in userRatings and otherItemId in userRatings:
                    item_vec.append(userRatings[itemId])
                    otherItem_vec.append(userRatings[otherItemId])
            similarity_matrix[itemId][otherItemId] = np.corrcoef(np.array(item_vec), np.array(otherItem_vec))[0][1]
print(similarity_matrix)

