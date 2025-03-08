#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// linked stack
struct StackNodeType {
	
	void* Data;
	struct StackNodeType* Next;
};

struct LinkedStackType {
	
	int Count;
	bool IsDynamic;
	struct StackNodeType* Head;
};

struct LinkedStackType* Create_LinkedStack (bool IsDynamic);
bool Push_LinkedStack (struct LinkedStackType* stack, void* data);
void* Pop_LinkedStack (struct LinkedStackType* stack);
void* Peek_LinkedStack (struct LinkedStackType* stack);
void Delete_LinkedStack (struct LinkedStackType* stack);
bool IsEmpty_LinkedStack (struct LinkedStackType* stack);

// Linked queue
struct QueueNodeType {
	
	void* Data;
	struct QueueNodeType* Next;
};

struct LinkedQueueType {
	
	int Count;
	bool IsDynamic;
	struct QueueNodeType* Head;
};

struct LinkedQueueType* Create_LinkedQueue (bool IsDynamic);
bool Enqueue_LinkedQueue (struct LinkedQueueType* queue, void* data);
void* Dequeue_LinkedQueue (struct LinkedQueueType* queue);
void* Peek_LinkedQueue (struct LinkedQueueType* queue);
void Delete_LinkedQueue (struct LinkedQueueType* queue);
bool IsEmpty_LinkedQueue (struct LinkedQueueType* queue);

// Linked heap
struct HeapNodeType {
	
	void* Data;
	struct HeapNodeType* LeftChild;
	struct HeapNodeType* RightChild;
};

struct LinkedHeapType {
	
	// event callback
	void (*PreorderTraversal_EventHandler) (struct LinkedHeapType* heap, struct LinkedStackType* stack, struct HeapNodeType* ParentNode);
	void (*InorderTraversal_EventHandler) (struct LinkedHeapType* heap, struct LinkedStackType* stack, struct HeapNodeType* ParentNode);
	void (*PostorderTraversal_EventHandler) (struct LinkedHeapType* heap, struct HeapNodeType* ParentNode);
	void (*LevelorderTraversal_EventHandler) (struct LinkedHeapType* heap, struct LinkedQueueType* queue, struct HeapNodeType* ParentNode);
	
	// compare callback
	int (*Comparator) (void*, void*);
	
	int Count;
	bool IsDynamic;
	struct HeapNodeType* Head;
};

struct LinkedHeapType* Create_LinkedHeap (int (*Comparator) (void*, void*), bool IsDynamic);
bool Insert_LinkedHeap (struct LinkedHeapType* heap, void* data);
void* Remove_LinkedHeap (struct LinkedHeapType* heap);
void Delete_LinkedHeap (struct LinkedHeapType* heap);
bool IsEmpty_LinkedHeap (struct LinkedHeapType* heap);

// traversal
void PreorderTraversal_LinkedHeap (struct LinkedHeapType* heap);
void InorderTraversal_LinkedHeap (struct LinkedHeapType* heap);
void PostorderTraversal_LinkedHeap (struct LinkedHeapType* heap);
void LevelorderTraversal_LinkedHeap (struct LinkedHeapType* heap);

void* MemorySet (void* source, int value, size_t type);
void Swap (void* argument1, void* argument2, size_t type);

int MaxHeap (void* argument1, void* argument2) {
	
	return *(int*) argument2 - *(int*) argument1;
}

int MinHeap (void* argument1, void* argument2) {
    
    return *(int*) argument1 - *(int*) argument2;
}

int* MakeRandomNumber (int length, int maximum) {
	
	int* array = (int*) calloc (length, sizeof (int));
	if (array == NULL) return NULL;
	
	int index = 0;
	for (index = 0; index < length; index++) array[index] = rand() % maximum;
	return array;
}

int main (int argc, char* argv[]) {
	
	struct LinkedHeapType* heap = Create_LinkedHeap (&MinHeap, true);
	if (heap == NULL) return -1;
	
	int size = 0;
	scanf ("%d", &size);
	
	int index = 0;
	for (index = 0; index < size; index++) {
		
		int* data = (int*) malloc (1 * sizeof (int));
		if (data == NULL) return -1;
		
		scanf ("%d", data);
		if (*data == 0) {
            if (IsEmpty_LinkedHeap (heap)) {
                
                printf ("0\n");
                continue;
            }
            int* element = (int*) Remove_LinkedHeap (heap);
            printf ("%d\n", *element);
            free ((int*) element);
            free ((int*) data);
		}
		else Insert_LinkedHeap (heap, data);
	}
	Delete_LinkedHeap (heap);
	return 0;
}

