#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define  COLOR_BLACK 0
#define  COLOR_RED   1

typedef struct red_black_node {
  int data;
  int color;
  struct red_black_node *father;
  struct red_black_node *lson;
  struct red_black_node *rson;
}red_black_node_t;

typedef struct red_black_tree {
  struct red_black_node *top;
}red_black_tree_t;

red_black_node_t *red_black_nil_node = NULL;

#define RB_NIL_NODE get_red_black_nil_node()

red_black_node_t *get_red_black_nil_node()
{
  if(red_black_nil_node == NULL)
  {
    red_black_nil_node = calloc(1, sizeof(red_black_node_t));
    red_black_nil_node->color  = COLOR_BLACK;
    red_black_nil_node->father = NULL;
    red_black_nil_node->lson   = NULL;
    red_black_nil_node->rson   = NULL;
  }
  return red_black_nil_node;
}

red_black_tree_t *red_black_tree_create()
{
  red_black_tree_t *tree = calloc(1, sizeof(red_black_tree_t));
  tree->top = RB_NIL_NODE;
  return tree;
}

void new_red_black_node(red_black_node_t **node,
                        red_black_node_t *father,
                        int data) 
{
  *node = calloc(1, sizeof(red_black_node_t));
  (*node)->data   = data;
  (*node)->color  = COLOR_RED;
  (*node)->father = father;
  (*node)->lson   = RB_NIL_NODE;
  (*node)->rson   = RB_NIL_NODE;
}

void rotate_tree_counterclockwise(red_black_node_t *node)
{
  red_black_node_t *father = node->father;
  if(father != NULL)
  {
    if(father->lson == node)
      father->lson = node->rson;
    if(father->rson == node)
      father->rson = node->rson;
  }

  node->father = node->rson;
  node->rson->father = father;

  node->rson = node->rson->lson;
  node->rson->lson = node;
}

void rotate_tree_clockwise(red_black_node_t *node)
{
  red_black_node_t *father = node->father;
  if(father != NULL)
  {
    if(father->lson == node)
      father->lson = node->lson;
    if(father->rson == node)
      father->rson = node->lson;
  }

  node->father = node->lson;
  node->lson->father = father;

  node->lson = node->lson->rson;
  node->lson->rson = node;
}

void red_black_tree_adjust(red_black_node_t *node)
{
  red_black_node_t *tnode = node;

  /* insert root node must be black */
  if(tnode->father == NULL)
  {
    tnode->color = COLOR_BLACK;
    return;
  }

  red_black_node_t *uncle = NULL;
  red_black_node_t *father = NULL;
  red_black_node_t *grandpa = NULL;
  red_black_node_t *tmp = NULL;
  while(tnode->father && tnode->father->color == COLOR_RED)
  {
    father = tnode->father;
    grandpa = tnode->father->father;
    if(grandpa == NULL) return;
    if(father == grandpa->lson)
    {
      uncle = grandpa->rson;
      if(uncle->color == COLOR_RED)
      {
        father->color = COLOR_BLACK; /* whatever father color is, set to black */
        uncle->color = COLOR_BLACK; /* uncle color from red to black */
        grandpa->color = COLOR_RED; /* grandpa color from black to red */
        tnode = grandpa; /* take grandpa node as tnode to adjust */
      }
      else //rotate LL
      {
        if(tnode == father->rson) //LR => LL
        {
          rotate_tree_counterclockwise(father);
          tmp = father;
          father = tnode;
          tnode = tmp;
        }
        //self is red, father to top, grandpa become brother
        father->color = COLOR_BLACK;
        grandpa->color = COLOR_RED;
        rotate_tree_clockwise(grandpa);
      }
    } 
    else if(father == grandpa->rson)
    {
      uncle = grandpa->lson;
      if(uncle->color == COLOR_RED)
      {
        father->color = COLOR_BLACK;
        uncle->color = COLOR_BLACK;
        grandpa->color = COLOR_RED;
        tnode = grandpa;
      }
      else //rotate RR
      {
        if(tnode == father->lson) //RL => RR
        {
          rotate_tree_clockwise(father);
          tmp = father;
          father = tnode;
          tnode = tmp;
        }
        //self is red, father to top, grandpa become brother
        father->color = COLOR_BLACK;
        grandpa->color = COLOR_RED;
        rotate_tree_counterclockwise(grandpa);
      }
    }
  }
}

void red_black_tree_insert(red_black_tree_t *tree, int data)
{
  red_black_node_t **node = &tree->top;
  red_black_node_t *father = NULL;
  while(*node != RB_NIL_NODE)
  {
    father = *node;
    if(data < (*node)->data)
      node = &(*node)->lson;
    else if(data > (*node)->data)
      node = &(*node)->rson;
    else
      return; /* already exist */
 printf("---> node %p\n", *node);  
  }

  new_red_black_node(node, father, data);
  red_black_tree_adjust(*node);
}

int main(int argc, char** args[])
{
  red_black_tree_t *tree = NULL;
  tree = red_black_tree_create();

  int i=0;
  for(; i<20; i++)
  {
    int val = rand() % 100;
    red_black_tree_insert(tree, val);
  }

  printf("nil node color is %d\n", RB_NIL_NODE->color);


  return 0;
}

