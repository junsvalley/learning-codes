#include "list.h"

/*
        0
     1     2
   3   4 5   6
  7 8

i=0   left 0*2+1 right 0*2+2
i=1   left 1*2+1 right 1*2+2
i=3   left 3*2+1 right 3*2+2

Original: 8 7 6 5 4 3 2 1 0
      8
   7     6
 5   4 3   2
1 0

After first sort: 6 4 2 0 7 3 8 1 5
      6
   4     2
 0   7 3   8
1 5

After second sort: 2 0 3 1 7 6 8 4 5
      2
   0     3
 1   7 6   8
4 5

After third sort: 0 1 3 2 7 6 8 4 5
      0
   1     3
 2   7 6   8
4 5


*/

static int heap_count = 0;

#define HEAP_SIZE 9
int heaparr[HEAP_SIZE]={8,7,6,5,4,3,2,1,0};
extern void array_build_max_heap(int idx, int range);
extern void array_sort_heap();

void print_heap_struct()
{
  int num = HEAP_SIZE;
  int depth = 0;
  do
  {
    depth++;
    num = (num >> 1);
  }
  while(num >= 1);

  int idx = 0;
  printf("             %02d\n", heaparr[0]); 
  printf("        %02d          %02d\n", heaparr[1], heaparr[2]); 
  printf("    %02d      %02d  %02d      %02d\n", heaparr[3], heaparr[4], heaparr[5], heaparr[6]); 
  printf("%02d      %02d\n", heaparr[7], heaparr[8]); 
}

void print_heap_list(link_list_t *list)
{
  int num = HEAP_SIZE;
  int depth = 0;
  do
  {
    depth++;
    num = (num >> 1);
  }
  while(num >= 1);

  link_node_t *node = get_list_node(list, 0); heaparr[0] = node->val;
  node = get_list_node(list, 1); heaparr[1] = node->val;
  node = get_list_node(list, 2); heaparr[2] = node->val;
  node = get_list_node(list, 3); heaparr[3] = node->val;
  node = get_list_node(list, 4); heaparr[4] = node->val;
  node = get_list_node(list, 5); heaparr[5] = node->val;
  node = get_list_node(list, 6); heaparr[6] = node->val;
  node = get_list_node(list, 7); heaparr[7] = node->val;
  node = get_list_node(list, 8); heaparr[8] = node->val;

  printf("             %02d\n", heaparr[0]); 
  printf("        %02d          %02d\n", heaparr[1], heaparr[2]); 
  printf("    %02d      %02d  %02d      %02d\n", heaparr[3], heaparr[4], heaparr[5], heaparr[6]); 
  printf("%02d      %02d\n", heaparr[7], heaparr[8]); 
}

void build_min_heap(link_list_t *list, int node_index, int len /* length to check */) {
  int left_index =  (node_index + 1) * 2 - 1;
  int right_index = (node_index + 1) * 2;

  link_node_t *parent_node = NULL;
  link_node_t *left_node = NULL;
  link_node_t *right_node = NULL;

  parent_node = get_list_node(list, node_index);
  link_node_t *min_node = parent_node;
  int min_index = node_index;
  if(left_index < len){
    left_node = get_list_node(list, left_index);
    if(parent_node->val > left_node->val) {
      min_node = left_node;
      min_index = left_index;
    }
    printf(" left val %d[idx=%d]\n ", left_node->val, left_index);
  }
  if(right_index < len) {
    right_node = get_list_node(list, right_index);
    if(min_node->val > right_node->val) {
      min_node = right_node;
      min_index = right_index;
    }
    printf("rigth val %d[idx=%d]\n ", right_node->val, right_index);
  }
  printf("parent val %d\n ", parent_node->val);
  if(min_node != parent_node) {
    printf(" select smallest value %d to top\n ", min_node->val);
    int tv = parent_node->val;
    parent_node->val = min_node->val;
    min_node->val = tv;
//print_heap_list(list);
    heap_count++;
    //now the mix_index stored the bigger value
    build_min_heap(list, min_index, len); 
  }
}

void my_heap_sort(link_list_t *list, int node_index) {
  int next_index = node_index + 1;
  int right_index = (node_index + 1) << 1;

  link_node_t *cnode = NULL;
  link_node_t *next_node = NULL;
  link_node_t *right_node = NULL;

  cnode = get_list_node(list, node_index);
  if(next_index < list->len)
    next_node = get_list_node(list, next_index);
  if(right_index < list->len)
    right_node = get_list_node(list, right_index);

  int min_index = node_index;
  link_node_t *min_node = cnode;

  if(next_node) {
    if(cnode->val > next_node->val) {
      min_node = next_node;
      min_index = next_index;
    }
  }
  if(right_node) {
    if(cnode->val > right_node->val) {
      min_node = right_node;
      min_index = right_index;
    }
  }

  if(min_node != cnode) {
    printf(" select smallest value %d to top\n ", min_node->val);
    int tv = cnode->val;
    cnode->val = min_node->val;
    min_node->val = tv;
  }

  if(next_node && right_node) {
    if(next_node->val > right_node->val) {
      printf(" switch next[idx=%d] %d and rigth[idx=%d] %d\n ",
             next_index, next_node->val, right_index, right_node->val);
      int tv = next_node->val;
      next_node->val = right_node->val;
      right_node->val = tv;
    }
  }

  if(next_index < list->len){
    my_heap_sort(list, next_index);
  }
  if(right_index < list->len){
    my_heap_sort(list, right_index);
  }
}

/*******************************
 * Average Time O(nlog2n)
 * Space O(1)
 *******************************/
