import pandas as pd #导入pandas包
# 导入数据集
ratings = pd.read_csv('Desktop/ratings.csv')    
print (ratings.head(20)) 

movies = pd.read_csv('Desktop/movies.csv') 
print(movie.head(5))

# 更具关联ID合并两个数据集
data = pd.merge(movies,ratings,on = 'movieId')
print(data.head(5))
data[['userId','rating','movieId','title']].sort_values('userId').to_csv('Desktop/data.csv',index=False)
# 将合并后的数据集输出保存到桌面 以备后续分析
files = pd.read_csv('Desktop/data.csv')
print(file.head(5))

# 添加信息到字典
# 逐行读取刚刚合并并保存的数据集
content = []
with open('Desktop/data.csv') as fp:  
    content = fp.readlines()

# 将用户、评分、和电影写入字典data
data = {}
for line in content[1:100]:
    line = line.strip().split(',')
    #如果字典中没有某位用户，则使用用户ID来创建这位用户
    if not line[0] in data.keys():
        data[line[0]] = {line[3]:line[1]}
    #否则直接添加以该用户ID为key字典中
    else:
        data[line[0]][line[3]] = line[1]


data 

# 计算两者间的欧式距离，然后计算相似度
from math import *
def Euclidean(user1,user2):
    #取出两位用户评论过的电影和评分
    user1_data=data[user1]
    user2_data=data[user2]
    distance = 0
    #找到两位用户都评论过的电影，并计算欧式距离
    for key in user1_data.keys():
        if key in user2_data.keys():
            #注意，distance越大表示两者越相似
            distance += pow(float(user1_data[key])-float(user2_data[key]),2)
 
    return 1/(1+sqrt(distance))#这里返回值越小，相似度越大
 
#计算某个用户与其他用户的相似度
def top10_simliar(userID):
    res = []
    for userid in data.keys():
        #排除与自己计算相似度
        if not userid == userID:
            simliar = Euclidean(userID,userid)
            res.append((userid,simliar))
    res.sort(key=lambda val:val[1])
    return res[:4]
 
RES = top10_simliar('1')
print(RES)
# 用户之间相似度结果：0表示两位的影评几乎一样，1表示没有共同的影评

# 根据相似度来推荐用户
def recommend(user):
    #相似度最高的用户
    top_sim_user = top10_simliar(user)[0][0]
    #相似度最高的用户的观影记录
    items = data[top_sim_user]
    recommendations = []
    #筛选出该用户未观看的电影并添加到列表中
    for item in items.keys():
        if item not in data[user].keys():
            recommendations.append((item,items[item]))
    recommendations.sort(key=lambda val:val[1],reverse=True)#按照评分排序
    #返回评分最高的10部电影
    return recommendations[:10]
 
Recommendations = recommend('1')
print(Recommendations）
