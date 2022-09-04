//
// Created by GentleCold on 2022/9/3.
//

#ifndef MYTINYALGORITHM_HASH_MAP_H
#define MYTINYALGORITHM_HASH_MAP_H

#include <string>
#include <cassert>

namespace myalm {


template <class T>
class Hash;

template <>
class Hash<std::string> {
public:
    size_t operator()(const std::string& key) const {
        unsigned long value = 0;
        int length = (int)key.length();
        for (int i = 0; i < length; i++) {
            value = 5 * value + key[i];
        }
        return size_t(value);
    }
};

template <>
class Hash<long> {
public:
    size_t operator()(const long key) const {
        return size_t(key);
    }
};

template <>
class Hash<int> {
public:
    size_t operator()(const int key) const {
        return size_t(key);
    }
};

template <>
class Hash<char> {
public:
    size_t operator()(const char key) const {
        return size_t(key);
    }
};

template <class K, class V>
class HashMap {
public:
    explicit HashMap(int divisor = 11);
    ~HashMap() {
        for (int i = 0; i < _divisor; i++) delete _table[i];
        delete [] _table;
        delete [] _f;
    }

    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    std::pair<const K, V>* find(const K&) const;
    void insert(const std::pair<const K, V>&);
    void erase(const K&);

private:
    int _search(const K&, bool jump) const;
    std::pair<const K, V> **_table = nullptr;
    bool *_f = nullptr;
    Hash<K> hash;
    int _size = 0;
    int _divisor = 0;
};

template <class K, class V>
HashMap<K, V>::HashMap(int divisor) {
    assert(divisor > 0);
    _divisor = divisor;
    _table = new std::pair<const K, V>*[divisor];
    _f = new bool[_divisor];
    for (int i = 0; i < divisor; i++) {
        _table[i] = nullptr;
        _f[i] = false;
    }
}

template <class K, class V>
int HashMap<K, V>::_search(const K &k, bool jump) const {
    int i = (int)hash(k) % _divisor;
    int j = i;
    do {
        if (jump && _f[j]) j++;
        if (_table[j] == nullptr || _table[j] -> first == k)
            return j;
        j = (j + 1) % _divisor;
    } while (j != i);

    return j;
}

template <class K, class V>
std::pair<const K, V>* HashMap<K, V>::find(const K &k) const {
    int i = _search(k, true);

    if (_table[i] == nullptr || _table[i] -> first != k) return nullptr;

    return _table[i];
}

template <class K, class V>
void HashMap<K, V>::insert(const std::pair<const K, V> &v) {
    assert(_size < _divisor); // if full
    int i = _search(v.first, false);

    if (_table[i]) {
        _table[i] -> second = v.second;
    } else {
        _table[i] = new std::pair<const K, V>(v);
        _size++;
    }
    _f[i] = false;
}

template <class K, class V>
void HashMap<K, V>::erase(const K &k) {
    int i = _search(k, true);

    if (_table[i] == nullptr || _table[i] -> first != k) return;

    delete _table[i];
    _table[i] = nullptr;
    _f[i] = true;
}


}

#endif //MYTINYALGORITHM_HASH_MAP_H
