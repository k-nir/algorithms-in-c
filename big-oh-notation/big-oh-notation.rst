================
Big-Oh Notation
================
---------
大O表示法
---------

.. contents:: 目录
	:depth: 2
	:backlinks: none

简介
====

大O表示法(o-notation或big-Oh notation)是一种数学记号，用于描述函数在趋近某个极限时具有的行为。
(即函数在其参数趋近特定值的情况下值增长/减小的速率，该特定值通常是无穷大或无穷小)

大O表示法和一些类似的表示法(小o/大 :math:`\Theta` /大 :math:`\Omega` /小 :math:`\omega` 表示法等)一起组成一个大类，
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

意义
-----

在上述例子中，大O表达式实际上表达了对应式子的两种特性:

- 用大O表达式概括整个式子时(例如: :math:`T(n) = O(n^2)`)，大O表达式表示整个式子的增长率。
- 式子只有一部分用大O表达式概括时(例如: :math:`T(n) = n^3 + O(n^2)`)，大O表达式表示式子中对整体增长率贡献可忽略的项。

第一种用法容易理解，不做赘述。
然而，在第二种用法中，以大O表达式表示的看似没有必要保留，因为在估计整个式子的值时，不必考虑以大O表达式表示的项。
(即 :math:`T(n) \approx n^3` 和 :math:`T(n) = n^3 + O(n^2)` 在估算 :math:`T(n)` 值方面的效果是一样的)
这里要注意到的是数学的严谨性，对于近似式来说，只有能确定其与原式的误差范围，才能证明该近似式是有效的，
式子 :math:`T(n) = n^3 + O(n^2)` 给出了误差范围，即 :math:`T(n) \leqslant n^3 + c_0n^2`，而 :math:`T(n) \approx n^3` 没有给出任何误差范围。

因此，可以说，大O表示法是一种能精确地表达近似关系的表示法，而 :math:`\approx` 式是一种不精确的近似关系表示法。

实际应用场景
-------------

无穷大渐进在计算机科学和数学中都很常用，无穷小渐进基本上只在数学中常用，计算机科学基本不使用。
其中，无穷大渐进对应大O表达式的第一种定义，无穷小渐进对应的大O表达式的第二种定义。
由此可知，计算机科学基本上只使用以第一种方式定义的大O表达式。


算法分析中的应用
===================

算法分析涉及的函数基本上都是定义域为自然数(包括0)，值域为非负实数的函数(即整个图像都在第一象限的函数)。
因此在算法分析中，大O表达式的定义可以简化成下述形式。

设有值为非负实数的函数 :math:`g(N)` 和 :math:`f(N)`，两者的定义域都是自然数(包括0)，
若存在正整数 :math:`c_0` 和自然数 :math:`N_0`，使得: 

.. math::
	g(N) \leqslant c_0 \cdot f(N) \text{\quad for all\ } N \geqslant N_0
	
则可以说:

.. math::
	g(N) = O(f(N))

上述定义可用精简的数学语言描述为:

.. math::
	g(N) = O(f(N)) \leftrightarrow \exists c_0 \in \mathbb{R}_{+}\,,\,\exists N_0 \in \mathbb{N} \,,\,\forall N \in \mathbb{N} \,,\, N \geqslant N_0 : g(N) \leqslant c_0 \cdot f(N)
	
在算法分析涉及的问题中，以下两种最常使用大O表达式:

- 预测程序在特定平台上的运行时间
- 描述算法增长速度的本质

预测程序在特定平台上的运行时间
------------------------------

假设现有一个程序A，内部包含一些初始化代码和一对嵌套在一起的循环。
在输入数据量为 :math:`N` 的情况下，每次运行中，内部的循环平均执行 :math:`2NH_N` 次(:math:`H_N` 指调和级数)，
外部的循环平均执行 :math:`N` 次，初始化代码只运行一次。

该程序在特定平台P上运行时，内部循环每执行一次大约需要 :math:`a_0` 纳秒(:math:`1ns = 1\times 10^-9s`)，
外部循环执行一次大约需要 :math:`a_1` 纳秒(扣除内部循环执行时间对外部循环的影响)，
初始化代码执行性一次大约需要 :math:`a_2` 纳秒。

