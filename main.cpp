/*
 * C++ Program to Implement B+ Tree
 */
#include<stdio.h>
//#include<conio.h>
#include<iostream>
using namespace std;
int grado=6;
int cantClaves= grado-1;
struct BpTreeNode
{
    int *data;
    BpTreeNode **child_ptr;
    bool leaf;
    int n;//cantidad de lugares ocupados en el nodo
}
    *root = nullptr, *node = nullptr, *nodoRoot = nullptr;
BpTreeNode * init()
{
    int numHijos = grado;
    node = new BpTreeNode;
    node->data = new int[cantClaves];
    node->child_ptr = new BpTreeNode *[numHijos];
    node->leaf = true;
    node->n = 0;
    for (int i = 0; i < grado; i++){
        node->child_ptr[i] = nullptr;
    }
    return node;
}
void print_tree(BpTreeNode* p)
{
    int i;
    cout<<endl;
    for (i = 0; i < p->n; i++)
    {
        cout<<"  ";
        if (p->leaf == false)
        {
            print_tree(p->child_ptr[i]);
        }

        cout << p->data[i];
    }

    if (p->leaf == false)
    {
        print_tree(p->child_ptr[i]);
    }
    cout<<endl;
}

void sort(int *node, int lugaresOcupados)
{
    int i, j, temp;
    for (i = 0; i < lugaresOcupados; i++)
    {
        for (j = i; j <= lugaresOcupados; j++)
        {
            if (node[i] > node[j]){
                temp = node[i];
                node[i] = node[j];
                node[j] = temp;
            }
        }
    }
}

int search_middle(BpTreeNode *nodo, int valIngresado, int *midpX, int *posMedio, int *separar){
    // la variable "valIngresado" es el valor a ingresar en el nodo, que desencadena la separacion del nodo.
    //si el grado de variable es 3 (2 claves).
    /* la variable "midpX", indica a la funcion split_child si el valor medio estaba en nodo , o si es el
     valor nuevo ingresado es el valor medio.
     midpX= 1 indica que el elemento medio pertenece a nodo
     midpX= -1 indica que el elemento medio NO pertenece a nodo
     */
    //la variable "posMedio" indica la posicion del valor medio en caso de este pertenecer a nodo.

    int middle;
    if (cantClaves==2)/*GRADO 3*/ {
        if (valIngresado < nodo->data[0]){
            middle = nodo->data[0];
            *posMedio=0;
            *midpX=1;
            return middle;
        }
        if(nodo->data[0] < valIngresado && valIngresado < nodo->data[1]){
            middle = valIngresado;
            *separar= 0;
            *midpX=-1;
            return middle;
        }
        if(nodo->data[1] < valIngresado){
            middle = nodo->data[1];
            *posMedio=1;
            *midpX=1;
            return middle;
        }
    }
    else if(cantClaves==3)/*GRADO 4*/{
        if(valIngresado < nodo->data[0] || valIngresado < nodo->data[1]){
            middle = nodo->data[1];
            *posMedio=1;
            *midpX=1;
            return middle;
        }
        if(nodo->data[1] < valIngresado && valIngresado < nodo->data[2]){
            middle = valIngresado;
            *separar= 1;
            *midpX=-1;
            return middle;
        }
        if(nodo->data[2] < valIngresado){
            middle = nodo->data[2];
            *posMedio=2;
            *midpX=1;
            return middle;
        }
    }
    else if (cantClaves==4)/*GRADO 5*/{
        if(valIngresado < nodo->data[0] || valIngresado < nodo->data[1]){
            middle = nodo->data[1];
            *posMedio=1;
            *midpX=1;
            return middle;
        }
        if(nodo->data[1] < valIngresado && valIngresado < nodo->data[2]){
            middle = valIngresado;
            *separar= 1;
            *midpX=-1;
            return middle;
        }
        if(nodo->data[2] < valIngresado || nodo->data[3] < valIngresado) {
            middle = nodo->data[2];
            *posMedio=2;
            *midpX=1;
            return middle;
        }
    }
    else if (cantClaves==5)/*GRADO 6*/{
        if(valIngresado < nodo->data[0] || valIngresado < nodo->data[1] || valIngresado < nodo->data[2]){
            middle = nodo->data[2];
            *posMedio=2;
            *midpX=1;
            return middle;
        }
        if(nodo->data[2] < valIngresado && valIngresado < nodo->data[3]){
            middle = valIngresado;
            *separar= 3;
            *midpX=-1;
            return middle;
        }
        if(nodo->data[3] < valIngresado || nodo->data[4] < valIngresado) {
            middle = nodo->data[3];
            *posMedio=3;
            *midpX=1;
            return middle;
        }
    }
}

