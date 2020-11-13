#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 20

int getSize(FILE *fp){
    char buf[MAXLINE];

    fgets(buf, MAXLINE, fp);

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

void buildList(FILE *fp, int* nums){
    char buf[MAXLINE];

    int i;
    int j = 0;
    int num = 0;

    if(fgets(buf, MAXLINE, fp) == NULL){
        return;
    }

    while(1){
        if(i == MAXLINE - 1){
            if(buf[i] == '\n'){
                if(fgets(buf, MAXLINE, fp) == NULL) {
                    nums[j] = num;
                    return;
                }
                nums[j] = num;
            }
            else{
                if(fgets(buf, MAXLINE, fp) == NULL){
                    nums[j] = num;
                    return;
                }
            }
            i = 0;
        }
        if(buf[i] == ' '){
            nums[j] = num;
            num = 0;
            j++;
            i++;
        }
        else if(buf[i] == '-'){

        }
        if(i != MAXLINE - 1) {
            num *= 10;
            num += buf[i] - 48;
            i++;
        }
    }
}

//int search(struct Link *head, int num, int size){
//    struct Link *cur = head;
//    int loc;
//    int mid = size / 2;
//    int i = 1;
//    for(; i < mid; i++){
//        cur = cur->next;
//    }
//    if(cur->val > num){
//        loc = search(cur, num, mid);
//    }
//    else{
//
//    }
//    cur->next = NULL;
//    return 0;
//}

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Syntax: ./binarySearch <sorted file> <number to find>");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");

    int size = getSize(fp);

    int *nums = malloc(sizeof(int) * size);

    buildList(fp, nums);

    //struct Link *head = buildListFromFile(fp);

    //int loc = search(head, atoi(argv[2]), size);

    //deleteList(head);
    fclose(fp);

    //int val = search(atoi(argv[2]));
    return EXIT_SUCCESS;
}