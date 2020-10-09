#include <stdio.h>
#include <stdlib.h>
#include "insertSort.h"

#define MAXSIZE 100
#define MAXLINE 1200

int getSize(FILE *fp){
    char buf[MAXSIZE];

    fgets(buf, MAXSIZE, fp);

    if(buf[0] != 's' && buf[1] != 'i' && buf[2] != 'z' && buf[3] != 'e' && buf[4] != ':' && buf[5] != ' '){
        fprintf(stderr, "Error reading input file: Does not start with \"size: \"");
        return 0;
    }

    int i = 6;
    int size = 0;
    while(buf[i] != '\n'){
        if(size == 0){
            size = buf[i] - 48;
        }
        else{
            size *= 10;
            size += buf[i] - 48;
        }
        i++;
    }

    return size;
}

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
    struct Link *temp;

    while(last->next != NULL){
        if(last->val > val){
            temp = last;
            last = last->next;
        }
        else{
            if(last == head){
                link->next = head;
                return link;
            }
            temp->next = link;
            link->next = last;
            return head;
        }
    }
    if(last->val > val){
        last->next = link;
        link->next = NULL;
        return head;
    }
    else{
        if(last == head){
            link->next = head;
            return link;
        }
        link->next = last;
        temp->next = link;
        return head;
    }
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

struct Link* buildList(FILE *fp){
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

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Syntax: ./insertSort <input file>\n");
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        fprintf(stderr, "Failed to open file");
        return EXIT_FAILURE;
    }

    int size = getSize(fp);

    struct Link *list = buildList(fp);

    deleteList(list);
    fclose(fp);
}