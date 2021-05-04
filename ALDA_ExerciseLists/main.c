#include "list.h"
#include <stdlib.h>

//this is our Light, it has a color and a pointer towards the next Light
struct Node {
	char color;
	struct Node* next;
};

struct Node* createNode(char color) {
	struct Node* newNode = malloc(sizeof(struct Node));
	newNode->color = color;
	newNode->next = NULL;

	return newNode;
}

//pointer as parameter, that point to the head of the list, the start
void printList(struct Node *head) {
	struct Node *tem = head;
	//while temporary Node != Null --> we aren't at the end yet
	while (tem != NULL) {
		//prints the color that tem is pointing to
		if (tem->next != NULL) {
			printf("%c - ", tem->color);
		}
		else {
			printf("%c", tem->color);
		}
		//tem now points at the next node, once we reach the end, its NULL
		tem = tem->next;
	}
}

void appendNodeAtStart(struct Node *node, struct Node **head) {
	//node points to the head --> it's infront of the head now
	node->next = *head;
	//since it's infront --> needs to be new head
	*head = node;
}

//to append at end --> 1)search for the last node(tail) with help of *head, 2) set the tail->next to the node.
void appendNodeAtEnd(struct Node *node, struct Node **head) {
	struct Node* tail = *head;
	//if tail = head == NULL --> means this is the first node that gets added to the list
	if (tail != NULL) {
	//looking through list until node points to NULL --> it's the tail
		while (tail != NULL) {
			if (tail->next == NULL) {
				break;
			}
			else {
				tail = tail->next;
			}
		}
	//now tail is our last node --> points at node, makes it the last node(tail)
	tail->next = node;
	}
	else {
		appendNodeAtStart(node, &*head);
	}
}

void insertNodeAt(struct Node *node, int index, struct Node **head) {
	struct Node* tmp = *head;
	//if index == 0 -> same as append at Start
	if (index == 0) {
		appendNodeAtStart(node, &*head);
	}
	//else tmp = the node at index-1
	else {
		for (int i = 0; i < index - 1; i++)
		{
			tmp = tmp->next;
		}
		//node points to the item at index --> it takes it's place
		node->next = tmp->next;
		//index-1's node points to node --> node is now inserted inbetween 
		tmp->next = node;
	}
}

void deleteNodeAt(int index, struct Node **head) {
	struct Node* tmp = *head;
	struct Node* tmp2 = *head;
	
	//looking for the node with index-1
	for (int i = 0; i < index-1; i++)
	{
		//saving the node infront of the one to delete in tmp2
		if (i == index - 2) {
			tmp2 = tmp;
		}
		tmp = tmp->next;
	}
	//tmp2 points to the node that the deleted node pointed to 
	tmp2->next = tmp->next;
	//deleting the node from memory
	free(tmp);
}

void reverseList(struct Node **head) {
	struct Node* prev = NULL;
	struct Node* node = *head;
	struct Node* next = NULL;

	while (node != NULL) {
		//next points to the next element
		next = node->next;
		//node points to NULL first iteration, second --> 
		node->next = prev;
		//prev is now the current node
		prev = node;
		//current node is now next node
		node = next;
	}
	//last element is now the head
	*head = prev;
}

int main() {
	struct Node *tmp;
	struct Node* head = NULL;

	char userInput = ' ';
	int index;

	while (userInput != 'x') {
		printf("m: ");
		scanf(" %c", &userInput);

		switch (userInput) {
		//Insert at the start
		case 'a':
			//if 0 gets entered -> end
			while (userInput != '0') {
				printf("l: ");
				scanf(" %c", &userInput);
				//0 should not be added to the list
				if (userInput != '0') {
					appendNodeAtStart(createNode(userInput), &head);
				}
			}
			break;

		//Insert at the end
		case 'e':
			while (userInput != '0') {
				printf("l: ");
				scanf(" %c", &userInput);
				//0 should not be added to the list
				if (userInput != '0') {
					appendNodeAtEnd(createNode(userInput), &head);
				}
			}
			break;

		//Insert at X
		case 'i':
			printf("p: ");
			scanf(" %i", &index);
			printf("m: ");
			scanf(" %c", &userInput);
			insertNodeAt(createNode(userInput), index, &head);
			break;

		//delete node at X
		case 'l':
			printf("p: ");
			scanf(" %i", &index);
			deleteNodeAt(index, &head);
			break;
		//reverse the list
		case 'u':
			reverseList(&head);
			break;
		}
		printList(head);
		printf("\n");
	}
	return 0;
}