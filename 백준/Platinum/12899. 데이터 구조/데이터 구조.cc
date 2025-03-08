#include <stdio.h>
#include <malloc.h>

int* Initialize (int size);
int Query (int* tree, int length, int order);
void Update (int* tree, int length, int target);

void Display (int* tree, int depth, int limit, int position, char direction) {

    if (limit == 0) return;

    for (int repeat = 0; repeat < depth; repeat++) printf ("   ");
    printf ("%c, %d\n", direction, tree[position]);

    Display (tree, depth + 1, limit - 1, position * 2, 'L');
    Display (tree, depth + 1, limit - 1, position * 2 + 1, 'R');
    return;
}

int main (int argc, char* argv[]) {

    int length = 2000000;
    int* tree = Initialize (length);

    int count = 0;
    scanf ("%d", &count);

    for (int repeat = 0; repeat < count; repeat++) {

        int commend = 0;
        scanf ("%d", &commend);
        if (commend == 1) {

            int data = 0;
            scanf ("%d", &data);
            Update (tree, length, data - 1);
        }
        else {

            int position = 0;
            scanf ("%d", &position);
            printf ("%d\n", Query (tree, length, position));
        }
    }

    // Update (tree, length, 1 - 1);
    // Update (tree, length, 5 - 1);
    // Update (tree, length, 7 - 1);
    // Update (tree, length, 8 - 1);
    // Update (tree, length, 10 - 1);
    
    // // Display (tree, 0, 5, 1, 'O');

    // printf ("%d\n", Query (tree, length, 1));
    // printf ("%d\n", Query (tree, length, 2));
    // printf ("%d\n", Query (tree, length, 3));

    // // Display (tree, 0, 5, 1, 'O');

    free ((int*)tree);
    return 0;
}

int* Initialize (int size) {

    return (int*) calloc (size * 4, sizeof (int));
}

// binary search and segment tree
int Query (int* tree, int length, int order) {

    int left = 1, right = length;
    int current = 1; // root
    while (left < right) {

        tree[current] = tree[current] - 1;
        
        int middle = (left + right) / 2;
        if (order <= tree[current * 2]) {

            current = current * 2;
            right = middle;
        }
        else {

            order = order - tree[current * 2];
            current = current * 2 + 1;
            left = middle + 1;
        }
    }

    tree[current] = tree[current] - 1;
    return right;
}

int UpdateRecursive (int* tree, int index, int position, int start, int end) {

    if (index < start || index > end) return tree[position];
    if (start == end) return tree[position] = tree[position] + 1;
    
    int middle = (start + end) / 2;
    
    return tree[position] = UpdateRecursive (tree, index, position * 2, start, middle) + 
            UpdateRecursive (tree, index, position * 2 + 1, middle + 1, end);
}

void Update (int* tree, int length, int target) {

    UpdateRecursive (tree, target, 1, 0, length - 1);
    return;
}