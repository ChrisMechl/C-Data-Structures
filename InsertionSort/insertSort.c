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
    struct Link *link = malloc(sizeof(struct Link*));
    link->next = NULL;
    link->val = val;

    return link;
}

struct Link* makeLink(struct Link *cur, int val){
    struct Link *link = malloc(sizeof(struct Link*));

    cur->next = link;
    link->next = NULL;
    link->val = val;

    return link;
}

struct Link* buildList(int size, FILE *fp){
    char buf[MAXLINE], num[MAXSIZE];
    struct Link *cur = NULL;
    struct Link *head;

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
            while (buf[i] != ' ' && buf[i] != '\n') {
                num[i - start] = buf[i];
                i++;
            }
            num[i - start] = 0;
            val = atoi(num);
            if (cur == NULL) {
                cur = makeFirstLink(val);
                head = cur;
            } else {
                cur = makeLink(cur, val);
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

    struct Link *list = buildList(size, fp);
}