
#include <stdio.h>
#include <stdlib.h>

/* 트리 노드 구조체 정의 */
typedef struct node {
	int key;
	struct node *left; // 왼쪽 노드를 가리키는 자기 참조 구조체 포인터
	struct node *right; // 오른쪽 노드를 가리키는 자기 참조 구조체 포인터
} Node;

int initializeBST(Node** h);

/* 함수 원형 정의 */
// 순회 함수
void inorderTraversal(Node* ptr);	  
void preorderTraversal(Node* ptr);    
void postorderTraversal(Node* ptr);	  
// 노드 삽입 삭제 함수
int insert(Node* head, int key);  
int deleteLeafNode(Node* head, int key);  
// 트리 탐색 함수
Node* searchRecursive(Node* ptr, int key);  
Node* searchIterative(Node* head, int key); 
// 메모리 초기화 함수
int freeBST(Node* head); 


int main()
{
    printf("------ [2019036068] [허원일] ------\n");
	char command;
	int key;
	Node* head = NULL; // 헤드 노드를 가리키는 노드 구조체 포인터 head
	Node* ptr = NULL; // 임시 노드 구조체 포인터 ptr

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
            /* BST를 초기화 */
			initializeBST(&head);
			break;

		case 'q': case 'Q':
            /* BST 메모리 해제 */
			freeBST(head);
			break;

		case 'n': case 'N':
            /* key에 해당하는 노드를 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;

		case 'd': case 'D':
            /* 리프노드 삭제 */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;

		case 'f': case 'F':
            /* 특정 key의 노드를 반복문으로 검색 */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL) // 존재할 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else // 존재하지 않는 경우
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 's': case 'S':
            /* 특정 key의 노드를 재귀문으로 검색 */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL) // 존재할 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else // 존재하지 않는 경우
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
            // BST를 중위순회
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
            // BST를 전위순회
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
            // BST를 후위순회
			postorderTraversal(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* BST를 초기화하는 함수 */
int initializeBST(Node** h) {

	/* head가 NULL이 아닌 경우 즉, 트리가 비어있지 않으면 freeBST로 트리에 할당된 메모리 해제 */
	if(*h != NULL)
		freeBST(*h);

	/* head에 메모리 할당 후 각 연결 노드 및 key 초기화 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	return 1; 
}

/* BST를 중위순회하는 함수 */
void inorderTraversal(Node* ptr)
{
    /* 노드가 존재하면 수행 */
	if(ptr) {
		inorderTraversal(ptr->left); // 노드의 왼쪽 노드를 재귀적으로 중위순회
		printf(" [%d] ", ptr->key); // 해당 노드의 key 출력
		inorderTraversal(ptr->right); // 노드의 오른쪽 노드를 재귀적으로 중위순회
	}
}

/* BST를 전위순회하는 함수 */
void preorderTraversal(Node* ptr)
{   
    /* 노드가 존재하면 수행 */
	if(ptr) {
		printf(" [%d] ", ptr->key); // 해당 노드의 key 출력
		preorderTraversal(ptr->left); // 노드의 왼쪽 노드를 재귀적으로 중위순회
		preorderTraversal(ptr->right); // 노드의 오른쪽 노드를 재귀적으로 중위순회
	}
}

/* BST를 후위순회하는 함수 */
void postorderTraversal(Node* ptr)
{   
    /* 노드가 존재하면 수행 */
	if(ptr) {
		postorderTraversal(ptr->left); // 노드의 왼쪽 노드를 재귀적으로 중위순회
		postorderTraversal(ptr->right); // 노드의 오른쪽 노드를 재귀적으로 중위순회
		printf(" [%d] ", ptr->key); // 해당 노드의 key 출력
	}
}

/* 특정 key값의 노드를 BST에 삽입하는 함수 */
int insert(Node* head, int key)
{   
    /* 새로운 노드 생성 */
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    /* head의 왼쪽이 NULL인 경우 */
	if (head->left == NULL) {
		head->left = newNode; // head의 왼쪽에 새로운 노드 삽입

		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr이 head의 왼쪽노드를 가리키게 함

	Node* parentNode = NULL; // 노드 구조체 포인터 parentNode

    // 
	while(ptr != NULL) {

		/* 해당 key의 노드가 존재할 경우 함수 종료 */
		if(ptr->key == key) return 1;

		parentNode = ptr; // parentNode는 ptr을 따라감

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
        /* 현재 노드의 key가 삽입될 노드의 key보다 작은 경우 */
		if(ptr->key < key)
			ptr = ptr->right; // ptr을 ptr의 오른쪽 자식 노드를 가리키게 함
        /* 현재 노드의 key가 삽입될 노드의 key보다 큰 경우 */
		else
			ptr = ptr->left; // ptr을 ptr의 왼쪽 자식 노드를 가리키게 함
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/* 리프노드를 삭제하는 함수 */
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/* 특정 key의 노드가 있는지 재귀문으로 탐색하는 함수 */
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}

/* 특정 key의 노드가 있는지 반복문으로 탐색하는 함수 */
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

/* 특정 노드 아래의 모든 자식노드의 메모리를 해제하는 함수 */
void freeNode(Node* ptr)
{
    /* 노드가 존재할 경우 */
	if(ptr) {
		freeNode(ptr->left); // 왼쪽 자식노드를 재귀적으로 호출하며 메모리 해제
		freeNode(ptr->right); // 오른쪽 자식노드를 재귀적으로 호출하며 메모리 해제
		free(ptr); // 해당 노드의 메모리 해제
	}
}

/* BST에 할당된 메모리를 해제하는 함수 */
int freeBST(Node* head)
{

    /* head의 왼쪽노드가 head인 경우 */
	if(head->left == head)
	{
        // head에 할당된 메모리 해제 후 함수 종료
		free(head); 

		return 1;
	}

	Node* p = head->left; // p가 head의 왼쪽 노드를 가리키게 함

	freeNode(p); // p에 할당된 메모리 해제

	free(head); // head에 할당된 메모리 해제

	return 1;
}





