#include <stdio.h>
#include <stdlib.h>
struct node
{
	int value;
	struct node *next;
};
typedef struct node NODE;
typedef NODE * LINK;

// 테스트용 소스파일입니다.

LINK creat_node(int value)
{
	LINK cur;
	cur = (LINK)malloc(sizeof(NODE));
	cur->value = value;
	cur->next = NULL;
	return cur;
}
LINK append(LINK head, LINK cur)
{
	LINK next_node = head;
	if (head == NULL)
	{
		head = cur;
		return head;
	}
	while (next_node->next != NULL)
		next_node = next_node->next;
	next_node->next = cur;
	return head;
}
int node_count(LINK first, LINK head)
{
	int count = 0;
	head = first;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return count;
}
void print_backword(LINK first, LINK head, int num)
{
	printf("Print Backword : ");
	for (int i = 0; i < num; i++) {
		head = first;
		for (int j = 0; j < num - i - 1; j++) {
			head = head->next;
		}
		printf("%d ", head->value);
	}
}
void print_middle(LINK first, LINK head, int num)
{
	int prtnum = num / 2;
	head = first;
	if (num % 2 == 0)
	{
		for (int i = 0; i < (prtnum-1); i++)
			head = head->next;
		printf("\nMiddle value   : %d , %d\n", head->value,head->next->value);
	}
	else
	{
		for (int i = 0; i < prtnum; i++)
			head = head->next;
		printf("\nMiddle value   : %d", head->value);
	}
}
void print_forword(LINK first, LINK head, int num)
{
	printf("\nPrint Forword  : ");
	head = first;
	for (int i = 0; i < num; i++)
	{
		printf("%d ", head->value);
		head = head->next;
	}
}
void del_odd_element(LINK first, LINK head, int num)
{
	first = first->next;
	head = first;
}

int main(void)
{
	int  user_num = 0, count = 0, num_node, odd = 0;
	LINK head = NULL;
	LINK cur;
	LINK first_node = NULL;
	printf("Enter the numbers :\n");
	while (scanf("%d", &user_num) != EOF)
	{
		cur = creat_node(user_num);
		if (count == 0)
			first_node = cur;
		head = append(head, cur);
		count++;
	}
	num_node = node_count(first_node, head);
	printf("Number of node : %d\n", num_node);
	print_backword(first_node, head, num_node);
	print_forword(first_node, head, num_node);
	first_node = first_node->next;
	head = first_node;
	if (num_node % 2 == 0)
		odd = num_node / 2 - 1;
	else
		odd = num_node / 2;
	for (int i = 0; i < odd; i++)
	{
		head->next = head->next->next;
		head = head->next;
	}
	num_node = node_count(first_node, head);
	print_forword(first_node, head, num_node);
	print_middle(first_node, head, num_node);
	puts("");
	free(cur);
	return 0;
}