#pragma region Linked heap

struct LinkedHeapType* Create_LinkedHeap (int (*Comparator) (void*, void*), bool IsDynamic) {
	
	if (Comparator == NULL) {
		
		printf ("Error! The comparator is null. Create_LinkedHeap()\n");
		return NULL;
	}
	
	struct LinkedHeapType* NewHeap = (struct LinkedHeapType*) malloc (1 * sizeof (struct LinkedHeapType));
	if (NewHeap == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Create_LinkedHeap()\n");
		return NULL;
	}
	MemorySet ((struct LinkedHeapType*) NewHeap, 0, 1 * sizeof (struct LinkedHeapType));
	NewHeap->Comparator = Comparator;
	NewHeap->IsDynamic = IsDynamic;
	
	NewHeap->Head = (struct HeapNodeType*) malloc (1 * sizeof (struct HeapNodeType));
	if (NewHeap->Head == NULL) {
		
		free ((struct LinkedHeapType*) NewHeap);
		printf ("Error! The dynamic memory allocation failed. Create_LinkedHeap()\n");
		return NULL;
	}
	MemorySet ((struct HeapNodeType*) NewHeap->Head, 0, 1 * sizeof (struct HeapNodeType));
	
	return NewHeap;
}

bool Insert_LinkedHeap (struct LinkedHeapType* heap, void* data) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! The linked heap is null. Insert_LinkedHeap()\n");
		return false;
	}
	
	struct HeapNodeType* NewNode = (struct HeapNodeType*) malloc (1 * sizeof (struct HeapNodeType));
	if (NewNode == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Insert_LinkedHeap()\n");
		return false;
	}
	MemorySet ((struct HeapNodeType*) NewNode, 0, 1 * sizeof (struct HeapNodeType));
	NewNode->Data = data;
	
	if (heap->Count++ == 0) {
		
		heap->Head->RightChild = NewNode; // root node
		return true;
	}
	
	int (*compare) (void*, void*) = heap->Comparator;
	
	struct HeapNodeType* PredecessorNode = heap->Head;
	struct HeapNodeType* SuccessorNode = PredecessorNode->RightChild; // root node
	unsigned int direction = (unsigned int) heap->Count, pivot = 0x1U;
	for (pivot <<= (unsigned int) log2 ((double) direction) - 0x1U; pivot; PredecessorNode = SuccessorNode, SuccessorNode = direction & pivot ? SuccessorNode->RightChild : SuccessorNode->LeftChild, pivot >>= 0x1U) {
		
		if (compare (SuccessorNode->Data, NewNode->Data) < 0) continue;
		
		NewNode->LeftChild = SuccessorNode->LeftChild;
		NewNode->RightChild = SuccessorNode->RightChild;
		SuccessorNode->LeftChild = SuccessorNode->RightChild = NULL;
		if (direction & (pivot << 0x1U)) PredecessorNode->RightChild = NewNode;
		else PredecessorNode->LeftChild = NewNode;

		Swap ((struct HeapNodeType**) &SuccessorNode, (struct HeapNodeType**) &NewNode, sizeof (struct HeapNodeType*));
	}
	
	if (direction & 0x1U) PredecessorNode->RightChild = NewNode;
	else PredecessorNode->LeftChild = NewNode;
	return true;
}

void Swapping (struct HeapNodeType* ParentNode, struct HeapNodeType* ChildNode) {
	
	struct HeapNodeType temporary = { 0, };
	temporary.LeftChild = ParentNode->LeftChild;
	temporary.RightChild = ParentNode->RightChild;
	ParentNode->LeftChild = ChildNode->LeftChild;
	ParentNode->RightChild = ChildNode->RightChild;
	if (temporary.LeftChild == ChildNode) {
		
		ChildNode->LeftChild = ParentNode;
		ChildNode->RightChild = temporary.RightChild;
	}
	else {
		
		ChildNode->LeftChild = temporary.LeftChild;
		ChildNode->RightChild = ParentNode;
	}
	return;
}

