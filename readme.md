# 2019 秋季赛季代码模板

Fudan U2

## 使用方法

* 在 `database` 文件夹中放入你的完整源代码文件（例如某道题的代码，要求可以过编译。编译命令 `clang++ -std=c++14 -x c++ [SOURCE]`）。`database` 文件夹中可以有子目录。

* **请务必确保源代码文件编码为 UTF-8**，否则中文可能无法正常显示。

* 源代码尽量使用 **2 空格缩进**。

* 如果只想将源代码中的某些片段放入代码模板，请使用 `#define ACM_BEGIN` 和 `#define ACM_END` 将这些代码片段包住。一个源文件中可以截取任意多的代码片段，打印时将会把这些片段依次连接输出（可以参见 `database/xzl/sa-nlogn.cpp`）。如果没有指定范围，则整个源文件都会打印（不会包含文件头部的注释）。

* **在每个源文件开头可以添加如下的注释**（以 `database/xzl/sais.cpp` 为例）：

    ```c++
    /**
     * title: 后缀排序：SA-IS
     * category: 字符串
     * description: sais.md
     */
    ```

    分别表示在打印稿中的标题、分类（已有的分类可以参考仓库中的 `output.pdf`）以及相关的说明文档。例如，在上面的 `description` 中指定了 `sais.md` 为该源代码的说明文件，则打印时会将 `sais.md` 文件中的内容放到代码前（具体效果参见 `output.pdf` 和 `output-compact.pdf`）。如果没有说明文档，则 `description` 处应填写 `/dev/null`（空文件占位符，可以参见 `database/xzl/simplex.cpp`）。

* （**2019.8.4 更新**）如果觉得添加上述注释比较麻烦，可以将源代码命名为 `标题，分类.cpp` 的格式，生成器会自动寻找与标题对应的说明文件（注意分隔符为全角逗号 “`，`”）。以 `database/xzl/仙人掌 DP, 图论.cpp` 为例，生成器会识别该代码的标题为 “仙人掌 DP”，分类为 “图论”，并且会找到同一目录下的 `仙人掌 DP.md` 作为该代码的说明文档。

* 说明文件使用 Markdown 编写，支持 LaTeX 数学公式。数学公式使用 [KaTeX](https://katex.org) 渲染，可以前往 [KaTeX 首页](https://katex.org)测试数学公式。

* 可以添加单独的 Markdown 文档而不附带源代码（参考 `database/lmj/bounded_flow.md`）。该类文档会被安排到模板文件的末尾，连同其文件名一起显示。

* （**2019.8.4 更新**）以 “`.`” 开头的文件和文件夹均被视为隐藏文件，不会被写入文档。

## 文档生成

**生成器依赖：**

* Python 2.7.15rc1
    * [Python Markdown](https://pypi.org/project/Markdown/) (PyPI)
    * [colorama](https://pypi.org/project/colorama/) (PyPI)
    * [python-clang-6.0](https://packages.ubuntu.com/bionic/python-clang-6.0) (bionic)
* [clang-6.0](https://packages.ubuntu.com/bionic/clang-6.0) (bionic)

**生成命令：**

```
./build.py -o output.html database
```

**使用 Chrome 75 渲染 PDF：**

Chrome 版本：`75.0.3770.66 (Official Build) beta (64-bit, Ubuntu 18.04 LTS)`

纸张大小：A4

页面边距：默认（Default）

打印时使用缩放： 35%