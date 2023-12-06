class Treap {
    void push_up(int x) {
        tr[x].size = tr[tr[x].ls].size + tr[tr[x].rs].size + tr[x].cnt;
    }
    std::pair<int, int> split(int x, const int &key) {
        if (!x)
            return {0, 0};
        if (tr[x].key >= key) {
            auto [a, b] = split(tr[x].ls, key);
            tr[x].ls = b, push_up(x);
            return {a, x};
        } else {
            auto [a, b] = split(tr[x].rs, key);
            tr[x].rs = a, push_up(x);
            return {x, b};
        }
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (tr[x].priority > tr[y].priority) {
            tr[x].rs = merge(tr[x].rs, y), push_up(x);
            return x;
        } else {
            tr[y].ls = merge(x, tr[y].ls), push_up(y);
            return y;
        }
    }
    int rt{0};

public:
    void insert(const int &key) {
        auto [a, b] = split(rt, key);
        auto [c, d] = split(b, key + 1);
        // a c d
        if (!c)
            c = new_node(key);
        tr[c].cnt += 1, tr[c].size += 1;

        rt = merge(a, merge(c, d));
    }
    void erase(const int &key) {
        auto [a, b] = split(rt, key);
        auto [c, d] = split(b, key + 1);

        if (c) {
            tr[c].cnt -= 1, tr[c].size -= 1;
            if (!tr[c].cnt)
                c = 0;
        }

        rt = merge(a, merge(c, d));
    }
};