struct HeapNodeType* GetWinningNode (struct HeapNodeType* LeftChild, struct HeapNodeType* RightChild, int (*Comparator) (void*, void*)) {
	
	if (LeftChild == NULL || RightChild == NULL) return LeftChild;
	return Comparator (LeftChild->Data, RightChild->Data) < 0 ? LeftChild : RightChild;
}

void* Remove_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! The linked heap is null. Remove_LinkedHeap()\n");
		return NULL;
	}
	if (IsEmpty_LinkedHeap (heap)) {
		
		printf ("Error! The linked heap is empty. Remove_LinkedHeap()\n");
		return NULL;
	}
	if (heap->Count == 0x1) {
		
		void* data = heap->Head->RightChild->Data;
		free ((struct HeapNodeType*) heap->Head->RightChild);
		heap->Head->RightChild = NULL;
		heap->Count = 0;
		return data;
	}
	
	// go to leaf node
	struct HeapNodeType* PredecessorNode = heap->Head->RightChild; // root node
	unsigned int direction = (unsigned int) heap->Count, pivot = 0x1U;
	for (pivot <<= (unsigned int) log2 ((double) direction) - 0x1U; pivot > 0x1U; pivot >>= 0x1U) PredecessorNode = direction & pivot ? PredecessorNode->RightChild : PredecessorNode->LeftChild;
	
	// swapping leaf node
	struct HeapNodeType* SuccessorNode = NULL;
	if (direction & 0x1U) { // right
		
		SuccessorNode = PredecessorNode->RightChild;
		PredecessorNode->RightChild = NULL;
	}
	else { // left
		
		SuccessorNode = PredecessorNode->LeftChild;
		PredecessorNode->LeftChild = NULL;
	}
	PredecessorNode = heap->Head;
	struct HeapNodeType* DeleteNode = PredecessorNode->RightChild; // root node
	PredecessorNode->RightChild = SuccessorNode;
	SuccessorNode->LeftChild = DeleteNode->LeftChild;
	SuccessorNode->RightChild = DeleteNode->RightChild;
	
	// sort linked heap
	int (*compare) (void*, void*) = heap->Comparator;
	struct HeapNodeType* ChildNode = NULL;
	for (ChildNode = NULL; (ChildNode = GetWinningNode (SuccessorNode->LeftChild, SuccessorNode->RightChild, compare)) && compare (SuccessorNode->Data, ChildNode->Data) > 0; PredecessorNode = ChildNode, Swapping (SuccessorNode, ChildNode)) {
		
		if (PredecessorNode->LeftChild == SuccessorNode) PredecessorNode->LeftChild = ChildNode;
		else PredecessorNode->RightChild = ChildNode;
	}
	
	void* data = DeleteNode->Data;
	free ((struct HeapNodeType*) DeleteNode);
	heap->Count--;
	return data;
}

void DeleteNode_LinkedHeap (struct HeapNodeType* ParentNode, bool IsDynamic) {
	
	if (ParentNode == NULL) return;
	
	DeleteNode_LinkedHeap (ParentNode->LeftChild, IsDynamic);
	DeleteNode_LinkedHeap (ParentNode->RightChild, IsDynamic);
	if (IsDynamic) free (ParentNode->Data);
	free ((struct HeapNodeType*) ParentNode);
	return;
}

void Delete_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL) return;
	if (heap->Head != NULL) DeleteNode_LinkedHeap (heap->Head, heap->IsDynamic);
	free ((struct LinkedHeapType*) heap);
	return;
}

