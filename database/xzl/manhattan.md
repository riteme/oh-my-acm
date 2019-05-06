**Manhattan 距离最小生成树**：每 $45^\circ$ 一个象限，对每个点找到每个象限中离它最近的点连边，然后做最小生成树。
优化：只用写找直线 $y = x$ 与直线 $x = 0$之间的最近点的代码，然后依次交换 $x$ 和 $y$、取反 $y$、交换 $x$ 和 $y$ 一共做 4 次扫描线即可。