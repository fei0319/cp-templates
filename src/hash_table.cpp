#include <vector>

template <typename K, typename V, typename Hasher>
class HashTable {
    std::vector<std::vector<std::pair<K, V>>> d;

public:
    void resize(std::size_t size){
        d.resize(size);
    }
    V &operator[](const K &key){   auto &vec = d[Hasher()(key) % d.size()];
        for (auto &[k, v] : vec) {
            if (key == k) {                return v;
            }        }

        vec.emplace_back(key, V());        return vec.back().second;
    }};