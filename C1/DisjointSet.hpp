#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <unordered_map>
#include <iostream>
#include <vector>

template <class T>
class DisjointSets {
private:

public:
    DisjointSets(bool pathCompression = false, bool unionByRank = false);
    int size();
    void makeSet(T u);
    T findSet(T u);
    void unionSet(T u, T v);
    T getParent(T u);
};
template <class T>
DisjointSets<T>::DisjointSets(bool pathCompression, bool unionByRank)
{

}
template <class T>
int DisjointSets<T>::size()
{

}
template <class T>
void DisjointSets<T>::makeSet(T u)
{

}
template <class T>
T DisjointSets<T>::findSet(T u)
{
    return T();
}
template <class T>
void DisjointSets<T>::unionSet(T u, T v)
{

}
template <class T>
T DisjointSets<T>::getParent(T u)
{
    return T();
}

#endif