因此，程序A在平台P上运行一次大约需要 :math:`2a_0NH_N + a_1N + a_2` 纳秒。

在 :math:`N` 非常大的情况下，:math:`a_1N + a_2` 对程序A的总运行时间影响很小，
因此，在实际估算中，可以以将其简化为 :math:`O(N)`，略去常量系数，只保留对渐进行为的描述。
这样做不仅能简化计算，还能省去对 :math:`a_1` 和 :math:`a_2` 的测算。

根据调和级数的近似公式 :math:`H_N \approx lnN + \gamma`，
:math:`2a_0NH_N` 可近似为 :math:`2a_0NlnN + O(N)`。

这样，整个运行时间就简化为

.. math::
	2a_0NlnN + O(N) + O(N) = 2a_0NlnN + O(N)

根据此式，我们可以估计程序A在平台P上运行一次的时间在 :math:`2a_0lnN` 左右。

即使在不知道 :math:`a_0` 的之的情况下，上述式子依然能用来估计输入量增加时运行时间的变化情况。
例，输入量为 :math:`2N` 时，程序A的运行时间为 :math:`2a_0(2N)ln(2N) + O(N)`，
与输入量为 :math:`N` 时的运行时间之比为

.. math::
	\frac{2a_0(2N)ln(2N) + O(N)}{2a_0NlnN + O(N)} = \frac{2ln(2N)+O(1)}{lnN + O(1)} = 2 + O\left(\frac{1}{logN}\right) \\
	\text{(参考 }\frac{N}{N+O(1)} = 1 + O\left(\frac{1}{N}\right) \text{ 的证明)}
	
常量的意义
...........

从上例中可见，程序运行时间估算式子中的常量实际上是由计算机的性能决定的，
所以估算式子中的常量不是其所描述的算法的本质特性，只有渐进特性(增长速度)是算法的本质性质。
	
通俗表述
.........

函数 :math:`f(n)` 的增长速度远远超过 :math:`g(n)` (即 :math:`\frac{g(N)}{f(N)} \rightarrow 0 \text{ as } N \rightarrow \infty`)时，
我们可以将 :math:`f(N) + O(g(N))` 通俗的表达为"大约 :math:`f(N)`"，将 :math:`cf(N) + g(N)` 通俗的表达为"与 :math:`f(N)` 成比例"

描述算法增长速度的本质
-----------------------



以实际运行数据倒推增长速率
............................

在前文中，我们发现可以在平台特性(常数)未知的情况下用近似式推出输入量翻倍时运行时间的变化情况。

常用的增长率类型与输入量翻倍时运行时间的变化情况的对应关系如下:

+------------------+--------------------------------+
| 增长率类型       | 输入量翻倍后运行时间的变化情况 |
+==================+================================+
| :math:`1`        | 无变化                         |
+------------------+--------------------------------+
| :math:`lgN`      | 稍微增长                       |
+------------------+--------------------------------+
| :math:`N`        | 2倍                            |
+------------------+--------------------------------+
| :math:`NlgN`     | 比2倍稍微多一点                |
+------------------+--------------------------------+
| :math:`N^{3/2}`  | :math:`2\sqrt{2}` 倍           |
+------------------+--------------------------------+
| :math:`N^2`      | 4倍                            |
+------------------+--------------------------------+
| :math:`N^3`      | 8倍                            |
+------------------+--------------------------------+
| :math:`2^N`      | 平方                           |
+------------------+--------------------------------+

根据该表，我们可以用实际运行得到的数据反推近似式(不包括常量)。


例，假设在实际运行中，输入量为1000时 ，算法A的运行时间为0.69s，输入量为2000时，算法A的运行时间变为1.52s。
因为，:math:`\frac{1.52}{0.69} \approx 2.2`，可以推断算法A的近似于 :math:`O(NlgN)`。

总结
-----

选择将函数的哪些项简化为大O表达式实际上是在选择函数表达式的精度，
例如: 对于函数 :math:`f(n) = 6n^3 + 5n^2 + 3N + 2`，需要以较高的精度进行计算时，
可将其简化为 :math:`f(n) = 6n^3 + 5n^2 + O(n)`，只需要较低的精度时，可将其简化为 :math:`f(n) = 6n^2 + O(n^2)`，
只进行非常笼统的计算时，可以将其简化为 :math:`f(n) = O(n^3)`。


