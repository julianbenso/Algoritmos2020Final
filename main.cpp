/*
 * C++ Program to Implement B+ Tree
 */
#include<stdio.h>
//#include<conio.h>
#include<iostream>
using namespace std;
int grado=6;
struct BpTreeNode
{
    int *data;
    BpTreeNode **child_ptr;
    bool leaf;
    int n;
}
    *root = NULL, *np = NULL, *x = NULL;
BpTreeNode * init()
{
    int i;
    //int grado=5;
    int numhijos= grado;
    np = new BpTreeNode;
    np->data = new int[grado-1];
    np->child_ptr = new BpTreeNode *[numhijos];
    np->leaf = true;
    np->n = 0;
    for (i = 0; i < 6; i++)
    {
        np->child_ptr[i] = NULL;
    }
    return np;
}
void traverse(BpTreeNode *p)
{
    cout<<endl;
    int i;
    for (i = 0; i < p->n; i++)
    {
        cout<<"  ";
        if (p->leaf == false)
        {
            traverse(p->child_ptr[i]);
        }

        cout << "" << p->data[i];
    }

    if (p->leaf == false)
    {
        traverse(p->child_ptr[i]);
    }
    cout<<endl;
}
void sort(int *p, int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (p[i] > p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int split_child(BpTreeNode *x, int i, int a)
{
    int j, mid;
    BpTreeNode *np1, *np3, *y;
    np3 = init();
    np3->leaf = true;
    int separarDesde=((grado-1)/2)+1;
    if (i == -1)
    {
        mid = x->data[separarDesde];
        x->data[separarDesde] = 0;
        x->n--;
        np1 = init();
        np1->leaf = false;
        x->leaf = true;

        for (j = separarDesde+1; j <5; j++)
        {
            np3->data[j - separarDesde-1] = x->data[j];
            np3->child_ptr[j - separarDesde-1] = x->child_ptr[j];
            np3->n++;
            x->data[j] = 0;
            x->n--;
        }
        for(j = 0; j < grado; j++)
        {
            x->child_ptr[j] = NULL;
        }
        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;
        root = np1;
    }
    else
    {
        y = x->child_ptr[i];
        mid = y->data[separarDesde];
        y->data[separarDesde] = 0;
        y->n--;
        for (j = separarDesde+1; j < 5; j++)
        {
            np3->data[j - separarDesde-1] = y->data[j];
            np3->n++;
            y->data[j] = 0;
            y->n--;
        }
        x->child_ptr[i + 1] = y;
        x->child_ptr[i + 1] = np3;
    }
    return mid;
}
void insert(int a)
{
    int i, temp;
    x = root;
    if (x == NULL)
    {
        root = init();
        x = root;
    }
    else
    {
        if (x->leaf == true && x->n == 5)
        {
            temp = split_child(x, -1,a);
            x = root;
            for (i = 0; i < (x->n); i++)
            {
                if ((a > x->data[i]) && (a < x->data[i + 1]))
                {
                    i++;
                    break;
                }
                else if (a < x->data[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            x = x->child_ptr[i];
            insert(temp);
        }
        else
        {
            while (x->leaf == false)
            {
                for (i = 0; i < (x->n); i++)
                {
                    if ((a > x->data[i]) && (a < x->data[i + 1]))
                    {
                        i++;
                        break;
                    }
                    else if (a < x->data[0])
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if ((x->child_ptr[i])->n == 5)
                {
                    temp = split_child(x, i, a);
                    x->data[x->n] = temp;
                    x->n++;
                    insert(temp);
                    continue;
                }
                else
                {
                    x = x->child_ptr[i];

                }
            }
        }
    }
    x->data[x->n] = a;
    sort(x->data, x->n);
    x->n++;
}
int main()
{
    int i, n, t;
    cout<<"enter the no of elements to be inserted\n";
    cin>>n;
    for(i = 0; i < n; i++)
    {
        cout<<"enter the element\n";
        cin>>t;
        insert(t);
    }
    cout<<"traversal of constructed tree\n";
    traverse(root);
    //getch();
}