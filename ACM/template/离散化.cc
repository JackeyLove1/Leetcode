for (int i = 1; i <= n; i++) scanf("%d", &w[i]), nums.push_back(w[i]);
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());
for (int i = 1; i <= n; i++)
    w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();
