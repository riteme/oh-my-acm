记号同whzzt18年集训队论文。 $f(x)$ 表示被求和的积性函数，并且在质数点值是是一个低阶多项式。 $h(n)=\sum\limits_{2\le p\le n \\ p是质数}f(p)$，$h_{n,m}=\sum\limits_{\begin{align} 2&\le x \le n\\ x不含\le m的&质因子或x是质数\end{align}}x^k$ ， $g_{n,m}=\sum\limits_{\begin{align} 2&\le x \le n\\ x不含\le m的&质因子或x是质数\end{align}}f(x)$，注意从 $2$ 开始。考虑线性筛的过程，每次筛掉一个最小的质数。对于 $h(n,m)$ 和 $g(n,m)$ 进行筛法时，考虑枚举 $i$ 的最小质因子，并且合数的最小质因子不超过 $\sqrt n$。

其中 $h(n)=h(n,0)$,  $h(n,m)$ 是筛 $h(n)$ 的过程，$g(n,0)$ 就是答案。

从而写出递推式（假设质数点值 $f(p)=p^k$）（这时候 $f(p)$ 是完全积性的，对下面的扣掉的性质特别好，可以在 $x\in[\lfloor{n\over p_j}\rfloor]$ 与 $p_j$ 不互质的时候也能这样直接扣掉）

$h(n,j) = h(n,j-1)-p_j^k\Big[h(\lfloor{n\over p_j}\rfloor,j-1)-h(p_{j-1})\Big]$

其中 $p_{j-1}\le \sqrt n$ 可以把 $h(p_{j-1})$ 打表，扣掉是要把最小质因子小的去掉，并且只有 $p_j^2\le n$ 时转移不为 $0$。从小到大按层转移。

$g(n,i) = g(n,i+1)+\sum\limits_{e\ge 1,p^{e+1}\le n} \Bigg[f(p_i^e)\Big[g(\lfloor{n\over p_i^e}\rfloor,i+1)-h(p_{i})\Big]+f(p_i^{e+1})\Bigg]$

同样的，只有$p_i^2<=n$ 是存在转移，分层计算即可。

初值 $h(n,0)=\sum_{i=1}^n i^k$ 全都算上，然后把不是质数的点值筛出去， $g(n,m)=h(n)$，先只计算质数上的点值，然后把合数的点值逐个加入到 $g$ 中。

最后的答案是 $g(n,0) + f(1)$。

https://blog.csdn.net/HOWARLI/article/details/80339931



卡常：把所有除法（除了算 pos 的一个）改成了实数乘法，注意到除数只可能是小于 $\sqrt n$ 的质数，因此可以预处理出来。

https://luosiyuan.blog.uoj.ac/blog/6684