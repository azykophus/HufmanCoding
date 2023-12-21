#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define maxunique 50
#define maxlength 1000000
#define maxcode 8
struct dict
{
        char s;
        int freq;
};
struct dict2
{
        char character;
        char code[maxcode];
};
int count2;
struct dict2 codes[maxunique];
int count = 0;
struct dict arr[maxunique];

struct node
{
        struct node *left, *right;
        char ch;
        int freq;
};

struct node *newnode(char s, int freq);
void insert(char s, int freq);
int in(char s);
void Insert(struct node *element);
struct node *DeleteMin();
void print(struct node *temp, char *code, FILE *output);

struct node *node;
struct node *heap[maxunique];
int heapSize = 0;

int main()
{

        char read[1000000];
        FILE *file = fopen("in.txt", "r");
        FILE *output = fopen("output.txt", "w");
        while (fgets(read, sizeof(read), file) != NULL)
                ;

        int length = strlen(read);

        for (int i = 0; i < length; i++)
        {
                int a = in(read[i]);
                if (a == -1)
                {
                        insert(read[i], 1);
                }
                else
                {
                        arr[a].freq++;
                }
        }

        for (int i = 0; i < count; i++)
        {
                printf("%c %d\n", arr[i].s, arr[i].freq);
        }

        heap[0] = (struct node *)malloc(sizeof(struct node));
        heap[0]->freq = 0;
        int n = count;

        for (int i = 0; i < n; i++)
        {

                struct node *temp = (struct node *)malloc(sizeof(struct node));
                temp->ch = arr[i].s;
                temp->freq = arr[i].freq;
                temp->left = temp->right = NULL;
                Insert(temp);
        }
        if (n == 1)
        {
                fprintf(output, "⚬ %c ⇄ 0\n", arr[0].s);
                return 0;
        }
        for (int i = 0; i < n - 1; i++)
        {
                struct node *left, *right, *top;
                left = DeleteMin();
                right = DeleteMin();
                top = (struct node *)malloc(sizeof(struct node));
                top->left = left;
                top->ch = 0;
                top->right = right;
                top->freq = left->freq + right->freq;
                Insert(top);
        }
        struct node *tree = DeleteMin();
        char code[maxcode];
        code[0] = '\0';
        print(tree, code, output);

        for (int i = 0; i < count2; i++)
        {
                printf("%c %s\n", codes[i].character, codes[i].code);
        }

        for (int i = 0; i < length; i++)
        {
                char print = read[i];
                int j;
                for (j = 0; j < count2; j++)
                {
                        if (codes[j].character == print)
                                break;
                }
                fprintf(output, "%s", codes[j].code);
        }
}

void insert(char s, int freq)
{
        arr[count].s = s;
        arr[count].freq = freq;
        count++;
}
int in(char s)
{
        for (int i = 0; i < count; i++)
        {
                if (arr[i].s == s)
                {
                        return i;
                }
        }
        return -1;
}

void Insert(struct node *element)
{       
        heapSize=heapSize+1;
        int now;
        now = heapSize;
        heap[heapSize] = element;
        for(;heap[now / 2]->freq > element->freq;now=now/2){
                heap[now] = heap[now / 2];
        }
        // while (heap[now / 2]->freq > element->freq)
        // {
        //         heap[now] = heap[now / 2];
        //         now /= 2;
        // }
        heap[now] = element;
}
struct node *DeleteMin()
{
        struct node *minElement, *lastElement;
        int child, now;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        for (now = 1; now * 2 <= heapSize; now = child)
        {
                child = now * 2;
                if (child != heapSize && heap[child + 1]->freq < heap[child]->freq)
                {
                        child++;
                }
                if (lastElement->freq > heap[child]->freq)
                {
                        heap[now] = heap[child];
                }
                else
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}
void print(struct node *temp, char *code, FILE *output)
{
        if (temp->left == NULL && temp->right == NULL)
        {
                codes[count2].character = temp->ch;
                strcat(codes[count2].code, code);
                count2++;
                fprintf(output, "⚬ %c ⇄ %s\n", temp->ch, code);
                return;
        }
        int length = strlen(code);
        char leftcode[maxcode], rightcode[maxcode];
        strcpy(leftcode, code);
        strcpy(rightcode, code);
        leftcode[length] = '0';
        leftcode[length + 1] = '\0';
        rightcode[length] = '1';
        rightcode[length + 1] = '\0';
        print(temp->left, leftcode, output);
        print(temp->right, rightcode, output);
}

struct node *newnode(char s, int freq)
{
        struct node *new = (struct node *)malloc(sizeof(struct node));
        new->ch = 0;
        new->left = new->right = NULL;
        return new;
}