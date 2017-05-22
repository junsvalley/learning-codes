#include <stdlib.h>
#include <iostream>

template<class T>
class TreeNode
{
    public:
	TreeNode():lson(NULL),rson(NULL),freq(1),hgt(0){}
	T data;
	int hgt;
	unsigned int freq;
	TreeNode* lson;
	TreeNode* rson;

};

template<class T>
class AVLTree
{
    private:
	TreeNode<T>* root;
	void insertpri(TreeNode<T>* &node,T x);
	TreeNode<T>* findpri(TreeNode<T>* node,T x);
	void insubtree(TreeNode<T>* node);
	void Deletepri(TreeNode<T>* &node,T x);
	int height(TreeNode<T>* node);
	void SingRotateLeft(TreeNode<T>* &k2);
	void SingRotateRight(TreeNode<T>* &k2);
	void DoubleRotateLR(TreeNode<T>* &k3);
	void DoubleRotateRL(TreeNode<T>* &k3);
	int Max(int cmpa,int cmpb);

    public:
	AVLTree():root(NULL){}
	void insert(T x);
	TreeNode<T>* find(T x);
	void Delete(T x);
	void traversal();

};

