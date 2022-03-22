import math
import torch
import numpy as np
import torch.nn as nn
import torch.optim as optim
import torch.utils.data as Data

device = 'cpu'
epochs = 20
sentences = [
    # 德语和英语的单词个数不要求相同
    # enc_input                dec_input           dec_output
    ['ich mochte ein bier P', 'S i want a beer .', 'i want a beer . E'],
    ['ich mochte ein cola P', 'S i want a coke .', 'i want a coke . E']
]

# 德语和英语的单词要分开建立词库
# Padding Should be Zero
src_vocab = {'P': 0, 'ich': 1, 'mochte': 2, 'ein': 3, 'bier': 4, 'cola': 5}
src_idx2word = {i: w for i, w in enumerate(src_vocab)}
src_vocab_size = len(src_vocab)

tgt_vocab = {'P': 0, 'i': 1, 'want': 2, 'a': 3, 'beer': 4, 'coke': 5, 'S': 6, 'E': 7, '.': 8}
idx2word = {i: w for i, w in enumerate(tgt_vocab)}
tgt_vocab_size = len(tgt_vocab)

src_len = 5  # （源句子的长度）enc_input max sequence length
tgt_len = 6  # dec_input(=dec_output) max sequence length

# Transformer Parameters
d_model = 512  # Embedding Size（token embedding和position编码的维度）
d_ff = 2048  # FeedForward dimension (两次线性层中的隐藏层 512->2048->512，线性层是用来做特征提取的），当然最后会再接一个projection层
d_k = d_v = 64  # dimension of K(=Q), V（Q和K的维度需要相同，这里为了方便让K=V）
n_layers = 6  # number of Encoder of Decoder Layer（Block的个数）
n_heads = 8  # number of heads in Multi-Head Attention（有几套头）
prob = 0.1


# 构建数据集
def make_data(sentences):
    """把单词序列转换为数字序列"""
    enc_inputs, dec_inputs, dec_outputs = [], [], []
    for i in range(len(sentences)):
        enc_input = [[src_vocab[n] for n in sentences[i][0].split()]]  # [[1, 2, 3, 4, 0], [1, 2, 3, 5, 0]]
        dec_input = [[tgt_vocab[n] for n in sentences[i][1].split()]]  # [[6, 1, 2, 3, 4, 8], [6, 1, 2, 3, 5, 8]]
        dec_output = [[tgt_vocab[n] for n in sentences[i][2].split()]]  # [[1, 2, 3, 4, 8, 7], [1, 2, 3, 5, 8, 7]]

        enc_inputs.extend(enc_input)
        dec_inputs.extend(dec_input)
        dec_outputs.extend(dec_output)

    return torch.LongTensor(enc_inputs), torch.LongTensor(dec_inputs), torch.LongTensor(dec_outputs)


enc_inputs, dec_inputs, dec_outputs = make_data(sentences)


class MyDataSet(Data.Dataset):
    """自定义DataLoader"""

    def __init__(self, enc_inputs, dec_inputs, dec_outputs):
        super(MyDataSet, self).__init__()
        self.enc_inputs = enc_inputs
        self.dec_inputs = dec_inputs
        self.dec_outputs = dec_outputs

    def __len__(self):
        return self.enc_inputs.shape[0]

    def __getitem__(self, idx):
        return self.enc_inputs[idx], self.dec_inputs[idx], self.dec_outputs[idx]


loader = Data.DataLoader(MyDataSet(enc_inputs, dec_inputs, dec_outputs), 2, True)


# 位置编码
class PositionEncoding(nn.Module):
    """
    @:param inputs [seq_len, batch_size, d_model]
    @:return enc_outputs: [seq_len, batch_size, d_model]
    """

    def __init__(self, d_model, dropout=prob, max_len=5000):
        super(PositionEncoding, self).__init__()
        self.dropout = nn.Dropout(p=dropout)
        # pe [max_len, d_model]
        pe = torch.zeros(max_len, d_model)
        position = torch.arange(0, max_len, dtype=torch.float).unsqueeze(1)
        _2i = torch.arange(0, d_model, step=2, device=device, dtype=torch.float)
        pe[:, 0::2] = torch.sin(position / (10000 ** (_2i / d_model)))
        pe[:, 1::2] = torch.cos(position / (10000 ** (_2i / d_model)))
        pe = pe.unsqueeze(1)  # [max_len, batch_size, d_model]
        self.register_buffer("pe", pe)

    def forward(self, inputs):
        inputs = inputs + self.pe[:inputs.size(0)]
        return self.dropout(inputs)


