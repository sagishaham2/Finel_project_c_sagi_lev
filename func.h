#ifndef FINAL_PROJECT_FUNC_H
#define FINAL_PROJECT_FUNC_H

//structs
typedef struct listNode
{
    int x;
    int y;
    struct listNode *next;
}ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail;
}List;

//chapter 1
void checkInput(int argc);
void checkValue(int a,int b);

//chapteer 2
char** makeEmptyMat(int rows,int columns);
void getInput(int m,int n, char** mat);
void checkAllocation(void* ptr);
int isSep(char c, char* seps);
void printMat(int m,int n,char** mat);
void setBit(char* byte,int i);
int isBitISet(char* byte, int i);
void freeMat(char** mat, int rows);

//chapter 3
List*** makeEmptyMatList(int rows, int columns);
List* makeEmptyList();
void insertNodeToEndList(List* lst, ListNode* newTail);
int isEmptyList(List lst);
ListNode* createNewListNode(int x, int y, ListNode* next);
void freeList(List* lst);
int compareCoordinates(ListNode* nodeOne, ListNode* nodeTwo);
void updateCellsInS(List*** S, List* old_lst, List* new_lst);

void BuildMatList(List*** s, char** g, int rows, int columns);
int IsXInDomain(int x);
int IsYInDomain(int y);
int checkAbove(int x, int y, char** mat);
int checkLeft(int x, int y, char** mat);
int checkAboveAndLeft(int x, int y, char** mat);
int whatToDoNext(int x, int y, char** g);
void BuildListS(List*** S, int x, int y, int to_do);
void UpdateAndMergeList(List*** S,List* lst_above, List* lst_left);
void mergeList(List* lst_new, List* lst_old);

void freeMatList(List*** matrix, int rows);//have to make yet

//chapter 4

typedef struct treeNode
{
    List* lst;
    int size;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{
    TreeNode *root;
}Tree;

void BuildTree(Tree* T, List*** S, int rows, int columns);
int len(List* lst);
TreeNode* insertToTreeRec(TreeNode* root, List* lst, int size);
int numNodes(Tree tr);
int numNodesRec(TreeNode* root);
void checkNum(int num, int range);
TreeNode *findNode(Tree *T, int num);
TreeNode* findNodeRec(TreeNode* root, int num);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);

void printNodeNum(Tree tr, int* n);
void printNodeNumRec(TreeNode* root, int *n);
#endif //FINAL_PROJECT_FUNC_H