void SORT___HEAP(link_list_t *list) {
  if(list->len == 1)
    return;
/*
  my_heap_sort(list, 0);
  my_heap_sort(list, 0);
  my_heap_sort(list, 0);
  my_heap_sort(list, 0);
  my_heap_sort(list, 0);
*/
  int i = list->len/2 - 1;
  while(i>=0){
    heap_count++;
    build_min_heap(list, i, list->len);
    i--;
  }

  link_node_t *inode = NULL;
  link_node_t *fnode = list->head; /* first node */

  int tv;
  for(i=list->len-1;i>0;i--){
    inode = get_list_node(list, i);
    tv = inode->val;
    inode->val = fnode->val;
    fnode->val = tv;
printf("Check Length=%d-------- last node val set to %d \n", i, inode->val);
//print_heap_list(list);
    heap_count++;
    build_min_heap(list, 0, i);
  }

  int ideal_cnt = list->len*(log(list->len)/log(2));
printf("-------->list len %d, nlog(2)n %d, heap_count %d\n", list->len, ideal_cnt, heap_count);

  //array test
  print_heap_struct();
  array_sort_heap();
  HeapSort(heaparr,9);  
  print_heap_struct();
}

void array_sort_heap()
{
  int ai = 0;
  for(ai = HEAP_SIZE/2 -1;ai>=0;ai--)
  {
    printf("bult----------%d---------\n", ai);
    array_build_max_heap(ai, HEAP_SIZE);
  }

  int i = HEAP_SIZE;
  for(;i>0;i--){
     int tmp = heaparr[i-1];
     heaparr[i-1] = heaparr[0];
     heaparr[0] = tmp;
     printf("sort -> exchange heaparr[%d]=%d heararr[%d]=%d to heaparr[%d]=%d heararr[%d]=%d\n",
       i-1, tmp, 0, heaparr[i-1], i-1, heaparr[i-1], 0, tmp);
     print_heap_struct();
    array_build_max_heap(0, i-1);
  //array_adjust_min_heap(i);
  }
}

#if 0
void array_adjust_min_heap(int idx)
{
  int right = ( idx + 1 ) * 2;
  int left = right - 1; 

  if ( left < HEAP_SIZE && right < HEAP_SIZE && heaparr[left] > heaparr[right] )
  {
     int tmp = heaparr[left];
     heaparr[left] = heaparr[right];
     heaparr[right] = tmp;
     printf("adjust left[%d]=%d right[%d]=%d to left[%d]=%d right[%d]=%d\n",
       left, tmp, right, heaparr[left], left, heaparr[left], right, tmp);
     print_heap_struct();
     array_build_max_heap(left, HEAP_SIZE);
     array_build_max_heap(right, HEAP_SIZE);
  }
}
#endif

void array_build_max_heap(int idx, int range)
{
  int right = ( idx + 1 ) * 2;
  int left = right - 1; 
  int max = idx;

  if ( left < range && heaparr[left] > heaparr[max] )
    max = left;
  if ( right < range && heaparr[right] > heaparr[max] )
    max = right;

  if ( max != idx )
  {
     int tmp = heaparr[idx];
     heaparr[idx] = heaparr[max];
     heaparr[max] = tmp;
     printf("exchange heaparr[%d]=%d heararr[%d]=%d to heaparr[%d]=%d heararr[%d]=%d\n",
       idx, tmp, max, heaparr[idx], idx, heaparr[idx], max, tmp);
     print_heap_struct();
     array_build_max_heap(max, range);
  } 
}



//获取父节点  
int Parent(int i)  
{  
    return i/2;  
}  
//获取左孩子  
int Left(int i)  
{  
    return 2*i;  
}  
//获取右孩子  
int Right(int i)  
{  
    return 2*i+1;  
}  
//从i节点开始生成最大堆  
void MaxHeap(int *a,int i,int length)  
{  
    int L,R;  
    L=Left(i);  
    R=Right(i);  
    int largest;  
    if(L<=length&&a[L-1]>a[i-1])  
    {  
        largest=L;  
    }  
    else  
        largest=i;  
    if(R<=length&&a[R-1]>a[largest-1])  
    {  
        largest=R;  
    }  
    if(largest!=i)  
    {  
        int temp;  
        temp=a[i-1];  
        a[i-1]=a[largest-1];  
        a[largest-1]=temp;  
     printf("exchange heaparr[%d]=%d heararr[%d]=%d to heaparr[%d]=%d heararr[%d]=%d\n",
       i-1, temp, largest-1, heaparr[i-1], i-1, heaparr[i-1], largest-1, temp);
     print_heap_struct();
        MaxHeap(a,largest,length);  
    }  
}  
//将整个树生成最大堆  
void Build_Max_Heap(int *a,int length)  
{  
    //从length/2开始是因为length/2节点以下的都是叶子节点  
    int i=length/2;
    for(;i>=1;i--)  
    {  
        MaxHeap(a,i,length);  
    }  
}  
//堆排序  
void HeapSort(int *a,int length)  
{  
    Build_Max_Heap(a,length);  
    int number=length;  
    int i=length;  
    for(;i>0;i--)  
    {  
        int temp;  
        temp=a[i-1];  
        a[i-1]=a[0];  
        a[0]=temp;  
        length-=1;  
     printf("HeapSort(i=%d) heaparr[%d]=%d heararr[%d]=%d to heaparr[%d]=%d heararr[%d]=%d\n",i,
       i-1, temp, 0, heaparr[i-1], i-1, heaparr[i-1], 0, temp);
    print_heap_struct();
        MaxHeap(a,1,length);  
    }  
}  

