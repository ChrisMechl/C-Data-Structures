#include <stdio.h>
#include <strings.h>
#include "linkList.h"
#define MAXSIZE 10 //max digits of number in list to sort

/* Gets size from first line of fp, throws error if not correctly formatted */
int getSize(FILE *fp){
    char buf[7], cur, num[MAXSIZE];
    int size;

    bzero(num, MAXSIZE);
    fgets(buf, 7, fp);

    if(buf[0] != 's' || buf[1] != 'i' || buf[2] != 'z' || buf[3] != 'e' || buf[4] != ':' || buf[5] != ' '){
        fprintf(stderr, "Error reading input file: Must start with \"size: \"");
        return 0;
    }

    int i = 0;
    cur = fgetc(fp);
    while(cur != '\n'){
        num[i] = cur;
        i++;
        if(i == MAXSIZE){
            fprintf(stderr, "Max number of digits (%d): exceeded\n", MAXSIZE);
        }
        cur = fgetc(fp);
    }

    size = atoi(num);

    return size;
}

/* Builds unsorted singly linked list from file at fp */
struct Link *buildList(FILE *fp){
    char num[MAXSIZE], cur, prev;
    struct Link *head = NULL;
    int i = 0;
    int val;

    bzero(num, MAXSIZE);
    while(1){
        prev = cur;
        cur = fgetc(fp);
        if(cur == EOF){
            if(prev < 48 || prev > 57){ //Previous character was not a number (\n or similar)
                break;
            }
            val = atoi(num);
            head = addLink(head, val);
            break;
        }
        else if(cur != '\n' && cur != ' '){
            num[i] = cur;
            i++;
        }
        else{
            val = atoi(num);
            head = addLink(head, val);
            bzero(num, MAXSIZE);
            i = 0;
        }
    }
    return head;
}

struct Link *sortedInsert(struct Link *head, struct Link *new){
    struct Link *cur;
    /* new val must go first (either sorted list is empty or new has smaller value than first entry) */
    if(head == NULL || head->val >= new->val){
        new->next = head;
        return new;
    }
    else{
        cur = head;
        /* Move through list until new->val is smaller than the next value in sorted list */
        while(cur->next != NULL && cur->next->val < new->val){
            cur = cur->next;
        }
        /* Insert new and update next value */
        new->next = cur->next;
        cur->next = new;
    }
    return head;
}

struct Link *sortList(struct Link *head){
    struct Link *sortedHead = NULL;
    struct Link *cur = head;
    struct Link *next;

    while(cur != NULL){
        next = cur->next;
        sortedHead = sortedInsert(sortedHead, cur);
        cur = next;
    }
    return sortedHead;
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        fprintf(stderr, "Syntax: ./insertSort <input file> <output file>\n");
        return EXIT_FAILURE;
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        fprintf(stderr, "Failed to open file");
        return EXIT_FAILURE;
    }

    int size = getSize(fp);
    if(size == 0){
        return EXIT_FAILURE;
    }
    struct Link *head = buildList(fp);
    fclose(fp);

    struct Link *sorted = sortList(head);

    fp = fopen(argv[2], "w");
    writeList(fp, sorted, size);
    fclose(fp);

    deleteList(sorted);
    return EXIT_SUCCESS;
}
