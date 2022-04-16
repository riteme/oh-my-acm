循环矩阵的行列式和结式

循环矩阵：参考高代白皮书例2.52，所以只需要算出来一个多项式（假设第一行是$(a_0,a_1,...,a_{n-1})$，那么多项式就是$f(x)=a_0+a_1x+...+a_{n-1}x^{n-1}$）带入所有单位根（也就是$x^n-1=0$的所有根）的结果的乘积就可以了。

结式的一个用处：求$f(x)$的所有根$\epsilon_i$，带入另一个多项式$g(x)$的乘积$\prod_{i=1}^n g(\epsilon_i)$。

这个东西其实就是结式$R(x^n-1,f(x))$，参考高代书上面的定理5.10.2，注意到$\prod_{j=1}^m(x_i-y_j)$。这部分就是$g_0(x_i)$的值，其中$g(x)=b_0g_0(x)$是首一多项式（两个多项式都要注意首一的问题）。所以算结式就可以了。

通过结式的行列式定义可以得到的几个性质：

$R(A,B)=(-1)^{nm}R(B,A)$

$R(A,B)=a_0^mb_0^n$，当某一个多项式是常数的时候。

$R(A,B)=a_0^{deg(B)-deg(B-CA)} R(A,B-CA)$，对任意的多项式$A,B,C$。这个只需要在行列式里面对着$B$的行减掉那些$A$的行乘一个系数就可以了。然后对第一列剩下的$a_0$进行行列式展开，如果度数减的多余1就继续展开。（这个只能证$deg(A)\le deg(B)$的情况，没考虑大于怎么办，只需要小于等于的情况就足够做辗转相减了）

求值的时候就大力辗转相减，复杂度$O(n^2)$。

回到循环矩阵的行列式，tangjz说可以fft求出这个东西。$n$不是$2$的幂次的时候需要用Bluestein算法在有限域上求离散傅里叶变换，就可以复杂度和FFT一样了。（我并不会）

https://www.zhihu.com/question/22013474

https://en.wikipedia.org/wiki/Chirp_Z-transform#Bluestein.27s_algorithm

代码里面$resultant(y,x)$的返回值就是第一行是$x=(x_0,x_1,...,x_{n-1})$的循环矩阵的行列式。前边的co是和题目有关的系数。