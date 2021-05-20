#ifndef LINK_LIST
#define LINK_LIST

#include <stdlib.h>
#include <stdio.h>

struct Link{
    struct Link *next;
    int val;
};

struct Link* addLink(struct Link *head, int val){
    struct Link *link = malloc(sizeof(struct Link));
    if(head == NULL){
        link->val = val;
        link->next = NULL;
        return link;
    }
    struct Link *cur = head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = link;
    link->val = val;
    link->next = NULL;

    return head;
}

void deleteList(struct Link *head){
    struct Link *cur = head;
    while(head->next != NULL){
        cur = head->next;
        free(head);
        head = cur;
    }
    free(cur);
}

void writeList(FILE *fp, struct Link *list, int size){
    fprintf(fp, "size: %d\n", size);

    int i = 1;
    while(list != NULL){
        if(i % 10 == 0){
            fprintf(fp, "%d\n", list->val);
        }
        else{
            fprintf(fp, "%d ", list->val);
        }
        i++;
        list = list->next;
    }
}
#endif