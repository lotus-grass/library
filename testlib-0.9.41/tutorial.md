> Q：写个 Special Judge 太难了，面对各种各样奇怪的输出，搞不好 spj 就 RE 了。
>
> A：试试用 Testlib 写 checker？根本不用担心各种各样奇怪的格式问题。
>
> Q：写个数据生成器太难了，同样一套数据生成器，同样的生成参数，放到 Linux 下生成的数据就变了个样，这咋整啊？
>
> A：用 Testlib 写 generator 吧，同样的数据生成器，同样的参数，保证在任何环境下参数都一样。
>
> Q：草，最近一场模拟赛出题人用脚造数据，明明是一棵树，他给造了个环出来。
>
> A：你可以教他用 Testlib 写 Validator。
>
> Q：最近想出个交互题，不知道交互器咋写。
>
> A：用 Testlib 吧，写 interactor 也方便了不少呢。
>
> Q：所以 Testlib 究竟是啥东西？为啥这么牛逼？

## 1 啥是 Testlib

Testlib 是一套历史悠久的出题辅助工具库。它可以用于书写数据生成器（Generator），数据校验器（Validator），答案检查器（checker），交互器（interactor）。

著名编程竞赛平台 Codeforces 是 Testlib 的最大使用者。在 Codeforces 上出题，上面提到的四种程序都需要使用 Testlib 完成（详见 [OI Wiki - 出题](https://oi-wiki.org/topic/problemsetting/)）。

最新版本的 Testlib 可以在 [Github](https://github.com/MikeMirzayanov/testlib) 上找到。

## 2 Testlib 的 IO 库

面对各种各样奇怪的输出文件，出题人都会感到十分头疼。

使用常规的 IO 来读取数据，鲁棒性很难得到保证。因此 Testlib 通过一套完善的 API 来读取数据，从而确保能在任何奇怪数据的考验下，都能给出正确的结果。

因为 Testlib 的 IO 库实在太重要了，我们对 Testlib 的介绍，首先从它的 IO 函数开始。

### 2.1 流对象

| 对象名 | 描述       |
| ------ | ---------- |
| `inf`  | 输入文件流 |
| `ouf`  | 选手输出流 |
| `ans`  | 标准答案流 |

调用不同流对象的成员函数，就可以从不同的流中读入数据。

### 2.2 流函数

因为 Testlib 的流函数非常多，这里只列出一些常用函数。

有些函数有等价的表示，下面也一并给出。

| 函数                                                                                                                                                                 | 描述                                                                                                                                                                               |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `char readChar()`                                                                                                                                                    | 读入一个字符。                                                                                                                                                                     |
| `char readChar(char c)`                                                                                                                                              | 读入一个字符，要求必须为 `c`。                                                                                                                                                     |
| `char readSpace()`                                                                                                                                                   | 读入一个空格，等价于 `readChar(' ')`。                                                                                                                                             |
| `void unreadChar(char c)`                                                                                                                                            | 把字符 `c` 返回到流中。                                                                                                                                                            |
| `string readToken()` 或 `string readWord()`                                                                                                                          | 读入一个串，不包含任何空字符（空格，制表符，换行等）。                                                                                                                             |
| `string readToken(string regex)` 或 `string readWord(string regex)`                                                                                                  | 读入一个串，且必须与 `regex` 一致。                                                                                                                                                |
| `long long readLong()`                                                                                                                                               | 读入一个 64 位带符号整数。                                                                                                                                                         |
| `long long readLong(long long L,long long R)`                                                                                                                        | 读入一个 64 位带符号整数，要求在 $[L,R]$ 的范围内。                                                                                                                                |
| `vector<long long> readLongs(int n, long long L, long long R)`                                                                                                       | 一次性读入 $n$ 个 64 位带符号整数，要求每个数都在 $[L,R]$ 的范围内。                                                                                                               |
| `int readInt()` 或 `int readInteger()`                                                                                                                               | 读入一个 32 位带符号整数。                                                                                                                                                         |
| `int readInt(int L,int R)` 或 `int readInteger(int L,int R)`                                                                                                         | 读入一个 32 位带符号整数，要求在 $[L,R]$ 范围内。                                                                                                                                  |
| `vector<int> readInts(int n, int L, int R)` 或 `vector<int> readIntegers(int n, int L, int R)`                                                                       | 一次性读入 $n$ 个 32 位带符号整数，要求每个数都在 $[L,R]$ 范围内。                                                                                                                 |
| `double readReal()` 或 `double readDouble()`                                                                                                                         | 读入一个双精度浮点数。                                                                                                                                                             |
| `double readReal(double L, double R)` 或 `double readDouble(double L, double R)`                                                                                     | 读入一个双精度浮点数，要求在 $[L,R]$ 范围内。                                                                                                                                      |
| `double readStrictReal(double L, double R, int minPrecision, int maxPrecision)` 或 `double readStrictDouble(double L, double R, int minPrecision, int maxPrecision)` | 读入一个双精度浮点数，要求在 $[L,R]$ 范围内，且它的小数位数必须介于 $[minPrecision,maxPrecision]$ 之间，且不允许使用科学计数法等其他形式（例如 `1.0e+2` 这样的形式就是不允许的）。 |
| `string readString()` 或 `string readLine()`                                                                                                                         | 读入一整行（包含换行符），将流指针指向新行的第一个字符（如果存在）。                                                                                                               |
| `string readString(string regex)` 或 `string readLine(string regex)`                                                                                                 | 读入一整行（包含换行符），且要求读入的串与 `regex` 一致。                                                                                                                          |
| `void readEoln()`                                                                                                                                                    | 读入换行符，注意在 Windows 下会读入 `CR LF`，而在 Linux 下会读入 `LF`。                                                                                                            |
| `void readEof()`                                                                                                                                                     | 读入文件结束符 EOF。                                                                                                                                                               |

调用的时候，只需按照 `流对象.流函数` 这样的语法调用，即可从指定的流中执行读入操作。例如 `inf.readInt()` 就可以从输入流中读入一个 32 位带符号整数。

如果读入的东西不符合期望（比如流指针指向一个字符串，却要求读入一个整数）会怎么办呢？在不同环境下结果会不一样，下面会讲到。

## 3 Generator

使用 Testlib 写数据生成器的一个好处是，如果参数一样，在不同的环境下数据生成器的结果都是一样的。而使用 `rand()` 的话，在不同环境下结果并不一样。

使用一个确定性的数据生成器显然会让出题人安心不少（方便了复现数据）。

### 3.1 一些函数

首先是初始化，我们在开头调用 `registerGen(argc, argv, 1);` 来初始化一个 Generator（最后一个参数是 Generator 的版本号，一般不用改）。在此之后，我们有了一个对象 `rnd`，通过调用它的成员函数来生成随机数。

请注意：**一旦使用了 Testlib，你就不能再调用 `rand()` 和 `random_shuffle()` 这些标准库内置随机函数**。你只能使用 Testlib 内的 `rnd` 对象和 `shuffle()` 函数。

下面是一个 `rnd` 对象的成员函数列表：

| 函数             | 描述                                                                                                                                                                                                       |
| ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---- | ----------------------------------------------- |
| `rnd.next()`     | 生成一个 $[0,1)$ 之间的浮点数。                                                                                                                                                                            |
| `rnd.next(R)`    | 如果传入的参数是整数，生成一个 $[0,R - 1]$ 之间的整数。如果传入的参数是浮点数。生成一个 $[0,R)$ 之间的浮点数。                                                                                             |
| `rnd.next(L,R)`  | 如果传入的参数是整数，生成一个 $[L,R]$ 之间的整数。如果传入的参数是浮点数。生成一个 $[L,R)$ 之间的浮点数。                                                                                                 |
| `rnd.any(c)`     | 返回容器 `c` 内的一个随机元素。对 `vector` 和 `string` 都可以使用。                                                                                                                                        |
| `rnd.wnext(i,t)` | 不均匀随机数生成器（具体定义比较长，下面会给出）。`rnd.wnext(4,2)` 相当于 `max(rnd.next(4),rnd.next(4))`；`rnd.wnext(4,-2)` 相当于 `min(rnd.next(4),rnd.next(4))`；`rnd.wnext(4,0)` 相当于 `rnd.next(4)`。 |
| `rnd.next("a     | b                                                                                                                                                                                                          | c")` | 等概率返回 `a`，`b`，`c` 这三个字符串中的一个。 |

附：关于 `rnd.wnext(i,t)` 的形式化定义：

$$
\operatorname{wnext}(i,t)=\begin{cases}\operatorname{next}(i) & t=0 \\\max(\operatorname{next}(i),\operatorname{wnext}(i,t-1)) & t>0 \\\min(\operatorname{next}(i),\operatorname{wnext}(i,t+1)) & t<0\end{cases}
$$

### 3.2 一个例子

下面是 [Codeforces](https://codeforces.com/blog/entry/18291) 上给出的一个生成树的代码（当参数 $t$ 较大时，生成的树更接近链，$t$ 较小时，生成的树更接近菊花）：

```cpp
registerGen(argc, argv, 1);//初始化数据生成器

int n = atoi(argv[1]);
int t = atoi(argv[2]);

vector<int> p(n);

//给 1..n-1 号点设置父亲
for(int i = 0; i < n; ++i)
    if (i > 0)
        p[i] = rnd.wnext(i, t);

printf("%d\n", n);

//打乱节点排序
vector<int> perm(n);
for(int i = 0; i < n; ++i)
    perm[i] = i;
shuffle(perm.begin() + 1, perm.end());

// 随机加边
vector<pair<int,int> > edges;
for (int i = 1; i < n; i++)
    if (rnd.next(2))
        edges.push_back(make_pair(perm[i], perm[p[i]]));
    else
        edges.push_back(make_pair(perm[p[i]], perm[i]));

//打乱边的顺序
shuffle(edges.begin(), edges.end());

for (int i = 0; i + 1 < n; i++)
    printf("%d %d\n", edges[i].first + 1, edges[i].second + 1);
```

### 3.3 生成多组数据

有两种方法可以一次性生成多组数据：

1. 写一个批处理脚本。
2. 使用 Testlib 内置的 `startTest(test_index)` 函数。

第一种方法非常简单，只需设好参数，将输出重定向到指定输出文件即可。

```bash
gen 1 1 > 1.in
gen 2 1 > 2.in
gen 1 10 > 3.in
```

对于第二种方法，在每生成一组数据前，调用一次 `startTest(test_index)`，即可将输出重定向至名为 `test_index` 的文件。

下面是一个使用 `startTest` 函数生成多组数据的例子。

```cpp
int main(int argc,char** argv)
{
 registerGen(argc,argv,1);
 int a,b,c;
 for(int i=1;i<=10;i++)
 {
  startTest(i);
  a=rnd.next(100),b=rnd.next(100),c=rnd.next(100);
  genData(a,b,c);
 }
 return 0;
}
```

## 4 Validator

生成了一组数据后，需要检验这个数据是否符合要求（是否满足数据范围，数据的性质是否正确），这时候就需要写一个 Validator 来校验数据正确性。

校验器的开头需要先调用 `registerValidation(argc, argv);` 完成初始化。

### 4.1 一个例子

下面是一个检验一个图是否是树的校验器：

```cpp
#include "testlib.h"
using namespace std;
int fa[105];
void init(int n)
{
 for(int i=1;i<=n;i++)
  fa[i]=i;
}
int find(int x)
{
 return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool merge(int x,int y)
{
 x=find(x),y=find(y);
 if(x==y)return false;
 fa[y]=x;
 return true;
}
int main(int argc,char** argv)
{
 registerValidation(argc,argv);//初始化校验器
 int n=inf.readInt(1,100);
 inf.readEoln();
 init(n);
 for(int i=1;i<n;i++)
 {
  //int u=inf.readInt(1,n),v=inf.readInt(1,n);
  //Validator 对格式要求非常严格，上面的写法忽略了两个数之间的空格
  //下面的写法是正确的
  int u=inf.readInt(1,n);
  inf.readSpace();
  int v=inf.readInt(1,n);
  ensuref(merge(u,v),"Loop found!");
  inf.readEoln();
 }
 //最后必须读入文件结束符 EOF
 inf.readEof();
 return 0;
}
```

在命令行下执行 `val < 1.in` 即可校验 `1.in` 是否合法，如果出现问题将返回错误信息。

### 4.2 注意事项

一些常见的坑点在上面的注释中写的很清楚了，这里再次强调一下：

1. **与 Checker 不同的是，Validator 对格式的要求非常严格**，多出的一个空格或一个回车都会导致校验失败。
2. Validator 最后必须读入文件结束符 EOF 表示校验结束。

### 4.3 `ensuref()` 的使用方式

在刚才的例子中，出现了一个新函数 `ensuref()`，它的作用与 `assert()` 类似。

以上面的例子为例，当 `merge(u,v)` 返回 false 时（即出现了环），`ensuref()` 就会被触发，并输出指定的错误信息。

## 5 Checker

现在的不少题目都没有一个固定的输出。给出一个输出，评判它是否正确，能得多少分，都需要用到 Checker。

Testlib 书写的 Checker 由于使用了一套较为严密的函数进行读取操作，从而避开了各种各样奇怪的输出导致 Judgment Failed 的惨剧。

### 5.1 一个简单的例子

先来一个浮点数加法的例子吧！

下面这个 checker 会判断选手输出和标准输出的绝对误差是否小于 $10^{-5}$，如果满足这一条件则认为输出正确。

还是一样，在使用 checker 前需要调用 `registerTestlibCmd(argc,argv);` 完成初始化。

```cpp
#include "testlib.h"
using namespace std;
int main(int argc,char** argv)
{
 registerTestlibCmd(argc,argv);//初始化 checker
 double pans=ouf.readDouble(),jans=ans.readDouble();
 if(abs(pans-jans)<=1e-5)quitf(_ok,"Correct!");
 else quitf(_wa,"Wrong Answer!");
}
```

编译后，按如下方式调用即可得到反馈：`spj <input-file> <output-file> <ans-file>`。

这里出现了一个新函数 `quitf()`，它将会反馈评测结果，并输出指定信息。

可用的状态有如下几种：

| 状态         | 描述                                                                         |
| ------------ | ---------------------------------------------------------------------------- |
| `_ok`        | 选手输出可以被接受。                                                         |
| `_wa`        | 选手输出不能被接受。                                                         |
| `_pe`        | 格式错误（事实上 Testlib 不检查输出格式）。                                  |
| `_pc(score)` | 部分正确，可以得到 score 的分数。                                            |
| `_fail`      | 出现异常。可能原因有选手的答案比标准答案优，或标准答案不合法，需要特别注意。 |

### 5.2 进阶用法

（下面的内容参考了 [Codeforces 上的文档](https://codeforces.com/blog/entry/18431)）

下面是一个比较复杂的例子：给一个有向无环图，求其最长路径并输出。如果有多条最长路径，任意输出一条。

下面是一个不太好的 checker 实现：

```cpp
#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int w = inf.readInt();
        edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
    }
    int s = inf.readInt();
    int t = inf.readInt();

    //读取标准答案
    int jvalue = 0;
    vector<int> jpath;
    int jlen = ans.readInt();
    for (int i = 0; i < jlen; i++) {
        jpath.push_back(ans.readInt());
    }
    for (int i = 0; i < jlen - 1; i++) {
        jvalue += edges[make_pair(jpath[i], jpath[i + 1])];
    }

    //读取选手输出
    int pvalue = 0;
    vector<int> ppath;
    vector<bool> used(n, false);
    int plen = ouf.readInt(2, n, "number of vertices");
    for (int i = 0; i < plen; i++) {
        int v = ouf.readInt(1, n, format("path[%d]", i + 1).c_str());
        if (used[v - 1]) //确保一个点不会被经过两次
            quitf(_wa, "vertex %d was used twice", v);
        used[v - 1] = true;
        ppath.push_back(v);
    }
    //检查路径是从 s 到 t 的路径
    if (ppath.front() != s)
        quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s, ppath.front());
    if (ppath.back() != t)
        quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t, ppath.back());
    //检查每一条边是否存在
    for (int i = 0; i < plen - 1; i++) {
        if (edges.find(make_pair(ppath[i], ppath[i + 1])) == edges.end())
            quitf(_wa, "there is no edge (%d, %d) in the graph", ppath[i], ppath[i + 1]);
        pvalue += edges[make_pair(ppath[i], ppath[i + 1])];
    }

    if (jvalue != pvalue)
        quitf(_wa, "jury has answer %d, participant has answer %d", jvalue, pvalue);
    else
        quitf(_ok, "answer = %d", pvalue);
}
```

这个 checker 的问题出在了哪里呢？

- 假如选手输出比标准输出更优的话，按照上面的说明应该返回的是 `_fail`，但这个 checker 返回的是 `_wa`。因此如果这种事情发生的话，上面的 checker 将无法发现数据出了问题。
- 代码过于冗杂。注意到标准输出和选手输出本质上是平等的（输出的内容都一样），我们可以写一个函数来处理这两个输出。

下面是一个改进后的 checker。

```cpp
#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;
int n, m, s, t;

//这个函数传入了一个流对象作为参数
//从而减少代码长度
int readAns(InStream& stream) {
    int value = 0;
    vector<int> path;
    vector<bool> used(n, false);
    int len = stream.readInt(2, n, "number of vertices");
    for (int i = 0; i < len; i++) {
        int v = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
        if (used[v - 1]) {//确保每个点不会被用两次
            //stream.quitf 和 quitf 的区别在于流的不同将会影响返回状态的不同
            //如果 stream=ouf，它和 quitf 没有区别
            //但如果 stream=ans，一切本来要返回 _wa 的状态都会返回 _fail（表明出现异常）
            stream.quitf(_wa, "vertex %d was used twice", v);
        }
        used[v - 1] = true;
        path.push_back(v);
    }
    //检查这条路径的起点是 s，终点是 t
    if (path.front() != s)
        stream.quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s, path.front());
    if (path.back() != t)
        stream.quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t, path.back());
    //检查路径上的相邻两点确实有边相连
    for (int i = 0; i < len - 1; i++) {
        if (edges.find(make_pair(path[i], path[i + 1])) == edges.end())
            stream.quitf(_wa, "there is no edge (%d, %d) in the graph", path[i], path[i + 1]);
        value += edges[make_pair(path[i], path[i + 1])];
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int w = inf.readInt();
        edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
    }
    int s = inf.readInt();
    int t = inf.readInt();

    int jans = readAns(ans);
    int pans = readAns(ouf);
    if (jans > pans)
        quitf(_wa, "jury has the better answer: jans = %d, pans = %d\n", jans, pans);
    else if (jans == pans)
        quitf(_ok, "answer = %d\n", pans);
    else //选手输出比标准答案更优，返回 _fail
        quitf(_fail, ":( participant has the better answer: jans = %d, pans = %d\n", jans, pans);
}
```

### 5.3 一些建议

如果你要动手写一个 checker 的话，这里有一些建议：

1. checker 与 validator 不同，不用特别检查空白字符。
2. `quitf` 的反馈信息应该尽量详细。这一方面方便选手了解问题出在何处，另一方面方便了调试；
3. 记得限定参数范围，防止 checker 出现访问非法内存等问题；
4. 善用 readAns 函数来降低代码长度；

## 6 Interactor

如果要出一道交互题的话，交互器是必不可少的。

Testlib 的交互器可以用于 stdio 交互（即选手通过标准输入输出与交互器进行交互）。

### 6.1 流对象

考虑到交互题比较特殊，流对象的含义也发生了些变化。

| 对象名 | 描述                                                                      |
| ------ | ------------------------------------------------------------------------- |
| `inf`  | 输入文件流                                                                |
| `ouf`  | 选手输出流（选手向交互器的输出）                                          |
| `ans`  | 标准答案流                                                                |
| `tout` | 输出日志流（交互器可以向该流写入信息，checker 可以从 ouf 中读取这些信息） |

### 6.2 交互流程

一个 interactor 的交互流程是这样的：

1. 从输入文件流 `inf` 中读取所需信息；
2. 从选手输出流 `ouf` 中读取选手向交互器的输出（如果读入的数据不合法，则会返回 `_wa`）；
3. 向标准输出 `stdout` 输出信息给选手程序；
4. 如果交互正常结束，checker 将确认答案正确性（这时候 checker 可以通过读取 `ouf` 的信息（也就是交互器向 `tout` 输出的信息）来判断交互情况）。

和选手写的程序一样，**为了确保输出不被缓存，请在输出一行后立刻刷新缓冲区**。

在本地环境下，请通过 `interactor <input-file> <output-file> [<ans-file>]` 的方式调用交互器（`ans-file` 是可选的）。

### 6.3 一个例子

（下面的内容参考了 [Codeforces 上的文档](https://codeforces.com/blog/entry/18455)）

这是一个非常经典的猜数字游戏的例子：交互器随机生成一个 $[1,10^9]$ 的整数，你有 $50$ 次猜测的机会。

你需要向交互器输出一个数，交互器将会根据情况返回这几种结果：

- 1：表示你猜的数和实际相等，你需要立刻停止询问；
- 0：表示你猜的数比实际小；
- 2：表示你猜的数比实际大。

```cpp
int main(int argc, char ** argv){
	registerInteraction(argc, argv);//初始化交互器
	int n = inf.readInt();
	cout.flush();
	int left = 50;
	bool found = false;
	while(left > 0 && !found){
		left --;
		int a = ouf.readInt(1, 1000000000);//读取选手猜的数，记得检查范围
		if(a < n)
			cout << 0 << endl;
		else if(a > n)
			cout << 2 << endl;
		else
			cout << 1 << endl, found = true;
		cout.flush();
	}
	if(!found)
		quitf(_wa, "couldn't guess the number with 50 questions");
	ouf.readEof();
	quitf(_ok, "guessed the number with %d questions!", 50 - left);
}
```

注：这个例子没有检查标准答案，因为并不需要这么做。但其他题可能并非如此。

## Reference

- [Testlib - Codeforces](https://codeforces.com/testlib)
- [Testlib - OI-wiki](https://oi-wiki.org/intro/testlib/)
