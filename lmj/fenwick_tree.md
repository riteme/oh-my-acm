二维树状数组维护区间加和区间求和。记录一下二维差分数组，然后大力写出前缀和的式子$\sum\limits_{i=1}^x\sum\limits_{j=1}^y\sum\limits_{k=1}^i\sum\limits_{l=1}^j d(k,l)=\sum\limits_{k=1}^x\sum\limits_{l=1}^y d(k,l) * (x-k+1)(y-k+1)$那么就可以分成四个差分数组都记下来，求的时候算下系数。

https://www.cnblogs.com/RabbitHu/p/BIT.html