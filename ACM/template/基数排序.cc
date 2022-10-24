inline void radix_sort(unsigned A[], int len)
{
    unsigned *B = new unsigned[len];
    int r = 65535, L[r + 1] = {0}, H[r + 1] = {0};
    for (int i = 0; i < len; ++i)
        L[A[i] & r]++, H[(A[i] >> 16) & r]++; // 计数
    for (int i = 1; i <= r; ++i)
        L[i] += L[i - 1], H[i] += H[i - 1]; // 求前缀和
    for (int i = len - 1; i >= 0; --i)
        B[--L[A[i] & r]] = A[i]; // 对低位进行计数排序
    for (int i = len - 1; i >= 0; --i)
        A[--H[(B[i] >> 16) & r]] = B[i]; // 对高位进行计数排序
    delete[] B;
}