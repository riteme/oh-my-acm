## 简介

Lindström–Gessel–Viennot lemma，即 LGV 引理，可以用来处理有向无环图上不相交路径计数等问题。

前置知识：[图论相关概念](https://github.com/OI-wiki/OI-wiki/blob/master/docs/graph/concept.md) 中的基础部分、[矩阵](https://github.com/OI-wiki/OI-wiki/blob/master/docs/math/matrix.md)、[高斯消元求行列式](https://github.com/OI-wiki/OI-wiki/blob/master/docs/math/gauss.md)。

LGV 引理仅适用于 **有向无环图**。

## 

## 定义

$\omega(P)$ 表示 $P$ 这条路径上所有边的边权之积。（路径计数时，可以将边权都设为 $1$）（事实上，边权可以为生成函数）

$e(u, v)$ 表示 $u$ 到 $v$ 的 **每一条** 路径 $P$ 的 $\omega(P)$ 之和，即 $e(u, v)=\sum\limits_{P:u\rightarrow v}\omega(P)$。

起点集合 $A$，是有向无环图点集的一个子集，大小为 $n$。

终点集合 $B$，也是有向无环图点集的一个子集，大小也为 $n$。

一组 $A\rightarrow B$ 的不相交路径 $S$：$S_i$ 是一条从 $A_i$ 到 $B_{\sigma(S)_i}$ 的路径（$\sigma(S)$ 是一个排列），对于任何 $i\ne j$，$S_i$ 和 $S_j$ 没有公共顶点。

$N(\sigma)$ 表示排列 $\sigma$ 的逆序对个数。

## 

## 引理

$$ M = \begin{bmatrix}e(A_1,B_1)&e(A_1,B_2)&\cdots&e(A_1,B_n)\\ e(A_2,B_1)&e(A_2,B_2)&\cdots&e(A_2,B_n)\\ \vdots&\vdots&\ddots&\vdots\\ e(A_n,B_1)&e(A_n,B_2)&\cdots&e(A_n,B_n)\end{bmatrix} $$

$$ \det(M)=\sum\limits_{S:A\rightarrow B}(-1)^{N(\sigma(S))}\prod\limits_{i=1}^n \omega(S_i) $$

其中 $\sum\limits_{S:A\rightarrow B}$ 表示满足上文要求的 $A\rightarrow B$ 的每一组不相交路径 $S$。

证明请参考 [维基百科](https://en.wikipedia.org/wiki/Lindström–Gessel–Viennot_lemma)。

from oiwiki