代码中 $f(x)$ 为 $n$ 个叶子的析合树的形态数量，也是合法连续段不同的排列种类（不同当且仅当存在一个区间，在一个排列里是连续段，在另一个里不是）。

考虑根节点是析点还是合点，然后枚举子树个数，要求子树叶子和是 $n$。

####$$f(n)=\sum\limits _{k\geq 2} \prod\limits_{\sum_{i=1}^ka_i=n}f(a_i)+\sum\limits _{k\geq 4} \prod\limits_{\sum_{i=1}^ka_i=n}f(a_i) $$

