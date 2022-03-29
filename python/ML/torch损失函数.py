import torch 

# 均方损失函数，回归问题
torch.nn.MSELoss()

# 平均绝对值误差损失	回归
torch.nn.L1Loss()

# 交叉熵损失	多分类
torch.nn.CrossEntropyLoss()

# 负对数似然函数损失	多分类
torch.nn.NLLLoss()

# 图片负对数似然函数损失	图像分割
torch.nn.NLLLoss2d()

# KL散度损失	回归
torch.nn.KLDivLoss()	

# 二分类交叉熵损失	二分类
torch.nn.BCELoss()

# 评价相似度的损失
torch.nn.MarginRankingLoss()	

# 多标签分类的损失	多标签分类
torch.nn.MultiLabelMarginLoss()

# 平滑的L1损失	回归
torch.nn.SmoothL1Loss()

# 多标签二分类问题的损失	多标签二分类
torch.nn.SoftMarginLoss()

