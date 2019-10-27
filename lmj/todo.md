斯坦纳树
连分数展开，在a/b到c/d之间分母最小的有理数，
https://en.wikipedia.org/wiki/Continued_fraction
https://blog.csdn.net/lanchunhui/article/details/51719743?utm_source=blogxgwz4
最佳渐进分数， Best rational within an interval，分子分母最小
最大空凸包

http://picks.logdown.com/posts/209226-newtons-method-of-polynomial
牛顿迭代

excrt



线性基取交

交也是线性空间。

引理：如果$V1,V2$是线性空间，且$B1,B2$是基，$W=B2\cap V1$，若$B1\cup(B2 - W)$线性无关，则$W$是$V1\cap V2$的基。

证明：考虑任意的 v∈V1∩V2，那么 v 可以被 B1,B2 线性表示。考虑证明 v 可以被 W 线性表示。不妨令 v 可以被 S 和 T 共同线性表示，其中 S∈W，T∈B?W，显然，由于 S 可以被 B1 线性表示，如果 T 不为空，则 T 与 B1 显然线性相关，与题目不符。因此 v 可以直接由 W 表示出。

但是显然，B1∪(B2?W) 有可能线性相关。于是其实我们只要换一组基，即把 B2 换一下即可。

考虑 bi 表示 B2 中前 i 个向量组成的基，令我们新构造的基为 γ，第 i 个向量为 γi，则若 B2 中第 i 个向量能够被 bi?1∪B1 表示出，不妨令它能够拆分为 S+T，其中 S?bi?1,T?B1，我们令 γi=S（或者T）；否则的话 γi 就是 B2 中的第 i 个向量。

显然，这样构造出的基满足 B1∪(γ?W) 线性无关，因此问题得以在 O(d3) 的时间内解决。其中 d 为向量维数。





常系数线性递推klogklogn/k^2logn

http://picks.logdown.com/posts/197262-polynomial-division

https://wenku.baidu.com/view/bac23be1c8d376eeafaa3111.html

https://www.cnblogs.com/Troywar/p/9078013.html

数列前2k项可以暴力求，或者生成函数，然后算出闭合式之后多项式求逆



min_25筛

定期重构

拉格朗日插值



lucas/exLucas



pick定理

https://en.wikipedia.org/wiki/Gaussian_binomial_coefficient

扩展欧拉定理