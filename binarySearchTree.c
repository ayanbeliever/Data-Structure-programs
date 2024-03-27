#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* llink;
    struct Node* rlink;
};
typedef struct Node node;

int count = 0;

node* createNode(int value) {
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL) {
        printf("Memory alllocation error!\n");
        exit(0);
    }
    newNode->data = value;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    return newNode;
}

node *insertion(node* root, int value) {
    if(root == NULL) {
        return createNode(value);
    }
    if(root->data > value) {
        root->llink = insertion(root->llink, value);
    }
    else {
        root->rlink = insertion(root->rlink, value);
    }
    return root;
}

void inorder(node* root) {
    if(root == NULL) {
        return;
    }
    inorder(root->llink);
    printf("%d ",root->data);
    inorder(root->rlink);
}

void preorder(node* root) {
    if(root == NULL) {
        return;
    }
    printf("%d ",root->data);
    preorder(root->llink);
    preorder(root->rlink);
}

void postorder(node* root) {
    if(root == NULL) {
        return;
    }
    postorder(root->llink);
    postorder(root->rlink);
    printf("%d ",root->data);
}

void freeBst(node *root) {
    if(root == NULL)
        return;

    freeBst(root->llink);
    free(root);
    freeBst(root->rlink);
}

node* minimum(node* root) {
    if(root == NULL) 
        return NULL;

    node* temp = root;
    while(temp->llink != NULL) {
        temp = temp->llink;
    }
    return temp;
}

void maximum(node* root) {
    //Also displays the details of max element such as parent
    if(root == NULL) {
        return;
    }
    node* temp = root;
    node* parent = NULL;
    while(temp->rlink != NULL) {
        parent = temp;
        temp = temp->rlink;
    }
    printf("Maximum element is %d\n",temp->data);
    if(parent != NULL) {
        printf("Parent : %d\n",parent->data);
    }
    else {
        printf("Its parent doesn't exist\n");
    }
    
}

void countNodes(node* root) {
    if(root == NULL) {
        return;
    }

    countNodes(root->llink);
    count++;
    countNodes(root->rlink);
}

void searchByKey(node* root , int key) {
    //Also displays details of node such as parent
    if(root == NULL) {
        return;
    }

    node* temp = root;
    node *parent = NULL;
    while(temp != NULL) {
        if(temp->data == key) {
            break;
        }
        parent = temp;
        if(temp->data > key) {
            temp = temp->llink;
        }
        else {
            temp = temp->rlink;
        }
    }
    if(temp == NULL) {
        printf("Key %d was not found\n");
    }
    else {
        printf("Key %d was found\n",key);
        if(parent != NULL) {
            printf("Parent : %d\n",parent->data);
        }
        else {
            printf("It doesn't have parent\n");
        }
    }
}

void countLeafs(node* root) {
    if(root == NULL) {
        return;
    }
    countLeafs(root->llink);
    if(root->llink ==  NULL && root->rlink == NULL) {
        count++;
    }
    countLeafs(root->rlink);
}

int max(int a , int b) {
    return (a>b) ? a : b;
}

int heightOfTree(node* root) {
    if(root == NULL)
        return 0;

    int h = max(heightOfTree(root->llink) , heightOfTree(root->rlink));
    return h+1;
}

node *findInorderSuccessor(node *root) {
    node *cur = root;
    while(cur->llink != NULL) {
        cur = cur->llink;
    }
    return cur;
}

node* deleteNode(node* root , int key) {
    if(root == NULL) {
        return NULL;
    }
    else {
        if(root->data < key) {
            root->rlink=deleteNode(root->rlink, key);
        }
        else if(root->data > key) {
            root->llink=deleteNode(root->llink, key);
        }
        else {
            if(root->llink == NULL && root->rlink == NULL) {
                free(root);
                return NULL;
            }
            else if(root->llink == NULL || root->rlink == NULL) {
                node *cur = root->llink != NULL ? root->llink : root->rlink;
                free(root);
                return cur;
            }
            else {
                node *inorderSuccessor = findInorderSuccessor(root->rlink);
                root->data = inorderSuccessor->data;
                root->rlink = deleteNode(root->rlink , inorderSuccessor->data);
            }
        }
        return root;
    }
}

int main() {
    node* root = NULL;
    node* min = NULL;
    node* max = NULL;
    int choice , value , key;

    node* found;

    printf("1.Insert\n2.Traversal\n3.Minimum element\n4.Maximum element with details\n5.Leafs count\n6.Seach by key\n7.Counting nodes\n8.Height of tree\n9.Delete a node\n10.Exit\n");

    do
    {
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice) {
            case 1 : printf("Enter the value to insert : ");
                     scanf("%d",&value);
                     root = insertion(root, value);
                    break;
            case 2 : printf("Inorder Traversal : ");
                     inorder(root);
                     printf("\n");
                     printf("Preorder Traversal : ");
                     preorder(root);
                     printf("\n");
                     printf("Postorder Traversal : ");
                     postorder(root);
                     printf("\n");
                    break;
            case 3 : min = minimum(root);
                     printf("Minimum element is : %d\n",min->data);
                    break;
            case 4 : maximum(root);
                    break;
            case 5 : count = 0;
                     countLeafs(root);
                     printf("Total leaf nodes are : %d\n",count);
                    break;
            case 6 : printf("Enter the key : ");
                     scanf("%d",&key);
                     searchByKey(root , key); 
                    break;
            case 7 : count = 0;
                     countNodes(root);
                     printf("Total number of nodes : %d\n",count);
                    break;
            case 8 : printf("Height of tree : %d\n", heightOfTree(root));
                    break;
            case 9 : printf("Enter the key to delete : ");
                     scanf("%d",&key); 
                     root = deleteNode(root , key);
                    break;    
            case 10 : printf("Exiting...\n");
                     freeBst(root);
                    break;
            default : printf("Invalid choice!\n");
        }
    } while (choice != 10);
    
    return 0;
}
