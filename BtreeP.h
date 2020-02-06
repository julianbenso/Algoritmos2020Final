//
// Created by julian on 6/2/20.
//

#ifndef FINAL2_BTREEP_H
#define FINAL2_BTREEP_H

#include<stdio.h>
#include<iostream>
#include <iomanip>
#include <vector>
using namespace std;

class BtreeP {
public:
    BtreeP(int grado)  {
        this->grado = grado;
        this->cantClaves = grado - 1;
    }

    struct BpTreeNode
    {
        int *data; // NO SE PUEDEN INSERTAR CEROS 0, no se va a imprimir
        BpTreeNode **child_ptr;
        bool leaf;
        int n;//cantidad de lugares ocupados en el nodo
        void print() {
            cout << "|";
            for (int i = 0; i < n; i++) {
                cout << " " <<  data[i];
            }
            cout << "|"<<endl;
        }
    };
    int getHeight() {
        return _getHeight(root);
    }
    void insert(int numeroAInsertar) {
        _insert(numeroAInsertar,root);
    }

    void printTree() {
        _printTree(root);
    }
    void splitChildTest() {
        cout << "PROBAMOS LA FUNCION PRINT_TREE"<<endl<<"Haremos el siguiente BpTree hardcodeado:" << endl<<endl;
        cout << "| 40 |" << endl<<endl;
        cout << "| 20 30 | | 50  60 |" << endl<<endl;
        cout << "| 10 15 | | 20 25 | | 30 35 | | 40 45 | | 50 55 | | 60 65 |" << endl;
        cout<<"grado: "<<grado<<endl;

        BpTreeNode *pruebaNodoHoja1;
        pruebaNodoHoja1=crearNodoVacio();
        pruebaNodoHoja1->data[0]=10;
        pruebaNodoHoja1->data[1]=15;
        pruebaNodoHoja1->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja1->child_ptr[i]= nullptr;}
        pruebaNodoHoja1->leaf= true;

