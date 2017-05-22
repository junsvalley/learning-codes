#include <stdlib.h>

template<class T>
class TreeNode
{
    public:
	TreeNode():lson(NULL),rson(NULL){}
	T data;
	int dfreq;
	TreeNode* lson;
	TreeNode* rson;
};

template<class T>
class BinaryTree
{
    private:
	TreeNode<T>* root;

    public:
	BinaryTree():root(NULL){}
	void PrintTree(TreeNode<T> *&startNode, TreeNode<T> *&endNode);
	void PrintTree();
	void Insert(TreeNode<T>* &node, T x);
	void Insert(T x);
	void removeNode(TreeNode<T>* &node);
	void Delete(TreeNode<T>* &node, T x);
	void Delete(T x);
	TreeNode<T>* find(T x);
};