大O表示法的运算
================

**习题2.21-4** 证明: :math:`f(N) - g(N) = O(h(N)) \rightarrow f(N) = g(N) + O(h(N))`

证明. 

.. math::
	\because 
	& f(N) - g(N) = O(h(N)) 
	\leftrightarrow 
	\exists c_0 > 0 \,,\,
	\exists N_0 \geqslant 0 \,,\,
	\forall N \geqslant N_0: 
	f(N) - g(N) \leqslant c_0h(N)
	\\
	\therefore 
	& \exists c_0 > 0 \,,\,
	\exists N_0 \geqslant 0 \,,\,
	\forall N \geqslant N_0: 
	f(N) \leqslant g(N) + c_0h(N) 
	\leftrightarrow 
	f(N) = g(N) + O(h(N))

**习题2.21-5** 证明: :math:`O(f(N))O(g(N)) \rightarrow O(f(N)g(N))`

证明.

.. math::
	\because
	& h(N) = O(f(N))O(g(N)) 
	\leftrightarrow 
	\exists c_f > 0 \,,\,
	\exists c_g > 0 \,,\,
	\exists N_f \geqslant 0 \,,\,
	\exists N_g \geqslant 0 \,,\,
	\forall N \geqslant max(N_f, N_g):
	h(N) \leqslant c_f c_g f(N) g(N)
	\\
	\therefore
	& \exists c_0 = c_f c_g \,,\,
	\exists N_0 = max(N_f, N_g) \,,\,
	\forall N \geqslant N_0:
	h(N) \leqslant c_0 f(N) g(N)
	\leftrightarrow
	h(N) = O(f(N)g(N))
	\\
	\therefore
	& O(f(N))O(g(N))
	\rightarrow
	O(f(N)g(N))

**习题2.21-6** 证明: :math:`O(f(N)) + O(g(N)) \rightarrow O(g(N)) \quad\text{if }\, f(N) = O(g(N))`

证明.

.. math::
	\because
	& h(N) = O(f(N)) + O(g(N))
	\leftrightarrow
	\exists c_f > 0 \,,\,
	\exists c_g > 0 \,,\,
	\exists N_f \geqslant 0 \,,\,
	\exists N_g \geqslant 0 \,,\,
	\forall N \geqslant max(N_f, N_g):
	h(N) \leqslant c_f f(N) + c_g g(N)
	\\
	\because
	& f(N) = O(g(N))
	\leftrightarrow
	\exists c_a > 0 \,,\,
	\exists N_a \leqslant 0 \,,\,
	\forall N \geqslant N_a:
	f(N) \leqslant c_a g(N)
	\\
	\therefore
	& h(N) \leqslant c_f c_a g(N) + c_g g(N)
	\\
	\therefore
	& \exists c_0 = c_f c_a + c_g \,,\,
	\exists N_0 = max(N_a, N_f, N_g) \,,\,
	\forall N \geqslant N_0:
	h(N) \leqslant c_0 g(N)
	\leftrightarrow
	h(N) = O(g(N))
	\\
	\therefore
	& O(f(N)) + O(g(N))
	\rightarrow
	O(g(N)) \quad\text{if }\, f(N) = O(g(N))
	
**习题2.22** 证明: :math:`(N + 1)(H_N + O(1)) = NlnN + O(N)`

证明.

