/**
 * @file
 * @brief A basic unbalanced binary search tree implementation in C.
 * @details The implementation provides:
 * - Insertion
 * - Deletion
 * - Search by key value
 * - Listing of node keys in order of value (from left to right)
 * - Height calculation
 */
#include <stdio.h>
#include <stdlib.h>

/** Node, the basic data structure in the tree */
typedef struct node {
    struct node *left;   /**< left child */
    struct node *right;  /**< right child */
    int data;            /**< data of the node */
} node;

/**
 * @brief Creates a new node with the given data.
 * @param data Data to store in a new node.
 * @returns Pointer to the newly created node.
 */
node *newNode(int data) {
    node *tmp = (node *)malloc(sizeof(node));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

/**
 * @brief Inserts a node into the Binary Search Tree.
 * @param root Pointer to parent node.
 * @param data Value to store in the new node.
 * @returns Updated root pointer.
 */
node *insert(node *root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data > root->data)
        root->right = insert(root->right, data);
    else if (data < root->data)
        root->left = insert(root->left, data);
    // Ignore duplicates
    return root;
}

/**
 * @brief Finds the node with the maximum value in a subtree.
 * @param root Pointer to the subtree root.
 * @returns Pointer to node with maximum value.
 */
node *getMax(node *root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

/**
 * @brief Deletes a node with a given value from the BST.
 * @param root Root node pointer.
 * @param data Value to delete.
 * @returns Updated root pointer.
 */
node *deleteNode(node *root, int data) {
    if (root == NULL)
        return NULL;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node found
        if (root->left == NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        } else {
            node *temp = getMax(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data);
        }
    }
    return root;
}

/**
 * @brief Searches for a value in the BST.
 * @param root Root node pointer.
 * @param data Value to find.
 * @returns 1 if found, 0 if not.
 */
int find(node *root, int data) {
    if (root == NULL)
        return 0;
    if (data == root->data)
        return 1;
    else if (data < root->data)
        return find(root->left, data);
    else
        return find(root->right, data);
}

/**
 * @brief Calculates the height of the BST.
 * @param root Root node pointer.
 * @returns Height (number of levels).
 */
int height(node *root) {
    if (root == NULL)
        return 0;
    int left_h = height(root->left);
    int right_h = height(root->right);
    return (left_h > right_h ? left_h : right_h) + 1;
}

/**
 * @brief Frees all nodes in the tree.
 * @param root Root node pointer.
 */
void purge(node *root) {
    if (root == NULL)
        return;
    purge(root->left);
    purge(root->right);
    free(root);
}

/**
 * @brief Prints tree nodes in ascending order.
 * @param root Root node pointer.
 */
void inOrder(node *root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

/**
 * @brief Demonstrates Binary Search Tree operations.
 */
int main(void) {
    node *root = NULL;
    int opt = -1, data;

    while (opt != 0) {
        printf("\n\n=== Binary Search Tree Menu ===\n");
        printf("[1] Insert Node\n");
        printf("[2] Delete Node\n");
        printf("[3] Find Node\n");
        printf("[4] Tree Height\n");
        printf("[5] Print In-Order\n");
        printf("[0] Exit\n");
        printf("Select an option: ");
        if (scanf("%d", &opt) != 1) {
            fprintf(stderr, "Invalid input! Exiting...\n");
            break;
        }

        switch (opt) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &data);
            root = deleteNode(root, data);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &data);
            printf(find(root, data) ? "Found!\n" : "Not found!\n");
            break;
        case 4:
            printf("Tree height: %d\n", height(root));
            break;
        case 5:
            printf("In-order traversal: ");
            inOrder(root);
            printf("\n");
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option! Try again.\n");
            break;
        }
    }

    purge(root);
    return 0;
}
