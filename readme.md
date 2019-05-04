# thupc2019 代码模板

## 使用方法

* 在 `database` 文件夹中放入你的完整源代码文件（例如某道题的代码，要求可以过编译）。

* 如果只想将源代码中的某些片段放入代码模板，请使用 `#define ACM_BEGIN` 和 `#define ACM_END` 将这些代码片段包住。一个源文件中可以截取任意多的代码片段，打印时将会把这些片段依次连接输出（可以参见 `database/sa-nlogn.cpp`）。如果没有指定范围，则整个源文件都会打印。

* **在每个源文件开头必须添加如下的注释**（以 `database/sais.cpp` 为例）：

    ```c++
    /**
     * title: 后缀排序：SA-IS
     * category: 字符串
     * description: sais.md
     */
    ```

    分别表示在打印稿中的标题、分类以及相关的说明文档。例如，在上面的 `description` 中指定了 `sais.md` 为该源代码的说明文件，则打印时会将 `sais.md` 文件中的内容放到代码前（具体效果参见 `output.pdf` 和 `output-compact.pdf`）。如果没有说明文档，则 `description` 处应填写 `/dev/null`（空文件占位符，可以参见 `database/simplex.cpp`）。

* 说明文件使用 Markdown 编写，支持 LaTeX 数学公式。数学公式使用 [KaTeX](https://katex.org) 渲染，可以前往 KaTeX 首页测试数学公式。