.. math::
	\because
	& H_N = NlnN + \gamma + O\left(\frac{1}{N}\right)
	\\
	\therefore
	 & (N + 1)(H_N + O(1)) \\
	=& (N + 1)(lnN + \gamma + O\left(\frac{1}{N}\right) + O(1)) \\
	=& (N + 1)lnN + (N + 1)\gamma + (N + 1)O\left(\frac{1}{N}\right) + (N + 1)O(1) \\
	=& (N + 1)lnN + (N + 1)\gamma + NO\left(\frac{1}{N}\right) + O\left(\frac{1}{N}\right) + NO(1) + O(1) \\
	=& (N + 1)lnN + (N + 1)\gamma + O(1) + O\left(\frac{1}{N}\right) + O(N) + O(1) \\
	=& (N + 1)lnN + O(N) + O\left(\frac{1}{N}\right) + O(1) \\
	=& NlnN + lnN + O(N) + O\left(\frac{1}{N}\right) + O(1) \\
	\leftrightarrow
	& \exists c_1 > 0 \,,\,
	\exists c_2 > 0 \,,\,
	\exists c_3 > 0 \,,\, \\
	& \exists N_1 \geqslant 0 \,,\,
	\exists N_2 \geqslant 0 \,,\,
	\exists N_3 \geqslant 0 \,,\, \\
	& \forall N \geqslant max(N_1, N_2, N_3):
	NlnN + lnN \leqslant NlnN + lnN + c_1 N + \frac{c_2}{N} + c_3
	\\
	\because
	& lnN < N \quad\text{for}\, N \geqslant 1
	\\
	\because
	& \frac{c_2}{N} \leqslant c_2 N \quad\text{for}\, N \geqslant 1
	\\
	\because
	& c_3 \leqslant c_3 N \quad\text{for}\, N \geqslant 1
	\\
	\therefore
	& \forall N \geqslant max(N_1, N_2, N_3, 1):
	NlnN + lnN \leqslant NlnN + N + c_1 N + c_2 N + c_3 N \\
	\rightarrow
	& \exists c_0 = c_1 + c_2 + c_3 + 1 \,,\,
	\exists N_0 = max(N_1, N_2, N_3, 1) \,,\, \\
	& \forall N \geqslant N_0:
	NlnN + lnN \leqslant NlnN + c_0 N
	\\
	\therefore
	& NlnN + lnN + O(N) + O\left(\frac{1}{N}\right) + O(1) = NlnN + O(N) \\
	\rightarrow
	& (N + 1)(H_N + O(1)) = NlnN + O(N)
	
**习题2.23** 证明: :math:`NlnN = O(N^{3/2})`

证明. 设 :math:`f(N) = NlnN`，设 :math:`g(N) = c_0 N^{3/2}\,,\,c_0 \in R_+`

由此可得 :math:`\frac{f(N)}{N} = lnN`，:math:`\frac{g(N)}{N} = c_0\sqrt{N}`

:math:`N \geqslant 1` 时，:math:`\frac{f(N)}{N}` 在 :math:`N` 附近的斜率为

.. math::
	\left(\frac{f(N)}{N}\right)^' = (lnN)^' = \frac{1}{N}
	
:math:`N \geqslant 1` 时，:math:`\frac{g(N)}{N}` 在 :math:`N` 附近的斜率为

.. math::
	\left(\frac{g(N)}{N}\right)^' = (c_0\sqrt{N})^' = \frac{c_0}{2\sqrt{N}}
	
比较两者，得

.. math::
	\frac{c_0}{2\sqrt{N}} / \frac{1}{N} = \frac{c_0\sqrt{N}}{2}
	
可见，:math:`c_0 \geqslant 2 \,,\, N \geqslant 1` 时，:math:`\frac{g(N)}{N}` 的斜率一定比 :math:`\frac{f(N)}{N}` 的大。

又因为，:math:`c_0 = 2 \,,\, N = 1` 时，:math:`\frac{g(N)}{N} = 1`，:math:`\frac{f(N)}{N} = 0`，即 :math:`\frac{g(N)}{N} > \frac{f(N)}{N}`。

所以，:math:`c_0 \geqslant 2 \,,\, N \geqslant 1` 时，:math:`\frac{g(N)}{N}` 的初始值和后续斜率都大于 :math:`\frac{f(N)}{N}`，因此可以断定 :math:`\frac{g(N)}{N}` 是 :math:`\frac{f(N)}{N}` 的上界。

所以，:math:`c_0 \geqslant 2 \,,\, N \geqslant 1` 时，:math:`NlnN < c_0 N^{3/2}` 一定成立，因此可以说 :math:`NlnN = O(N^{3/2})`。

**习题2.24** 证明: 对于任意 :math:`M` 和常量 :math:`\alpha > 1`，都有 :math:`N^M = O(\alpha)^N`

证明. 对 :math:`N^M` 求 :math:`M` 次导，得

