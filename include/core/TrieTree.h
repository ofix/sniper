#ifndef TRIETREE_H
#define TRIETREE_H

#include <wx/vector.h>

/*********************************
 *@class TrieNode
 *********************************/
#define MAX_TRIE_NODES 26

template <class T>
class TrieNode
{
public:
    T word;
    T value;
    TrieNode<T>* next[MAX_TRIE_NODES];
};

template <class T>
class TrieTree
{
    public:
        TrieTree();
        virtual ~TrieTree();
        bool IsExist(T& word);
        bool Insert(T& word); // if word already exist return false, otherwise return true
        bool Delete(T& word); // delete node from trie tree
        wxVector<T> FindNodesWithPrefix(T& prefix); // search all words with prefix
        size_t GetNodeCount() const; // record trie nodes count
        void Print(); // visible TrieTree in canvas

    protected:
        TrieNode<T>* m_pRoot; //
        size_t m_nNodes;
};

#endif // TRIETREE_H
