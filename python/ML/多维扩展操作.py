import torch
queries = queries.repeat_interleave(n_repeat).reshape((-1, n_repeat))

