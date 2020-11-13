#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

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
        if(buf[i] != ' ' && i < MAXLINE - 1){
            if(buf[i] == '\n'){
                nums[j] = num;
                num = 0;
                i = 0;
                j++;
                if(fgets(buf, MAXLINE, fp) == NULL){
                    return;
                }
            }
            else if(buf[i] == '-'){
                i++;
                if(i == MAXLINE - 1){
                    fgets(buf, MAXLINE, fp);
                    i = 0;
                }
                num *= 10;
                num += buf[i] - 48;
                num *= -1;
                i++;
            }
            else{
                num *= 10;
                if(num < 0){
                    num -= buf[i] - 48;
                }
                else {
                    num += buf[i] - 48;
                }
                i++;
            }
        }
        else if(buf[i] == ' '){
            nums[j] = num;
            num = 0;
            j++;
            i++;
        }
        else{
            if(fgets(buf, MAXLINE, fp) == NULL){
                nums[j] = num;
                return;
            }
            i = 0;
        }
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Syntax: ./binarySearch <sorted file> <number to find>");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");

    int size = getSize(fp);

    int *nums = malloc(sizeof(int) * size);
    bzero(nums, size);

    buildList(fp, nums);

    //struct Link *head = buildListFromFile(fp);

    //int loc = search(head, atoi(argv[2]), size);

    //deleteList(head);
    fclose(fp);

    //int val = search(atoi(argv[2]));
    return EXIT_SUCCESS;
}