.. math::
	(N^M)^{[M]} = M \cdot (M-1) \cdot (M-2) \cdot \ldots \cdot 2 \cdot 1
	
可见结果是一个常数。

对 :math:`\alpha^N` 求 :math:`M` 次导，得

.. math::
	(\alpha^N)^{[M]} = \alpha^N \cdot (ln\alpha)^M
	
结果是一个底数大于1的指数函数。因此，对于任意常数，都必然存在 :math:`N` 使得 :math:`\alpha^N \cdot (ln\alpha)^M` 能大于该常数。

所以，无论 :math:`M` 和 :math:`\alpha` 的值有多大，都必然存在 :math:`N`，使得 :math:`(a^N)^{[M]} > (N^M)^{[M]}`。

这就意味着 :math:`\alpha^N` 的增长率必然能在某个 :math:`N` 后超过 :math:`N^M`，
所以可以说 :math:`N^M = O(\alpha^N)`。

**习题2.25** 证明: :math:`\frac{N}{N + O(1)} = 1 + O\left(\frac{1}{N}\right)`

证明.

.. math::
	\because
	& f(N) = \frac{N}{N + O(1)}
	\leftrightarrow
	\exists c_0 > 0 \,,\,
	\exists N_0 \geqslant 0 \,,\,
	\forall N \geqslant N_0:
	f(N) \leqslant \frac{N}{N + c_0}
	\\
	\because
	& N + c_0 > N
	\rightarrow
	\forall N > 0:
	\frac{N}{N + c_0} < \frac{N + c_0}{N}
	\\
	\therefore
	& \exists c_0 > 0 \,,\,
	\exists N_1 > 0 \,,\,
	\forall N \geqslant N_1:
	f(N) \leqslant \frac{N + c_0}{N}
	\leftrightarrow
	f(N) = \frac{N + O(1)}{N} = 1 + O(\frac{1}{N})
	
(观察图象可发现，:math:`\frac{N}{N + O(1)}` 是一条从左下向右上渐进 :math:`y=1` 的曲线，
:math:`1 + O\left(\frac{1}{N}\right)` 是一条从左上向右下渐进 :math:`y=1` 的曲线)

**习题2.26** 设 :math:`H_k = N`，请以 :math:`N` 的函数近似地表示 :math:`k`

解.

.. math::
	\because
	H_k =& lnk + \gamma + O\left(\frac{1}{k}\right) \\
	=& lnk + O(1)
	\\
	\therefore
	N =& lnk + O(1) \\
	\rightarrow
	k =& e^{N - O(1)} \\
	=& e^N / e^{O(1)} \\
	=& O(e^N)

**习题2.27** 设 :math:`lg(k!) = N`，请以 :math:`N` 的函数近似地表示 :math:`k`

解. :math:`lg(k!)` 的近似式为 

.. math::
	lg(k!) \approx klgk - klge + lg\sqrt{2\pi k}

这个近似式的精度很高，增长率与 :math:`lg(k!)` 保持一致。

因此，可以用大 :math:`\Theta` 表示法将 :math:`lg(k!)` 表示为

.. math::
	lg(k!) = N = \Theta(klgk)
	
即

.. math::
	\exists c_0 > 0 \,,\,
	\exists c_1 > 0 \,,\,
	\exists k_0 \geqslant 0 \,,\,
	\forall k \geqslant k_0:
	c_0klg(c_0k) \leqslant lg(k!) \leqslant c_1klg(c_1k)
	
即

.. math::
	\exists c_0 > 0 \,,\,
	\exists c_1 > 0 \,,\,
	\exists k_0 \geqslant 0 \,,\,
	\forall k \geqslant k_0:
	c_0klgk \leqslant N \leqslant c_1klgk
	
我们的目标是用 :math:`N` 的函数表示 :math:`k`，因此我们需要将不等式中 :math:`k` 的数量减少，
对不等式的所有式子取对数可以使 :math:`klgk` 中的两个 :math:`k` 分开，使我们例目标近一点，

取对数得得

.. math::
	lg(c_0k) + lglgk \leqslant lgN \leqslant lg(c_1k) + lglgk

取对数后，可以发现 :math:`lglgk` 的增长速度相对于其他项要小得多，因此我们可以想办法把 :math:`lglgk` 消除，
首先处理 :math:`lg(c_0k) + lglgk` 中的 :math:`lglgk`，

