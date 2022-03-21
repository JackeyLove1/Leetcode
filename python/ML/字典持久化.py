# json verison
# json_dic.py

import json
number = {1:1, 2:1}
for i in range(3, 11):
    number[i] = number[i - 1] + number[i - 2]
print (number)

with open('number.json', 'w') as file:
    json.dump(number, file)

with open('number.json', 'r') as file:
    data = json.load(file)

print (data)

# pickle version 
# pickle_dic.py

import pickle
number = {1:1, 2:1}
for i in range(3, 11):
    number[i] = number[i - 1] + number[i - 2]

with open('number.pickle', 'wb') as file:
    pickle.dump(number, file)

with open('number.pickle', 'rb') as file:
    data = pickle.load(file)

print (data)

# sqlite3 version 
import sqlite3
from tqdm import trange

conn = sqlite3.connect('test_sqlite3.db')
cur = conn.cursor()
try:
    sql_test_1 = '''CREATE TABLE number
                    (i NUMBER,
                     n NUMBER);'''
    cur.execute(sql_test_1)
except:
    pass
cur.execute("INSERT INTO number VALUES(1,1)")
cur.execute("INSERT INTO number VALUES(2,1)")
for i in trange(3, 11):
    sql_test_6 = "SELECT * FROM number WHERE i={}".format(i - 1)
    cur.execute(sql_test_6)
    select_result1 = cur.fetchall()[0][1]
    sql_test_7 = "SELECT * FROM number WHERE i={}".format(i - 2)
    cur.execute(sql_test_7)
    select_result2 = cur.fetchall()[0][1]
    cur.execute("INSERT INTO number VALUES({},{})".format(i, select_result1 + select_result2))

cur.execute("SELECT * FROM number WHERE i=10")
print (cur.fetchall())
conn.commit()
cur.close()
conn.close()

# shelve
import shelve

with shelve.open('data') as db:
    username = db['username'] # 建议使用db.get(key)
    password = db['password']

print(f'账号为：{username}')
print(f'密码为：{password}')