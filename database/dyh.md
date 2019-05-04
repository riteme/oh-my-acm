计算积性函数 $f(n)$ 的前缀和 $F(n) = \sum_{k = 1}^n f(k)$：先选定辅助函数 $g(n)$ 进行 Dirichlet 卷积，得到递推公式：

$$
F(n) = \frac1{g(1)}\left(\sum_{k = 1}^n(f \times g)(k) - \sum_{k = 2}^ng(k)F\left(\left\lfloor{n \over k}\right\rfloor\right)\right)
$$

对于 Euler 函数 $\varphi(n)$，选定 $g(n) = 1$，得：

$$
\Phi(n) = {n(n + 1) \over 2} - \sum_{k = 2}^n \Phi\left(\left\lfloor {n \over k} \right\rfloor\right)
$$

对于 Mobius 函数 $\mu(n)$，选定 $g(n) = 1$，得：

$$
\Mu(n) = 1 - \sum_{k = 2}^n \Mu\left(\left\lfloor {n \over k} \right\rfloor\right)
$$

如果没有预处理，时间复杂度为 $\Theta(n^{3/4})$，空间复杂度为 $\Theta(\sqrt n)$。如果预处理前 $\Theta(n^{2/3})$ 项前缀和，则时空复杂度均变为 $\Theta(n^{2/3})$。下面的代码以 Euler 函数为例，能够在 1s 内计算 $10^{10}$ 内的数据。可以多次调用。