# 获取掩码函数
# 掩码矩阵中的True就是填充-1e9的地方
def get_attn_pad_mask(seq_q, seq_k):
    """
    将seq_q和seq_k有效重叠的部分为有效(False)，其余为无效(True)
    seq_q: [batch_size, len_q]
    seq_k: [batch_size, len_k]
    @:return pad_mask_attn [batch_size, len_q, len_k]
    """
    batch_size, len_q = seq_q.size()
    batch_size, len_k = seq_k.size()
    pad_attn_mask = seq_k.eq(0).unsqueeze(1)
    return pad_attn_mask.repeat(1, len_q, 1)


def get_attn_subsequence_mask(seq):
    """
    获取dec_inputs自己与自己的掩码，即一个上三角矩阵往上平移一格
    seq: [batch_size, seq_len]
    @:return subsequence_mask [batch_size, seq_len, seq_len]
    """
    attn_shape = [seq.size(0), seq.size(1), seq.size(1)]
    subsequence_mask = torch.triu(torch.ones(attn_shape), diagonal=1).byte()
    return subsequence_mask


# 多头注意力
class MultiHeadAttention(nn.Module):
    """
    处理QKV
    Encoder的self-attention
    Decoder Masked-attention
    Encoder-Decoder的attention
    @:param input-q, input-k, input-v, attn-mask
    @:return outputs, attn

    """

    def __init__(self):
        super(MultiHeadAttention, self).__init__()
        """
        :param input_Q/K/V: [batch_size, len_q, d_model] -> [batch_size, len_q, d_k * n_heads] 
                    -> [batch_size, len_q, n_heads, d_k] -> [batch_size, n_heads, len_q, d_k]
        """
        self.W_Q = nn.Linear(d_model, d_k * n_heads, bias=False)
        self.W_K = nn.Linear(d_model, d_k * n_heads, bias=False)
        self.W_V = nn.Linear(d_model, d_v * n_heads, bias=False)
        self.fc = nn.Linear(d_v * n_heads, d_model, bias=False)

    def forward(self, input_Q, input_K, input_V, attn_mask):
        """
        len_q == len_k
        :param input_Q: [batch_size, len_q, d_model]
        :param input_K: [batch_size, len_k, d_model]
        :param input_V: [batch_size, len_v, d_model]
        :param attn_mask: [batch_size,  seq_len, seq_len]
        :return: outputs: [batch_size, n_heads, len_q, d_model], attn
        """
        residual, batch_size = input_Q, input_Q.size(0)
        # Q: [batch_size, n_heads, len_q, d_k]
        Q = self.W_Q(input_Q).view(batch_size, -1, n_heads, d_k).transpose(1, 2)
        K = self.W_K(input_K).view(batch_size, -1, n_heads, d_k).transpose(1, 2)
        V = self.W_V(input_V).view(batch_size, -1, n_heads, d_v).transpose(1, 2)

        # attn_mask: [batch_size, n_heads, seq_len, seq_len]
        attn_mask = attn_mask.unsqueeze(1).repeat(1, n_heads, 1, 1)

        context, attn = ScaledDotProductAttention()(Q, K, V, attn_mask)
        # print("after ScaledDP context.size: ", context.size())
        # context [batch_size, n_heads, len_q, d_v](d_v == d_k)
        context = context.transpose(1, 2).reshape(batch_size, -1, n_heads * d_v)
        # context [batch_size,len_q, d_v * n_heads]
        output = self.fc(context)
        return nn.LayerNorm(d_model).to(device)(residual + output), attn


# 点积注意力
class ScaledDotProductAttention(nn.Module):
    """
    len_q == len_k == len_v
    :param Q: [batch_size, n_heads, len_q, d_k]
    :param K: [batch_size, n_heads, len_k, d_k]
    :param V: [batch_size, n_heads, len_v, d_k]
    :param attn_mask: [batch_size, n_heads, seq_len, seq_len]
    :return: context , attn
    """

    def __init__(self):
        super(ScaledDotProductAttention, self).__init__()

    def forward(self, Q, K, V, attn_mask):
        scores = torch.matmul(Q, K.transpose(-1, -2)) / np.sqrt(d_k)
        scores.masked_fill_(attn_mask, -1e9)
        attn = nn.Softmax(dim=-1)(scores)
        # attn: [batch_size, n_heads, len_q, len_k]
        context = torch.matmul(attn, V)
        # context: [batch_size, n_heads, len_q, d_k]
        return context, attn


# PoswiseFeedForwardNet全连接层
class PoswiseFeedForwardNet(nn.Module):
    """
    本质上就是一个MLP+LayerNorm
    @:param inputs [batch_size, seq_len, d_model]
    @:return outputs [batch_size, seq_len, d_model]
    """

    def __init__(self):
        super(PoswiseFeedForwardNet, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(d_model, d_ff, bias=False),
            nn.ReLU(),
            nn.Linear(d_ff, d_model, bias=False)
        )

    def forward(self, inputs):
        """
        inputs: [batch_size, seq_len, d_model]
        """
        residual = inputs
        output = self.fc(inputs)
        return nn.LayerNorm(d_model).to(device)(output + residual)


