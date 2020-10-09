#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Syntax: ./insertSort <input file>\n");
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        fprintf(stderr, "Failed to open file");
        return EXIT_FAILURE;
    }
}