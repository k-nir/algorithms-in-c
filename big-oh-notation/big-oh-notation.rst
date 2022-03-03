================
Big-Oh Notation
================
---------
大O表示法
---------


简介
====

大O表示法(o-notation或big-Oh notation)是一种数学记号，用于描述函数在趋近某个极限时具有的行为。
(即函数在其参数趋近特定值的情况下值增长/减小的速率，该特定值通常是无穷大或无穷小)

大O表示法和一些类似的表示法(小o/大Theta/大Omega/小Omega表示法等)一起组成一个大类，
称为巴赫曼-朗道表示法(Bachmann-Landau notation)或渐进表示法(asymptotic notation)。


正式定义
========

大O表示法有两种正式定义，
一种定义默认被描述函数的定义域是无界集，
另一种定义将被描述函数的定义域限定在特定值的周围。

设有值为实数或复数的函数 :math:`g(N)`，值为实数的函数 :math:`f(N)`，

在第一种定义中，
:math:`g(N)` 和 :math:`f(N)` 的定义域是正实数域中的某个无界集(unbounded set)(即右侧为正无穷的区间)，
此时，若存在正实数 :math:`c_0` 和实数 :math:`N_0`，使得: 

.. math::
	|g(N)| \leqslant c_0 \cdot f(N) \text{\quad for all\ } N \geqslant N_0
	
则可以说:

.. math::
	g(N) = O(f(N)) \text{\quad as\ } N \rightarrow \infty

上述表达式可以简写为:

.. math::
	g(N) = O(f(N))
	
在第二种定义中，
:math:`g(N)` 和 :math:`f(N)` 的定义域是实数 :math:`a` 附近的区域，
存在一个正实数 :math:`d`，使得 :math:`0<|N-a|<d`，
此时，若存在正实数 :math:`c_0` 和实数 :math:`N_0`，使得: 

.. math::
	|g(N)| \leqslant c_0 \cdot f(N) \text{\quad for all\ } N \text{\ with\ } 0<|N-a|<d
	
则可以说:

.. math::
	g(N) = O(f(N)) \text{\quad as\ } N \rightarrow a
	
第二种定义中的 :math:`a` 通常是0。


应用分类
=========

大O表示法主要有两种用法:

- 描述函数趋近无穷大时的行为(称为无穷大渐进)
- 描述函数趋近无穷小时的行为(称为无穷小渐进)

无穷大渐进
----------

该用法用大O表示法概括复杂函数 :math:`f(N)` 在 :math:`N \rightarrow \infty` 过程中的行为(增长速率)。

以函数 :math:`T(n) = 4n^2 -2n + 2` 为例，用大O表示法可将其表示为: :math:`T(n) = O(n^2)`。

推导过程
.........

在 :math:`T(n)` 中，:math:`n` 的值越大( :math:`n>1` 的情况下)，:math:`4n^2` 项对 :math:`T(n)` 的值的影响越大。
例如，当 :math:`n=500` 时，:math:`4n^2` 比 :math:`2n` 大1000倍，使得 :math:`2n` 项对 :math:`T(n)` 的值几乎没有影响。
因此，:math:`T(n)` 的增长速率由 :math:`4n^2` 决定，即在 :math:`n` 越大的情况下， :math:`T(N)` 的增长速率越接近 :math:`4n^2`。

既然 :math:`T(n)` 的增长速率会趋近 :math:`4n^2`，那么在两者足够接近的情况下(即 :math:`n` 超过某个 :math:`n_0` 以后),
一定存在一个 :math:`c_0 \cdot n^2` (:math:`c_0` 为常量)，使 :math:`T(n) \leqslant c_0 \cdot n^2` (例如: :math:`c_0=5\,,\,n_0=3`)。
这意味着在区间 :math:`[N_0, \infty)` 内，:math:`c_0 \cdot n^2` 的图形都在 :math:`T(n)` 之上，
即 :math:`c_0 \cdot n^2` 能概括 :math:`T(n)` 在 :math:`[N_0, \infty)` 区间内的行为。