void PreorderTraversal_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! The linked heap is null. PreorderTraversal_LinkedHeap()\n");
		return;
	}
	if (IsEmpty_LinkedHeap (heap)) {
		
		printf ("Error! The linked heap is empty. PreorderTraversal_LinkedHeap()\n");
		return;
	}
	
	struct LinkedStackType* stack = Create_LinkedStack (false);
	if (stack == NULL) return;
	
	Push_LinkedStack (stack, heap->Head->RightChild);
	while (!IsEmpty_LinkedStack (stack)) {
		
		struct HeapNodeType* ParentNode = (struct HeapNodeType*) Pop_LinkedStack (stack);
		if (ParentNode == NULL) continue;
		
		if (heap->PreorderTraversal_EventHandler != NULL) heap->PreorderTraversal_EventHandler (heap, stack, ParentNode);
		if (ParentNode->RightChild != NULL) Push_LinkedStack (stack, ParentNode->RightChild);
		if (ParentNode->LeftChild != NULL) Push_LinkedStack (stack, ParentNode->LeftChild);
	}
	
	Delete_LinkedStack (stack);
	return;
}

void InorderTraversal_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! The linked heap is null. InorderTraversal_LinkedHeap()\n");
		return;
	}
	if (IsEmpty_LinkedHeap (heap)) {
		
		printf ("Error! The linked heap is empty. InorderTraversal_LinkedHeap()\n");
		return;
	}
	
	struct LinkedStackType* stack = Create_LinkedStack (false);
	if (stack == NULL) return;
	
	struct HeapNodeType* ParentNode = heap->Head->RightChild; // root node
	for (ParentNode = heap->Head->RightChild; true; ParentNode = ParentNode->RightChild) {
		while (ParentNode != NULL) {
			
			Push_LinkedStack (stack, ParentNode);
			ParentNode = ParentNode->LeftChild;
		}
		
		if (IsEmpty_LinkedStack (stack)) break;
		
		ParentNode = (struct HeapNodeType*) Pop_LinkedStack (stack);
		if (stack == NULL) break;
		
		if (heap->InorderTraversal_EventHandler != NULL) heap->InorderTraversal_EventHandler (heap, stack, ParentNode);
	}
	
	Delete_LinkedStack (stack);
	return;
}

void PostorderTraversalNode_LinkedHeap (struct LinkedHeapType* heap, struct HeapNodeType* ParentNode) {
	
	if (ParentNode == NULL) return;
	
	PostorderTraversalNode_LinkedHeap (heap, ParentNode->LeftChild);
	PostorderTraversalNode_LinkedHeap (heap, ParentNode->RightChild);
	if (heap->PostorderTraversal_EventHandler != NULL) heap->PostorderTraversal_EventHandler (heap, ParentNode);
	return;
}

void PostorderTraversal_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! The linked heap is null. PostorderTraversal_LinkedHeap()\n");
		return;
	}
	if (IsEmpty_LinkedHeap (heap)) {
		
		printf ("Error! The linked heap is empty. PostorderTraversal_LinkedHeap()\n");
		return;
	}
	
	PostorderTraversalNode_LinkedHeap (heap, heap->Head->RightChild);
	return;
}

void LevelorderTraversal_LinkedHeap (struct LinkedHeapType* heap) {
	
	if (heap == NULL || heap->Head == NULL) {
		
		printf ("Error! the linked heap is null. LevelorderTraversal_LinkedHeap()\n");
		return;
	}
	if (IsEmpty_LinkedHeap (heap)) {
		
		printf ("Error! the linked heap is empty. LevelorderTraversal_LinkedHeap()\n");
		return;
	}
	
	struct LinkedQueueType* queue = Create_LinkedQueue (false);
	if (queue == NULL) return;
	
	Enqueue_LinkedQueue (queue, heap->Head->RightChild);
	while (!IsEmpty_LinkedQueue (queue)) {
		
		struct HeapNodeType* ParentNode = (struct HeapNodeType*) Dequeue_LinkedQueue (queue);
		if (ParentNode == NULL) continue;
		
		if (heap->LevelorderTraversal_EventHandler != NULL) heap->LevelorderTraversal_EventHandler (heap, queue, ParentNode);
		if (ParentNode->LeftChild != NULL) Enqueue_LinkedQueue (queue, ParentNode->LeftChild);
		if (ParentNode->RightChild != NULL) Enqueue_LinkedQueue (queue, ParentNode->RightChild);
	}
	
	Delete_LinkedQueue (queue);
	return;
}

bool IsEmpty_LinkedHeap (struct LinkedHeapType* heap) {
	
	return heap->Count == 0;
}

#pragma endregion

#pragma region Linked queue