# Encoder
class EncoderLayer(nn.Module):
    """
    enc_outputs += pe_encoding
    enc_outputs = dropout(enc_outputs)
    @:param enc_inputs, enc_self_attn_mask
    @:return enc_outputs, attn
    """

    def __init__(self):
        super(EncoderLayer, self).__init__()
        self.enc_self_attn = MultiHeadAttention()
        self.mlp = PoswiseFeedForwardNet()

    def forward(self, enc_inputs, enc_self_attn_mask):
        """
        enc_inputs: [batch_size, seq_len, d_model]
        enc_self_attn_mask: [batch_size, seq_len, seq_len]
        """
        enc_outputs, attn = self.enc_self_attn(enc_inputs, enc_inputs, enc_inputs,
                                               enc_self_attn_mask)
        enc_outputs = self.mlp(enc_outputs)
        return enc_outputs, attn


class Encoder(nn.Module):
    def __init__(self):
        super(Encoder, self).__init__()
        self.sec_emb = nn.Embedding(src_vocab_size, d_model)  # Embedding的作用是将每次词都扩展为词向量
        self.pos_emb = PositionEncoding(d_model)
        self.layers = nn.ModuleList([EncoderLayer() for _ in range(n_layers)])

    def forward(self, enc_inputs):
        """
        :param enc_inputs: [batch_size, src_len]
        """
        enc_outputs = self.sec_emb(enc_inputs)  # [batch_size, src_len, d_model]
        enc_outputs = self.pos_emb(enc_outputs.transpose(0, 1)).transpose(0, 1)
        enc_self_atten_mask = get_attn_pad_mask(enc_inputs, enc_inputs)
        for layer in self.layers:
            enc_outputs, _ = layer(enc_outputs, enc_self_atten_mask)  # enc_outputs [batch_size, src_len, d_model]
        return enc_outputs


# Decoder
class DecoderLayer(nn.Module):
    def __init__(self):
        super(DecoderLayer, self).__init__()
        self.dec_self_attn = MultiHeadAttention()
        self.dec_enc_attn = MultiHeadAttention()
        self.mlp = PoswiseFeedForwardNet()

    def forward(self, dec_inputs, enc_outputs, dec_self_attn_mask, dec_enc_attn_mask):
        """
        :param dec_inputs: [batch_size, tgt_len, d_model]
        :param enc_outputs: [batch_size, src_len. d_model]
        :param dec_self_attn_mask: [batch_size, tgt_len, tgt_len]
        :param dec_enc_attn_mask: [batch_size, tgt_len, tgt_len]
        :return: dec_outputs, dec_self_attn, dec_enc_attn
        """
        dec_outputs, dec_self_attn = self.dec_self_attn(dec_inputs, dec_inputs, dec_inputs,
                                                        dec_self_attn_mask)

        dec_outputs, dec_enc_attn = self.dec_enc_attn(dec_outputs, enc_outputs, enc_outputs,
                                                      dec_enc_attn_mask)
        dec_outputs = self.mlp(dec_outputs)
        return dec_outputs, dec_self_attn, dec_enc_attn


class Decoder(nn.Module):
    def __init__(self):
        super(Decoder, self).__init__()
        self.tgt_emb = nn.Embedding(tgt_vocab_size, d_model)
        self.pos_emb = PositionEncoding(d_model)
        self.layers = nn.ModuleList([DecoderLayer() for _ in range(n_layers)])

    def forward(self, dec_inputs, enc_inputs, enc_outputs):
        """
        :param dec_inputs: [batch_size, tgt_len]
        :param enc_inputs: [batch_size, src_len]
        :param enc_outputs: [batch_size, src_len, d_model]
        :return:
        """
        dec_outputs = self.tgt_emb(dec_inputs)
        dec_outputs = self.pos_emb(dec_outputs.transpose(0, 1)).transpose(0, 1).to(device)
        dec_self_attn_mask = get_attn_pad_mask(dec_inputs, dec_inputs).to(device)
        dec_self_attn_subsequence_mask = get_attn_subsequence_mask(dec_inputs)
        dec_self_attn_mask = torch.gt((dec_self_attn_mask + dec_self_attn_subsequence_mask), 0).to(device)
        dec_enc_attn_mask = get_attn_pad_mask(dec_inputs, enc_inputs)
        for layer in self.layers:
            dec_outputs, _, _ = layer(dec_outputs, enc_outputs, dec_self_attn_mask, dec_enc_attn_mask)
        return dec_outputs


