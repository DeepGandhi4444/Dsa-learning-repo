#include <stdio.h>
#include <stdlib.h>
struct node
{
   int data;
   struct node *leftChild, *rightChild;
};
struct node *newNode(int data)
{
   struct node *Node = (struct node *)malloc(sizeof(struct node));
   Node->data = data;
   Node->leftChild = Node->rightChild = NULL;
   return (Node);
}
struct node *rightRotate(struct node *x)
{
   struct node *y = x->leftChild;
   x->leftChild = y->rightChild;
   y->rightChild = x;
   return y;
}
struct node *leftRotate(struct node *x)
{
   struct node *y = x->rightChild;
   x->rightChild = y->leftChild;
   y->leftChild = x;
   return y;
}
struct node *splay(struct node *root, int data)
{
   if (root == NULL || root->data == data)
      return root;
   if (root->data > data)
   {
      if (root->leftChild == NULL)
         return root;
      if (root->leftChild->data > data)
      {
         root->leftChild->leftChild = splay(root->leftChild->leftChild, data);
         root = rightRotate(root);
      }
      else if (root->leftChild->data < data)
      {
         root->leftChild->rightChild = splay(root->leftChild->rightChild, data);
         if (root->leftChild->rightChild != NULL)
            root->leftChild = leftRotate(root->leftChild);
      }
      return (root->leftChild == NULL) ? root : rightRotate(root);
   }
   else
   {
      if (root->rightChild == NULL)
         return root;
      if (root->rightChild->data > data)
      {
         root->rightChild->leftChild = splay(root->rightChild->leftChild, data);
         if (root->rightChild->leftChild != NULL)
            root->rightChild = rightRotate(root->rightChild);
      }
      else if (root->rightChild->data < data)
      {
         root->rightChild->rightChild = splay(root->rightChild->rightChild, data);
         root = leftRotate(root);
      }
      return (root->rightChild == NULL) ? root : leftRotate(root);
   }
}
struct node *insert(struct node *root, int k)
{
   if (root == NULL)
      return newNode(k);
   root = splay(root, k);
   if (root->data == k)
      return root;
   struct node *newnode = newNode(k);
   if (root->data > k)
   {
      newnode->rightChild = root;
      newnode->leftChild = root->leftChild;
      root->leftChild = NULL;
   }
   else
   {
      newnode->leftChild = root;
      newnode->rightChild = root->rightChild;
      root->rightChild = NULL;
   }
   return newnode;
}
void printTree(struct node *root)
{
   if (root == NULL)
      return;
   if (root != NULL)
   {
      printTree(root->leftChild);
      printf("%d ", root->data);
      printTree(root->rightChild);
   }
}
int main()
{
   struct node *root = newNode(34);
   root->leftChild = newNode(15);
   root->rightChild = newNode(40);
   root->leftChild->leftChild = newNode(12);
   root->leftChild->leftChild->rightChild = newNode(14);
   root->rightChild->rightChild = newNode(59);
   printf("The Splay tree is: \n");
   printTree(root);
   printf("\n");
   return 0;
}
