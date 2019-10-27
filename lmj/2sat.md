#### Priest John's Busiest Day

##### Description

John  is the only priest in his town. September 1st is the John's busiest day  in a year because there is an old legend in the town that the couple  who get married on that day will be forever blessed by the God of Love.  This year *N* couples plan to get married on the blessed day. The *i*-th couple plan to hold their wedding from time *Si* to time *Ti*.  According to the traditions in the town, there must be a special  ceremony on which the couple stand before the priest and accept  blessings. The *i*-th couple need *Di* minutes to  finish this ceremony. Moreover, this ceremony must be either at the  beginning or the ending of the wedding (i.e. it must be either from *Si* to *Si* + *Di*, or from *Ti* - *Di* to *Ti*). Could you tell John how to arrange his schedule so that he can present at every special ceremonies of the weddings.

Note that John can not be present at two weddings simultaneously.

##### Input

The first line contains a integer *N* ( 1 ≤ *N* ≤ 1000).
The next *N* lines contain the *Si*, *Ti* and *Di*. *Si* and *Ti* are in the format of *hh:mm*.

##### Output

The  first line of output contains "YES" or "NO" indicating whether John can  be present at every special ceremony. If it is "YES", output another *N* lines describing the staring time and finishing time of all the ceremonies.

##### Sample Input

```
2
08:00 09:00 30
08:15 09:00 20
```

##### Sample Output

```
YES
08:00 08:30
08:40 09:00
```

<br>

##### Task Description

有 $n$ 个 Boolean 变量 $\{x_i\}$，以及一个有如下形式的逻辑表达式：$(x_i \lor x_j)\land(\lnot x_p \lor x_q)\land\cdots$。（大概就是一堆 or 的 and，然后每个括号里面有两个变量）

##### Solution

显然我们可以建一个 $2n$ 个点的有向图。对于每个变量 $x_i$ 我们开两个变量分别表示 $x_i$ 为真和 $x_i$ 为假。

对于每组 $(i\lor j)$ ，我们连两条边 $\lnot i \implies j$ 以及 $\lnot j \implies i$（因为至少要选一个）。

现在对于每个变量 $x$ 有四种情况：

- $x$ 和 $\lnot x$ 毫无关系：爱取啥取啥
- $x \implies \lnot x$：那么我们取 $x$ 为假
- $\lnot x \implies x$：那么我们取 $x$ 为真
- $x \implies \lnot x$ 并且 $\lnot x \implies x$：那么无解

注意到只有第四种情况是无解的，这对应了有向图中 $x$ 和 $\lnot x$ 是在同一个强连通分量中。于是我们可以跑一遍 Tarjan，判断是否有一个变量的两点在同一个强连通分量中。

------

以上我们学习了如何判断 2SAT 是否有解，那么如何给出一组可行解呢？

首先我们用 Tarjan 强连通缩点，现在的图变成了一个 DAG。假设我们有任意一组这个 DAG 的拓扑序，如果拓扑序中 $x$ 在 $\lnot x$ 前面，那么我们设 $x$ 为假，否则为真。

<https://zhuanlan.zhihu.com/p/50211772> by 后缀自动机 · 张