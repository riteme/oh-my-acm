作者：XLor

## 问题

给定一个字符串 ![[公式]](https://www.zhihu.com/equation?tex=s%281%5Cle+%7Cs%7C+%5Cle+10%5E5%29) ，求最小的 ![[公式]](https://www.zhihu.com/equation?tex=k) ，使得存在 ![[公式]](https://www.zhihu.com/equation?tex=s_1%2Cs_2%2C%5Cdots%2Cs_k) ，满足 ![[公式]](https://www.zhihu.com/equation?tex=s_i%281%5Cle+i+%5Cle+k%29) 均为回文串，且 ![[公式]](https://www.zhihu.com/equation?tex=s_1%2Cs_2%2C+%5Cdots+%2Cs_k) 依次连接后得到的字符串等于 ![[公式]](https://www.zhihu.com/equation?tex=s) 。

## 暴力做法

考虑动态规划，记 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D) 表示 ![[公式]](https://www.zhihu.com/equation?tex=s) 长度为 ![[公式]](https://www.zhihu.com/equation?tex=i) 的前缀的最小划分数，转移只需要枚举以第 ![[公式]](https://www.zhihu.com/equation?tex=i+) 个字符结尾的所有回文串：![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D%3D1%2B%5Cmin_%7B+s%5Bj%2B1..i%5D+%5Ctext%7B+%E4%B8%BA%E5%9B%9E%E6%96%87%E4%B8%B2%7D+%7D+dp%5Bj%5D)

由于一个字符串最多会有 ![[公式]](https://www.zhihu.com/equation?tex=O%28n%5E2%29) 个回文子串，因此上述算法的时间复杂度为 ![[公式]](https://www.zhihu.com/equation?tex=O%28n%5E2%29) 。

显然不能接受，为了加速转移，首先给出一些引理。

## 引理与证明

> 知乎传公式太麻烦了，证明过程留作读者自行思考（误，可以自行翻阅参考资料或前往我的博客阅读 [https://xlor.cn/2019/11/mpf](http://link.zhihu.com/?target=https%3A//xlor.cn/2019/11/mpf)）

## 定义

记字符串 ![[公式]](https://www.zhihu.com/equation?tex=s) 长度为 ![[公式]](https://www.zhihu.com/equation?tex=i) 的前缀为 ![[公式]](https://www.zhihu.com/equation?tex=pre%28s%2Ci%29) ，长度为 ![[公式]](https://www.zhihu.com/equation?tex=i) 的后缀为 ![[公式]](https://www.zhihu.com/equation?tex=suf%28s%2Ci%29) 。

周期：若 ![[公式]](https://www.zhihu.com/equation?tex=0%3C+p+%5Cle+%7Cs%7C) ， ![[公式]](https://www.zhihu.com/equation?tex=%5Cforall+1+%5Cle+i+%5Cle+%7Cs%7C-p%2Cs%5Bi%5D%3Ds%5Bi%2Bp%5D) ，就称 ![[公式]](https://www.zhihu.com/equation?tex=p) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的周期。

border：若 ![[公式]](https://www.zhihu.com/equation?tex=0+%5Cle+r+%3C+%7Cs%7C) ， ![[公式]](https://www.zhihu.com/equation?tex=pre%28s%2Cr%29%3Dsuf%28s%2Cr%29) ，就称 ![[公式]](https://www.zhihu.com/equation?tex=pre%28s%2Cr%29) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border。

## 周期和 border 的关系

![[公式]](https://www.zhihu.com/equation?tex=t) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border，当且仅当 ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C-%7Ct%7C) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的周期。

证明：

若 ![[公式]](https://www.zhihu.com/equation?tex=t) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border，那么 ![[公式]](https://www.zhihu.com/equation?tex=pre%28s%2C%7Ct%7C%29%3Dsuf%28s%2C%7Ct%7C%29) ，因此 ![[公式]](https://www.zhihu.com/equation?tex=%5Cforall+1%5Cle+i+%5Cle+%7Ct%7C%2C+s%5Bi%5D%3Ds%5B%7Cs%7C-%7Ct%7C%2Bi%5D) ，所以 ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C-%7Ct%7C) 就是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的周期。

若 ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C-%7Ct%7C) 为 ![[公式]](https://www.zhihu.com/equation?tex=s) 周期，则 ![[公式]](https://www.zhihu.com/equation?tex=%5Cforall+1+%5Cle+i+%5Cle+%7Cs%7C-%28%7Cs%7C-%7Ct%7C%29%3D%7Ct%7C%2Cs%5Bi%5D%3Ds%5B%7Cs%7C-%7Ct%7C%2Bi%5D+) ，因此 ![[公式]](https://www.zhihu.com/equation?tex=pre%28s%2C%7Ct%7C%29%3Dsuf%28s%2C%7Ct%7C%29) ，所以 ![[公式]](https://www.zhihu.com/equation?tex=t) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border。

## 引理 1

![[公式]](https://www.zhihu.com/equation?tex=t) 是回文串 ![[公式]](https://www.zhihu.com/equation?tex=s) 的后缀， ![[公式]](https://www.zhihu.com/equation?tex=t) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border 当且仅当 ![[公式]](https://www.zhihu.com/equation?tex=t) 是回文串。

下图中，相同颜色的位置表示字符对应相同。



![img](https://pic4.zhimg.com/v2-2cca1d9e0b46bc47ebcb55f76f95931e_b.jpg)![img](https://pic4.zhimg.com/80/v2-2cca1d9e0b46bc47ebcb55f76f95931e_hd.jpg)



## 引理 2

![[公式]](https://www.zhihu.com/equation?tex=t) 是回文串 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border ( ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C%5Cle+2%7Ct%7C) )， ![[公式]](https://www.zhihu.com/equation?tex=s) 是回文串当且仅当 ![[公式]](https://www.zhihu.com/equation?tex=t) 是回文串。

## 引理 3

![[公式]](https://www.zhihu.com/equation?tex=t) 是字符串 ![[公式]](https://www.zhihu.com/equation?tex=s) 的 border，则 ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C-%7Ct%7C) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的周期， ![[公式]](https://www.zhihu.com/equation?tex=%7Cs%7C-%7Ct%7C) 为 ![[公式]](https://www.zhihu.com/equation?tex=s) 的最小周期，当且仅当 ![[公式]](https://www.zhihu.com/equation?tex=t) 是 ![[公式]](https://www.zhihu.com/equation?tex=s) 的最长回文真后缀。

## 引理 4

![[公式]](https://www.zhihu.com/equation?tex=x) 是一个回文串， ![[公式]](https://www.zhihu.com/equation?tex=y) 是 ![[公式]](https://www.zhihu.com/equation?tex=x) 的最长回文真后缀， ![[公式]](https://www.zhihu.com/equation?tex=z) 是 ![[公式]](https://www.zhihu.com/equation?tex=y) 的最长回文真后缀。令 ![[公式]](https://www.zhihu.com/equation?tex=u%2Cv) 分别为满足 ![[公式]](https://www.zhihu.com/equation?tex=x%3Duy%2Cy%3Dvz) 的字符串，则有下面三条性质

1. ![[公式]](https://www.zhihu.com/equation?tex=%7Cu%7C+%5Cge+%7Cv%7C) ；
2.  如果 ![[公式]](https://www.zhihu.com/equation?tex=%7Cu%7C+%3E+%7Cv%7C+) ，那么 ![[公式]](https://www.zhihu.com/equation?tex=%7Cu%7C+%3E+%7Cz%7C) ；
3.  如果 ![[公式]](https://www.zhihu.com/equation?tex=%7Cu%7C+%3D+%7Cv%7C) ，那么 ![[公式]](https://www.zhihu.com/equation?tex=u%3Dv) 。

## 推论

![[公式]](https://www.zhihu.com/equation?tex=s) 的所有回文后缀按照长度排序后，可以划分成 ![[公式]](https://www.zhihu.com/equation?tex=%5Clog+%7Cs%7C+) 段等差数列。

## 做法

有了上述结论后，我们现在可以考虑如何优化 dp 的转移。

回文树上的每个节点 ![[公式]](https://www.zhihu.com/equation?tex=u) 需要多维护两个信息， ![[公式]](https://www.zhihu.com/equation?tex=diff%5Bu%5D) 和 ![[公式]](https://www.zhihu.com/equation?tex=slink%5Bu%5D) 。 ![[公式]](https://www.zhihu.com/equation?tex=diff%5Bu%5D) 表示节点 ![[公式]](https://www.zhihu.com/equation?tex=u) 和 ![[公式]](https://www.zhihu.com/equation?tex=fail%5Bu%5D) 所代表的回文串的长度差，即 ![[公式]](https://www.zhihu.com/equation?tex=len%5Bu%5D-len%5Bfail%5Bu%5D%5D) 。 ![[公式]](https://www.zhihu.com/equation?tex=slink%5Bu%5D) 表示 ![[公式]](https://www.zhihu.com/equation?tex=u) 一直沿着 fail 向上跳到第一个节点 ![[公式]](https://www.zhihu.com/equation?tex=v) ，使得 ![[公式]](https://www.zhihu.com/equation?tex=diff%5Bv%5D+%5Cneq+diff%5Bu%5D) ，也就是 ![[公式]](https://www.zhihu.com/equation?tex=u) 所在等差数列中长度最小的那个节点。

根据上面证明的结论，如果使用 slink 指针向上跳的话，每向后填加一个字符，只需要向上跳 ![[公式]](https://www.zhihu.com/equation?tex=O%28%5Clog+%7Cs%7C%29) 次。因此，可以考虑将一个等差数列表示的所有回文串的 dp 值之和（在原问题中指 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmin) ），记录到最长的那一个回文串对应节点上。

![[公式]](https://www.zhihu.com/equation?tex=g%5Bv%5D) 表示 ![[公式]](https://www.zhihu.com/equation?tex=v) 所在等差数列的 dp 值之和，且 ![[公式]](https://www.zhihu.com/equation?tex=v) 是这个等差数列中长度最长的节点，则 ![[公式]](https://www.zhihu.com/equation?tex=g%5Bv%5D%3D%5Csum_%7Bslink%5Bx%5D%3Dv%7D+dp%5Bi-len%5Bx%5D%5D) 。

下面我们考虑如何更新 g 数组和 dp 数组。以下图为例，假设当前枚举到第 ![[公式]](https://www.zhihu.com/equation?tex=i) 个字符，回文树上对应节点为 ![[公式]](https://www.zhihu.com/equation?tex=x) 。 ![[公式]](https://www.zhihu.com/equation?tex=g%5Bx%5D) 为橙色三个位置的 dp 值之和（最短的回文串 ![[公式]](https://www.zhihu.com/equation?tex=slink%5Bx%5D) 算在下一个等差数列中）。 ![[公式]](https://www.zhihu.com/equation?tex=fail%5Bx%5D) 上一次出现位置是 ![[公式]](https://www.zhihu.com/equation?tex=i-diff%5Bx%5D) （在 ![[公式]](https://www.zhihu.com/equation?tex=i-diff%5Bx%5D) 处结束）， ![[公式]](https://www.zhihu.com/equation?tex=g%5Bfail%5Bx%5D%5D) 包含的 ![[公式]](https://www.zhihu.com/equation?tex=dp) 值是蓝色位置。因此， ![[公式]](https://www.zhihu.com/equation?tex=g%5Bx%5D) 实际上等于 ![[公式]](https://www.zhihu.com/equation?tex=g%5Bfail%5Bx%5D%5D) 和多出来一个位置的 dp 值之和，多出来的位置是 ![[公式]](https://www.zhihu.com/equation?tex=i-%28slink%5Bx%5D%2Bdiff%5Bx%5D%29) 。最后再用 ![[公式]](https://www.zhihu.com/equation?tex=g%5Bx%5D) 去更新 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D) ，这部分等差数列的贡献就计算完毕了，不断跳 ![[公式]](https://www.zhihu.com/equation?tex=slink%5Bx%5D) ，重复这个过程即可。具体实现方式可参考例题代码。



![img](https://pic4.zhimg.com/v2-7a74155a250f4318248e6104dd422c3e_b.jpg)![img](https://pic4.zhimg.com/80/v2-7a74155a250f4318248e6104dd422c3e_hd.jpg)



最后，上述做法的正确性依赖于：如果 ![[公式]](https://www.zhihu.com/equation?tex=x) 和 ![[公式]](https://www.zhihu.com/equation?tex=fail%5Bx%5D) 属于同一个等差数列，那么 ![[公式]](https://www.zhihu.com/equation?tex=fail%5Bx%5D) 上一次出现位置是 ![[公式]](https://www.zhihu.com/equation?tex=i-diff%5Bx%5D) 。

## [Codeforces 932G Palindrome Partition](http://link.zhihu.com/?target=https%3A//codeforces.com/problemset/problem/932/G)

构造字符串 ![[公式]](https://www.zhihu.com/equation?tex=t%3D%E2%80%89s%5B0%5Ds%5Bn%E2%80%89-%E2%80%891%5Ds%5B1%5Ds%5Bn%E2%80%89-%E2%80%892%5Ds%5B2%5Ds%5Bn%E2%80%89-%E2%80%893%5D+%5Cdots+s%5Bn%E2%80%89%2F%E2%80%892%E2%80%89-%E2%80%891%5Ds%5Bn%E2%80%89%2F%E2%80%892%5D) ，问题等价于求 ![[公式]](https://www.zhihu.com/equation?tex=t) 的偶回文划分方案数，把上面的转移方程改成求和形式并且只在偶数位置更新 dp 数组即可。

