#include <stdio.h>
#include <stdlib.h>
#include "strctalg.h"

#define MAXLINE 1024
#define MAXSIZE 256

struct Link* makeFirstLink(int val){
    struct Link *head = malloc(sizeof(struct Link));
    head->next = NULL;
    head->val = val;

    return head;
}

struct Link* makeLink(struct Link *head, int val){
    struct Link *link = malloc(sizeof(struct Link));
    link->val = val;
    struct Link *last = head;

    while(last->next != NULL){
        last = last->next;
    }

    last->next = link;
    link->next = NULL;

    return head;
}

void deleteList(struct Link *list){
    struct Link *cur = list;
    while(list->next != NULL){
        cur = list->next;
        free(list);
        list = cur;
    }
    free(cur);
}

void writeListToFIle(FILE *fp, struct Link *list, int size){
    fprintf(fp, "size: %d\n", size);

    int i = 1;
    while(list->next != NULL){
        if(i % 100 == 0){
            fprintf(fp, "%d\n", list->val);
        }
        else{
            fprintf(fp, "%d ", list->val);
        }
        i++;
        list = list->next;
    }
}

void printList(struct Link *list){
    int i = 1;
    while(list->next != NULL) {
        if(i % 10 == 0){
            printf("%d\n", list->val);
        }
        else{
            printf("%d ", list->val);
        }
        list = list->next;
        i++;
    }
}

struct Link* buildListFromFile(FILE *fp){
    char buf[MAXLINE], num[MAXSIZE];
    struct Link *head = NULL;

    fgets(buf, MAXLINE, fp);

    int i = 0;
    int start;
    int val;
    while(buf[i] != 4){
        while(buf[i] != '\n'){
            if(buf[i] == ' '){
                i++;
            }
            start = i;
            while(buf[i] != ' ' && buf[i] != '\n'){
                num[i - start] = buf[i];
                i++;
            }
            num[i - start] = 0;
            val = atoi(num);
            if(head == NULL){
                head = makeFirstLink(val);
            }
            else{
                head = makeLink(head, val);
            }
        }
        if(!fgets(buf, MAXLINE, fp)){
            break;
        }
        i = 0;
    }
    return head;
}