struct LinkedQueueType* Create_LinkedQueue (bool IsDynamic) {
	
	struct LinkedQueueType* NewQueue = (struct LinkedQueueType*) malloc (1 * sizeof (struct LinkedQueueType));
	if (NewQueue == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Create_LinkedQueue()\n");
		return NULL;
	}
	MemorySet ((struct LinkedQueueType*) NewQueue, 0, 1 * sizeof (struct LinkedQueueType));
	NewQueue->IsDynamic = IsDynamic;
	
	NewQueue->Head = (struct QueueNodeType*) malloc (1 * sizeof (struct QueueNodeType));
	if (NewQueue->Head == NULL) {
		
		free ((struct LinkedQueueType*) NewQueue);
		printf ("Error! The dynamic memory allocation failed. Create_LinkedQueue()\n");
		return NULL;
	}
	MemorySet ((struct QueueNodeType*) NewQueue->Head, 0, 1 * sizeof (struct QueueNodeType));
	
	return NewQueue;
}

bool Enqueue_LinkedQueue (struct LinkedQueueType* queue, void* data) {
	
	if (queue == NULL || queue->Head == NULL) {
		
		printf ("Error! The linked queue is null. Enqueue_LinkedQueue()\n");
		return false;
	}
	
	struct QueueNodeType* HeadNode = queue->Head;
	struct QueueNodeType* NewNode = (struct QueueNodeType*) malloc (1 * sizeof (struct QueueNodeType));
	if (NewNode == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Enqueue_LinkedQueue()\n");
		return false;
	}
	MemorySet ((struct QueueNodeType*) NewNode, 0, 1 * sizeof (struct QueueNodeType));
	NewNode->Data = data;
	
	if (queue->Count++ == 0) {
		
		NewNode->Next = HeadNode->Next = NewNode;
		return true;
	}
	
	NewNode->Next = HeadNode->Next->Next;
	HeadNode->Next->Next = HeadNode->Next = NewNode;
	return true;
}

void* Dequeue_LinkedQueue (struct LinkedQueueType* queue) {
	
	if (queue == NULL || queue->Head == NULL) {
		
		printf ("Error! The linked queue is null. Dequeue_LinkedQueue()\n");
		return NULL;
	}
	if (IsEmpty_LinkedQueue (queue)) {
		
		printf ("Error! The linked queue is empty. Dequeue_LinkedQueue()\n");
		return NULL;
	}
	
	struct QueueNodeType* PreviousNode = queue->Head->Next;
	struct QueueNodeType* DeleteNode = PreviousNode->Next;
	PreviousNode->Next = DeleteNode->Next;
	void* element = DeleteNode->Data;
	
	free ((struct QueueNodeType*) DeleteNode);
	queue->Count--;
	return element;
}

void* Peek_LinkedQueue (struct LinkedQueueType* queue) {
	
	if (queue == NULL || queue->Head == NULL) return NULL;
	if (IsEmpty_LinkedQueue (queue)) return NULL;
	
	return queue->Head->Next->Next->Data;
}

void Delete_LinkedQueue (struct LinkedQueueType* queue) {
	
	if (queue == NULL) return;
	if (queue->Head != NULL) {
		
		struct QueueNodeType* HeadNode = queue->Head;
		int index = 0, count = queue->Count;
		for (index = 0; index < count; index++) {
			
			struct QueueNodeType* DeleteNode = HeadNode->Next;
			HeadNode->Next = DeleteNode->Next;
			if (queue->IsDynamic) free (DeleteNode->Data);
			free ((struct QueueNodeType*) DeleteNode);
		}
		free ((struct QueueNodeType*) HeadNode);
	}
	free ((struct LinkedQueueType*) queue);
	return;
}

bool IsEmpty_LinkedQueue (struct LinkedQueueType* queue) {
	
	return queue->Count == 0;
}

#pragma endregion

#pragma region Linked stack

struct LinkedStackType* Create_LinkedStack (bool IsDynamic) {
	
	struct LinkedStackType* NewStack = (struct LinkedStackType*) malloc (1 * sizeof (struct LinkedStackType));
	if (NewStack == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Create_LinkedStack()\n");
		return NULL;
	}
	MemorySet ((struct LinkedStackType*) NewStack, 0, 1 * sizeof (struct LinkedStackType));
	NewStack->IsDynamic = IsDynamic;
	
