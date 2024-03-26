#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};
typedef struct Node node;

struct cDoublyList {
    node* head;
};
typedef struct cDoublyList cDl;

int count = 0;

node* createNode(int value) {
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL) {
        exit(0);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void freeList(cDl* list) {
    if(list->head == NULL || count==0) {
        return;
    }
    node* temp = list->head;
    node* firstNode = list->head;
    
    do {
        list->head = temp->next;
        free(temp);
        temp = list->head;
        printf("List freed\n");
    } while (temp != firstNode);
}

void displayList(cDl* list) {
    if(list->head == NULL || count==0) {
        return;
    }
    
    node* temp = list->head;
    
    do
    {
        printf("%d ",temp->data);
        temp = temp->next;

    } while (temp != list->head);
    printf("\n");
}

void insertAtStart(cDl* list, int value) {
    node* newNode = createNode(value);
    if(list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        list->head->prev->next = newNode;
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev = newNode;
        list->head = newNode;
    }
    count++;
    displayList(list);
}

void insertAtRear(cDl* list, int value) {
    node* newNode = createNode(value);
    if(list->head == NULL) {
        insertAtStart(list, value);
        return;    
    } else {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head->prev = newNode;
    }
    count++;
    displayList(list);
}

void insertByOrder(cDl *list, int value) {
    node *newNode = createNode(value);
    if(list->head == NULL || count == 0) {
        list->head = newNode;
        list->head->prev = newNode;
        list->head->next = newNode;
    }
    else if(value <= list->head->data) {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head->prev = newNode;
        list->head = newNode;
    }
    else {
        node *temp = list->head;
        while(temp->next != list->head && temp->next->data < value) {
            temp = temp->next;
        }
        node *nextNode = temp->next;
        newNode->next = nextNode;
        newNode->prev = temp;
        nextNode->prev = newNode;
        temp->next = newNode;
    }

    count++;
    displayList(list);
}

void searchByKey(cDl* list, int key) {
    if(count == 0) return;
    node* temp = list->head;
    int i = 1;
    do
    {
        if(temp->data == key) {
            printf("Key found at %d position\n",i);
            return;
        }
        temp = temp->next;
        i++;
    } while (temp != list->head);

    printf("Key not found\n");
    
}

void searchByPosition(cDl *list, int position) {
    if(position < 1 || position > count) {
        printf("Invalid Position\n");
        return;
    }

    node *temp = list->head;
    int i=1;
    while(i<position) {
        temp = temp->next;
        i++;
    }
    printf("Element at position %d is %d\n",position,temp->data);

}

void deleteAtPosition(cDl* list, int position) {
    if(position<1 || position>count) {
        printf("Invalid position\n");
        return;
    }

    node* temp = list->head;
    int i=1;
    while(i<position) {
        temp = temp->next;
        i++;
    }
    if(temp == list->head) {
        list->head = temp->next;
    }
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    free(temp);
    count--;
    displayList(list);
}

void deleteByKey(cDl *list, int key) {
    if(list->head == NULL || count == 0) {
        printf("List is empty\n");
        return;
    }

    node *temp = list->head;
    do
    {
        if(temp->data == key) {
            if(temp == list->head) {
                list->head = temp->next;
            }
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            free(temp);
            count--;
            displayList(list);
            return;
        }
        
        temp = temp->next;
    } while (temp != list->head);

    printf("Key not found\n");
}

void deleteByFront(cDl *list) {
    if(list->head == NULL || count == 0) {
        printf("List is Empty\n");
        return;
    }

    node* temp = list->head;
    if(temp->next == list->head) {
        list->head = NULL;
    } else {
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        list->head = temp->next;
    }

    free(temp);
    count--;
    displayList(list);
}

void deleteByRear(cDl *list) {
    if(list->head == NULL || count == 0) {
        printf("List is Empty\n");
        return;
    }

    node *temp = list->head->prev;
    if(temp == list->head) {
        list->head = NULL;
    }
    else {
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
    }
    free(temp);
    count--;
    displayList(list);
}

int main() {
    cDl* list = (cDl*)malloc(sizeof(cDl));
    list->head = NULL;

    int choice, value, position, key;

    printf("1.Insert at Start\n2.Insert at End\n3.Insert by order\n4.Search by key\n5.Search by position\n6.Delete at position\n7.Delete by key\n8.Delete by front\n9.Delete by Rear\n0.Exit\n");

    do
    {
        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1 : printf("Enter the value : ");
            scanf("%d",&value);
            insertAtStart(list, value);
            break;
        case 2 : printf("Enter the value : ");
            scanf("%d",&value);
            insertAtRear(list, value);
            break;
        case 3 : 
            printf("Enter the position : ");
            scanf("%d",&position);
            deleteAtPosition(list, position);
            break;
        case 4 : printf("Enter the key to search : ");
            scanf("%d",&key);
            searchByKey(list, key);
            break;
        case 5 : printf("Enter the element : ");
            scanf("%d",&value);
            insertByOrder(list, value);
            break;
        case 6 : 
            printf("Enter the key : ");
            scanf("%d",&key);
            deleteByKey(list, key);
            break;
        case 7 : 
            printf("Enter the position : ");
            scanf("%d",&position);
            searchByPosition(list, position);
            break;
        case 8 : 
            deleteByFront(list);
            break;
        case 9 : 
            deleteByRear(list);
            break;
        case 0 : printf("Exiting program...\n");
            freeList(list);
            break;
        default: printf("Invalid choice !\n");
            break;
        }
    } while (choice != 0);

    
    free(list);

    return 0;
}