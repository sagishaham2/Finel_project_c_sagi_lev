#include "func.h"
#include <stdio.h>
#include <stdlib.h>

//chapter 1

void checkInput(int argc)
{
    if (argc!=3)
    {
        printf("Wrong number of arguments\n");
        exit(1);
    }
}
void checkValue(int a,int b)
{
    if (b<1 || a<1)
    {
        printf("Value error, value should be natural number\n");
        exit(1);
    }
}

//chapter 2
void getInput(int m,int n, char ** mat)
{
    char seps[] = " \n\t"; //white spaces
    int row=0,collum;
    char c = getchar();//gets first input
    while (row < m)
    {
        collum = 0;
        while (collum < n )
        {
            if (c == '#' || c == '.') //checks if char is legal
            {
                if (c == '#')
                {
                    setBit(&mat[row][collum/8],collum%8);
                }
                collum++;
            }
            else if (isSep(c,seps)==0)//checks if char is NOT legal
                {
                    printf("Invalid matrix character");
                    exit(1);
                }
            c = getchar();//keeps getting input
        }
        row++;
    }
}
void setBit(char* byte,int i)//sets right bit
{
    char mask = 1 << i;
    *byte = *byte | mask;
}

int isBitISet(char* byte, int i)//checks if bit is set
{
    char mask = 1 << i;
    return *byte & mask;
}
void printMat(int m, int n, char** mat) //prints the matrix
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (isBitISet(&mat[i][j / 8], j % 8))
            {
                putchar('1');
            }
            else
            {
                putchar('0');
            }
        }
        putchar('\n');
    }
}
void checkAllocation(void* ptr) //checks dynamically allocation
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
}
int isSep(char c, char* seps){ //checks if char is in the separators
   int i = 0;
    while (seps[i]!= '\0')
    {
        if (c == seps[i])
            return 1;
        i++;
    }
    return 0;
}
char** makeEmptyMat(int rows,int columns){ //creates empty matrix
    char** mat;
    int i;
    int num_bytes = columns/8;
    if (columns%8!=0)
        num_bytes++;
    mat = malloc(sizeof(char*)*rows);
    checkAllocation(mat);
    for (i=0;i<rows;i++)
    {
        mat[i] = calloc(sizeof(char),num_bytes);
        checkAllocation(mat[i]);
    }
    return mat;
}


void freeMat(char** mat, int rows) {//frees dynamically allocated memory
    int i;
    for (i=0;i<rows;i++) {
        free(mat[i]);
    }
    free(mat);
}

//chapter 3

List*** makeEmptyMatList(int rows, int columns){
  /*creates empty matrix each object equals NULL
    [[NULL,...,NULL],...,[NULL,...,NULL]]        */

    List*** res=malloc(sizeof(List**)*rows);
    checkAllocation(res);

    int i;

    for (i=0;i<rows;++i) {
        res[i]=calloc(sizeof(List*),columns); //sets every pointer to NULL
        checkAllocation(res[i]);
    }
    return res;
}

void BuildMatList(List*** s, char** g, int rows, int columns) {
    int x,y;
    int next_move;

    for (x=0;x<rows;x++) {
        for (y=0;y<columns;++y) {
            if (isBitISet(&g[x][y/8],y%8)) {
                next_move=whatToDoNext(x,y,g);
                BuildListS(s, x ,y, next_move);
            }
        }
    }
}

int whatToDoNext(int x, int y, char** g) {
    /*
        1- merge 2 lists
        2- insert to list above
        3- insert to list on left
        4- create new list
    */

    if (IsXInDomain(x)&&IsYInDomain(y))
        return checkAboveAndLeft(x,y,g);
    if (IsXInDomain(x) && checkAbove(x, y, g))
        //check above y-1
        return 2;
    if ( IsYInDomain(y) && checkLeft(x, y, g))
        //check left x-1
        return 3;
    return 4;
}

int IsXInDomain(int x) {
    return x>0;
}

int IsYInDomain(int y) {
    return y>0;
}

int checkAbove(int x, int y, char** mat) {
    return isBitISet(&mat[x-1][y/8], y%8);
}

int checkLeft(int x, int y, char** mat) {
    return isBitISet(&mat[x][(y-1)/8], (y-1)%8);
}

int checkAboveAndLeft(int x, int y, char** mat) {//checks what is the next step
    /*
        1- merge 2 lists
        2- insert to list above
        3- insert to list on left
        4- create new list
    */
    if (checkAbove(x,y,mat) && checkLeft(x,y,mat))
        return 1;
    if (checkAbove(x,y,mat))
        return 2;
    if (checkLeft(x,y,mat))
        return  3;
    return 4;
}

void BuildListS(List*** S, int x, int y, int to_do) {
    ListNode* node=createNewListNode(x,y,NULL);
    if (to_do==1) {
        //merge sort
        if (S[x-1][y]->head!=S[x][y-1]->head)
            UpdateAndMergeList(S,S[x-1][y], S[x][y-1]);
        insertNodeToEndList(S[x-1][y],node);
        S[x][y]=S[x-1][y];
    }
    else if (to_do==2) {
        //insert to the list x-1
        insertNodeToEndList(S[x-1][y],node);
        S[x][y]=S[x-1][y];
    }
    else if (to_do==3) {
        //insert to the list y-1
        insertNodeToEndList(S[x][y-1],node);
        S[x][y]=S[x][y-1];
    }
    else {
        //make new list with current node
        S[x][y]=makeEmptyList();
        insertNodeToEndList(S[x][y],node);
    }
}