因此，我们可以说 :math:`T(n) = O(n^2)`。

对次要项的省略
..............

:math:`O(n^2)` 与 :math:`T(n)` 相比，省略了二次项以外的所有项。
这样的省略之所以可取的原因，已经在推导过程中提到，就是因为与二次项相比，次要项对函数的增长的贡献微不足道。

对常量系数的省略
................

:math:`O(n^2)` 与 :math:`c_0 \cdot n^2` 相比，省略了常量系数。
之所以可以省略常量系数，是因为大O表示法关注的焦点是函数的增长速率，
:math:`c_0 \cdot n^2` 中决定增长速率(函数图像形状)的是 :math:`n^2`，
:math:`c_0` 只决定函数图像在纵轴上的位置(不影响形状)。

从另一个视角也可以看出常量系数的次要性。
比较 :math:`c_0 \cdot n^2` 与 :math:`U(n) = n^3`，
无论 :math:`c_0` 有多大，:math:`c_0 \cdot n^2` 的函数图像都会在某个点被 :math:`U(n)` 的函数图像超越。

无穷小渐进
----------

该用法用大O表示法概括复杂函数 :math:`f(N)` 在 :math:`N \rightarrow 0` 过程中的行为(增长速率)。

以指数函数 :math:`e^x` 为例，用大O表示法可将其表示为: :math:`e^x = 1 + x + O(x^2) \text{\quad as\ } x \rightarrow 0`。

推导过程
.........

:math:`e^x` 可展开为 :math:`1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \frac{x^4}{4!} + \cdots`，
在展开式中，:math:`x` 越接近0， 指数项对 :math:`e^x` 的值的影响越小。
例如，当 :math:`x=0.05` 时，:math:`1+x = 1.05`，指数项的值为 :math:`e^x-(1+x)=0.00127\ldots`，
对 :math:`e^x` 的结果影响非常小。因此，在 :math:`x` 趋向0的情况下，我们可以将 :math:`e^x` 的展开式中的指数项称为余项。

观察余项，可以发现，:math:`x` 越接近0，余项中高次幂对余项值的贡献越小，因为幂的指数越大，接近0的速度越快。
因此，:math:`x` 趋近0时，余项的减小速率由 :math:`\frac{x^2}{2}` 主导。
也就是说，:math:`x` 越接近0，余项的减小速率越接近 :math:`\frac{x^2}{2}`。

余项的减小速率与 :math:`\frac{x^2}{2}` 的减小速率足够接近(:math:`x` 大于某个 :math:`x_0`)时，
一定存在一个 :math:`c_0 \cdot \frac{x^2}{2}`，(:math:`c_0` 为常量)，
使得 :math:`\left|\frac{x^2}{2!} + \frac{x^3}{3!} + \frac{x^4}{4!} + \cdots\right| \leqslant c_0 \cdot \left|\frac{x^2}{2}\right|`。

忽略常量系数，即可得 :math:`e^x = 1 + x + O(x^2) \text{\quad as\ } x \rightarrow 0`。
这个式子的意思是: 当 :math:`x` 趋近0时，:math:`e^x` 展开式的余项 :math:`e^x - (1 + x)` 的绝对值一定小于等于 :math:`c_0\cdot |x^2|`。

对次要项的省略
..............

:math:`e^x = 1 + x + O(x^2)` 与 :math:`1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \frac{x^4}{4!} + \cdots` 相比，
省略了二次项以外的所有高次项，这些高次项相对函数值减小的贡献很小。

对常量系数的省略
................

:math:`O(x^2)` 与 :math:`c_0 \cdot \frac{x^2}{2}` 相比，省略了常量系数。
除了常量系数非常大(例如: :math:`c_0 = 1 \times 10^10`)的情况，
在 :math:`x` 很小时，省略常量系数对 :math:`1 + x + O(x^2)` 的值的影响很小。

实际应用场景
-------------

无穷大渐进在计算机科学和数学中都很常用，无穷小渐进基本上只在数学中常用，计算机科学基本不使用。


计算机科学中的应用
===================

简化定义
常量和计算机性能的关系
