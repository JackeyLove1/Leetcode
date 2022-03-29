# df根据行列创建dataframe
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list("ABCD"))

# df转换成为numpy
df.to_numpy()

# sort
df.sort_index(axis=1, ascending=False)
df.sort_values(by="B")

# select 
df.at[dates[0], "A"] = 0
# We can also propagate non-null values forward or backward.
df.loc[:, "D"] = np.array([5] * len(df))
values = {"A": 0, "B": 1, "C": 2, "D": 3}
df.fillna(value=values)
# Only replace the first NaN element.
df.fillna(value=values, limit=1)

# 统计不重复id数目
trn_click.user_id.nunique()



# Missing Data 
df.dropna(how="any")
df.fillna(method="ffill")








# apply 
df.apply(np.cumsum)
df.apply(lambda x: x.max() - x.min())

