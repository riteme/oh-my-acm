拟阵定义：$M=(S,I)$，其中$S$是一个集合，$I\subseteq P(S)$是一个子集族，成为独立集的集合。需要满足两条性质：

1.如果$A\in I,B\subseteq A$那么$B\in I$。（向下封闭）

2.如果$A,B\in I,|B|>|A|$那么存在元素$z\in J-I$满足$A\cup\{z\}\in I$。（交换性）

拟阵的极大独立集称为基，极小非独立集成为环。

引理：所有基的大小相同

引理（基交换定理）：对于两个不同的基$A,B$，那么对任意$z\in A-B$，存在一个$y\in B-A$，满足$A-\{z\}+\{y\}$是独立集。

定义：基的元素的个数成为拟阵的秩。一个$S$的子集的$U$的秩函数是$r(U)$为$U$中极大独立集的大小。

定理（次模性）：$r(A\cup B)+r(A\cap B)\le r(A)+r(B)$

### 拟阵上的最优化

如果每个$s\in S$有个权值，独立集的权值是里面元素权值之和，那么可以贪心求最大权的独立集。（按照权值从大到小贪心加到当前集合里）

### 拟阵交

给两个$S$相同的拟阵，但是独立集不同，分别是$I_1,I_2$。求同时在两个独立集里面的最大（权）的子集的（权值和）大小。

warning：拟阵的交不是拟阵。

定理（强基交换定理）：对于两个不同的基$A,B$，那么对任意$z\in A-B$，存在一个$y\in B-A$，满足$A-\{z\}+\{y\}$和$B-\{y\}+\{x\}$都是基。

定理（最小最大定理）：$\max\limits_{A\in I_1\cap I_2}(A) = \min\limits_{U\subseteq S} (r_1(U)+r_2(S-U))$

下面的算法可以构造一个取等的独立集$A$。

![matroid](assets/matroid.png)

这张图是交换图，注意是有向图。左边是当前已经增广出来的答案，右边是剩下的东西。右边又有$X_1,X_2$，分别是加进去$I+\{x_0\}\in I_1$的和$I+\{x_0\}\in I_2$的（可能同时在两个集合里，会被直接增广）。然后$(y_i,x_i)$表示$I-\{y_i\}+\{x_i\}\in I_1$，$(x_i,y_i)$表示$I-\{y_i\}+\{x_i\}\in I_2$。

每次就是建出图，找一个从$X_1$到$X_2$的增广路，把路径上的点和$I$做对称差。这样每次答案的大小加一。这里直接广搜找最短路。

复杂度：设$r=\max(r_1(S),r_2(S))$，每次造出来都是$n$个点，$rn$条边的图。每次复杂度是广搜$O(n+m)$的。只会增广$r$次，总复杂度$O(r^2n)$。

求最大权版本：只需要把建图的时候加上点权，$I$里面的是$-w(x)$，$S-I$里面的是$w(x)$求一个**！！！最小最小最小！！！**的从$X_1$到$X_2$的路径就可以了。（因为最大最小定理的扩展版本右侧是一个取最小值）。可以证明图上没有负环，一定有解。

论文里说需要找最短路，带权版本要求第二关键字是经过边数最少，感觉不需要。

多个拟阵的交是NP-HARD的。

参考杨乾澜18年集训队论文以及https://zhuanlan.zhihu.com/p/54713563。

代码是求一个最大的线性独立集，并且要求每个数选择自不同的集合。就是$I_1$要求是独立集，$I_2$要求是选择自不同集合。