	NewStack->Head = (struct StackNodeType*) malloc (1 * sizeof (struct StackNodeType));
	if (NewStack->Head == NULL) {
		
		free ((struct LinkedStackType*) NewStack);
		printf ("Error! The dynamic memory allocation failed. Create_LinkedStack()\n");
		return NULL;
	}
	MemorySet ((struct StackNodeType*) NewStack->Head, 0, 1 * sizeof (struct StackNodeType));
	
	return NewStack;
}

bool Push_LinkedStack (struct LinkedStackType* stack, void* data) {
	
	if (stack == NULL || stack->Head == NULL) {
		
		printf ("Error! The linked stack is null. Push_LinkedStack()\n");
		return false;
	}
	
	struct StackNodeType* HeadNode = stack->Head;
	struct StackNodeType* NewNode = (struct StackNodeType*) malloc (1 * sizeof (struct StackNodeType));
	if (NewNode == NULL) {
		
		printf ("Error! The dynamic memory allocation failed. Push_LinkedStack()\n");
		return false;
	}
	MemorySet ((struct StackNodeType*) NewNode, 0, 1 * sizeof (struct StackNodeType));
	NewNode->Data = data;
	
	NewNode->Next = HeadNode->Next;
	HeadNode->Next = NewNode;
	stack->Count++;
	return true;
}

bool IsEmpty_LinkedStack (struct LinkedStackType* stack) {
	
	return stack->Count == 0;
}

void* Pop_LinkedStack (struct LinkedStackType* stack) {
	
	if (stack == NULL || stack->Head == NULL) {
		
		printf ("Error! The linked stack is null. Pop_LinkedStack()\n");
		return NULL;
	}
	if (IsEmpty_LinkedStack (stack)) {
		
		printf ("Error! The linked stack is empty. Pop_LinkedStack()\n");
		return NULL;
	}
	
	struct StackNodeType* HeadNode = stack->Head;
	struct StackNodeType* DeleteNode = HeadNode->Next;
	HeadNode->Next = DeleteNode->Next;
	
	void* data = DeleteNode->Data;
	free ((struct StackNodeType*) DeleteNode);
	stack->Count--;
	return data;
}

void* Peek_LinkedStack (struct LinkedStackType* stack) {
	
	if (stack == NULL || stack->Head == NULL || stack->Head->Next == NULL) return NULL;
	return stack->Head->Next->Data;
}

void Delete_LinkedStack (struct LinkedStackType* stack) {
	
	if (stack == NULL) return;
	if (stack->Head != NULL) {
		
		struct StackNodeType* HeadNode = stack->Head;
		int index = 0, count = stack->Count;
		for (index = 0; index < count; index++) {
			
			struct StackNodeType* DeleteNode = HeadNode->Next;
			HeadNode->Next = DeleteNode->Next;
			if (stack->IsDynamic) free (DeleteNode->Data);
			free ((struct StackNodeType*) DeleteNode);
		}
		free ((struct StackNodeType*) HeadNode);
	}
	free ((struct LinkedStackType*) stack);
	return;
}

#pragma endregion

#pragma region Standard library

void* MemorySet (void* source, int value, size_t type) {
	
	if (source == NULL) return NULL;
	
	char* memory = (char*) source;
	size_t byte = 0LLU;
	for (byte = 0LLU; byte < type; byte++) {
		
		memory[byte] = value;
	}
	return memory;
}

/*
case 1.
 >> argument1 = 9, argument2 = 17
temporary = argument1	->	temporary = 9
argument1 = argument2	->	argument1 = 17
argument2 = temporary	->	argument2 = 9
 >> argument1 = 17, argument2 = 9
*/
void Swap (void* argument1, void* argument2, size_t type) {
	
	unsigned char* element1 = (unsigned char*) argument1, *element2 = (unsigned char*) argument2;
	size_t byte = 0LLU;
	for (byte = 0LLU; byte < type; byte++) {
		
		unsigned char temporary = element1[byte];
		element1[byte] = element2[byte];
		element2[byte] = temporary;
	}
	return;
}

#pragma endregion
