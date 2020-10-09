#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* createFile(char* fileName){
    FILE *fp;

    fp = fopen(fileName, "w");
    if(fp == NULL){
        return NULL;
    }
    return fp;
}

void genNums(int quantity, int max, int min, FILE *fp){
    int i = 1;
    srand(time(NULL));

    if(min < 0){
        int dif = max - min;
        for(; i <= quantity; i++){
            int num = rand() % (dif + 1);
            num += min;
            if(i % 100 == 0){
                fprintf(fp, "%d\n", num);
            }
            else {
                fprintf(fp, "%d ", num);
            }
        }
    }
    else{
        for(; i <= quantity; i++){
            int num = rand() % (max - min + 1) + min;
            if(i % 100 == 0){
                fprintf(fp, "%d\n", num);
            }
            else {
                fprintf(fp, "%d ", num);
            }
        }
    }
}

int main(int argc, char* argv[]){
    int min, max, quantity;

    if(argc == 2){
        min = 0;
        max = 100;
        quantity = 100;
    }
    else if(argc == 4){
        min = atoi(argv[2]);
        max = atoi(argv[3]);
        quantity = 100;
    }
    else if(argc == 5){
        min = atoi(argv[2]);
        max = atoi(argv[3]);
        quantity = atoi(argv[4]);
    }
    else{
        fprintf(stderr, "Syntax:\n./numGen <outFileName> :will default min=0 max=100 quantity=100 or\n./numGen <outFile>  <min> <max> :will default quantity=100 or\n./numGen <outFile>  <min> <max> <quantity>\n");
    }

    char* name = argv[1];

    FILE *fp = createFile(name);
    if(fp == NULL){
        return EXIT_FAILURE;
    }

    genNums(quantity, max, min, fp);


    fclose(fp);
    return EXIT_SUCCESS;
}