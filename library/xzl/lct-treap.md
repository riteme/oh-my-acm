用处不大，主要是有 Treap 的 2-way `join2(x, y)`、3-way `join(x, u, y)` 和 3-way `split(x)`。注意初始化每个节点的 `wt` 和 `size`，以及 `split` 后节点 `x` 数据的重设。`mrand` 是 Xorshift 算法，比 C 标准库的 `rand` 快。
