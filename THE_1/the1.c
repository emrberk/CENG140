#include <stdio.h>
#include <math.h>
#include "the1.h"
/*Checks whether the queue is empty(i.e. elements are all -1).*/
int is_empty(int queue[MAX_LENGTH]) {
    int i,empty=1;
    for(i=0;i<MAX_LENGTH;i++) {
        if (queue[i] != -1) {
            empty = 0;
        }
    }
    return empty;
}
/*Finds minimum of three numbers.*/
int min(int a,int b,int c) {
    int tempmin=0;
    if (a<=b) tempmin = a;
    else tempmin = b;
    if (c<=tempmin) return c;
    else return tempmin;
}
/*Checks ranges of array*/
int have_leftchild(int node) {
    if ((2*node+1)<=MAX_LENGTH) {
        return 1;
    }
    else {
        return 0;
    }
}
int have_rightchild(int node) {
    if ((2*node+2)<=MAX_LENGTH) {
        return 1;
    }
    else {
        return 0;
    }
}
/*Checks whether given node is leaf.*/
int is_leaf(int binary_tree[MAX_LENGTH],int node) {
    if ((have_leftchild(node) && (binary_tree[2*node+1] != -1)) ||(have_rightchild(node) && binary_tree[2*node+2] != -1)) {
        return 0;
    }
    else {
        return 1;
    }
}
/*Traverses the given tree to breadth form.*/
void breadth_traversal(int queue[MAX_LENGTH],int binary_tree[MAX_LENGTH]) {
    int i=0,j=0;
    while(queue[i] != -1) {
        if (have_leftchild(queue[i]) && binary_tree[2*queue[i]+1] != -1) {
            for(j=0;j<MAX_LENGTH;j++) {
                if (queue[j]==-1) {
                    queue[j] = 2*queue[i]+1;
                    break;
                }
            }
        }
        if (have_rightchild(queue[i]) && binary_tree[2*queue[i]+2] != -1) {
            for(j=0;j<MAX_LENGTH;j++) {
                if (queue[j]==-1) {
                    queue[j] = 2*queue[i]+2;
                    break;
                }
            }
        }    
        i++;
    }
}
/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/
void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    int numinputs,i,index,value;
    for (i=0;i<MAX_LENGTH+1;i++) {
        binary_tree[i] = -1;
    }
    if (get_values_from_user == 1) {
        scanf("%d",&numinputs);
        for (i=0;i<numinputs;i++) {
            scanf("%d %d",&index,&value);
            binary_tree[index] = value;        
        }
    }   
}
/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {
    if (where == 'l' && have_leftchild(node)) {
        if (binary_tree[2*node+1] == -1) {
            binary_tree[2*node+1] = value;
        }
    }
    else if (where =='r' && have_rightchild(node) ) {
        if (binary_tree[2*node+2] == -1) {
            binary_tree[2*node+2] = value;
        }
    }
    else if (where == 'i') {
        if (binary_tree[node] == -1) {
            binary_tree[node] = value;
        }
    }
}
/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    if (is_leaf(binary_tree,node)) {
        binary_tree[node] = -1;
    }
    else {
        binary_tree[node] = -1;
        delete_node_rec(binary_tree,2*node+1);
        delete_node_rec(binary_tree,2*node+2);
    }
}
/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void recursivetab(int i) {
    if (i>0) {
        printf("\t");
        i -= 1;
        recursivetab(i);
    }
}
void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    void drawhelper(int binary_tree[MAX_LENGTH],int root,int depth,int count);
    int count = 0;
    drawhelper(binary_tree,root,depth,count);
}
void drawhelper(int binary_tree[MAX_LENGTH],int root,int depth,int count) {
    int i;
    if(have_leftchild(root) && binary_tree[2*root+1] != -1) {
        drawhelper(binary_tree,2*root+1,depth,count+1);
    }
    
    i = depth-count;
    recursivetab(i);
    
    if (root<=MAX_LENGTH && binary_tree[root]!= -1) {        
	printf("%d\n",binary_tree[root]);
    }
    
    if(have_rightchild(root) && binary_tree[2*root+2] != -1) {
        drawhelper(binary_tree,2*root+2,depth,count+1);
    }
}
/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int heighthelper(int binary_tree[MAX_LENGTH],int root,int height);
    int height = 0;
    return heighthelper(binary_tree,root,height);
}

int heighthelper(int binary_tree[MAX_LENGTH],int root,int height) {
    int leftheight=0,rightheight=0;
    if (!is_leaf(binary_tree,root)) {
        if (have_leftchild(root) && binary_tree[2*root+1] != -1) {
            leftheight = heighthelper(binary_tree,2*root+1,height+1);
        }
        if (have_rightchild(root) && binary_tree[2*root+2] != -1) {
            rightheight = heighthelper(binary_tree,2*root+2,height+1);
        }   
    if (leftheight>=rightheight) {
        height = leftheight;
    }
    else {
        height = rightheight;
    }
}
    return height;
    
}
/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int minhelper(int binary_tree[MAX_LENGTH],int root,int leftmin,int rightmin,int value);
    int leftmin = -1,rightmin = -1,value=-1;
    return minhelper(binary_tree,root,leftmin,rightmin,value);
}
int minhelper(int binary_tree[MAX_LENGTH],int root,int leftmin,int rightmin,int value) {
    value = binary_tree[root];
    if (!is_leaf(binary_tree,root)) {
        if (have_leftchild(root) && binary_tree[2*root+1] != -1) {
            leftmin = minhelper(binary_tree,2*root+1,leftmin,rightmin,value);
        }
        else {
            leftmin = MAX_LENGTH;
        }
        if (have_rightchild(root) && binary_tree[2*root+2] != -1) {
            rightmin = minhelper(binary_tree,2*root+2,leftmin,rightmin,value);
        }
        else {
            rightmin = MAX_LENGTH;
        }
        return min(leftmin,rightmin,value);
    }
    else {
        return value;
    }
}
/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    int queue[MAX_LENGTH],i;
    for(i=0;i<MAX_LENGTH;i++) {
        queue[i] = -1;
    }
    queue[0]=root;
    breadth_traversal(queue,binary_tree);
    for(i=0;i<MAX_LENGTH;i++) {
        if (binary_tree[queue[i]] == value) {
            return queue[i];
        }
    }
    return -1;
}
/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    int ret;
    if ((have_leftchild(root) && 2*root+1 != -1)) {
        ret = depth_first_search_rec(binary_tree,2*root+1,value);
        if (ret != -1) {
            return ret;
        }
    }
    if((have_rightchild(root) && 2*root+2 != -1)) {
        ret = depth_first_search_rec(binary_tree,2*root+2,value);
        if (ret != -1) {
            return ret;
        }
    }
    if (value == binary_tree[root]) {
        return root;
    }    
    else {
        return -1;
    }
}
/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }
}



