又叫圆方树

这个代码用来构造仙人掌的圆方树，两个点一条边的双联通分量不会被处理为圆点+方点，而是两个圆点直接相连，kind=0为圆点。tot是圆点+方点的数量。注意数组大小要开两倍来维护方点。不可以处理任意的点双。

gt是造好的圆方树，如果还是从1号点开始遍历树的话，那么方点的边表中，就是按照dfn顺序的那些点，也就是按照环的顺序排序的，开头是与1号点最近的点，可以方便地处理环。

第二段代码可以处理任意的点双，并且两个点的点双也会加方点。addt第三个参数是和题目有关的，不需要管。只需要抄tarjan函数。