#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	initialize_the_tree(binary_tree, 0);
	
    binary_tree[0] = 7;
    binary_tree[1] = 53;
    binary_tree[2] = 10;
    binary_tree[3] = 7;
    binary_tree[4] = 6;
    binary_tree[5] = 81;
    binary_tree[6] = 9;
    binary_tree[9] = 74;
    binary_tree[12] = 74;
    binary_tree[13] = 81;
    binary_tree[14] = 47;
    binary_tree[25] = 14;
    binary_tree[27] = 35;
    binary_tree[29] = 9;
    binary_tree[30] = 6;
    binary_tree[61] = 53;
    
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);
	
    printf("Tree representation of root[%d] with pre-order\n", 0);
	draw_binary_tree_rec(binary_tree, 0, 5);
		
    printf("Tree representation of root[%d] with pre-order\n", 14);
	draw_binary_tree_rec(binary_tree, 14, 2);
    	
	return 0;
}
