#include "list.h"

int link_list_split(link_list_t *l, int low, int high) {
  link_node_t *pn; /* pivot node */
  link_node_t *hn; /* high node */
  link_node_t *ln; /* low node */
  pn = get_list_node(l, low);

  while(low < high) {
    hn = get_list_node(l, high);
    while(low < high && pn->val <= hn->val) {
      hn = hn->pre;
      high--;
    }
    exchange_link_node(l, pn, hn);

    ln = get_list_node(l, low);
    while(low < high && pn->val >= ln->val) {
      ln = ln->next;
      low++;
    }
    exchange_link_node(l, ln, pn);
  }
  return low;
}

void link_quick_sort(link_list_t *l, int low, int high) {
  if(low < high){
    int pivot = link_list_split(l, low, high);
    link_quick_sort(l, low, pivot - 1);
    link_quick_sort(l, pivot + 1, high);
  }
}

/*******************************
 * Average Time O(nlog2n)
 * Space O(nlog2n)
 *******************************/
void SORT__QUICK(link_list_t *list) {
  link_quick_sort(list, 0, list->len - 1);
}

#define true 1
#define false 0
#define bool unsigned char

typedef struct node {
  int data;
  struct node* prev;
  struct node* next;
}Node_t;

bool isLeftNodeBehind(Node_t* leftNode, Node_t* rightNode)
{
  Node_t* theNode = leftNode;

  while( NULL != theNode )
  {
    if ( theNode == rightNode )
    {
      return false;
    }
    theNode = theNode->next;
  }
  printf("left behind right, return false...\n");
  return true;
}

void quickSort_0(Node_t* leftNode, Node_t* rightNode)
{
  Node_t* origLNode = leftNode;
  Node_t* origRNode = rightNode;
  int baseData=0;

  //1. unmatched return
  if(isLeftNodeBehind(leftNode, rightNode))return;

  //2. loop
  baseData=leftNode->data;
  while(leftNode!=rightNode)
  {
    while(leftNode!=rightNode && rightNode->data>=baseData)rightNode=rightNode->prev;
    leftNode->data=rightNode->data;
    while(leftNode!=rightNode && leftNode->data<=baseData)leftNode=leftNode->next;
    rightNode->data=leftNode->data;
  }
  leftNode->data=baseData;

  //3. recurse
  quickSort_0(origLNode, leftNode->prev);
  quickSort_0(leftNode->next, origRNode);
}

Node_t* partition(Node_t* leftNode, Node_t* rightNode)
{
  Node_t* tmpNode=leftNode;
  int baseData=leftNode->data;
  while(leftNode!=rightNode)
  {
    while(leftNode!=rightNode && rightNode->data>=baseData)rightNode=rightNode->prev;
    leftNode->data=rightNode->data;
    while(leftNode!=rightNode && leftNode->data<=baseData)leftNode=leftNode->next;
    rightNode->data=leftNode->data;
  }
  leftNode->data=baseData;
  //printNodeList(tmpNode);
  return leftNode;
}

void quickSort_1(Node_t* leftNode, Node_t* rightNode)
{
  Node_t* origLNode = leftNode;
  Node_t* origRNode = rightNode;
  Node_t* pivotNode = NULL;

  //1. unmatched return
  if(isLeftNodeBehind(leftNode, rightNode))return;

  //2. loop
  pivotNode=partition(leftNode, rightNode);

  //3. recurse
  quickSort_1(origLNode, pivotNode->prev);
  quickSort_1(pivotNode->next, origRNode);
}

