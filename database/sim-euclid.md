类 Euclid 算法在模意义下计算：

$$
\sum_{k = 0}^n k^p \left\lfloor {ak + b \over c} \right\rfloor^q
$$

其中所有参数非负，在计算过程中始终保证 $K = p + q$ 不增，$a,\ c \geqslant 1$ 且 $b \geqslant 0$。需要 Bernoulli 数（$B_1 = +1/2$）来计算自然数幂前缀和 $S_p(x) = \sum_{k = 1}^x k^p = \sum_{k = 1}^{p + 1} a^{(p)}_k x^k$，其中 $a^{(p)}_k = \frac1{p + 1}{p + 1 \choose k}B_{p + 1 - k}$。代码中 `has` 为访问标记数组，**每次使用前需清空**，`val` 为记忆化使用的数组，`qpow` 是快速幂，`S` 是自然数幂前缀和，`A` 记录了 $a^{(p)}_k$，`C` 是组合数。时空复杂度为 $\mathrm O(K^3 \log \max\{a,\ c\})$。

算法主要分为三个情况，其中 $a \geqslant c$ 和 $b \geqslant c$ 的情况比较简单。当 $a,\ b < c$ 时，用 $j = \lfloor (ak + b) / c \rfloor$ 进行代换，注意最终要转化为 $\lfloor (c(j - 1) + c - b - 1) / a \rfloor < k \leqslant \lfloor (cj + c - b - 1) / a \rfloor$，再进行一次分部求和即可。注意处理 $k \leqslant n$ 这个条件。