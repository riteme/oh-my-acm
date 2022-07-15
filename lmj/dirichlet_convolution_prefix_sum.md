给定任意函数$A(x),B(x)$，并且可以快速求出在$\lfloor {n\over i}\rfloor$处的前缀和，现在要在$O((n\log n)^{2/3})$的时间内求二者狄利克雷卷积的所有$\lfloor {n\over i}\rfloor$处的前缀和。

先取定阈值$T$，暴力计算出$C(x),1\le x \le T$的值。然后对每个$x=\lfloor {n\over i}\rfloor\ge T$，利用$SC(x)=\sum_{i=1}^{\sqrt x} (A(i)*SB(x/i)+B(i)*SA(x/i))-SA(\sqrt x)SB(\sqrt x)$

积分可以求出暴力计算的复杂度是$O(n/\sqrt T)$的。取$T=O(n^{2/3})$即可实现。

代码中求的是$F(x)=F(x)\otimes F(x) + P(x)$。其中$SF(x)=SP(x)+\sum_{ij\le x}F(i)F(j)$，用上述方法可以发现从小到大算，需要的东西都是之前已经算出来的。