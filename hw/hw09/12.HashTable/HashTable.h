#pragma once

#include <vector>
#include <list>
#include <string>
#include <functional>
#include <optional>
#include <algorithm>

namespace OtusAlgo {

template<typename K, typename V>
class HashTable {
private:
    struct HashEntry {
        K key;
        V value;
    };

    using HashTableType = std::vector<std::list<HashEntry>>;
    static const size_t DEFAULT_CAPACITY=11;
    static constexpr float DEFAULT_LOAD_FACTOR=0.75f;
    float m_load_factor;
    size_t m_threshold;
    size_t m_size = 0;
    HashTableType m_buckets;

public:
    HashTable();
    explicit HashTable(int init_size);
    HashTable(int init_size, const float load_factor);
    size_t size() const;
    bool empty() const;
    bool containsValue(V value) const;
    bool containsKey(K key) const;
    std::optional<V> get(K key) const;
    std::optional<V> put(K key, V value);
private:
    size_t getHash(K key) const;
    void rehash();
};



template<typename K, typename V>
HashTable<K,V>::HashTable():
    HashTable(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) {}

template<typename K, typename V>
HashTable<K, V>::HashTable(const int init_size):
    HashTable(init_size, DEFAULT_LOAD_FACTOR) {}

template<typename K, typename V>
HashTable<K, V>::HashTable(int init_size, const float load_factor){
    if (init_size < 0)
        throw std::runtime_error("Illegal Init Size: " + std::to_string(init_size));
    if (load_factor <= 0)
        throw std::runtime_error("Illegal Load: " + std::to_string(load_factor));
     
    if (init_size == 0)
        init_size = 1;
    m_buckets.resize(init_size);
    m_load_factor = load_factor;
    m_threshold = (size_t) (init_size * m_load_factor);
}

template<typename K, typename V>
size_t HashTable<K, V>::size() const {
    return m_size;
}

template<typename K, typename V>
bool HashTable<K, V>::empty() const {
    return m_size == 0;
}

template<typename K, typename V>
bool HashTable<K, V>::containsValue(V value) const {
    for (const auto &chain: m_buckets) {
        auto found = std::find_if(chain.begin(), chain.end(),
                                  [&value](const auto& entry){
            return entry.value == value;
        });
        if (found != chain.end())
            return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::containsKey(K key) const {
    size_t idx = getHash(key);
    const auto& chain = m_buckets[idx];
    auto found = std::find_if(chain.begin(), chain.end(),
                              [&key](const auto& entry){
        return entry.key == key;
    });
    return found != chain.end();
}

template<typename K, typename V>
size_t HashTable<K, V>::getHash(K key) const {
    return std::hash<K>{}(key) % m_buckets.size();
}


template<typename K, typename V>
std::optional<V> HashTable<K, V>::get(K key) const {
    const size_t idx = getHash(key);
    const auto& chain = m_buckets[idx];
    auto found = std::find_if(chain.begin(), chain.end(),
                              [&key](auto entry){
        return entry.key == key;
    });
    if (found != chain.end()) {
        return {found->value};
    }
    else {
        return std::nullopt;
    }
}

template<typename K, typename V>
std::optional<V> HashTable<K, V>::put(K key, V value) {
    size_t idx = getHash(key);
    auto& chain = m_buckets[idx];
    auto found = std::find_if(chain.begin(), chain.end(),
                              [&key](auto entry){
        return entry.key == key;
    });
    // found entry
    if (found != chain.end()) {
        V r = found->value;
        found->value = value;
        return {r};
    }
    // need to add a new value
    if (++m_size > m_threshold) {
        rehash();
        idx = getHash(key);
    }
    
    m_buckets[idx].push_back({key, value});
    return std::nullopt;
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    size_t new_capacity = m_buckets.size()*2 + 1;
    m_threshold = m_load_factor*new_capacity;
    // new hash table
    HashTableType new_table(new_capacity);
    // copy old data to a new hash-table
    for (const auto& chain: m_buckets) {
        for (auto& entry: chain) {
            size_t idx = getHash(entry.key);
            new_table[idx].push_back(std::move(entry));
        }
    }
    std::swap(m_buckets, new_table);
}

} // namespace OtusAlgo