class Transformer(nn.Module):
    def __init__(self):
        super(Transformer, self).__init__()
        self.encoder = Encoder().to(device)
        self.decoder = Decoder().to(device)
        self.projection = nn.Linear(d_model, tgt_vocab_size)

    def forward(self, enc_inputs, dec_inputs):
        '''
        enc_inputs: [batch_size, src_len]
        dec_inputs: [batch_size, tgt_len]
        '''
        enc_outputs = self.encoder(enc_inputs)
        # enc_outputs [batch_size, src_len, d_model]
        dec_outputs = self.decoder(dec_inputs, enc_inputs, enc_outputs)
        # dec_outputs: [batch_size, tgt_len, d_model]
        dec_logits = self.projection(dec_outputs)
        # dec_logits: [batch_size, tgt_len, tgt_vocab_size]
        return dec_logits.view(-1, dec_logits.size(-1))


# 训练代码
model = Transformer().to(device)
# 这里的损失函数里面设置了一个参数 ignore_index=0，因为 "pad" 这个单词的索引为 0，这样设置以后，就不会计算 "pad" 的损失（因为本来 "pad" 也没有意义，不需要计算）
criterion = nn.CrossEntropyLoss(ignore_index=0)
optimizer = optim.SGD(model.parameters(), lr=1e-3, momentum=0.99)  # 用adam的话效果不好

# ====================================================================================================
for epoch in range(epochs):
    for enc_inputs, dec_inputs, dec_outputs in loader:
        """
        enc_inputs: [batch_size, src_len]
        dec_inputs: [batch_size, tgt_len]
        dec_outputs: [batch_size, tgt_len]
        """
        enc_inputs, dec_inputs, dec_outputs = enc_inputs.to(device), dec_inputs.to(device), dec_outputs.to(device)
        # print("epoch enc_inputs type: ", type(enc_inputs))
        # outputs: [batch_size * tgt_len, tgt_vocab_size]
        outputs = model(enc_inputs, dec_inputs)
        loss = criterion(outputs, dec_outputs.view(-1))  # dec_outputs.view(-1):[batch_size * tgt_len, tgt_vocab_size]
        print('Epoch:', '%04d' % (epoch + 1), 'loss =', '{:.6f}'.format(loss))

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()


def greedy_decoder(model, enc_input, start_symbol):
    """贪心编码
    For simplicity, a Greedy Decoder is Beam search when K=1. This is necessary for inference as we don't know the
    target sequence input. Therefore we try to generate the target input word by word, then feed it into the transformer.
    Starting Reference: http://nlp.seas.harvard.edu/2018/04/03/attention.html#greedy-decoding
    :param model: Transformer Model
    :param enc_input: The encoder input
    :param start_symbol: The start symbol. In this example it is 'S' which corresponds to index 4
    :return: The target input
    """
    enc_outputs = model.encoder(enc_input)
    dec_input = torch.zeros(1, 0).type_as(enc_input.data)
    terminal = False
    next_symbol = start_symbol
    while not terminal:
        # 预测阶段：dec_input序列会一点点变长（每次添加一个新预测出来的单词）
        dec_input = torch.cat([dec_input.to(device), torch.tensor([[next_symbol]], dtype=enc_input.dtype).to(device)],
                              -1)
        dec_outputs = model.decoder(dec_input, enc_input, enc_outputs)
        projected = model.projection(dec_outputs)
        prob = projected.squeeze(0).max(dim=-1, keepdim=False)[1]
        # 增量更新（我们希望重复单词预测结果是一样的）
        # 我们在预测是会选择性忽略重复的预测的词，只摘取最新预测的单词拼接到输入序列中
        next_word = prob.data[-1]  # 拿出当前预测的单词(数字)。我们用x'_t对应的输出z_t去预测下一个单词的概率，不用z_1,z_2..z_{t-1}
        next_symbol = next_word
        if next_symbol == tgt_vocab["E"]:
            terminal = True
        # print(next_word)

    # greedy_dec_predict = torch.cat(
    #     [dec_input.to(device), torch.tensor([[next_symbol]], dtype=enc_input.dtype).to(device)],
    #     -1)
    greedy_dec_predict = dec_input[:, 1:]
    return greedy_dec_predict


# ==========================================================================================
# 预测阶段
enc_inputs, _, _ = next(iter(loader))
for i in range(len(enc_inputs)):
    greedy_dec_predict = greedy_decoder(model, enc_inputs[i].view(1, -1).to(device), start_symbol=tgt_vocab["S"])
    print(enc_inputs[i], '->', greedy_dec_predict.squeeze())
    print([src_idx2word[t.item()] for t in enc_inputs[i]], '->',
          [idx2word[n.item()] for n in greedy_dec_predict.squeeze()])