因为 :math:`lglgk` 单调增长
	
所以对于任意 :math:`c_0`，必然有

.. math::
	\exists k_1 \geqslant 2 \,,\,
	\forall k \geqslant k_1:
	lglgk \geqslant lg\left(\frac{1}{c_0}\right)
	
所以

.. math::
	\exists c_0 > 0 \,,\,
	\exists k_1 \geqslant 2 \,,\,
	\forall k \geqslant k_1:
	lg(c_0k) + lg\left(\frac{1}{c_0}\right) \leqslant lgN
	
即

.. math::
	\exists c_0 > 0 \,,\,
	\exists k_1 \geqslant 2 \,,\,
	\forall k \geqslant k_1:
	lgk \leqslant lgN
	
然后处理 :math:`lg(c_1k) + lglgk` 中的 :math:`lglgk`，

因为

.. math::
	\forall k \geqslant 2:
	lglgk < lgk
	
所以

.. math::
	\exists c_1 > 0 \,,\,
	\exists k_0 \geqslant 2 \,,\,
	\forall k \geqslant k_0:
	lgN < lg(c_1k) + lgk
	
即
	
.. math::
	\exists c_1 > 0 \,,\,
	\exists k_0 \geqslant 2 \,,\,
	\forall k \geqslant k_0:
	lgN < 2lgk + lg(c_1)
	
因为 :math:`lg(c_1)` 是常数，而 :math:`lgk` 单调增长，

所以必然有

.. math::
	\exists c_2 > 2 \,,\,
	\exists k_0 \geqslant 2 \,,\,
	\forall k \geqslant k_0:
	lgN < c_2lgk
	
综上

.. math::
	\exists c_2 > 2 \,,\,
	\exists k_2 \geqslant max(k_0,k_1) \,,\,
	\forall k \geqslant k_2:
	lgk \leqslant lgN < c_2lgk
	\leftrightarrow
	lgN = \Theta(lgk)
	
由此
	
.. math::
	\frac{N}{lgN} = \frac{\Theta(klgk)}{\Theta(lgk)} = \Theta(k)
	
根据大 :math:`\Theta` 表示法的运算法则，有

.. math::
	k = \Theta\left(\frac{N}{lgN}\right)
	
**习题2.28** 假设一个算法的运行时间是 :math:`O(NlogN)`，另一个算法的运行时间是 :math:`O(N^3)`，
请问根据以上信息能做出哪些关于这两个算法的相对性能的判断？

解. 大O表示法只给出函数的上界，因此严格来说，无法断定哪个算法的增长率更高。

从一般用法来看(即大O表示法表示大 :math:`\Theta` 表示法的意思)，数据增加量相同时，第一个算法耗时增加的百分比应小于第二个算法。

大O表达式不提供算法的实际运行时间信息，所以无法判断两个算法运行时间之间的关系。

**习题2.29** 假设一个算法的运行时间大约是 :math:`NlogN`，另一个算法的运行时间是 :math:`O(N^3)`，
请问根据以上信息能做出哪些关于这两个算法的相对性能的判断？

解. 数据增加量相同时，第一个算法耗时增加的百分比小于第二个算法。

数据量足够大时，第二个算法的运行时间一定会超过第一个。

**习题2.30** 假设一个算法的运行时间大约是 :math:`NlogN`，另一个算法的运行时间大约是 :math:`N^3`，
请问根据以上信息能做出哪些关于这两个算法的相对性能的判断？

解. 数据量相等时，第一个算法总是比第二个算法快，且数据量越大时快得越多。

**习题2.31** 假设一个算法的运行时间与 :math:`NlogN` 成比例，另一个算法的运行时间与 :math:`N^3` 成比例，
请问根据以上信息能做出哪些关于这两个算法的相对性能的判断？

解. 成比例的说法意味着第一个算法的运行时间是 :math:`\Theta(NlogN)`，第二个算法的运行时间是 :math:`\Theta(N^3)`。

因此可以断定，数据增加量相同时，第一个算法耗时增加的百分比小于第二个算法。
	
大 :math:`\Theta` 表示法和大 :math:`\Omega` 表示法
====================================================