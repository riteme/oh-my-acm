可以支持尾端插入，删除的PAM。用非势能的方式建树，每个点维护如果这个点是last，然后再续一个字符c之后，跳fail会跳到哪里的数组q。q[u,c]和q[fail(u),c]只在一个位置上有区别，是u节点对应串中，fail(u)后缀的前一个字符上，这个位置指向fail(u)。暴力做是$O(\Sigma)$的，可以可持久化线段树维护可持久化数组加速。

详见17翁文涛集训队论文。