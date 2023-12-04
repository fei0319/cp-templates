std::function<void(int, int)> dfs = [&](int node, int f) {
    stack.push_back(node);
    vist[node] = true;
    dfn[node] = low[node] = ++ind;

    for (int to : G[node]) {
        if (!vist[to]) {
            dfs(to, node);
            low[node] = std::min(low[node], low[to]);
        } else {
            low[node] = std::min(low[node], dfn[to]);
        }
    }

    if (f == -1) {
        if (G[node].empty()) {
            ans.push_back({node});
        }
    } else if (low[node] == dfn[f]) {
        std::vector<int> component {f, node};
        while (stack.back() != node) {
            component.push_back(stack.back());
            stack.pop_back();
        }
        stack.pop_back();
        ans.push_back(component);
    }
};