#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

typedef struct
{
    node *Head;
    node *Tail;
    int Count;
} doublyCircularList;

#define head list->Head
#define tail list->Tail
#define count list->Count

doublyCircularList *initList()
{
    doublyCircularList *list = (doublyCircularList *)malloc(sizeof(doublyCircularList));
    if (list == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    head = (node *)malloc(sizeof(node));
    if (head == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    head->next = head->prev = NULL;
    tail = NULL;
    count = 0;
    return list;
}

bool isEmpty(doublyCircularList *list)
{
    return !(head && tail && count);
}

void insertAtHead(doublyCircularList *list, int data)
{
    node *newNode = createNode(data);
    if (isEmpty(list))
        head->next = tail = newNode;
    else
    {
        newNode->next = head->next;
        newNode->prev = tail;
        tail->next = newNode;
        head->next = newNode;
    }
    count++;
}

void insertAtRear(doublyCircularList *list, int data)
{
    if (isEmpty(list))
        return insertAtHead(list, data);
    node *newNode = createNode(data);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    tail->next = head->next;
    head->next->prev = tail;
    count++;
}

void insertAtPosition(doublyCircularList *list, int data, int position)
{
    if (position < 0 || position >= count)
    {
        printf("Invalid positon to insert.\n");
        return;
    }
    if (position == 0)
        return insertAtHead(list, data);
    else if (position == count - 1)
        return insertAtRear(list, data);
    else
    {
        node *temp = head->next;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        node *newNode = createNode(data);
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        count++;
    }
}

void display(doublyCircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, no elements to display.\n");
        return;
    }
    node *temp = head->next;
    printf("Elements of the list are, \n");
    do
    {
        printf("%d<=>", temp->data);
        temp = temp->next;
    } while (temp != head->next);
    printf("%d\n", temp->data);
}

int deleteAtHead(doublyCircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, no elements to delete.\n");
        return -1;
    }
    node *toDelete = head->next;
    int data = toDelete->data;

    if (count == 1)
        head->next = tail = NULL;
    else
    {
        head->next = toDelete->next;
        tail->next = head->next;
        head->next->prev = tail;
    }
    free(toDelete);
    count--;
    return data;
}

int deleteAtRear(doublyCircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, no elements to delete.\n");
        return -1;
    }
    if (count == 1)
        return deleteAtHead(list);

    node *toDelete = tail;
    int data = toDelete->data;

    tail = tail->prev;
    tail->next = head->next;
    head->prev = tail;

    free(toDelete);
    count--;
    return data;
}

int deleteAtPosition(doublyCircularList *list, int position)
{
    if (isEmpty(list))
    {
        printf("List is empty, no elements to delete.\n");
        return -1;
    }
    if (position < 0 || position >= count)
    {
        printf("Invalid psoition to delete.\n");
        return -1;
    }

    if (position == 0)
        return deleteAtHead(list);
    else if (position == count - 1)
        return deleteAtRear(list);
    else{
        node *temp = head->next;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        node *toDelete = temp->next;
        int data = toDelete->data;

        temp->next = toDelete->next;
        toDelete->next->prev = temp;

        free(toDelete);
        count--;
        return data;
    }
}

void destructList(doublyCircularList *list)
{
    if (isEmpty(list))
    {
        free(head);
        free(list);
    }
    node *temp = head->next;
    do
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    } while (temp != head->next);
    free(head);
    free(list);
}

int main()
{
    doublyCircularList *myList = initList();
    doublyCircularList *copy;
    int choice, data, position, key;

    do
    {
        printf("\n\n");
        printf("Menu.\n");
        printf("1. Insert at head(front).\n");
        printf("2. Insert at rear\n");
        printf("3. Insert at specific position.\n");
        printf("4. Delete from head(front).\n");
        printf("5. Delete from rear(tail).\n");
        printf("6. Delete from specific position.\n");
        printf("7. Delete by key.\n");
        printf("8. Search by key.\n");
        printf("9. Create a ordered list.\n");
        printf("10. Reverse the linked list.\n");
        printf("11. Create a copy of the list.\n");
        printf("12.Display the list.\n");
        printf("13.Exit.\n");

        printf("Enter the choice of operation : ");
        scanf("%d", &choice);
        printf("\n\n");

        // added menu driven feature intend as you need.

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at front: ");
            scanf("%d", &data);
            insertAtHead(myList, data);
            display(myList);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(myList, data);
            display(myList);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(myList, data, position);
            display(myList);
            break;
        case 4:
            deleteAtHead(myList);
            display(myList);
            break;
        case 5:
            deleteAtRear(myList);
            display(myList);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(myList, position);
            display(myList);
            break;
        // case 7:
        //     printf("Enter key to delete: ");
        //     scanf("%d", &key);
        //     deleteByKey(myList, key);
        //     display(myList);
        //     break;
        // case 8:
        //     printf("Enter key to search: ");
        //     scanf("%d", &key);
        //     searchByKey(myList, key);
        //     break;
        // case 9:
        //     printf("Enter data to insert in the ordered list: ");
        //     scanf("%d", &data);
        //     createOrderedList(myList, data);
        //     display(myList);
        //     break;
        // case 10:
        //     reverse(myList);
        //     printf("Reversed list is,\n");
        //     display(myList);
        //     break;
        // case 11:
        //     copy = copyList(myList);
        //     display(myList);
        //     printf("Copied list is,\n");
        //     display(copy);
        //     destructList(copy);
        //     break;
        case 12:
            display(myList);
            break;
        case 13:
            printf("Exiting the program....\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    destructList(myList);
    return 0;
}
