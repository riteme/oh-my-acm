记号同 whzzt18 年集训队论文。$f(x)$ 表示被求和的积性函数，并且在质数点值是是一个低阶多项式。

$$
h(n) = \sum_{\substack{2 \leqslant p \leqslant n \\ p \text{ prime}}} f(p)
$$

$$
h_{n,\ m} = \sum_{\substack{2 \leqslant x \leqslant n \\ x \text{ 不含 }\leqslant m \text{ 的质因子} \\ \text{或 }x\text{ 是质数}}} x^k
$$

$$
g_{n,\ m}=\sum\limits_{\substack{2 \leqslant x \leqslant n\\ x \text{ 不含} \leqslant m\text{ 的质因子}\\ \text{或 }x\text{ 是质数}}}f(x)
$$

注意从 $2$ 开始。考虑线性筛的过程，每次筛掉一个最小的质数。对于 $h(n,\ m)$ 和 $g(n,\ m)$ 进行筛法时，考虑枚举 $i$ 的最小质因子，并且合数的最小质因子不超过 $\sqrt n$。其中 $h(n)=h(n,\ 0)$，$h(n,\ m)$ 是筛 $h(n)$ 的过程，$g(n,\ 0)$ 就是答案。从而写出递推式（假设质数点值 $f(p)=p^k$）

$$
h(n,\ j) = h(n,\ j-1) - p_j^k\left[h\left(\left\lfloor{n\over p_j}\right\rfloor,\ j-1\right) - h(p_{j-1})\right]
$$

其中 $p_{j-1} \leqslant \sqrt n$ 可以把 $h(p_{j-1})$ 打表，扣掉是要把最小质因子小的去掉，并且只有 $p_j^2\leqslant n$ 时转移不为 $0$。从小到大按层转移。

$$
\begin{aligned}
g(n,\ i) &= g(n,\ i+1) + \\
&\sum_{\substack{e\geqslant 1 \\ p^{e+1}\leqslant n}} \left[f(p_i^e)\left[g\left(\left\lfloor{n\over p_i^e}\right\rfloor,\ i+1\right) - h(p_{i})\right]+f(p_i^{e+1})\right]
\end{aligned}
$$

同样的，只有 $p_i^2 \leqslant n$ 时存在转移，分层计算即可。初值 $h(n,\ 0)=\sum_{i=1}^n i^k$ 全都算上，然后把不是质数的点值筛出去，$g(n,\ m) = h(n)$，先只计算质数上的点值，然后把合数的点值逐个加入到 $g$ 中。最后的答案是 $g(n,\ 0) + f(1)$。