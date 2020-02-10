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
    void test_getPadre() {
        cout << "\nArbol de prueba de grado 4, setear el grado en ese valor o valor mayor\n";
        cout << "\nPROBAMOS LA FUNCION PRINT_TREE"<<endl<<"Haremos el siguiente BpTree hardcodeado:" << endl<<endl;
        cout << "| 40 |" << endl;
        cout << "| 20 30 | | 50  60 |" << endl;
        cout << "| 10 15 | | 20 25 | | 30 35 | | 40 45 | | 50 55 | | 60 65 |" << endl;
        cout<<"grado escogido: "<<grado<<endl;

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

        cout<<"\n----------------------ARBOL----------------------\n";
        _printTree(pruebaNodoRoot);

        cout<<"\n----------------------ALTURA DEL ARBOL ----------------------\n";
        cout << "Altura esperada: 3" << endl;
        cout << "Altura obtenida: " << _getHeight(pruebaNodoRoot) << endl;

        cout << "---------- Funcion getPadre ----------" <<endl;

        BpTreeNode *resultadoBusqueda1 = getPadre(pruebaNodoRoot, pruebaNodoHoja5,false);
        cout << "Resultado esperado: "  << endl;
        pruebaNodoRama2->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda1 == nullptr) cout<<"No se encontro nodo hijo\n";
        else resultadoBusqueda1->print();

        BpTreeNode *resultadoBusqueda2 = getPadre(pruebaNodoRoot, pruebaNodoHoja2,false);
        cout << "\nResultado esperado: "  << endl;
        pruebaNodoRama1->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda2 == nullptr) cout<<"No se encontro nodo hijo\n";
        else resultadoBusqueda2->print();

        BpTreeNode *resultadoBusqueda3 = getPadre(pruebaNodoRoot, pruebaNodoHoja4,false);
        cout << "\nResultado esperado: "  << endl;
        pruebaNodoRama2->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda3 == nullptr) cout<<"No se encontro nodo hijo\n";
        else resultadoBusqueda3->print();

        /************************************PRUEBAS**************************************************/
    }
    void test_valorMedioPerteneceANodo(){
        cout<<"\nIngresar grado 6\n";

        int valorMedio1=22;
        //Ingreso valor 22;
        BpTreeNode *pruebaNodo1;
        pruebaNodo1=crearNodoVacio();
        pruebaNodo1->data[0]=10;
        pruebaNodo1->data[1]=15;
        pruebaNodo1->data[2]=20;
        pruebaNodo1->data[3]=25;
        pruebaNodo1->n= 4;
        for(int i=0;i<cantClaves;i++){pruebaNodo1->child_ptr[i]= nullptr;}
        pruebaNodo1->leaf= true;

        int valorMedio2=5;
        //Ingreso valor 2
        BpTreeNode *pruebaNodo2;
        pruebaNodo2=crearNodoVacio();
        pruebaNodo2->data[0]=1;
        pruebaNodo2->data[1]=3;
        pruebaNodo2->data[2]=5;
        pruebaNodo2->data[3]=7;
        pruebaNodo2->data[4]=9;
        pruebaNodo2->n= 5;
        for(int i=0;i<cantClaves;i++){pruebaNodo2->child_ptr[i]= nullptr;}
        pruebaNodo2->leaf= true;

        cout<<"****************************************\n";
        cout<<"Nodo: ";
        pruebaNodo1->print();
        cout << "Valor Insertado: 22";
        cout << "\nEn este caso el valor Medio es el: 22";
        cout<<"\n----------------------------\n";
        cout << "El Valor Medio pertenece al nodo?\n";
        cout<<"bool esperado: false\n";
        cout<<"bool obtenido: ";
        if(valorMedioPerteneceANodo(pruebaNodo1, valorMedio1) == true){
            cout<<"true\n";
        }
        else cout<<"false\n";
        cout<<"****************************************\n";

        cout<<"****************************************\n";
        cout<<"Nodo: ";
        pruebaNodo2->print();
        cout << "Valor Insertado: 2";
        cout << "\nEn este caso el valor Medio es el: 5";
        cout<<"\n----------------------------\n";
        cout << "El Valor Medio pertenece al nodo?\n";
        cout<<"bool esperado: true\n";
        cout<<"bool obtenido: ";
        if(valorMedioPerteneceANodo(pruebaNodo2, valorMedio2) == true){
            cout<<"true\n";
        }
        else cout<<"false\n";
        cout<<"****************************************\n";

    }
    void test_posicionDelElementoMedio(){
        cout<< "\n--------------TEST POSICION ELEMENTO MEDIO--------------\nTest para grado 5 y 6.\n";

        if(grado==5){
            int valorInsertado1=2; //Inserto el valor 2
            BpTreeNode *pruebaNodo1;
            pruebaNodo1=crearNodoVacio();
            pruebaNodo1->data[0]=3;
            pruebaNodo1->data[1]=5;
            pruebaNodo1->data[2]=12;
            pruebaNodo1->data[3]=25;
            pruebaNodo1->n= 4;
            for(int i=0;i<cantClaves;i++){pruebaNodo1->child_ptr[i]= nullptr;}
            pruebaNodo1->leaf= true;
            int valorInsertado2=20; //Inserto el valor 20
            BpTreeNode *pruebaNodo2;
            pruebaNodo2=crearNodoVacio();
            pruebaNodo2->data[0]=12;
            pruebaNodo2->data[1]=18;
            pruebaNodo2->data[2]=35;
            pruebaNodo2->data[3]=68;
            pruebaNodo2->n= 4;
            for(int i=0;i<cantClaves;i++){pruebaNodo2->child_ptr[i]= nullptr;}
            pruebaNodo2->leaf= true;

            cout<<"\n****************************************\n";
            cout<< "Nodo: ";
            pruebaNodo1->print();
            cout<< "\nValor insertado: 2\n";
            cout<< "En este caso el Valor Medio es: 5";
            cout<<"\n----------------------------\n";
            cout<<"posicion esperada del elemento Medio: 1\n";
            cout<<"posicion obtenida del elemento Medio: ";
            cout<<posicionDelElementoMedio(pruebaNodo1,valorInsertado1);
            cout<<"\n****************************************\n";
            cout<<"\n****************************************\n";
            cout<< "Nodo: ";
            pruebaNodo2->print();
            cout<< "\nValor insertado: 20\n";
            cout<< "En este caso el Valor Medio es: 20\nEl elemento medio no pertence a Nodo";
            cout<<"\n----------------------------\n";
            cout<<"posicion esperada del elemento Medio: 2\n";
            cout<<"posicion obtenida del elemento Medio: ";
            cout<<posicionDelElementoMedio(pruebaNodo2,valorInsertado2);
            cout<<"\n****************************************\n";
        }

        if (grado == 6){
            int valorInsertado3=122; //Inserto el valor 24
            BpTreeNode *pruebaNodo3;
            pruebaNodo3=crearNodoVacio();
            pruebaNodo3->data[0]=2;
            pruebaNodo3->data[1]=8;
            pruebaNodo3->data[2]=15;
            pruebaNodo3->data[3]=34;
            pruebaNodo3->data[4]=77;
            pruebaNodo3->n= 5;
            for(int i=0;i<cantClaves;i++){pruebaNodo3->child_ptr[i]= nullptr;}
            pruebaNodo3->leaf= true;

            cout<<"\n****************************************\n";
            cout<< "Nodo: ";
            pruebaNodo3->print();
            cout<< "\nValor insertado: 122\n";
            cout<< "En este caso el Valor Medio es: 34";
            cout<<"\n----------------------------\n";
            cout<<"posicion esperada del elemento Medio: 3\n";
            cout<<"posicion obtenida del elemento Medio: ";
            cout<<posicionDelElementoMedio(pruebaNodo3,valorInsertado3);
            cout<<"\n****************************************\n";
        }
        if(grado == 3){
            int valorInsertado4=3; //Inserto el valor 3
            BpTreeNode *pruebaNodo4;
            pruebaNodo4=crearNodoVacio();
            pruebaNodo4->data[0]=2;
            pruebaNodo4->data[1]=8;
            pruebaNodo4->n = 2;
            for(int i=0;i<cantClaves;i++){pruebaNodo4->child_ptr[i]= nullptr;}
            pruebaNodo4->leaf= true;

            cout<<"\n****************************************\n";
            cout<< "Nodo: ";
            pruebaNodo4->print();
            cout<< "\nValor insertado: 3\n";
            cout<< "En este caso el Valor Medio es: 3";
            cout<<"\n----------------------------\n";
            cout<<"posicion esperada del elemento Medio: 1\n";
            cout<<"posicion obtenida del elemento Medio: ";
            cout<<posicionDelElementoMedio(pruebaNodo4,valorInsertado4);
            cout<<"\n****************************************\n";
        }


    }
    void test_buscarMedio(){
        cout<<"--------------TEST BUSCAR MEDIO--------------\n";

        if (grado==6){
            int valorInsertado1= 13; //Inserto el valor 13
            BpTreeNode *pruebaNodo1;
            pruebaNodo1=crearNodoVacio();
            pruebaNodo1->data[0] = 3;
            pruebaNodo1->data[1] = 5;
            pruebaNodo1->data[2] = 12;
            pruebaNodo1->data[3] = 77;
            pruebaNodo1->data[4] = 25;
            pruebaNodo1->n = 5;
            for(int i=0;i<cantClaves;i++){pruebaNodo1->child_ptr[i]= nullptr;}
            pruebaNodo1->leaf= true;

            int valorInsertado4= 7; //Inserto el valor 7
            BpTreeNode *pruebaNodo4;
            pruebaNodo4=crearNodoVacio();
            pruebaNodo4->data[0] = 3;
            pruebaNodo4->data[1] = 8;
            pruebaNodo4->data[2] = 2;
            pruebaNodo4->data[3] = 4;
            pruebaNodo4->data[4] = 1;
            pruebaNodo4->n = 5;
            for(int i=0;i<cantClaves;i++){pruebaNodo4->child_ptr[i]= nullptr;}
            pruebaNodo4->leaf= true;

            cout<<"****************************************\n";
            cout<< "Nodo Original: ";
            pruebaNodo1->print();
            cout<<"Se inserta el valor: 13\n";
            cout<<"---------------------------\n";
            cout<<"nodo esperado: | 3 5 12 13 25 77 |\n";
            cout<<"nodo obtenido: ";
            cout<<buscarMedio(pruebaNodo1, valorInsertado1);
            cout<<"\nValor medio esperado: 13\n";
            cout<<"****************************************\n";

            cout<<"****************************************\n";
            cout<< "Nodo Original: ";
            pruebaNodo4->print();
            cout<<"Se inserta el valor: 7\n";
            cout<<"---------------------------\n";
            cout<<"nodo esperado: | 1 2 3 4 7 8 |\n";
            cout<<"nodo obtenido: ";
            cout<<buscarMedio(pruebaNodo4, valorInsertado4);
            cout<<"\nValor medio esperado: 4\n";
            cout<<"****************************************\n";
        }

        if (grado==5){

            int valorInsertado2= 65; //Inserto el valor 65
            BpTreeNode *pruebaNodo2;
            pruebaNodo2=crearNodoVacio();
            pruebaNodo2->data[0] = 15;
            pruebaNodo2->data[1] = 44;
            pruebaNodo2->data[2] = 12;
            pruebaNodo2->data[3] = 52;
            pruebaNodo2->n = 4;
            for(int i=0;i<cantClaves;i++){pruebaNodo2->child_ptr[i]= nullptr;}
            pruebaNodo2->leaf= true;

            cout<<"****************************************\n";
            cout<< "Nodo Original: ";
            pruebaNodo2->print();
            cout<<"Se inserta el valor: 65\n";
            cout<<"---------------------------\n";
            cout<<"nodo esperado: | 12 15 44 52 65 |\n";
            cout<<"nodo obtenido: ";
            cout<<buscarMedio(pruebaNodo2, valorInsertado2);
            cout<<"\nValor medio esperado: 44\n";
            cout<<"****************************************\n";
        }
        if (grado==4){
            int valorInsertado3= 22; //Inserto el valor 22
            BpTreeNode *pruebaNodo3;
            pruebaNodo3=crearNodoVacio();
            pruebaNodo3->data[0] = 15;
            pruebaNodo3->data[1] = 44;
            pruebaNodo3->data[2] = 12;
            pruebaNodo3->n = 3;
            for(int i=0;i<cantClaves;i++){pruebaNodo3->child_ptr[i]= nullptr;}
            pruebaNodo3->leaf= true;

            cout<<"****************************************\n";
            cout<< "Nodo Original: ";
            pruebaNodo3->print();
            cout<<"Se inserta el valor: 22\n";
            cout<<"---------------------------\n";
            cout<<"nodo esperado: | 12 15 22 44 |\n";
            cout<<"nodo obtenido: ";
            cout<<buscarMedio(pruebaNodo3, valorInsertado3);
            cout<<"\nValor medio esperado: 22\n";
            cout<<"****************************************\n";
        }
        if(grado == 3){
            int valorInsertado3= 61; //Inserto el valor 61
            BpTreeNode *pruebaNodo3;
            pruebaNodo3=crearNodoVacio();
            pruebaNodo3->data[0] = 15;
            pruebaNodo3->data[1] = 38;
            pruebaNodo3->n = 2;
            for(int i=0;i<cantClaves;i++){pruebaNodo3->child_ptr[i]= nullptr;}
            pruebaNodo3->leaf= true;

            cout<<"****************************************\n";
            cout<< "Nodo Original: ";
            pruebaNodo3->print();
            cout<<"Se inserta el valor: 61\n";
            cout<<"---------------------------\n";
            cout<<"nodo esperado: | 15 38 61 |\n";
            cout<<"nodo obtenido: ";
            cout<<buscarMedio(pruebaNodo3, valorInsertado3);
            cout<<"\nValor medio esperado: 38\n";
            cout<<"****************************************\n";
        }
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
    int getChildCount(BpTreeNode *node) {
        int i = 0;
        while (true) {
            if (node->child_ptr[i] == nullptr) return i;
            i++;
        }
    }
    void sort(int *nodo, int lugaresOcupados)
    {
        int i, j, temp;
        for (i = 0; i < lugaresOcupados; i++)
        {
            for (j = i; j < lugaresOcupados; j++)
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
    BpTreeNode* getPadre(BpTreeNode* nodoRoot, BpTreeNode* nodoABuscar, bool recursiveCall) {
        int cantHijos = getChildCount(nodoRoot);
        static BpTreeNode* nodoEncontrado;
        if (recursiveCall == false) nodoEncontrado = nullptr;
        if(nodoEncontrado == nullptr) {
            for (int i = 0; i < cantHijos; i++) {
                if (nodoRoot->child_ptr[i] == nodoABuscar) nodoEncontrado = nodoRoot;
                else getPadre(nodoRoot->child_ptr[i], nodoABuscar, true);
            }
        }
        return nodoEncontrado;
    }


    void organizarPunterosHijosDePadre(BpTreeNode* padre, vector<BpTreeNode*> hijos) {

    }

    int split_child(BpTreeNode *nodoOriginal, int i, int valIngresado)
    {
        int j, mid;
        BpTreeNode *padre, *hijoMenor, *hijoMayor, *y;
        int midpX=0;  //parametro numero 3 de search_middle
        int posMedio=0;   //posicion del elemento medio cuando este pertenece al nodoOriginal
        int separar=0;  //para separar desde un cierto elemento cuando el elemento medio no pertenece a nodoOriginal
        int separarDesde = buscarMedio(nodoOriginal, valIngresado);

        if (i == -1) //si hay que separar un nodo, dado que esta lleno y es una hoja, sin padre
        {
            cout << "\nEl elemento medio es:" << buscarMedio(nodoOriginal, valIngresado) << endl;
            mid = buscarMedio(nodoOriginal, valIngresado);
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

    bool valorMedioPerteneceANodo(BpTreeNode* nodo, int valorMedio){
        for (int i = 0; i < cantClaves ; ++i) {
            if(nodo->data[i] == valorMedio){
                return true;
            }
        }
        return false;
    }

    int posicionDelElementoMedio(BpTreeNode* nodo, int valorNuevoInsertado){
        int valorMedio = buscarMedio(nodo, valorNuevoInsertado);
        if(valorMedioPerteneceANodo(nodo,valorMedio) == true){
            for (int i = 0; i < cantClaves ; ++i) {
                if(nodo->data[i] == valorMedio){
                    return i;
                }
            }
        }
        else{
            for (int i = 0; i < cantClaves ; ++i) {
                if(valorNuevoInsertado <= nodo->data[i]){
                    return i;
                }
            }
        }
    }

    int buscarMedio(BpTreeNode* nodo, int valorNuevoInsertado){
        int tamanioNodoNuevo = cantClaves + 1;
        int nodoNuevo[tamanioNodoNuevo];//Este nodo contendra el nodo + valorNuevoInsertado
        for (int i = 0; i < cantClaves ; ++i) {
            nodoNuevo[i] = nodo->data[i];
        }
        nodoNuevo[tamanioNodoNuevo-1] = valorNuevoInsertado;
        sort(nodoNuevo, tamanioNodoNuevo);
        /*cout <<"|";
        for (int j = 0; j < cantClaves+1 ; ++j) {
            cout <<" "<<nodoNuevo[j];
        }
        cout <<" |\n";*/
        int valorMedio = (tamanioNodoNuevo)/2;
        //cout<<"Valor medio obtenido: ";
        return nodoNuevo[valorMedio];
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