        BpTreeNode *pruebaNodoHoja2;
        pruebaNodoHoja2=crearNodoVacio();
        pruebaNodoHoja2->data[0]= 20;
        pruebaNodoHoja2->data[1]= 25;
        pruebaNodoHoja2->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja2->child_ptr[i]= nullptr;}
        pruebaNodoHoja2->leaf= true;

        BpTreeNode *pruebaNodoHoja3;
        pruebaNodoHoja3=crearNodoVacio();
        pruebaNodoHoja3->data[0]= 30;
        pruebaNodoHoja3->data[1]= 35;
        pruebaNodoHoja3->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja3->child_ptr[i]= nullptr;}
        pruebaNodoHoja3->leaf= true;

        BpTreeNode *pruebaNodoHoja4;
        pruebaNodoHoja4=crearNodoVacio();
        pruebaNodoHoja4->data[0]= 40;
        pruebaNodoHoja4->data[1]= 45;
        pruebaNodoHoja4->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja4->child_ptr[i]= nullptr;}
        pruebaNodoHoja4->leaf= true;

        BpTreeNode *pruebaNodoHoja5;
        pruebaNodoHoja5=crearNodoVacio();
        pruebaNodoHoja5->data[0]= 50;
        pruebaNodoHoja5->data[1]= 55;
        pruebaNodoHoja5->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja5->child_ptr[i]= nullptr;}
        pruebaNodoHoja5->leaf= true;

        BpTreeNode *pruebaNodoHoja6;
        pruebaNodoHoja6=crearNodoVacio();
        pruebaNodoHoja6->data[0]= 60;
        pruebaNodoHoja6->data[1]= 65;
        pruebaNodoHoja6->n= 2;
        for(int i=0;i<cantClaves;i++){pruebaNodoHoja6->child_ptr[i]= nullptr;}
        pruebaNodoHoja6->leaf= true;

        BpTreeNode *pruebaNodoRama1;
        pruebaNodoRama1=crearNodoVacio();
        pruebaNodoRama1->data[0]= 20;
        pruebaNodoRama1->data[1]= 30;
        pruebaNodoRama1->n= 2;
        pruebaNodoRama1->child_ptr[0]= pruebaNodoHoja1;
        pruebaNodoRama1->child_ptr[1]= pruebaNodoHoja2;
        pruebaNodoRama1->child_ptr[2]= pruebaNodoHoja3;
        pruebaNodoRama1->child_ptr[3]= nullptr;
        pruebaNodoRama1->leaf= false;

        BpTreeNode *pruebaNodoRama2;
        pruebaNodoRama2=crearNodoVacio();
        pruebaNodoRama2->data[0]= 50;
        pruebaNodoRama2->data[1]= 60;
        pruebaNodoRama2->n= 2;
        pruebaNodoRama2->child_ptr[0]= pruebaNodoHoja4;
        pruebaNodoRama2->child_ptr[1]= pruebaNodoHoja5;
        pruebaNodoRama2->child_ptr[2]= pruebaNodoHoja6;
        pruebaNodoRama2->child_ptr[3]= nullptr;
        pruebaNodoRama2->leaf= false;

        BpTreeNode *pruebaNodoRoot;
        pruebaNodoRoot=crearNodoVacio();
        pruebaNodoRoot->data[0]= 40;
        pruebaNodoRoot->n= 1;
        pruebaNodoRoot->child_ptr[0]= pruebaNodoRama1;
        pruebaNodoRoot->child_ptr[1]= pruebaNodoRama2;
        pruebaNodoRoot->child_ptr[2]= nullptr;
        pruebaNodoRoot->child_ptr[3]= nullptr;
        pruebaNodoRoot->leaf= false;

        cout<<"\n----------------------Arbol----------------------\n";
        //imprimir_arbolBenso(pruebaNodoRoot, nullptr);
        _printTree(pruebaNodoRoot);
        //printTree(pruebaNodoRoot);
        //print_tree(pruebaNodoRoot);


        cout<<"\n----------------------ALTURA DEL ARBOL ----------------------\n";
        cout << "Altura esperada: 3" << endl;
        cout << "Altura obtenida: " << _getHeight(pruebaNodoRoot) << endl;

        cout << "---------- Funcion getPadre ----------" <<endl;

        BpTreeNode *resultadoBusqueda1 = getPadre(pruebaNodoRoot, pruebaNodoHoja5);

        cout << "Resultado esperado: "  << endl;
        pruebaNodoRama2->print();
        cout << "Resultado obtenid0: " << endl;
        if (resultadoBusqueda1 == nullptr) cout<<"No se encontro nodo hijo";
        else resultadoBusqueda1->print();

        BpTreeNode *resultadoBusqueda2 = getPadre(pruebaNodoRoot, pruebaNodoHoja2);

        cout << "Resultado esperado: "  << endl;
        pruebaNodoRama1->print();
        cout << "Resultado obtenid0: " << endl;
        if (resultadoBusqueda2 == nullptr) cout<<"No se encontro nodo hijo";
        else resultadoBusqueda2->print();

        /************************************PRUEBAS**************************************************/
    }



