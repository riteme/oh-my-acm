不会证，可以直接抄woodcube的板子。第一个solve是$n^2$暴力的，第二个是FFT快速乘法的。matpow和det两个函数不用抄。不会用woodcube的多项式板子，可以抄自己的mtt用来做乘法。

一个问题是加速矩阵快速幂的时候需要多少项，感觉需要多一些才比较稳定。可以两倍矩阵非零元素个数？但是比较慢。