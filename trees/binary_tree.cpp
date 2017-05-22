#include <iostream>
#include "binary_tree.h"
using namespace std;

template<class T>
void BinaryTree<T>::PrintTree(TreeNode<T> *&startNode, TreeNode<T> *&endNode)
{
    if(startNode == NULL)
    {
        cout << "The Binary Tree is empty" << endl;
        return;
    }

    TreeNode<T> *snode;
    snode = startNode;
    if(snode != endNode)
    {
        //get the smallest node from the tree
        while(snode->lson != endNode) snode = snode->lson;
        cout << "(" << snode->data << ":"<<  snode->dfreq << ") ";

        //print smallest node's right tree
        TreeNode<T> *enode = NULL;
        if(snode->rson != NULL) PrintTree(snode->rson, enode);

        //set snode as end node
        PrintTree(startNode, snode);
    }
}

template<class T>
void BinaryTree<T>::PrintTree()
{
    TreeNode<T> *enode  = NULL;
    PrintTree(root, enode);
}

template<class T>
void BinaryTree<T>::Insert(TreeNode<T>* &node, T x)
{
    if(node == NULL)
    {
      node = new TreeNode<T>();
      node->data = x;
      node->dfreq = 1;
      return;
    }

    if(x > node->data)
    {
        Insert(node->rson, x);
    }
    else if(x < node->data)
    {
        Insert(node->lson, x);
    }
    else
    {
        (node->dfreq)++;
    }
}

template<class T>
void BinaryTree<T>::Insert(T x)
{
    Insert(root, x); 
}

template<class T>
void BinaryTree<T>::removeNode(TreeNode<T>* &node)
{
    if(node->lson == NULL && node->rson == NULL) 
    {
        node = NULL;
        return;
    }

    TreeNode<T> *tnode = node;
    if(node->lson != NULL && node->rson == NULL)
    {
        tnode = node;
        node = node->lson;
        delete(tnode);
        return;
    }

    if(node->lson == NULL && node->rson != NULL)
    {
        tnode = node;
        node = node->rson;
        delete(tnode);
        return;
    }

    TreeNode<T> *snode;
    if(node->lson != NULL && node->rson != NULL)
    {
        //fine smallest node in the right node
        snode = node->rson;
        while(snode != NULL)
        {
            tnode = snode;
            snode = snode->lson;
        }
        snode = tnode;

        //set
        tnode = node;
        snode->lson = node->lson;
        node = node->rson;
        delete(tnode);
        return;
    }

    return;
}

template<class T>
void BinaryTree<T>::Delete(TreeNode<T>* &node, T x)
{
    if(node == NULL) return;
    if(x > node->data)
    {
        Delete(node->rson, x);
    }
    else if(x < node->data)
    {
        Delete(node->lson, x);
    }
    else
    {
        if(node->dfreq > 1)
            (node->dfreq)--;
        else
            removeNode(node);
    }
}

template<class T>
void BinaryTree<T>::Delete(T x)
{
    Delete(root, x);
}

int main(int argc, char* args[])
{
    //BinaryTree<int> btree();
    BinaryTree<int> btree = BinaryTree<int>();

    int n[7] = {3,8,0,2,5,2,4};

    for(int i=0;i<7;i++)
    {
        btree.Insert(n[i]);
        btree.PrintTree();
        cout<<endl;
    }

    for(int i=0;i<7;i++)
    {
        btree.Delete(n[i]);
        btree.PrintTree();
        cout<<endl;
    }

    return 0;
}

