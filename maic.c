#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int main(int argc,char* argv[])
{
    char** G;
    List*** S;
    Tree T;
    int M,N, num;
    //chapter 1
    checkInput(argc);
    N = atoi(argv[1]); //columns
    M = atoi(argv[2]); //rows
    checkValue(M,N);

    //chapter 2
    G = makeEmptyMat(M,N);
    getInput(M,N,G);

    //chapter 3
    S=makeEmptyMatList(M,N);
    BuildMatList(S,G,M,N);
    freeMat(G,M); //frees G

    //chapter 4
    BuildTree(&T,S,M,N);
    freeMatList(S,M);//frees S

    scanf(" %d", &num);
    checkNum(num,numNodes(T));
    printNodeNum(T, &num);
    freeTree(T);
    return 0;
}

