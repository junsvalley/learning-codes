#include "balance_binary_tree.h"
using namespace std;

template<class T>
int AVLTree<T>::height(TreeNode<T>* node)
{
    if(node!=NULL)
	return node->hgt;
    return -1;
}

template<class T>
int AVLTree<T>::Max(int cmpa,int cmpb)
{
    return cmpa>cmpb?cmpa:cmpb;
}

template<class T>
void AVLTree<T>::SingRotateLeft(TreeNode<T>* &k2)
{
    TreeNode<T>* k1;
    k1=k2->lson;
    k2->lson=k1->rson;
    k1->rson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->lson),k2->hgt)+1;
}

template<class T>
void AVLTree<T>::SingRotateRight(TreeNode<T>* &k2)
{
    TreeNode<T>* k1;
    k1=k2->rson;
    k2->rson=k1->lson;
    k1->lson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->rson),k2->hgt)+1;
}

template<class T>
void AVLTree<T>::DoubleRotateLR(TreeNode<T>* &k3)
{
    SingRotateRight(k3->lson);
    SingRotateLeft(k3);
}

template<class T>
void AVLTree<T>::DoubleRotateRL(TreeNode<T>* &k3)
{
    SingRotateLeft(k3->rson);
    SingRotateRight(k3);
}

template<class T>
void AVLTree<T>::insertpri(TreeNode<T>* &node,T x)
{
    if(node==NULL)
    {
	node=new TreeNode<T>();
	node->data=x;
	return;
    }
    if(node->data>x)
    {
	insertpri(node->lson,x);
	if(2==height(node->lson)-height(node->rson))
	    if(x<node->lson->data)
		SingRotateLeft(node);
	    else
		DoubleRotateLR(node);
    }
    else if(node->data<x)
    {
	insertpri(node->rson,x);
	if(2==height(node->rson)-height(node->lson))
	    if(x>node->rson->data)
		SingRotateRight(node);
	    else
		DoubleRotateRL(node);
    }
    else ++(node->freq);
    node->hgt=Max(height(node->lson),height(node->rson));
}

template<class T>
void AVLTree<T>::insert(T x)
{
    insertpri(root,x);
}

template<class T>
TreeNode<T>* AVLTree<T>::findpri(TreeNode<T>* node,T x)
{
    if(node==NULL)
    {
	return NULL;
    }
    if(node->data>x)
    {
	return findpri(node->lson,x);
    }
    else if(node->data<x)
    {
	return findpri(node->rson,x);
    }
    else return node;
}

template<class T>
TreeNode<T>* AVLTree<T>::find(T x)
{
    return findpri(root,x);
}

template<class T>
void AVLTree<T>::Deletepri(TreeNode<T>* &node,T x)
{
    if(node==NULL) return ;//not founf the node with the value x
    if(x < node->data)
    {
	Deletepri(node->lson,x);//if x < node's val, then delete x from the left child tree
	if(2==height(node->rson)-height(node->lson))
	    if(node->rson->lson!=NULL&&(height(node->rson->lson)>height(node->rson->rson)) )
		DoubleRotateRL(node);
	    else
		SingRotateRight(node);
    }

    else if(x > node->data)
    {
	Deletepri(node->rson,x);//if x > node's val, then delete x from the right child tree
	if(2==height(node->lson)-height(node->rson))
	    if(node->lson->rson!=NULL&& (height(node->lson->rson)>height(node->lson->lson) ))
		DoubleRotateLR(node);
	    else
		SingRotateLeft(node);
    }

    else//if equal, this noe need to delete
    {
	if(node->lson&&node->rson)//this node has two child
	{
	    TreeNode<T>* temp=node->rson;//temp points to the right child node
	    while(temp->lson!=NULL) temp=temp->lson;//find smallest node in right child tree

	    //set this node as the smallest node in the right child tree
	    node->data=temp->data;
	    node->freq=temp->freq;
	    Deletepri(node->rson,temp->data);//delete smallest node in right child tree
	    if(2==height(node->lson)-height(node->rson))
	    {
		if(node->lson->rson!=NULL&& (height(node->lson->rson)>height(node->lson->lson) ))
		    DoubleRotateLR(node);
		else
		    SingRotateLeft(node);
	    }
	}
	else//this node has 1 or 0 child
	{
	    TreeNode<T>* temp=node;
	    if(node->lson==NULL)//only has right child
		node=node->rson;
	    else if(node->rson==NULL)//only has left child
		node=node->lson;
	    delete(temp);
	    temp=NULL;
	}
    }
    if(node==NULL) return;
    node->hgt=Max(height(node->lson),height(node->rson))+1;
    return;
}

template<class T>
void AVLTree<T>::Delete(T x)
{
    Deletepri(root,x);
}


template<class T>
void AVLTree<T>::insubtree(TreeNode<T>* node)
{
    if(node==NULL) return;
    insubtree(node->lson);
    cout<<node->data<<" ";
    insubtree(node->rson);
}

template<class T>
void AVLTree<T>::traversal()
{
    insubtree(root);
}

int main(int argc, char *argv[])
{
    cout<<"Start the doing something..."<<endl;
    AVLTree<int> avltree = AVLTree<int>();
    
    int n[7]={3,8,0,2,5,2,4};
    for(int i;i<7;i++)
    {
        avltree.insert(n[i]);
        avltree.traversal();
        cout<<endl;
    }
    return 0;
}

