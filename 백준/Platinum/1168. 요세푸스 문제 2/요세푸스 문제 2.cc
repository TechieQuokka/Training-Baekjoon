#include <stdio.h>
#include <malloc.h>
#include <math.h>

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

    int size = 7, interval = 3;
    scanf ("%d%d", &size, &interval);
    int tree[400001] = { 0, };

    for (int number = 0; number < size; number++) {

        Update (tree, size, number);
    }

    //Display (tree, 0, 5, 1, 'O');

    printf ("<");
    int current = interval;
    for (int increase = 0; increase < size; increase++) {

        printf ("%d", Query (tree, size, current));

        if (increase < size - 1) {

            current = (current + interval - 2) % (size - increase - 1) + 1;
            printf (", ");
        }
    }

    printf (">");
    
    // Display (tree, 0, 4, 1, 'O');
    return 0;
}

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