//
// Created by GentleCold on 2022/8/16.
// 线性表的抽象模板类
//

#ifndef MYTINYALGORITHM_LINEAR_LIST_H
#define MYTINYALGORITHM_LINEAR_LIST_H

template <class T>
class LinearList {
public:
    virtual ~LinearList() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int index) const = 0;
    virtual int index_of(const T& element) const = 0;
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T& element) = 0;
    virtual void push_back(const T& element) = 0;
    virtual void clear() = 0;
};


#endif //MYTINYALGORITHM_LINEAR_LIST_H
