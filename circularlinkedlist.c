#include <stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node*next;
};


void display(struct node* head){
    struct node *ptr = head;

    printf("element is %d\n",ptr->data);
    ptr = ptr->next;
    while (ptr!=head)
    {
        printf("element is %d\n",ptr->data);
        ptr = ptr->next;
    }
}


int main()
{
   struct node* head;
   struct node* second;
   struct node* third;
   struct node* fourth;

   head = (struct node*)malloc(sizeof(struct node*));
   second = (struct node*)malloc(sizeof(struct node*));
   third = (struct node*)malloc(sizeof(struct node*));
   fourth = (struct node*)malloc(sizeof(struct node*));

   head->data = 7;
   head->next = second;
    second->data = 5;
    second->next = third;
    third->data =11;
    third->next = fourth;
    fourth->data =13;
    fourth->next = head; ;


    display(head);

   return 0;
}