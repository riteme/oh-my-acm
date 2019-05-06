**FWT 算法**：分治 $A → A_1, A_2$，线性变换 $T$，合并时 $A = T[A_1, A_2]^T$。逆变换时取 $T$ 的逆矩阵即可。

|卷积类型|变换|
|:-:|:-:|
| 异或卷积  | $$\left[\begin{matrix}1 & 1 \\1 & -1\end{matrix}\right],\ \left[\begin{matrix}1/2 & 1/2 \\1/2& -1/2\end{matrix}\right]$$ |
|或卷积|$$\left[\begin{matrix}1 & 0 \\1 & 1\end{matrix}\right],\ \left[\begin{matrix}1 & 0 \\-1 & 1\end{matrix}\right]$$|
|和卷积|$$\left[\begin{matrix}1 & 1 \\0 & 1\end{matrix}\right],\ \left[\begin{matrix}1 & -1 \\0 & 1\end{matrix}\right]$$|

或卷积就是子集和变换。通过按子集大小分类可在 $\mathrm O(n \log^2 n)$ 时间内计算子集卷积：

```
for i = 0 → n - 1:  // 按大小分类
  F[c][i] = f[i]
  G[c][i] = g[i]
for i = 0 → k - 1:  // 提前计算 FWT
  F[i] = fwt(F[i])
  G[i] = fwt(G[i])
for i + j = k:  // 卷积
  H[k] += F[i] · G[j]
for i in xrange(k):  // FWT 逆变换
    H[i] = rfwt(H[i])
for all subset S:  // 得到卷积结果
    R[i] = H[popcount(S)][i]
```