void UpdateAndMergeList(List*** S, List* lst_above, List* lst_left) {
    List *new_lst, *old_lst;

    if (compareCoordinates(lst_above->head, lst_left->head) == 1) {
        new_lst = lst_above;
        old_lst = lst_left;
    }
    else {
        new_lst = lst_left;
        old_lst = lst_above;
    }

    // update cells in S to point to the base list
    updateCellsInS(S, old_lst, new_lst);

    mergeList(new_lst, old_lst);

    free(old_lst); //frees unnecessary list
}


int compareCoordinates(ListNode* nodeOne, ListNode* nodeTwo) {
    if (nodeOne->x < nodeTwo->x)
        return 1;
    if (nodeOne->x > nodeTwo->x)
        return -1;
    // If x is equal, check y
    if (nodeOne->y < nodeTwo->y)
        return 1;
    if (nodeOne->y > nodeTwo->y)
        return -1;

    return 0; // Exactly the same coordinates
}

void updateCellsInS(List*** S, List* old_lst, List* new_lst) {
    ListNode* curr=old_lst->head;

    while (curr!=NULL) {
        S[(curr->x)-1][(curr->y)-1]=new_lst;
        curr=curr->next;
    }
}

void mergeList(List* lst_new, List* lst_old) {
    ListNode* curr_new=lst_new->head, *next_new, *temp;
    ListNode* curr_old=lst_old->head, *next_old;

    temp=curr_new;
    curr_new=curr_new->next;
    while (curr_new!=NULL && curr_old!=NULL) {

        if (compareCoordinates(curr_new, curr_old)==1) {
            temp->next=curr_new;
            temp=temp->next;
            curr_new=curr_new->next;
        }
        else{
            temp->next=curr_old;
            temp=temp->next;
            curr_old=curr_old->next;
        }
    }

    if (curr_new!=NULL) {
        temp->next=curr_new; //connects the rest
    }

    if (curr_old!=NULL) {
        temp->next = curr_old; //connects the rest
        lst_new->tail = lst_old->tail; // updates tale
    }
}
List* makeEmptyList()
{
    List* new_list=malloc(sizeof(List));
    checkAllocation((new_list));
    new_list->head=new_list->tail= NULL;
    return new_list;
}

int isEmptyList(List lst)
{
    return (lst.head == NULL);
}

ListNode* createNewListNode(int x, int y, ListNode* next)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    checkAllocation(node);
    node->x = x+1;
    node->y = y+1;
    node->next = next;
    return node;
}

void insertNodeToEndList(List* lst, ListNode* newTail)
{
    if (isEmptyList(*lst))
        lst->head = lst->tail=newTail;
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void freeList(List *lst)
{
    ListNode* curr = lst->head, *next;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(lst);
}


void freeMatList(List*** matrix, int rows) {
    int i;
    for (i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

//chapter 4

TreeNode* createNewTreeNode(int area, List* lst, TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->lst=lst;
    node->size = area;
    node->left = left;
    node->right = right;

    return node;
}

void BuildTree(Tree* T, List*** S, int rows, int columns) {
    int i,j;
    T->root=NULL;
    for (i=0;i<rows;++i) {
        for (j=0;j<columns;++j) {
            if (S[i][j]!=NULL) {
                if (S[i][j]->head->x==i+1 && S[i][j]->head->y==j+1)
                    T->root=insertToTreeRec(T->root, S[i][j], len(S[i][j]));
            }
        }
    }
}

int len(List* lst) {
    ListNode* curr=lst->head;
    int res=0;
    while (curr!=NULL) {
        res++;
        curr=curr->next;
    }
    return res;
}

TreeNode* insertToTreeRec(TreeNode* root, List* lst, int size) {
    if (root==NULL)
        return createNewTreeNode(size,lst,NULL,NULL);
    else {
        if (size>root->size) //if new size bigger than size of root
            root->right=insertToTreeRec(root->right, lst, size);
        else if (size<root->size)  //if new size smaller than size of root
            root->left=insertToTreeRec(root->left, lst, size);
        else {//sizes are equal
            if (compareCoordinates(root->lst->head, lst->head)==1) //left head closer to (1,1), so insert to the right
                root->right=insertToTreeRec(root->right, lst, size);
            else
                root->left=insertToTreeRec(root->left, lst, size);
        }
        return root;
    }
}

int numNodes(Tree tr)
{
    return numNodesRec(tr.root);
}

int numNodesRec(TreeNode* root)
{
    if (root == NULL)
        return 0;
    else
    {
        int numLeft, numRight;

        numLeft = numNodesRec(root->left);
        numRight = numNodesRec(root->right);

        return numLeft + numRight + 1;
    }
}

void checkNum(int num, int range) { //freeTree?????
    if (num<1 || num>range) {
        printf("Invalid area index");
        exit(1);
    }
}

void freeTree(Tree tr)
{
    freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeRec(root->left);
        freeTreeRec(root->right);
        freeList(root->lst);
        free(root);
    }
}


void printNodeNum(Tree tr, int* n)
{
    printNodeNumRec(tr.root, n);
}

void printNodeNumRec(TreeNode* root, int *n)
{
    if (root == NULL|| *(n)==0)
        return;
    else
    {
        printNodeNumRec(root->left, n);
        if (*n==0)
            return;
        if (*n==1)
            printf("%d %d %d\n", root->size, root->lst->head->y, root->lst->head->x);
        (*n)--;
        printNodeNumRec(root->right, n);
    }
}
