#include "core/TrieTree.h"

template <class T>
TrieTree<T>::TrieTree():m_nNodes(0),m_pRoot(nullptr)
{
   m_pRoot = new TrieNode<T>();
}

template <class T>
TrieTree<T>::~TrieTree()
{
    delete m_pRoot;
}

template <class T>
bool TrieTree<T>::IsExist(T& word)
{
    return false;
}

template <class T>
bool TrieTree<T>::Insert(T& word)
{
    return false;
}

template <class T>
bool TrieTree<T>::Delete(T& word)
{
    return false;
}

template <class T>
wxVector<T> TrieTree<T>::FindNodesWithPrefix(T& prefix)
{
    wxVector<T> words;
    return words;
}

template <class T>
size_t TrieTree<T>::GetNodeCount() const
{
    return 0;
}

template <class T>
void TrieTree<T>::Print()
{

}