private:
    BpTreeNode* root;
    int cantClaves, grado;
    BpTreeNode * crearNodoVacio()
    {
        int numHijos = grado;
        BpTreeNode *node = new BpTreeNode;
        node->data = new int[cantClaves];
        node->child_ptr = new BpTreeNode *[numHijos];
        node->leaf = true;
        node->n = 0;
        for (int i = 0; i < grado; i++){
            node->child_ptr[i] = nullptr;
        }
        return node;
    }
    int getChildCount(BpTreeNode *pNode) {
        int i = 0;
        while (true) {
            if (pNode->child_ptr[i] == nullptr) return i;
            i++;
        }
    }
    void sort(int *nodo, int lugaresOcupados)
    {
        int i, j, temp;
        for (i = 0; i < lugaresOcupados; i++)
        {
            for (j = i; j <= lugaresOcupados; j++)
            {
                if (nodo[i] > nodo[j]){
                    temp = nodo[i];
                    nodo[i] = nodo[j];
                    nodo[j] = temp;
                }
            }
        }
    }
    int _getHeight (BpTreeNode* heightRootNode)
    {
        int childCount = getChildCount(heightRootNode);
        if (getChildCount(heightRootNode) == 0) {
            return 1;
        }
        int alturas[childCount];
        for (int i = 0; i<childCount; i++) {
            alturas[i] = _getHeight(heightRootNode->child_ptr[i]);
        }
        int maxAltura = 0;
        for (int i = 0; i<childCount; i++) {
            if (alturas[i]>maxAltura) maxAltura = alturas[i];
        }
        return 1+maxAltura;
    }
    void traverse(BpTreeNode* printTreeNode, vector<vector<string>>& miLista){
        static int niveles = 0;
        miLista[niveles].push_back("|");
        for (int j = 0; j < printTreeNode->data[j] != 0; ++j) {
            int dataAInsertar = printTreeNode->data[j];
            miLista[niveles].push_back(to_string(dataAInsertar));
        }
        string hijos = "n="+to_string(printTreeNode->n)+"c=" + to_string(getChildCount(printTreeNode))+"|";
        miLista[niveles].push_back(hijos);
        if (getChildCount(printTreeNode) == 0) {
            return;
        }
        else {
            niveles++;
            for (int i = 0 ; printTreeNode->child_ptr[i] != nullptr; i++) {
                traverse(printTreeNode->child_ptr[i], miLista);
            }
            niveles--;
        }
    }
    void _printTree(BpTreeNode* printTreeNode) {
        vector<vector<string>> miLista;
        int altura = _getHeight(printTreeNode);
        for (int i = 0; i < altura ; i++) {
            miLista.push_back(vector<string>());
        }
        traverse(printTreeNode, miLista);

        for (int i = 0; i < miLista.size(); i++) {
            for (int j = 0; j < miLista[i].size(); j++) {
                cout << miLista[i][j]<<" ";
            }
            cout << endl;
        }
    }


    int split_child(BpTreeNode *nodoOriginal, int i, int valIngresado)
    {
        int j, mid;
        BpTreeNode *padre, *hijoMenor, *hijoMayor, *y;
        int midpX=0;  //parametro numero 3 de search_middle
        int posMedio=0;   //posicion del elemento medio cuando este pertenece al nodoOriginal
        int separar=0;  //para separar desde un cierto elemento cuando el elemento medio no pertenece a nodoOriginal
        int separarDesde = search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar);

        if (i == -1) //si hay que separar un nodo, dado que esta lleno y es una hoja, sin padre
        {
            cout << "\nEl elemento medio es:" << search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar) << endl;
            mid = search_middle(nodoOriginal, valIngresado, &midpX, &posMedio, &separar);
            padre = crearNodoVacio();
            padre->leaf = false;
            hijoMenor = crearNodoVacio();
            hijoMenor->leaf = true;
            hijoMayor = crearNodoVacio();
            hijoMayor->leaf = true;

            if (midpX == -1)/*si el elemento a insertar NO pertenece a NodoOriginal*/ {
                cout << "El elemento medio NO pertenece a X";

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
            hijoMenor= crearNodoVacio();
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

    bool perteneceAlNodo(int valorAIngresar, BpTreeNode* nodo) {

    }

    int getPosicionDeClaveAllevarAlPadre(BpTreeNode* nodo) {

    }

    void organizarPunterosHijosDePadre(BpTreeNode* padre, vector<BpTreeNode*> hijos) {

    }

    BpTreeNode* getPadre(BpTreeNode* nodoRoot, BpTreeNode* nodoABuscar) {
        int cantHijos = getChildCount(nodoRoot);
        static BpTreeNode* nodoEncontrado = nullptr;
        for (int i = 0; i< cantHijos; i++) {
            if (nodoRoot->child_ptr[i] == nodoABuscar) nodoEncontrado = nodoRoot;
            else getPadre(nodoRoot->child_ptr[i],nodoABuscar);
        }
        return nodoEncontrado;
    }


    int search_middle(BpTreeNode *nodo, int valIngresado, int *midpX, int *posMedio, int *separar){
        // la variable "valIngresado" es el valor a ingresar en el nodo, que desencadena la separacion del nodo.
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
        return 0;
    }

    void _insert(int valIngresado, BpTreeNode* nodoRoot)
    {
        int i, valorNuevoEnPadre;
        nodoRoot = root;
        if (nodoRoot == nullptr)
        {
            root = crearNodoVacio();
            nodoRoot = root;
        }
        else
        {
            if (nodoRoot->leaf == true && nodoRoot->n == cantClaves)
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
                _insert(valorNuevoEnPadre,nodoRoot);
                return;
            }
            else
            {
                while (nodoRoot->leaf == false)
                {
                    for (i = 0; i < (nodoRoot->n); i++)
                    {
                        if ((nodoRoot->data[i] < valIngresado ) && (valIngresado < nodoRoot->data[i + 1]))
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
                        _insert(valorNuevoEnPadre, nodoRoot);
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


};


#endif //FINAL2_BTREEP_H
