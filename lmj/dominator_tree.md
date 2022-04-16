有向图支配树，不一定是DAG。Tarjan的论文A  Fast  Algorithm  for  Finding  Dominators in  a  Flowgraph。和写的比较好的博客：https://www.cnblogs.com/meowww/p/6475952.html

sdom(w)定义：存在一条只用dfs序大于w的中间点到w的路径的点中dfs序最小的。sdom(w)肯定是dfs树上面w的祖先。

等价定义：$sdom(w)=min($$\{v|(v,w)\in E,v<w\}\cup$ $\{sdom(u)|u>w,\exists (v,w)\in E,u\rightarrow v\})$其中$u\rightarrow v$表示u在dfs树上面是v的祖先，小于号表示dfs序小于。

性质：u是在dfs树上sdom(w)到w的路径上不包含sdom(w)中sdom(u)最小的一个，则$idom(w)=\begin{cases}sdom(w) & \text {for } sdom(u)=sdom(w)\\ idom(u) & \text{for }sdom(u)<sdom(w)\end{cases}$

代码中除idfn外其他数组的下标都是真实下标，表示编号为i的点对应的元素。idom(w)->w的连边构成了支配树。

注意有可能有些点从起点到不了，导致dfs得到的点数小于n。

