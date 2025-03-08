#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct HeapType {
  
  int* Table;
  int Size;
  int NumberOfElement;
  
  bool (*Compare) (const int, const int);
};

struct HeapType* Create_Heap (int size, bool (*Compare) (int, int));
void Insert_Heap (struct HeapType* heap, int data);
int Remove_Heap (struct HeapType* heap);
void Delete_Heap (struct HeapType* heap);

void Display (struct HeapType* heap, int current, int depth) {
  
  if (heap == NULL || heap->Table == NULL) return;
  if (current > heap->NumberOfElement) return;
  
  for (int space = 0; space < depth; space++) printf ("  ");
  printf ("%d\n", heap->Table[current]);
  
  Display (heap, current * 2, depth + 1);
  Display (heap, current * 2 + 1, depth + 1);
  return;
}

bool MaxHeap (const int left, const int right) {
  
  return left > right;
}

bool MinHeap (const int left, const int right) {
  
  return left < right;
}

int main (int argc, char* argv[]) {
  
  int length = 0;
  scanf ("%d", &length);
  
  struct HeapType* heap = Create_Heap (length * 2 + 1, &MaxHeap);
  for (int index = 0; index < length; index++) {
    
    int data = 0;
    scanf ("%d", &data);
    if (data == 0) {
      
      printf ("%d\n", Remove_Heap (heap));
    }
    else Insert_Heap (heap, data);
  }
  
  Delete_Heap (heap);
  return 0;
}

struct HeapType* Create_Heap (int size, bool (*compare) (const int, const int)) {
  
  if (size < 1) return NULL;
  
  struct HeapType* newheap = (struct HeapType*) malloc (1 * sizeof (struct HeapType));
  if (newheap == NULL) return NULL;
  
  newheap->Table = (int*) calloc (size + 1, sizeof (int));
  if (newheap->Table == NULL) {
    
    free ((struct HeapType*) newheap);
    return NULL;
  }
  
  newheap->Table[0] = -2147483648; // -inf
  newheap->Size = size;
  newheap->NumberOfElement = 0;
  newheap->Compare = compare;
  return newheap;
}

bool IsFull_Heap (struct HeapType* heap) {
  
  return heap->Size == heap->NumberOfElement;
}

bool IsEmpty_Heap (struct HeapType* heap) {
  
  return heap->NumberOfElement == 0;
}

int Parent (int current) {
  
  return current / 2;
}

int LeftChild (int current) {
  
  return current * 2;
}

int RightChild (int current) {
  
  return current * 2 + 1;
}

void Swap (int* left, int* right) {
  
  int temp = *left;
  *left = *right;
  *right = temp;
  return;
}

void HeapifyRecursive (struct HeapType* heap, int current) {
  
  int left = LeftChild (current);
  int right = RightChild (current);
  
  int largest = -1;
  if (left <= heap->NumberOfElement && heap->Compare (heap->Table[left], heap->Table[current])) {
    
    largest = left;
  }
  else largest = current;
  
  if (right <= heap->NumberOfElement && heap->Compare (heap->Table[right], heap->Table[largest])) {
    
    largest = right;
  }
  
  if (largest == current) return;
  
  Swap (heap->Table + current, heap->Table + largest);
  HeapifyRecursive (heap, largest);
  return;
}

void InsertRecursive (struct HeapType* heap, int current) {
  
  int parentIndex = Parent (current);
  if (parentIndex == 0) return;
  
  if (heap->Compare (heap->Table[parentIndex], heap->Table[current])) return;
  
  Swap (heap->Table + parentIndex, heap->Table + current);
  InsertRecursive (heap, parentIndex);
  return;
}

void Insert_Heap (struct HeapType* heap, int data) {
  
  if (heap == NULL || heap->Table == NULL) return;
  if (IsFull_Heap (heap)) return;
  
  int leaf = ++heap->NumberOfElement;
  heap->Table[leaf] = data;
  
  InsertRecursive (heap, leaf);
  return;
}

int Remove_Heap (struct HeapType* heap) {
  
  if (heap == NULL || heap->Table == NULL) return -1;
  if (IsEmpty_Heap (heap)) return 0;
  
  int leaf = heap->NumberOfElement--;
  int root = 1;
  int data = heap->Table[root];
  Swap (heap->Table + root, heap->Table + leaf);
  heap->Table[leaf] = 0;
  
  HeapifyRecursive (heap, 1);
  return data;
}

void Delete_Heap (struct HeapType* heap) {
  
  if (heap == NULL) return;
  
  if (heap->Table != NULL) {
    
    free ((int*) heap->Table);
  }
  free ((struct HeapType*) heap);
  return;
}