int split_child(BpTreeNode *nodoOriginal, int i, int valIngresado)
{
    int j, mid;
    BpTreeNode *padre, *hijoMenor, *hijoMayor, *y;
    int midpX=0;  //parametro numero 3 de search_middle
    int posMedio=0;   //posicion del elemento medio
    int separar=0;  //para separar desde un cierto elemento cuando el elemento medio no pertenece a nodoOriginal
    int separarDesde = search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar);

    if (i == -1) //si hay que separar un nodo, dado que esta lleno y es una hoja, sin padre
    {
        cout << "\nEl elemento medio es:" << search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar) << endl;
        mid = search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar);

        if (midpX == -1)/*si el elemento a insertar NO pertenece a NodoOriginal*/ {
            cout << "El elemento medio NO pertenece a X";
            padre = init();
            padre->leaf = false;
            hijoMenor = init();
            hijoMenor->leaf = true;
            hijoMayor = init();
            hijoMayor->leaf = true;

            //bucle para rellenar el hijo menor (hijo Izquierdo)
            cout << endl << "El hijo menor es: ";
            for (j = 0; j < separar; j++) {
                hijoMenor->data[j] = nodoOriginal->data[j];
                hijoMenor->child_ptr[j] = nodoOriginal->child_ptr[j];
                hijoMenor->n++;
                cout << " " << hijoMenor->data[j];
            }
            //bucle para rellenar el hijo mayor (hijo Derecho)
            cout << endl << "El hijo mayor es: ";
            for (j = separar; j < cantClaves; j++) {
                hijoMayor->data[j - separar] = nodoOriginal->data[j];
                hijoMayor->child_ptr[j - separar] = nodoOriginal->child_ptr[j];
                hijoMayor->n++;
                cout << " " << hijoMayor->data[j - separar];
            }
            cout << endl << endl;
            padre->data[padre->n] = mid;
            padre->child_ptr[padre->n] = hijoMenor;
            padre->child_ptr[padre->n + 1] = hijoMayor;
            padre->n++;
            root = padre;
        }

        if (midpX == 1) /*si el elemento a insertar pertenece a nodoOriginal*/
        {
            cout << "El elemento medio pertenece a X\n";
            padre = init();
            padre->leaf = false;
            hijoMenor = init();
            hijoMenor->leaf = true;
            hijoMayor = init();
            hijoMayor->leaf = true;

            //bucle para rellenar el hijo menor (hijo Izquierdo)
            for (j = 0; j < posMedio; j++) {
                hijoMenor->data[j] = nodoOriginal->data[j];
                hijoMenor->child_ptr[j] = nodoOriginal->child_ptr[j];
                hijoMenor->n++;
            }
            if(valIngresado < nodoOriginal->data[posMedio]){
                hijoMenor->data[hijoMenor->n] = valIngresado;
                sort(hijoMenor->data,hijoMenor->n);
                hijoMenor->n++;
            }
            cout << endl << "El hijo menor es: ";
            for(j=0;j < hijoMenor->n;j++){
                cout << " " << hijoMenor->data[j];
            }

            //bucle para rellenar el hijo mayor (hijo Derecho)
            for (j = posMedio+1; j < cantClaves; j++) {
                hijoMayor->data[j - posMedio-1] = nodoOriginal->data[j];
                hijoMayor->child_ptr[j - posMedio-1] = nodoOriginal->child_ptr[j];
                hijoMayor->n++;
            }
            if(nodoOriginal->data[posMedio] < valIngresado){
                hijoMayor->data[hijoMayor->n] = valIngresado;
                sort(hijoMayor->data,hijoMayor->n);
                hijoMayor->n++;
            }
            cout << endl << "El hijo mayor es: ";
            for(j=0;j < hijoMayor->n;j++){
                cout << " " << hijoMayor->data[j];
            }
            cout << endl << endl;

            padre->data[padre->n] = mid;
            padre->n++;
            padre->child_ptr[padre->n] = hijoMenor;
            padre->child_ptr[padre->n + 1] = hijoMayor;
            root = padre;
        }
    }
    else
    {
        /*FALTA HACERLA CORRECTAMENTE*/
        hijoMenor=init();
        y = nodoOriginal->child_ptr[i];
        mid = y->data[separarDesde];
        y->data[separarDesde] = 0;
        y->n--;
        for (j = separarDesde+1; j < 5; j++)
        {
            hijoMenor->data[j - separarDesde-1] = y->data[j];
            hijoMenor->n++;
            y->data[j] = 0;
            y->n--;
        }
        nodoOriginal->child_ptr[i + 1] = y;
        nodoOriginal->child_ptr[i + 1] = hijoMenor;
    }
    return mid;

}
void insert(int valIngresado)
{
    int i, valorNuevoEnPadre;
    nodoRoot = root;
    if (nodoRoot == nullptr)
    {
        root = init();
        nodoRoot = root;
    }
    else
    {
        if (nodoRoot->leaf == true && nodoRoot->n == 5)
        {

            valorNuevoEnPadre = split_child(nodoRoot, -1, valIngresado);
            nodoRoot = root;
            for (i = 0; i < (nodoRoot->n); i++)
            {
                if ((nodoRoot->data[i] < valIngresado) && (valIngresado < nodoRoot->data[i + 1]))
                {
                    i++;
                    break;
                }
                else if (valIngresado < nodoRoot->data[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            nodoRoot = nodoRoot->child_ptr[i];
            insert(valorNuevoEnPadre);
            return;
        }
        else
        {
            while (nodoRoot->leaf == false)
            {
                for (i = 0; i < (nodoRoot->n); i++)
                {
                    if ((valIngresado > nodoRoot->data[i]) && (valIngresado < nodoRoot->data[i + 1]))
                    {
                        i++;
                        break;
                    }
                    else if (valIngresado < nodoRoot->data[0])
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if ((nodoRoot->child_ptr[i])->n == 5)
                {
                    valorNuevoEnPadre = split_child(nodoRoot, 1, valIngresado);
                    nodoRoot->data[nodoRoot->n] = valorNuevoEnPadre;
                    nodoRoot->n++;
                    insert(valorNuevoEnPadre);
                    continue;
                }
                else
                {
                    nodoRoot = nodoRoot->child_ptr[i];

                }
            }
        }
    }
    nodoRoot->data[nodoRoot->n] = valIngresado;
    sort(nodoRoot->data, nodoRoot->n);
    nodoRoot->n++;
}

int main()
{
    int cantidadElementos, ValorIngresado;
    cout<<"Ingresar cantidad de elementos a insertar: ";
    cin>>cantidadElementos;
    for(int i = 0; i < cantidadElementos; i++)
    {
        cout << "Ingresar valor: ";
        cin >> ValorIngresado;
        insert(ValorIngresado);
    }
    cout << "Arbol trasversal:";
    print_tree(root);
    //getch();
}