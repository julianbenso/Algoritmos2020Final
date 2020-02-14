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

    BtreeP(int grado) {
        this->grado = grado;
        this->cantClaves = grado - 1;
    }

    struct BpTreeNode {
        int *data; // NO SE PUEDEN INSERTAR CEROS 0, no se va a imprimir
        BpTreeNode **child_ptr;
        bool leaf;
        int n;//cantidad de lugares ocupados en el nodo
        void print() {
            cout << "|";
            for (int i = 0; i < n; i++) {
                cout << " " << data[i];
            }
            cout << " |" << endl;
        }

        bool isLeaf () {
            return getChildCount(this) == 0;
        }
    };

    int getHeight() {
        return _getHeight(root);
    }

    void insert(int numeroAInsertar) {
        if (root == nullptr) {
            root = crearNodoVacio();
            root->data[0] = numeroAInsertar;
            root->n++;
            root->leaf = true;
            cout << "Primer valor insertado en nodo" << endl;
        }
        else {
            BpTreeNode* nodoLeafDondeInsertar = buscarNodoEnDondeInsertarValorIngresado(root,numeroAInsertar,false);
            int clavesOcupadas = cantidadDeClavesOcupadas(nodoLeafDondeInsertar);
            if (clavesOcupadas < cantClaves) {
                nodoLeafDondeInsertar->data[clavesOcupadas] = numeroAInsertar;
                nodoLeafDondeInsertar->n++;
                sort(nodoLeafDondeInsertar->data,clavesOcupadas+1);
                cout << "Insertado y ordenado exitosamente" << endl;
            }
            else {
                // El nodo esta lleno
                int medio= separarNodo(root,nodoLeafDondeInsertar,numeroAInsertar,false);
                separarNodo(root,nodoLeafDondeInsertar,numeroAInsertar,false);
                nodoLeafDondeInsertar->n++;
                insert(medio);

            }
        }
    }

    void printTree() {
        _printTree(root);
    }

    void buscarValor(int elementoBuscado) {
        _buscarValor(root, elementoBuscado, false);
    }

    /********************FUNCIONES TEST********************/
    void test_printTree(){
        cout << "\n-------------TEST IMPRIMIR ARBOL-------------\n";
        cout << "Este test funciona para grado 5\n";

        if (grado == 5){

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 6;
            pruebaNodoHoja1->data[1] = 13;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 14;
            pruebaNodoHoja2->data[1] = 16;
            pruebaNodoHoja2->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 18;
            pruebaNodoHoja3->data[1] = 20;
            pruebaNodoHoja3->data[2] = 33;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 52;
            pruebaNodoHoja4->data[1] = 59;
            pruebaNodoHoja4->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 67;
            pruebaNodoHoja5->data[1] = 83;
            pruebaNodoHoja5->data[2] = 91;
            pruebaNodoHoja5->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoRoot1;
            pruebaNodoRoot1 = crearNodoVacio();
            pruebaNodoRoot1->data[0] = 14;
            pruebaNodoRoot1->data[1] = 18;
            pruebaNodoRoot1->data[2] = 52;
            pruebaNodoRoot1->data[3] = 67;
            pruebaNodoRoot1->n = 4;
            pruebaNodoRoot1->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRoot1->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRoot1->child_ptr[2] = pruebaNodoHoja3;
            pruebaNodoRoot1->child_ptr[3] = pruebaNodoHoja4;
            pruebaNodoRoot1->child_ptr[4] = pruebaNodoHoja5;
            pruebaNodoRoot1->leaf = false;


            cout << "*********************************************";
            cout << "\nSe crean el siguente arbol hardcodeado:\n";
            cout << "| 14 18 52 67 |" << endl;
            cout << "| 6 13 | | 14 16 | | 18 20 33 | | 52 59 | | 67 83 91 |\n";
            cout <<"\n-------------------------------------------------\n";
            cout <<" Arbol esperado:\n";
            cout << "| 14 18 52 67 n=4c=5|" << endl;
            cout << "| 6 13 n=2c=0| | 14 16 n=2c=0| | 18 20 33 n=3c=0| | 52 59 n=2c=0| | 67 83 91 n=3c=0|\n\n";
            cout << "Arbol Obtenido:\n";
            _printTree(pruebaNodoRoot1);
            cout << "\n*********************************************\n";
        }

    }

    void test_getPadre() {
        cout << "\nArbol de prueba de grado 4, setear el grado en ese valor o valor mayor\n";
        cout << "\nPROBAMOS LA FUNCION PRINT_TREE" << endl
             << "Haremos el siguiente BpTree hardcodeado:" << endl << endl;
        cout << "| 40 |" << endl;
        cout << "| 20 30 | | 50  60 |" << endl;
        cout << "| 10 15 | | 20 25 | | 30 35 | | 40 45 | | 50 55 | | 60 65 |" << endl;
        cout << "grado escogido: " << grado << endl;

        BpTreeNode *pruebaNodoHoja1;
        pruebaNodoHoja1 = crearNodoVacio();
        pruebaNodoHoja1->data[0] = 10;
        pruebaNodoHoja1->data[1] = 15;
        pruebaNodoHoja1->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
        pruebaNodoHoja1->leaf = true;

        BpTreeNode *pruebaNodoHoja2;
        pruebaNodoHoja2 = crearNodoVacio();
        pruebaNodoHoja2->data[0] = 20;
        pruebaNodoHoja2->data[1] = 25;
        pruebaNodoHoja2->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
        pruebaNodoHoja2->leaf = true;

        BpTreeNode *pruebaNodoHoja3;
        pruebaNodoHoja3 = crearNodoVacio();
        pruebaNodoHoja3->data[0] = 30;
        pruebaNodoHoja3->data[1] = 35;
        pruebaNodoHoja3->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
        pruebaNodoHoja3->leaf = true;

        BpTreeNode *pruebaNodoHoja4;
        pruebaNodoHoja4 = crearNodoVacio();
        pruebaNodoHoja4->data[0] = 40;
        pruebaNodoHoja4->data[1] = 45;
        pruebaNodoHoja4->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
        pruebaNodoHoja4->leaf = true;

        BpTreeNode *pruebaNodoHoja5;
        pruebaNodoHoja5 = crearNodoVacio();
        pruebaNodoHoja5->data[0] = 50;
        pruebaNodoHoja5->data[1] = 55;
        pruebaNodoHoja5->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
        pruebaNodoHoja5->leaf = true;

        BpTreeNode *pruebaNodoHoja6;
        pruebaNodoHoja6 = crearNodoVacio();
        pruebaNodoHoja6->data[0] = 60;
        pruebaNodoHoja6->data[1] = 65;
        pruebaNodoHoja6->n = 2;
        for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
        pruebaNodoHoja6->leaf = true;

        BpTreeNode *pruebaNodoRama1;
        pruebaNodoRama1 = crearNodoVacio();
        pruebaNodoRama1->data[0] = 20;
        pruebaNodoRama1->data[1] = 30;
        pruebaNodoRama1->n = 2;
        pruebaNodoRama1->child_ptr[0] = pruebaNodoHoja1;
        pruebaNodoRama1->child_ptr[1] = pruebaNodoHoja2;
        pruebaNodoRama1->child_ptr[2] = pruebaNodoHoja3;
        pruebaNodoRama1->child_ptr[3] = nullptr;
        pruebaNodoRama1->leaf = false;

        BpTreeNode *pruebaNodoRama2;
        pruebaNodoRama2 = crearNodoVacio();
        pruebaNodoRama2->data[0] = 50;
        pruebaNodoRama2->data[1] = 60;
        pruebaNodoRama2->n = 2;
        pruebaNodoRama2->child_ptr[0] = pruebaNodoHoja4;
        pruebaNodoRama2->child_ptr[1] = pruebaNodoHoja5;
        pruebaNodoRama2->child_ptr[2] = pruebaNodoHoja6;
        pruebaNodoRama2->child_ptr[3] = nullptr;
        pruebaNodoRama2->leaf = false;

        BpTreeNode *pruebaNodoRoot;
        pruebaNodoRoot = crearNodoVacio();
        pruebaNodoRoot->data[0] = 40;
        pruebaNodoRoot->n = 1;
        pruebaNodoRoot->child_ptr[0] = pruebaNodoRama1;
        pruebaNodoRoot->child_ptr[1] = pruebaNodoRama2;
        pruebaNodoRoot->child_ptr[2] = nullptr;
        pruebaNodoRoot->child_ptr[3] = nullptr;
        pruebaNodoRoot->leaf = false;

        cout << "\n----------------------ARBOL----------------------\n";
        _printTree(pruebaNodoRoot);

        cout << "\n----------------------ALTURA DEL ARBOL ----------------------\n";
        cout << "Altura esperada: 3" << endl;
        cout << "Altura obtenida: " << _getHeight(pruebaNodoRoot) << endl;

        cout << "---------- Funcion getPadre ----------" << endl;

        BpTreeNode *resultadoBusqueda1 = getPadre(pruebaNodoRoot, pruebaNodoHoja5, false);
        cout << "Resultado esperado: " << endl;
        pruebaNodoRama2->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda1 == nullptr) cout << "No se encontro nodo hijo\n";
        else resultadoBusqueda1->print();

        BpTreeNode *resultadoBusqueda2 = getPadre(pruebaNodoRoot, pruebaNodoHoja2, false);
        cout << "\nResultado esperado: " << endl;
        pruebaNodoRama1->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda2 == nullptr) cout << "No se encontro nodo hijo\n";
        else resultadoBusqueda2->print();

        BpTreeNode *resultadoBusqueda3 = getPadre(pruebaNodoRoot, pruebaNodoHoja4, false);
        cout << "\nResultado esperado: " << endl;
        pruebaNodoRama2->print();
        cout << "Resultado obtenido: " << endl;
        if (resultadoBusqueda3 == nullptr) cout << "No se encontro nodo hijo\n";
        else resultadoBusqueda3->print();

        /************************************PRUEBAS**************************************************/
    }

    void test_valorMedioPerteneceANodo() {
        cout << "\nIngresar grado 6\n";

        int valorMedio1 = 22;
        //Ingreso valor 22;
        BpTreeNode *pruebaNodo1;
        pruebaNodo1 = crearNodoVacio();
        pruebaNodo1->data[0] = 10;
        pruebaNodo1->data[1] = 15;
        pruebaNodo1->data[2] = 20;
        pruebaNodo1->data[3] = 25;
        pruebaNodo1->n = 4;
        for (int i = 0; i < cantClaves; i++) { pruebaNodo1->child_ptr[i] = nullptr; }
        pruebaNodo1->leaf = true;

        int valorMedio2 = 5;
        //Ingreso valor 2
        BpTreeNode *pruebaNodo2;
        pruebaNodo2 = crearNodoVacio();
        pruebaNodo2->data[0] = 1;
        pruebaNodo2->data[1] = 3;
        pruebaNodo2->data[2] = 5;
        pruebaNodo2->data[3] = 7;
        pruebaNodo2->data[4] = 9;
        pruebaNodo2->n = 5;
        for (int i = 0; i < cantClaves; i++) { pruebaNodo2->child_ptr[i] = nullptr; }
        pruebaNodo2->leaf = true;

        cout << "****************************************\n";
        cout << "Nodo: ";
        pruebaNodo1->print();
        cout << "Valor Insertado: 22";
        cout << "\nEn este caso el valor Medio es el: 22";
        cout << "\n----------------------------\n";
        cout << "El Valor Medio pertenece al nodo?\n";
        cout << "bool esperado: false\n";
        cout << "bool obtenido: ";
        if (valorMedioPerteneceANodo(pruebaNodo1, valorMedio1) == true) {
            cout << "true\n";
        } else cout << "false\n";
        cout << "****************************************\n";

        cout << "****************************************\n";
        cout << "Nodo: ";
        pruebaNodo2->print();
        cout << "Valor Insertado: 2";
        cout << "\nEn este caso el valor Medio es el: 5";
        cout << "\n----------------------------\n";
        cout << "El Valor Medio pertenece al nodo?\n";
        cout << "bool esperado: true\n";
        cout << "bool obtenido: ";
        if (valorMedioPerteneceANodo(pruebaNodo2, valorMedio2) == true) {
            cout << "true\n";
        } else cout << "false\n";
        cout << "****************************************\n";

    }

    void test_posicionDelElementoMedio() {
        cout
                << "\n--------------TEST POSICION ELEMENTO MEDIO--------------\nTest para grado 5 y 6.\n";

        if (grado == 5) {
            int valorInsertado1 = 2; //Inserto el valor 2
            BpTreeNode *pruebaNodo1;
            pruebaNodo1 = crearNodoVacio();
            pruebaNodo1->data[0] = 3;
            pruebaNodo1->data[1] = 5;
            pruebaNodo1->data[2] = 12;
            pruebaNodo1->data[3] = 25;
            pruebaNodo1->n = 4;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo1->child_ptr[i] = nullptr; }
            pruebaNodo1->leaf = true;
            int valorInsertado2 = 20; //Inserto el valor 20
            BpTreeNode *pruebaNodo2;
            pruebaNodo2 = crearNodoVacio();
            pruebaNodo2->data[0] = 12;
            pruebaNodo2->data[1] = 18;
            pruebaNodo2->data[2] = 35;
            pruebaNodo2->data[3] = 68;
            pruebaNodo2->n = 4;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo2->child_ptr[i] = nullptr; }
            pruebaNodo2->leaf = true;

            cout << "\n****************************************\n";
            cout << "Nodo: ";
            pruebaNodo1->print();
            cout << "\nValor insertado: 2\n";
            cout << "En este caso el Valor Medio es: 5";
            cout << "\n----------------------------\n";
            cout << "posicion esperada del elemento Medio: 1\n";
            cout << "posicion obtenida del elemento Medio: ";
            cout << posicionDelElementoMedio(pruebaNodo1, valorInsertado1);
            cout << "\n****************************************\n";
            cout << "\n****************************************\n";
            cout << "Nodo: ";
            pruebaNodo2->print();
            cout << "\nValor insertado: 20\n";
            cout << "En este caso el Valor Medio es: 20\nEl elemento medio no pertence a Nodo";
            cout << "\n----------------------------\n";
            cout << "posicion esperada del elemento Medio: 2\n";
            cout << "posicion obtenida del elemento Medio: ";
            cout << posicionDelElementoMedio(pruebaNodo2, valorInsertado2);
            cout << "\n****************************************\n";
        }

        if (grado == 6) {
            int valorInsertado3 = 122; //Inserto el valor 24
            BpTreeNode *pruebaNodo3;
            pruebaNodo3 = crearNodoVacio();
            pruebaNodo3->data[0] = 2;
            pruebaNodo3->data[1] = 8;
            pruebaNodo3->data[2] = 15;
            pruebaNodo3->data[3] = 34;
            pruebaNodo3->data[4] = 77;
            pruebaNodo3->n = 5;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo3->child_ptr[i] = nullptr; }
            pruebaNodo3->leaf = true;

            cout << "\n****************************************\n";
            cout << "Nodo: ";
            pruebaNodo3->print();
            cout << "\nValor insertado: 122\n";
            cout << "En este caso el Valor Medio es: 34";
            cout << "\n----------------------------\n";
            cout << "posicion esperada del elemento Medio: 3\n";
            cout << "posicion obtenida del elemento Medio: ";
            cout << posicionDelElementoMedio(pruebaNodo3, valorInsertado3);
            cout << "\n****************************************\n";
        }
        if (grado == 3) {
            int valorInsertado4 = 3; //Inserto el valor 3
            BpTreeNode *pruebaNodo4;
            pruebaNodo4 = crearNodoVacio();
            pruebaNodo4->data[0] = 2;
            pruebaNodo4->data[1] = 8;
            pruebaNodo4->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo4->child_ptr[i] = nullptr; }
            pruebaNodo4->leaf = true;

            cout << "\n****************************************\n";
            cout << "Nodo: ";
            pruebaNodo4->print();
            cout << "\nValor insertado: 3\n";
            cout << "En este caso el Valor Medio es: 3";
            cout << "\n----------------------------\n";
            cout << "posicion esperada del elemento Medio: 1\n";
            cout << "posicion obtenida del elemento Medio: ";
            cout << posicionDelElementoMedio(pruebaNodo4, valorInsertado4);
            cout << "\n****************************************\n";
        }


    }

    void test_buscarMedio() {
        cout << "--------------TEST BUSCAR MEDIO--------------\n";

        if (grado == 6) {
            int valorInsertado1 = 13; //Inserto el valor 13
            BpTreeNode *pruebaNodo1;
            pruebaNodo1 = crearNodoVacio();
            pruebaNodo1->data[0] = 3;
            pruebaNodo1->data[1] = 5;
            pruebaNodo1->data[2] = 12;
            pruebaNodo1->data[3] = 77;
            pruebaNodo1->data[4] = 25;
            pruebaNodo1->n = 5;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo1->child_ptr[i] = nullptr; }
            pruebaNodo1->leaf = true;

            int valorInsertado4 = 7; //Inserto el valor 7
            BpTreeNode *pruebaNodo4;
            pruebaNodo4 = crearNodoVacio();
            pruebaNodo4->data[0] = 3;
            pruebaNodo4->data[1] = 8;
            pruebaNodo4->data[2] = 2;
            pruebaNodo4->data[3] = 4;
            pruebaNodo4->data[4] = 1;
            pruebaNodo4->n = 5;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo4->child_ptr[i] = nullptr; }
            pruebaNodo4->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo1->print();
            cout << "Se inserta el valor: 13\n";
            cout << "---------------------------\n";
            cout << "nodo esperado: | 3 5 12 13 25 77 |\n";
            cout << "nodo obtenido: ";
            cout << buscarMedio(pruebaNodo1, valorInsertado1);
            cout << "\nValor medio esperado: 13\n";
            cout << "****************************************\n";

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo4->print();
            cout << "Se inserta el valor: 7\n";
            cout << "---------------------------\n";
            cout << "nodo esperado: | 1 2 3 4 7 8 |\n";
            cout << "nodo obtenido: ";
            cout << buscarMedio(pruebaNodo4, valorInsertado4);
            cout << "\nValor medio esperado: 4\n";
            cout << "****************************************\n";
        }

        if (grado == 5) {

            int valorInsertado2 = 65; //Inserto el valor 65
            BpTreeNode *pruebaNodo2;
            pruebaNodo2 = crearNodoVacio();
            pruebaNodo2->data[0] = 15;
            pruebaNodo2->data[1] = 44;
            pruebaNodo2->data[2] = 12;
            pruebaNodo2->data[3] = 52;
            pruebaNodo2->n = 4;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo2->child_ptr[i] = nullptr; }
            pruebaNodo2->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo2->print();
            cout << "Se inserta el valor: 65\n";
            cout << "---------------------------\n";
            cout << "nodo esperado: | 12 15 44 52 65 |\n";
            cout << "nodo obtenido: ";
            cout << buscarMedio(pruebaNodo2, valorInsertado2);
            cout << "\nValor medio esperado: 44\n";
            cout << "****************************************\n";
        }
        if (grado == 4) {
            int valorInsertado3 = 22; //Inserto el valor 22
            BpTreeNode *pruebaNodo3;
            pruebaNodo3 = crearNodoVacio();
            pruebaNodo3->data[0] = 15;
            pruebaNodo3->data[1] = 44;
            pruebaNodo3->data[2] = 12;
            pruebaNodo3->n = 3;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo3->child_ptr[i] = nullptr; }
            pruebaNodo3->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo3->print();
            cout << "Se inserta el valor: 22\n";
            cout << "---------------------------\n";
            cout << "nodo esperado: | 12 15 22 44 |\n";
            cout << "nodo obtenido: ";
            cout << buscarMedio(pruebaNodo3, valorInsertado3);
            cout << "\nValor medio esperado: 22\n";
            cout << "****************************************\n";
        }
        if (grado == 3) {
            int valorInsertado3 = 61; //Inserto el valor 61
            BpTreeNode *pruebaNodo3;
            pruebaNodo3 = crearNodoVacio();
            pruebaNodo3->data[0] = 15;
            pruebaNodo3->data[1] = 38;
            pruebaNodo3->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo3->child_ptr[i] = nullptr; }
            pruebaNodo3->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo3->print();
            cout << "Se inserta el valor: 61\n";
            cout << "---------------------------\n";
            cout << "nodo esperado: | 15 38 61 |\n";
            cout << "nodo obtenido: ";
            cout << buscarMedio(pruebaNodo3, valorInsertado3);
            cout << "\nValor medio esperado: 38\n";
            cout << "****************************************\n";
        }
    }

    void test_cantidadDeClavesOcupadas() {
        cout << "\n----------TEST POSICIONES DEL NODO OCUPADAS----------\n";
        cout << "Test hechos para grado de variable 3 y 6\n\n";
        if (grado == 6) {
            BpTreeNode *pruebaNodo1;
            pruebaNodo1 = crearNodoVacio();
            pruebaNodo1->data[0] = 3;
            pruebaNodo1->data[1] = 5;
            pruebaNodo1->data[2] = 12;
            pruebaNodo1->data[3] = 0;
            pruebaNodo1->data[4] = 0;
            pruebaNodo1->n = 3;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo1->child_ptr[i] = nullptr; }
            pruebaNodo1->leaf = true;

            BpTreeNode *pruebaNodo2;
            pruebaNodo2 = crearNodoVacio();
            pruebaNodo2->data[0] = 3;
            pruebaNodo2->data[1] = 4;
            pruebaNodo2->data[2] = 16;
            pruebaNodo2->data[3] = 88;
            pruebaNodo2->data[4] = 102;
            pruebaNodo2->n = 5;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo2->child_ptr[i] = nullptr; }
            pruebaNodo2->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo1->print();
            cout << "-----------------------------------------\n";
            cout << "numero de lugares ocupados esperado: 3\n";
            cout << "numero de lugares ocupados obtenido: ";
            cout << cantidadDeClavesOcupadas(pruebaNodo1);
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo2->print();
            cout << "-----------------------------------------\n";
            cout << "numero de lugares ocupados esperado: 5\n";
            cout << "numero de lugares ocupados obtenido: ";
            cout << cantidadDeClavesOcupadas(pruebaNodo2);
            cout << "\n****************************************\n";
        }

        if (grado == 3) {
            BpTreeNode *pruebaNodo1;
            pruebaNodo1 = crearNodoVacio();
            pruebaNodo1->data[0] = 3;
            pruebaNodo1->data[1] = 5;
            pruebaNodo1->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo1->child_ptr[i] = nullptr; }
            pruebaNodo1->leaf = true;

            BpTreeNode *pruebaNodo2;
            pruebaNodo2 = crearNodoVacio();
            pruebaNodo2->data[0] = 3;
            pruebaNodo2->data[1] = 0;
            pruebaNodo2->n = 1;
            for (int i = 0; i < cantClaves; i++) { pruebaNodo2->child_ptr[i] = nullptr; }
            pruebaNodo2->leaf = true;

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo1->print();
            cout << "---------------------------\n";
            cout << "numero de lugares ocupados esperado: 2\n";
            cout << "numero de lugares ocupados obtenido: ";
            cout << cantidadDeClavesOcupadas(pruebaNodo1);
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            cout << "Nodo Original: ";
            pruebaNodo2->print();
            cout << "---------------------------\n";
            cout << "numero de lugares ocupados esperado: 1\n";
            cout << "numero de lugares ocupados obtenido: ";
            cout << cantidadDeClavesOcupadas(pruebaNodo2);
            cout << "\n****************************************\n";
        }

    }

    void test_buscarValor() {
        cout << "\n-------------TEST BUSCAR VALOR EN ARBOL-------------\n";
        cout << "Este test funciona para grado 3";

        if (grado == 3) {
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 50 |" << endl;
            cout << "| 30 | | 70 |" << endl;
            cout << "| 20 | | 40 | | 60 | | 80 |" << endl;
            cout
                    << "| 10 12 | | 20  25 | | 30 31 | | 40 45 | | 50 55 | | 60 63 | | 70 78 | | 80  90 |"
                    << endl;
            cout << "grado: " << grado << endl;

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 10;
            pruebaNodoHoja1->data[1] = 12;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 20;
            pruebaNodoHoja2->data[1] = 25;
            pruebaNodoHoja2->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 30;
            pruebaNodoHoja3->data[1] = 31;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 40;
            pruebaNodoHoja4->data[1] = 45;
            pruebaNodoHoja4->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 50;
            pruebaNodoHoja5->data[1] = 55;
            pruebaNodoHoja5->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoHoja6;
            pruebaNodoHoja6 = crearNodoVacio();
            pruebaNodoHoja6->data[0] = 60;
            pruebaNodoHoja6->data[1] = 63;
            pruebaNodoHoja6->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja6->leaf = true;

            BpTreeNode *pruebaNodoHoja7;
            pruebaNodoHoja7 = crearNodoVacio();
            pruebaNodoHoja7->data[0] = 70;
            pruebaNodoHoja7->data[1] = 78;
            pruebaNodoHoja7->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja7->child_ptr[i] = nullptr; }
            pruebaNodoHoja7->leaf = true;

            BpTreeNode *pruebaNodoHoja8;
            pruebaNodoHoja8 = crearNodoVacio();
            pruebaNodoHoja8->data[0] = 80;
            pruebaNodoHoja8->data[1] = 90;
            pruebaNodoHoja8->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja8->leaf = true;

            BpTreeNode *pruebaNodoRama11;
            pruebaNodoRama11 = crearNodoVacio();
            pruebaNodoRama11->data[0] = 20;
            pruebaNodoRama11->n = 1;
            pruebaNodoRama11->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRama11->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRama11->child_ptr[2] = nullptr;
            pruebaNodoRama11->leaf = false;

            BpTreeNode *pruebaNodoRama12;
            pruebaNodoRama12 = crearNodoVacio();
            pruebaNodoRama12->data[0] = 40;
            pruebaNodoRama12->n = 1;
            pruebaNodoRama12->child_ptr[0] = pruebaNodoHoja3;
            pruebaNodoRama12->child_ptr[1] = pruebaNodoHoja4;
            pruebaNodoRama12->child_ptr[2] = nullptr;
            pruebaNodoRama12->leaf = false;

            BpTreeNode *pruebaNodoRama13;
            pruebaNodoRama13 = crearNodoVacio();
            pruebaNodoRama13->data[0] = 60;
            pruebaNodoRama13->n = 1;
            pruebaNodoRama13->child_ptr[0] = pruebaNodoHoja5;
            pruebaNodoRama13->child_ptr[1] = pruebaNodoHoja6;
            pruebaNodoRama13->child_ptr[2] = nullptr;
            pruebaNodoRama13->leaf = false;

            BpTreeNode *pruebaNodoRama14;
            pruebaNodoRama14 = crearNodoVacio();
            pruebaNodoRama14->data[0] = 80;
            pruebaNodoRama14->n = 1;
            pruebaNodoRama14->child_ptr[0] = pruebaNodoHoja7;
            pruebaNodoRama14->child_ptr[1] = pruebaNodoHoja8;
            pruebaNodoRama14->child_ptr[2] = nullptr;
            pruebaNodoRama14->leaf = false;

            BpTreeNode *pruebaNodoRama01;
            pruebaNodoRama01 = crearNodoVacio();
            pruebaNodoRama01->data[0] = 30;
            pruebaNodoRama01->n = 1;
            pruebaNodoRama01->child_ptr[0] = pruebaNodoRama11;
            pruebaNodoRama01->child_ptr[1] = pruebaNodoRama12;
            pruebaNodoRama01->child_ptr[2] = nullptr;
            pruebaNodoRama01->leaf = false;

            BpTreeNode *pruebaNodoRama02;
            pruebaNodoRama02 = crearNodoVacio();
            pruebaNodoRama02->data[0] = 70;
            pruebaNodoRama02->n = 1;
            pruebaNodoRama02->child_ptr[0] = pruebaNodoRama13;
            pruebaNodoRama02->child_ptr[1] = pruebaNodoRama14;
            pruebaNodoRama02->child_ptr[2] = nullptr;
            pruebaNodoRama02->leaf = false;

            BpTreeNode *pruebaNodoRoot;
            pruebaNodoRoot = crearNodoVacio();
            pruebaNodoRoot->data[0] = 50;
            pruebaNodoRoot->n = 1;
            pruebaNodoRoot->child_ptr[0] = pruebaNodoRama01;
            pruebaNodoRoot->child_ptr[1] = pruebaNodoRama02;
            pruebaNodoRoot->child_ptr[2] = nullptr;
            pruebaNodoRoot->leaf = false;

            cout << "****************************************\n";
            int valorBuscado1 = 80;
            cout << "Valor buscado: " << valorBuscado1 << endl;
            cout << "resultado de busqueda esperado: Valor encontrado.\n";
            cout << "resultado de busqueda obtenido: ";
            BpTreeNode *resultadoDeBusqueda1 = _buscarValor(pruebaNodoRoot, valorBuscado1, false);
            if (resultadoDeBusqueda1 != nullptr) {
                cout << "Valor encontrado.\nEste valor pertenece al Nodo: ";
                resultadoDeBusqueda1->print();
            } else cout << "Valor no encontrado.";
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorBuscado2 = 35;
            cout << "Valor buscado: " << valorBuscado2 << endl;
            cout << "resultado de busqueda esperado: Valor no encontrado.\n";
            cout << "resultado de busqueda obtenido: ";
            BpTreeNode *resultadoDeBusqueda2 = _buscarValor(pruebaNodoRoot, valorBuscado2, false);
            if (resultadoDeBusqueda2 != nullptr) {
                cout << "Valor encontrado.\nEste valor pertenece al Nodo: ";
                resultadoDeBusqueda2->print();
            } else cout << "Valor no encontrado.";
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorBuscado3 = 50;
            cout << "Valor buscado: " << valorBuscado3 << endl;
            cout << "resultado de busqueda esperado: Valor encontrado.\n";
            cout << "resultado de busqueda obtenido: ";
            BpTreeNode *resultadoDeBusqueda3 = _buscarValor(pruebaNodoRoot, valorBuscado3, false);
            if (resultadoDeBusqueda3 != nullptr) {
                cout << "Valor encontrado.\nEste valor pertenece al Nodo: ";
                resultadoDeBusqueda3->print();
            } else cout << "Valor no encontrado.";
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorBuscado4 = 15;
            cout << "Valor buscado: " << valorBuscado4 << endl;
            cout << "resultado de busqueda esperado: Valor no encontrado.\n";
            cout << "resultado de busqueda obtenido: ";
            BpTreeNode *resultadoDeBusqueda4 = _buscarValor(pruebaNodoRoot, valorBuscado4, false);
            if (resultadoDeBusqueda4 != nullptr) {
                cout << "Valor encontrado.\nEste valor pertenece al Nodo: ";
                resultadoDeBusqueda4->print();
            } else cout << "Valor no encontrado.";
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorBuscado5 = 12;
            cout << "Valor buscado: " << valorBuscado5 << endl;
            cout << "resultado de busqueda esperado: Valor encontrado.\n";
            cout << "resultado de busqueda obtenido: ";
            BpTreeNode *resultadoDeBusqueda5 = _buscarValor(pruebaNodoRoot, valorBuscado5, false);
            if (resultadoDeBusqueda5 != nullptr) {
                cout << "Valor encontrado.\nEste valor pertenece al Nodo: ";
                resultadoDeBusqueda5->print();
            } else cout << "Valor no encontrado.";
            cout << "\n****************************************\n";
        }
    }

    void test_buscarNodoEnDondeInsertarValorIngresado() {

        cout<< "\n-------------TEST BUSCAR NODO EN EL CUAL INSERTAR EL NUEVO VALOR INSERTADO-------------\n";
        cout << "Este test funciona para grado 3 y 4\n";

        if (grado == 3) {
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 50 |" << endl;
            cout << "| 30 | | 70 |" << endl;
            cout << "| 20 | | 40 | | 60 | | 80 |" << endl;
            cout
                    << "| 10 12 | | 20  25 | | 30 31 | | 40 45 | | 50 55 | | 60 63 | | 70 78 | | 80  90 |"
                    << endl;
            cout << "grado: " << grado << endl;

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 10;
            pruebaNodoHoja1->data[1] = 12;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 20;
            pruebaNodoHoja2->data[1] = 25;
            pruebaNodoHoja2->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 30;
            pruebaNodoHoja3->data[1] = 31;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 40;
            pruebaNodoHoja4->data[1] = 45;
            pruebaNodoHoja4->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 50;
            pruebaNodoHoja5->data[1] = 55;
            pruebaNodoHoja5->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoHoja6;
            pruebaNodoHoja6 = crearNodoVacio();
            pruebaNodoHoja6->data[0] = 60;
            pruebaNodoHoja6->data[1] = 63;
            pruebaNodoHoja6->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja6->leaf = true;

            BpTreeNode *pruebaNodoHoja7;
            pruebaNodoHoja7 = crearNodoVacio();
            pruebaNodoHoja7->data[0] = 70;
            pruebaNodoHoja7->data[1] = 78;
            pruebaNodoHoja7->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja7->child_ptr[i] = nullptr; }
            pruebaNodoHoja7->leaf = true;

            BpTreeNode *pruebaNodoHoja8;
            pruebaNodoHoja8 = crearNodoVacio();
            pruebaNodoHoja8->data[0] = 80;
            pruebaNodoHoja8->data[1] = 90;
            pruebaNodoHoja8->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja8->leaf = true;

            BpTreeNode *pruebaNodoRama11;
            pruebaNodoRama11 = crearNodoVacio();
            pruebaNodoRama11->data[0] = 20;
            pruebaNodoRama11->n = 1;
            pruebaNodoRama11->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRama11->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRama11->child_ptr[2] = nullptr;
            pruebaNodoRama11->leaf = false;

            BpTreeNode *pruebaNodoRama12;
            pruebaNodoRama12 = crearNodoVacio();
            pruebaNodoRama12->data[0] = 40;
            pruebaNodoRama12->n = 1;
            pruebaNodoRama12->child_ptr[0] = pruebaNodoHoja3;
            pruebaNodoRama12->child_ptr[1] = pruebaNodoHoja4;
            pruebaNodoRama12->child_ptr[2] = nullptr;
            pruebaNodoRama12->leaf = false;

            BpTreeNode *pruebaNodoRama13;
            pruebaNodoRama13 = crearNodoVacio();
            pruebaNodoRama13->data[0] = 60;
            pruebaNodoRama13->n = 1;
            pruebaNodoRama13->child_ptr[0] = pruebaNodoHoja5;
            pruebaNodoRama13->child_ptr[1] = pruebaNodoHoja6;
            pruebaNodoRama13->child_ptr[2] = nullptr;
            pruebaNodoRama13->leaf = false;

            BpTreeNode *pruebaNodoRama14;
            pruebaNodoRama14 = crearNodoVacio();
            pruebaNodoRama14->data[0] = 80;
            pruebaNodoRama14->n = 1;
            pruebaNodoRama14->child_ptr[0] = pruebaNodoHoja7;
            pruebaNodoRama14->child_ptr[1] = pruebaNodoHoja8;
            pruebaNodoRama14->child_ptr[2] = nullptr;
            pruebaNodoRama14->leaf = false;

            BpTreeNode *pruebaNodoRama01;
            pruebaNodoRama01 = crearNodoVacio();
            pruebaNodoRama01->data[0] = 30;
            pruebaNodoRama01->n = 1;
            pruebaNodoRama01->child_ptr[0] = pruebaNodoRama11;
            pruebaNodoRama01->child_ptr[1] = pruebaNodoRama12;
            pruebaNodoRama01->child_ptr[2] = nullptr;
            pruebaNodoRama01->leaf = false;

            BpTreeNode *pruebaNodoRama02;
            pruebaNodoRama02 = crearNodoVacio();
            pruebaNodoRama02->data[0] = 70;
            pruebaNodoRama02->n = 1;
            pruebaNodoRama02->child_ptr[0] = pruebaNodoRama13;
            pruebaNodoRama02->child_ptr[1] = pruebaNodoRama14;
            pruebaNodoRama02->child_ptr[2] = nullptr;
            pruebaNodoRama02->leaf = false;

            BpTreeNode *pruebaNodoRoot;
            pruebaNodoRoot = crearNodoVacio();
            pruebaNodoRoot->data[0] = 50;
            pruebaNodoRoot->n = 1;
            pruebaNodoRoot->child_ptr[0] = pruebaNodoRama01;
            pruebaNodoRoot->child_ptr[1] = pruebaNodoRama02;
            pruebaNodoRoot->child_ptr[2] = nullptr;
            pruebaNodoRoot->leaf = false;

            cout << "****************************************\n";
            int valorAInsertar1 = 83;
            cout << "Nuevo valor a insertar: " << valorAInsertar1 << endl;
            cout << "Nodo en el cual insertar esperado: | 80 90 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda1 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar1, false);
            resultadoDeBusqueda1->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar2 = 35;
            cout << "Nuevo valor a insertar: " << valorAInsertar2 << endl;
            cout << "Nodo en el cual insertar esperado: | 30 31 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda2 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar2, false);
            resultadoDeBusqueda2->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar3 = 57;
            cout << "Nuevo valor a insertar: " << valorAInsertar3 << endl;
            cout << "Nodo en el cual insertar esperado: | 50 55 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda3 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar3, false);
            resultadoDeBusqueda3->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar4 = 15;
            cout << "Nuevo valor a insertar: " << valorAInsertar4 << endl;
            cout << "Nodo en el cual insertar esperado: | 10 12 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda4 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar4, false);
            resultadoDeBusqueda4->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar5 = 62;
            cout << "Nuevo valor a insertar: " << valorAInsertar5 << endl;
            cout << "Nodo en el cual insertar esperado: | 60 63 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda5 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar5, false);
            resultadoDeBusqueda5->print();
            cout << "\n****************************************\n";
            
        }

        else if (grado == 4) {
            
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 40 |" << endl;
            cout << "| 20 30 | | 50  60 |" << endl;
            cout << "| 10 15 | | 20 25 | | 30 35 | | 40 45 | | 50 55 | | 60 65 |" << endl;

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 10;
            pruebaNodoHoja1->data[1] = 15;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 20;
            pruebaNodoHoja2->data[1] = 25;
            pruebaNodoHoja2->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 30;
            pruebaNodoHoja3->data[1] = 35;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 40;
            pruebaNodoHoja4->data[1] = 45;
            pruebaNodoHoja4->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 50;
            pruebaNodoHoja5->data[1] = 55;
            pruebaNodoHoja5->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoHoja6;
            pruebaNodoHoja6 = crearNodoVacio();
            pruebaNodoHoja6->data[0] = 60;
            pruebaNodoHoja6->data[1] = 65;
            pruebaNodoHoja6->n = 2;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja6->leaf = true;

            BpTreeNode *pruebaNodoRama1;
            pruebaNodoRama1 = crearNodoVacio();
            pruebaNodoRama1->data[0] = 20;
            pruebaNodoRama1->data[1] = 30;
            pruebaNodoRama1->n = 2;
            pruebaNodoRama1->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRama1->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRama1->child_ptr[2] = pruebaNodoHoja3;
            pruebaNodoRama1->child_ptr[3] = nullptr;
            pruebaNodoRama1->leaf = false;

            BpTreeNode *pruebaNodoRama2;
            pruebaNodoRama2 = crearNodoVacio();
            pruebaNodoRama2->data[0] = 50;
            pruebaNodoRama2->data[1] = 60;
            pruebaNodoRama2->n = 2;
            pruebaNodoRama2->child_ptr[0] = pruebaNodoHoja4;
            pruebaNodoRama2->child_ptr[1] = pruebaNodoHoja5;
            pruebaNodoRama2->child_ptr[2] = pruebaNodoHoja6;
            pruebaNodoRama2->child_ptr[3] = nullptr;
            pruebaNodoRama2->leaf = false;

            BpTreeNode *pruebaNodoRoot;
            pruebaNodoRoot = crearNodoVacio();
            pruebaNodoRoot->data[0] = 40;
            pruebaNodoRoot->n = 1;
            pruebaNodoRoot->child_ptr[0] = pruebaNodoRama1;
            pruebaNodoRoot->child_ptr[1] = pruebaNodoRama2;
            pruebaNodoRoot->child_ptr[2] = nullptr;
            pruebaNodoRoot->child_ptr[3] = nullptr;
            pruebaNodoRoot->leaf = false;

            cout << "****************************************\n";
            int valorAInsertar1 = 51;
            cout << "Nuevo valor a insertar: " << valorAInsertar1 << endl;
            cout << "Nodo en el cual insertar esperado: | 50 55 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda1 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar1, false);
            resultadoDeBusqueda1->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar2 = 38;
            cout << "Nuevo valor a insertar: " << valorAInsertar2 << endl;
            cout << "Nodo en el cual insertar esperado: | 30 35 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda2 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar2, false);
            resultadoDeBusqueda2->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            int valorAInsertar3 = 41;
            cout << "Nuevo valor a insertar: " << valorAInsertar3 << endl;
            cout << "Nodo en el cual insertar esperado: | 40 45 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda3 = buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot, valorAInsertar3, false);
            resultadoDeBusqueda3->print();
            cout << "\n****************************************\n";

            cout << "****************************************\n";
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 12 31 42 |" << endl;

            BpTreeNode *pruebaNodoRoot1;
            pruebaNodoRoot1 = crearNodoVacio();
            pruebaNodoRoot1->data[0] = 12;
            pruebaNodoRoot1->data[1] = 31;
            pruebaNodoRoot1->data[2] = 42;
            pruebaNodoRoot1->n = 3;
            for (int i = 0; i < cantClaves; i++) { pruebaNodoRoot1->child_ptr[i] = nullptr; }
            pruebaNodoRoot1->leaf = true;
            cout << "****************************************\n";
            int valorAInsertar4 = 51;
            cout << "Nuevo valor a insertar: " << valorAInsertar3 << endl;
            cout << "Nodo en el cual insertar esperado: | 12 31 42 |\n";
            cout << "Nodo en el cual insertar obtenido: ";
            BpTreeNode *resultadoDeBusqueda4= buscarNodoEnDondeInsertarValorIngresado(
                    pruebaNodoRoot1,valorAInsertar4 , false);
            resultadoDeBusqueda4->print();
            cout << "\n****************************************\n";
            
            
        }

    }

    void test_separarNodo() {
        cout << "\n-------------TEST SEPARAR NODO-------------\n";
        cout << "Este test funciona para grado 4 y 5\n\n";
        if (grado == 5) {


            cout << "*********************************************";
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 10 |" << endl;
            cout << "| 2 5 8 | | 10 30 50 70 |" << endl;
            int insertarValor1 = 40;

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 2;
            pruebaNodoHoja1->data[1] = 5;
            pruebaNodoHoja1->data[2] = 8;
            pruebaNodoHoja1->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 10;
            pruebaNodoHoja2->data[1] = 30;
            pruebaNodoHoja2->data[2] = 50;
            pruebaNodoHoja2->data[3] = 70;
            pruebaNodoHoja2->n = 4;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoRoot1;
            pruebaNodoRoot1 = crearNodoVacio();
            pruebaNodoRoot1->data[0] = 10;
            pruebaNodoRoot1->n = 1;
            pruebaNodoRoot1->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRoot1->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRoot1->child_ptr[2] = nullptr;
            pruebaNodoRoot1->child_ptr[3] = nullptr;
            pruebaNodoRoot1->child_ptr[4] = nullptr;
            pruebaNodoRoot1->leaf = false;

            cout << "Se inserta el valor: " << insertarValor1;
            cout << "\n--------------------------------------\n";
            cout << "Se espera lo siguiente:\n";
            cout << "Padre: | 10 40 |\nHijo menor: | 10 30 |\nhijo mayor: | 50 70 |\n";
            cout << "\nSe obtiene lo siguiente: ";
            separarNodo(pruebaNodoRoot1, pruebaNodoHoja2, insertarValor1,false);
            cout << "*********************************************\n";


            cout << "\n*********************************************";
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 20 40 |" << endl;
            cout << "| 2 10 | | 20 22 28 30 | | 40 50 60 |" << endl;
            int insertarValor5 = 21;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 2;
            pruebaNodoHoja3->data[1] = 10;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 20;
            pruebaNodoHoja4->data[1] = 22;
            pruebaNodoHoja4->data[2] = 28;
            pruebaNodoHoja4->data[3] = 30;
            pruebaNodoHoja4->n = 4;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 40;
            pruebaNodoHoja5->data[1] = 50;
            pruebaNodoHoja5->data[2] = 60;
            pruebaNodoHoja5->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoRoot5;
            pruebaNodoRoot5 = crearNodoVacio();
            pruebaNodoRoot5->data[0] = 20;
            pruebaNodoRoot5->data[1] = 40;
            pruebaNodoRoot5->n = 2;
            pruebaNodoRoot5->child_ptr[0] = pruebaNodoHoja3;
            pruebaNodoRoot5->child_ptr[1] = pruebaNodoHoja4;
            pruebaNodoRoot5->child_ptr[2] = pruebaNodoHoja5;
            pruebaNodoRoot5->child_ptr[3] = nullptr;
            pruebaNodoRoot5->child_ptr[4] = nullptr;
            pruebaNodoRoot5->leaf = false;

            cout << "Se inserta el valor: " << insertarValor5;
            cout << "\n--------------------------------------\n";
            cout << "Se espera lo siguiente:\n";
            cout << "Padre: | 20 22 40 |\nHijo menor: | 20 21 |\nhijo mayor: | 28 30 |";
            cout << "\nSe obtiene lo siguiente: ";
            separarNodo(pruebaNodoRoot5, pruebaNodoHoja4, insertarValor5,false);
            cout << "*********************************************\n";


            cout << "\n*********************************************";
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 15 18 22 57 |" << endl;
            int insertarValor2 = 40;

            BpTreeNode *pruebaNodoRoot2;
            pruebaNodoRoot2 = crearNodoVacio();
            pruebaNodoRoot2->data[0] = 15;
            pruebaNodoRoot2->data[1] = 18;
            pruebaNodoRoot2->data[2] = 22;
            pruebaNodoRoot2->data[3] = 57;
            pruebaNodoRoot2->n = 4;
            pruebaNodoRoot2->child_ptr[0] = nullptr;
            pruebaNodoRoot2->child_ptr[1] = nullptr;
            pruebaNodoRoot2->child_ptr[2] = nullptr;
            pruebaNodoRoot2->child_ptr[3] = nullptr;
            pruebaNodoRoot2->child_ptr[4] = nullptr;
            pruebaNodoRoot2->leaf = true;

            cout << "Se inserta el valor: " << insertarValor2;
            cout << "\n--------------------------------------\n";
            cout << "Se espera lo siguiente:\n";
            cout << "Padre: | 22 |\nHijo menor: | 15 18 |\nhijo mayor: | 40 57 |";
            cout << "\nSe obtiene lo siguiente: ";
            separarNodo(pruebaNodoRoot2, pruebaNodoRoot2, insertarValor2,false);
            cout << "*********************************************\n";

        }

        if(grado == 4){
            cout << "*********************************************";
            cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
            cout << "| 30 50 70 |" << endl;
            cout << "| 10 12 | | 30 40 | | 50 55 60 | | 70 80 90 |" << endl;
            int insertarValor1 = 72;

            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 10;
            pruebaNodoHoja1->data[1] = 12;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 30;
            pruebaNodoHoja2->data[1] = 40;
            pruebaNodoHoja2->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 50;
            pruebaNodoHoja3->data[1] = 55;
            pruebaNodoHoja3->data[2] = 60;
            pruebaNodoHoja3->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 70;
            pruebaNodoHoja4->data[1] = 80;
            pruebaNodoHoja4->data[2] = 90;
            pruebaNodoHoja4->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoRoot1;
            pruebaNodoRoot1 = crearNodoVacio();
            pruebaNodoRoot1->data[0] = 30;
            pruebaNodoRoot1->data[1] = 50;
            pruebaNodoRoot1->data[2] = 70;
            pruebaNodoRoot1->n = 3;
            pruebaNodoRoot1->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRoot1->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRoot1->child_ptr[2] = pruebaNodoHoja3;
            pruebaNodoRoot1->child_ptr[3] = pruebaNodoHoja4;
            pruebaNodoRoot1->leaf = false;

            cout << "Se inserta el valor: " << insertarValor1;
            cout << "\n--------------------------------------\n";

            cout << "Se espera lo siguiente:\n";
            cout << "Padre: | 70 |\nHijo menor: | 30 50 |\nhijo mayor: | 80 |\n\n";
            cout << "Padre: | 80 |\nHijo menor: | 70 72 |\nHijo mayor: | 90 |\n";
            cout << "\nSe obtiene lo siguiente: ";
            separarNodo(pruebaNodoRoot1, pruebaNodoHoja4, insertarValor1, false);
            cout << "*********************************************\n\n";

        }
    }

    void test_organizarPunterosHijosDePadre(){
        cout << "\n-------------TEST ORGANIZAR LOS PUNTERO DEL NODO PADRE-------------\n";
        cout << "Este test funciona para grado 5 y 6\n\n";

        if( grado == 5){
            BpTreeNode *pruebaNodoHoja1;
            pruebaNodoHoja1 = crearNodoVacio();
            pruebaNodoHoja1->data[0] = 18;
            pruebaNodoHoja1->data[1] = 31;
            pruebaNodoHoja1->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
            pruebaNodoHoja1->leaf = true;

            BpTreeNode *pruebaNodoHoja2;
            pruebaNodoHoja2 = crearNodoVacio();
            pruebaNodoHoja2->data[0] = 35;
            pruebaNodoHoja2->data[1] = 51;
            pruebaNodoHoja2->data[2] = 62;
            pruebaNodoHoja2->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
            pruebaNodoHoja2->leaf = true;

            BpTreeNode *pruebaNodoHoja3;
            pruebaNodoHoja3 = crearNodoVacio();
            pruebaNodoHoja3->data[0] = 8;
            pruebaNodoHoja3->data[1] = 12;
            pruebaNodoHoja3->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
            pruebaNodoHoja3->leaf = true;

            BpTreeNode *pruebaNodoRoot1;
            pruebaNodoRoot1 = crearNodoVacio();
            pruebaNodoRoot1->data[0] = 18;
            pruebaNodoRoot1->data[1] = 35;
            pruebaNodoRoot1->n = 2;
            pruebaNodoRoot1->child_ptr[0] = pruebaNodoHoja1;
            pruebaNodoRoot1->child_ptr[1] = pruebaNodoHoja2;
            pruebaNodoRoot1->child_ptr[2] = pruebaNodoHoja3;
            pruebaNodoRoot1->child_ptr[3] = nullptr;
            pruebaNodoRoot1->child_ptr[4] = nullptr;
            pruebaNodoRoot1->leaf = false;

            vector<BpTreeNode*>hijosDesordenados1;
            hijosDesordenados1.push_back(pruebaNodoHoja1);
            hijosDesordenados1.push_back(pruebaNodoHoja2);
            hijosDesordenados1.push_back(pruebaNodoHoja3);

            cout << "*********************************************";
            cout << "\nSe crean los siguientes nodos hardcodeado:\n";
            cout << "padre: | 18 35 |" << endl;
            cout << "ch0: | 18 31 |\nch1: | 35 51 62 |\nch2: | 8 12 |\n";
            cout <<"-------------------------------------------------\n";
            cout <<" Arbol esperado:\n";
            cout << "| 18 35 n=2c=3|" << endl;
            cout << "| 8 12 n=2c=0| | 18 31 n=2c=0| | 35 51 62 n=3c=0|\n\n";
            cout << "Arbol Obtenido:\n";
            organizarPunterosHijosDePadre(pruebaNodoRoot1,hijosDesordenados1);
            _printTree(pruebaNodoRoot1);
            cout << "\n*********************************************\n";

            BpTreeNode *pruebaNodoHoja4;
            pruebaNodoHoja4 = crearNodoVacio();
            pruebaNodoHoja4->data[0] = 52;
            pruebaNodoHoja4->data[1] = 59;
            pruebaNodoHoja4->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
            pruebaNodoHoja4->leaf = true;

            BpTreeNode *pruebaNodoHoja5;
            pruebaNodoHoja5 = crearNodoVacio();
            pruebaNodoHoja5->data[0] = 18;
            pruebaNodoHoja5->data[1] = 20;
            pruebaNodoHoja5->data[2] = 33;
            pruebaNodoHoja5->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja5->child_ptr[i] = nullptr; }
            pruebaNodoHoja5->leaf = true;

            BpTreeNode *pruebaNodoHoja6;
            pruebaNodoHoja6 = crearNodoVacio();
            pruebaNodoHoja6->data[0] = 6;
            pruebaNodoHoja6->data[1] = 13;
            pruebaNodoHoja6->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja6->child_ptr[i] = nullptr; }
            pruebaNodoHoja6->leaf = true;

            BpTreeNode *pruebaNodoHoja7;
            pruebaNodoHoja7 = crearNodoVacio();
            pruebaNodoHoja7->data[0] = 67;
            pruebaNodoHoja7->data[1] = 83;
            pruebaNodoHoja7->data[2] = 91;
            pruebaNodoHoja7->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja7->child_ptr[i] = nullptr; }
            pruebaNodoHoja7->leaf = true;

            BpTreeNode *pruebaNodoHoja8;
            pruebaNodoHoja8 = crearNodoVacio();
            pruebaNodoHoja8->data[0] = 14;
            pruebaNodoHoja8->data[1] = 16;
            pruebaNodoHoja8->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja8->child_ptr[i] = nullptr; }
            pruebaNodoHoja8->leaf = true;

            BpTreeNode *pruebaNodoRoot2;
            pruebaNodoRoot2 = crearNodoVacio();
            pruebaNodoRoot2->data[0] = 14;
            pruebaNodoRoot2->data[1] = 18;
            pruebaNodoRoot2->data[2] = 52;
            pruebaNodoRoot2->data[3] = 67;
            pruebaNodoRoot2->n = 4;
            pruebaNodoRoot2->child_ptr[0] = pruebaNodoHoja4;
            pruebaNodoRoot2->child_ptr[1] = pruebaNodoHoja5;
            pruebaNodoRoot2->child_ptr[2] = pruebaNodoHoja6;
            pruebaNodoRoot2->child_ptr[3] = pruebaNodoHoja7;
            pruebaNodoRoot2->child_ptr[4] = pruebaNodoHoja8;
            pruebaNodoRoot2->leaf = false;

            vector<BpTreeNode*>hijosDesordenados2;
            hijosDesordenados2.push_back(pruebaNodoHoja4);
            hijosDesordenados2.push_back(pruebaNodoHoja5);
            hijosDesordenados2.push_back(pruebaNodoHoja6);
            hijosDesordenados2.push_back(pruebaNodoHoja7);
            hijosDesordenados2.push_back(pruebaNodoHoja8);

            cout << "*********************************************";
            cout << "\nSe crean los siguientes nodos hardcodeado:\n";
            cout << "padre: | 14 18 52 67 |" << endl;
            cout << "ch0: | 52 59 |\nch1: | 18 20 33 |\nch2: | 6 13 |\n";
            cout << "ch3: | 67 83 91 |\nch4: | 14 16 |";
            cout <<"\n-------------------------------------------------\n";
            cout <<" Arbol esperado:\n";
            cout << "| 14 18 52 67 n=4c=5|" << endl;
            cout << "| 6 13 n=2c=0| | 14 16 n=2c=0| | 18 20 33 n=3c=0| | 52 59 n=2c=0| | 67 83 91 n=3c=0|\n\n";
            cout << "Arbol Obtenido:\n";
            organizarPunterosHijosDePadre(pruebaNodoRoot2,hijosDesordenados2);
            _printTree(pruebaNodoRoot2);
            cout << "\n*********************************************\n";

            BpTreeNode *pruebaNodoHoja9;
            pruebaNodoHoja9 = crearNodoVacio();
            pruebaNodoHoja9->data[0] = 52;
            pruebaNodoHoja9->data[1] = 59;
            pruebaNodoHoja9->data[2] = 67;
            pruebaNodoHoja9->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja9->child_ptr[i] = nullptr; }
            pruebaNodoHoja9->leaf = true;

            BpTreeNode *pruebaNodoHoja10;
            pruebaNodoHoja10 = crearNodoVacio();
            pruebaNodoHoja10->data[0] = 18;
            pruebaNodoHoja10->data[1] = 20;
            pruebaNodoHoja10->data[2] = 33;
            pruebaNodoHoja10->n = 3;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja10->child_ptr[i] = nullptr; }
            pruebaNodoHoja10->leaf = true;

            BpTreeNode *pruebaNodoHoja11;
            pruebaNodoHoja11 = crearNodoVacio();
            pruebaNodoHoja11->data[0] = 6;
            pruebaNodoHoja11->data[1] = 13;
            pruebaNodoHoja11->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja11->child_ptr[i] = nullptr; }
            pruebaNodoHoja11->leaf = true;

            BpTreeNode *pruebaNodoHoja12;
            pruebaNodoHoja12 = crearNodoVacio();
            pruebaNodoHoja12->data[0] = 14;
            pruebaNodoHoja12->data[1] = 16;
            pruebaNodoHoja12->n = 2;
            for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja12->child_ptr[i] = nullptr; }
            pruebaNodoHoja12->leaf = true;

            BpTreeNode *pruebaNodoRoot3;
            pruebaNodoRoot3 = crearNodoVacio();
            pruebaNodoRoot3->data[0] = 14;
            pruebaNodoRoot3->data[1] = 18;
            pruebaNodoRoot3->data[2] = 52;
            pruebaNodoRoot3->n = 3;
            pruebaNodoRoot3->child_ptr[0] = pruebaNodoHoja9;
            pruebaNodoRoot3->child_ptr[1] = pruebaNodoHoja10;
            pruebaNodoRoot3->child_ptr[2] = pruebaNodoHoja11;
            pruebaNodoRoot3->child_ptr[3] = pruebaNodoHoja12;
            pruebaNodoRoot3->child_ptr[4] = nullptr;
            pruebaNodoRoot3->leaf = false;

            vector<BpTreeNode*>hijosDesordenados3;
            hijosDesordenados3.push_back(pruebaNodoHoja9);
            hijosDesordenados3.push_back(pruebaNodoHoja10);
            hijosDesordenados3.push_back(pruebaNodoHoja11);
            hijosDesordenados3.push_back(pruebaNodoHoja12);

            cout << "*********************************************";
            cout << "\nSe crean los siguientes nodos hardcodeado:\n";
            cout << "padre: | 14 18 52 |" << endl;
            cout << "ch0: | 52 59 67 |\nch1: | 18 20 33 |\nch2: | 6 13 |\n";
            cout << "ch3: | 14 16 |";
            cout <<"\n-------------------------------------------------\n";
            cout <<" Arbol esperado:\n";
            cout << "| 14 18 52  n=3c=4|" << endl;
            cout << "| 6 13 n=2c=0| | 14 16 n=2c=0| | 18 20 33 n=3c=0| | 52 59 67 n=3c=0|\n\n";
            cout << "Arbol Obtenido:\n";
            organizarPunterosHijosDePadre(pruebaNodoRoot3,hijosDesordenados3);
            _printTree(pruebaNodoRoot3);
            cout << "\n*********************************************\n";
        }
    }

    void test_nodosHojasDelArbol(){
        cout << "\n-------------TEST NODOS HOJA DEL ARBOL-------------\n";
        cout << "Este test funciona para grado 4\n\n";

        cout << "*********************************************";
        cout << "\nSe crea el siguiente BpTree hardcodeado:\n";
        cout << "| 30 50 70 |" << endl;
        cout << "| 10 12 | | 30 40 | | 50 55 60 | | 70 80 90 |" << endl;

        BpTreeNode *pruebaNodoHoja1;
        pruebaNodoHoja1 = crearNodoVacio();
        pruebaNodoHoja1->data[0] = 10;
        pruebaNodoHoja1->data[1] = 12;
        pruebaNodoHoja1->n = 2;
        for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja1->child_ptr[i] = nullptr; }
        pruebaNodoHoja1->leaf = true;

        BpTreeNode *pruebaNodoHoja2;
        pruebaNodoHoja2 = crearNodoVacio();
        pruebaNodoHoja2->data[0] = 30;
        pruebaNodoHoja2->data[1] = 40;
        pruebaNodoHoja2->n = 2;
        for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja2->child_ptr[i] = nullptr; }
        pruebaNodoHoja2->leaf = true;

        BpTreeNode *pruebaNodoHoja3;
        pruebaNodoHoja3 = crearNodoVacio();
        pruebaNodoHoja3->data[0] = 50;
        pruebaNodoHoja3->data[1] = 55;
        pruebaNodoHoja3->data[2] = 60;
        pruebaNodoHoja3->n = 3;
        for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja3->child_ptr[i] = nullptr; }
        pruebaNodoHoja3->leaf = true;

        BpTreeNode *pruebaNodoHoja4;
        pruebaNodoHoja4 = crearNodoVacio();
        pruebaNodoHoja4->data[0] = 70;
        pruebaNodoHoja4->data[1] = 80;
        pruebaNodoHoja4->data[2] = 90;
        pruebaNodoHoja4->n = 3;
        for (int i = 0; i < cantClaves + 1; i++) { pruebaNodoHoja4->child_ptr[i] = nullptr; }
        pruebaNodoHoja4->leaf = true;

        BpTreeNode *pruebaNodoRoot1;
        pruebaNodoRoot1 = crearNodoVacio();
        pruebaNodoRoot1->data[0] = 30;
        pruebaNodoRoot1->data[1] = 50;
        pruebaNodoRoot1->data[2] = 70;
        pruebaNodoRoot1->n = 3;
        pruebaNodoRoot1->child_ptr[0] = pruebaNodoHoja1;
        pruebaNodoRoot1->child_ptr[1] = pruebaNodoHoja2;
        pruebaNodoRoot1->child_ptr[2] = pruebaNodoHoja3;
        pruebaNodoRoot1->child_ptr[3] = pruebaNodoHoja4;
        pruebaNodoRoot1->leaf = false;

        cout<<"\n---------------------------------------\n";
        cout<<"Se esperan los siguientes nodos:\n";
        cout <<"| 10 12 | | 30 40 | | 50 55 60 | | 70 80 90 |" << endl;
        cout<<"\nSe obtienen los siguientes nodos:\n";
        nodosHojasDelArbol(pruebaNodoRoot1);

    }
    /*******************************************************/

private:

    BpTreeNode* root;
    int cantClaves, grado;

    BpTreeNode * crearNodoVacio()
    {
        int numHijos = grado;
        BpTreeNode *node = new BpTreeNode();
        node->data = new int[cantClaves];
        node->child_ptr = new BpTreeNode *[numHijos+1];
        node->child_ptr[numHijos] = nullptr;
        node->leaf = true;
        node->n = 0;
        for (int i = 0; i < grado; i++){
            node->child_ptr[i] = nullptr;
        }
        return node;
    }

    static int getChildCount(BpTreeNode *node) {
        int i = 0;
        while (true) {
            if (node->child_ptr[i] == nullptr ) return i;
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

    int cantidadDeClavesOcupadas(BpTreeNode* nodo){
        int numeroDeElementos = 0;
        for (int i = 0; i < cantClaves ; i++) {
            if (nodo->data[i] != 0) numeroDeElementos++;
        }
        return numeroDeElementos;
    }

    BpTreeNode* buscarNodoEnDondeInsertarValorIngresado (BpTreeNode* nodoRoot, int valorAInsertar, bool recursiveCall){
        static BpTreeNode* nodoEncontrado = nullptr;
        if(recursiveCall == false) {nodoEncontrado = nullptr;}
        int clavesOcupadas = cantidadDeClavesOcupadas(nodoRoot);
        if(nodoRoot->leaf == false)
        {
            int posicionNodoElegido = 0;
            while (true) {
                if (posicionNodoElegido == clavesOcupadas) {
                    break;
                }
                else if(valorAInsertar < nodoRoot->data[posicionNodoElegido]) break;
                else posicionNodoElegido++;
            }
            buscarNodoEnDondeInsertarValorIngresado(nodoRoot->child_ptr[posicionNodoElegido], valorAInsertar, true);
        }
        else{
            nodoEncontrado = nodoRoot;
            return nodoEncontrado;
        }
    }

    bool valorMedioPerteneceANodo(BpTreeNode* nodo, int valorMedio){
        for (int i = 0; i < cantClaves ; ++i) {
            if(nodo->data[i] == valorMedio){
                return true;
            }
        }
        return false;
    }

    int buscarMedio(BpTreeNode* nodo, int valorNuevoInsertado){
        int tamanioArregloNuevo = cantClaves + 1;
        int arrelgoNuevo[tamanioArregloNuevo];//Este nodo contendra el nodo + valorNuevoInsertado
        for (int i = 0; i < cantClaves ; ++i) {
            arrelgoNuevo[i] = nodo->data[i];
        }
        arrelgoNuevo[tamanioArregloNuevo-1] = valorNuevoInsertado;
        sort(arrelgoNuevo, tamanioArregloNuevo);
        /*cout <<"|";
        for (int j = 0; j < cantClaves+1 ; ++j) {
            cout <<" "<<arrelgoNuevo[j];
        }
        cout <<" |\n";*/
        int valorMedio = (tamanioArregloNuevo)/2;
        //cout<<"Valor medio obtenido: ";
        return arrelgoNuevo[valorMedio];
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

    BpTreeNode* _buscarValor(BpTreeNode* nodoRoot, int valorBuscado, bool recursiveCall){
        int cantHijos = getChildCount(nodoRoot);
        static BpTreeNode* nodoEncontrado = nullptr;
        if(recursiveCall == false) {nodoEncontrado = nullptr;}
        int clavesOcupadas = cantidadDeClavesOcupadas(nodoRoot);
        if(nodoRoot->leaf == false)
        {
            int posicionHijoElegido = 0;
            while (true) {
                if (posicionHijoElegido == clavesOcupadas) {
                    break;
                }
                else if(valorBuscado < nodoRoot->data[posicionHijoElegido]) break;
                else posicionHijoElegido++;
            }
            _buscarValor(nodoRoot->child_ptr[posicionHijoElegido], valorBuscado, true);
        }
        else{
            for (int i = 0; i < clavesOcupadas ; i++) {
                if(nodoRoot->data[i] == valorBuscado){
                    nodoEncontrado = nodoRoot;
                }
            }
        }
        return nodoEncontrado;
    }

    bool hijoCorrespondeAPuntero(int claveIzquierdaPadre, int claveDerechaPadre , BpTreeNode* nodoHijo){
        int cantidadClavesOcupadasEnHijo = cantidadDeClavesOcupadas(nodoHijo);
        int valorMinimoDelNodo = nodoHijo->data[0];
        int valorMaximoDelNodo = nodoHijo->data[0];;

        for (int i = 0; i < cantidadClavesOcupadasEnHijo ; i++) {
            if(nodoHijo->data[i] < valorMinimoDelNodo){
                valorMinimoDelNodo = nodoHijo->data[i];
            }
            if(valorMaximoDelNodo < nodoHijo->data[i]){
                valorMaximoDelNodo = nodoHijo->data[i];
            }
        }

        if( claveIzquierdaPadre == 0 ){
            if( valorMaximoDelNodo < claveDerechaPadre){ return true; }
            else {return false;}
        }
        else if( claveDerechaPadre == 0){
            if (claveIzquierdaPadre <= valorMinimoDelNodo){ return true; }
            else {return false;}
        }
        else {
            if(claveIzquierdaPadre <= valorMinimoDelNodo && valorMaximoDelNodo < claveDerechaPadre){
                return true;
            }
            else {return false;}
        }
    }

    void organizarPunterosHijosDePadre(BpTreeNode* padre, vector<BpTreeNode*> hijos) {
        int clavesOcupadasPadre = cantidadDeClavesOcupadas(padre);
        int cantidadDeHijosDelPadre = clavesOcupadasPadre + 1;

        /*for (int k = 0; k < cantidadDeHijosDelPadre ; k++) {
           padre->child_ptr[k] = nullptr;
        }*/

        for (int i = 0; i <= clavesOcupadasPadre; i++) {

            for (int j = 0; j < hijos.size() ; j++) {
                 BpTreeNode* AsignarPunteroAHijo = hijos.at(j);
                 bool hijoEncontrado = false;
                if( i == 0){
                    hijoEncontrado = hijoCorrespondeAPuntero(0, padre->data[i], AsignarPunteroAHijo);
                    if(hijoEncontrado == true){
                        padre->child_ptr[i] = hijos.at(j);
                        break;
                    }
                    else continue;
                }
                else if (i+1 == cantidadDeHijosDelPadre){
                    hijoEncontrado = hijoCorrespondeAPuntero(padre->data[i - 1], 0,
                                                             AsignarPunteroAHijo);
                    if(hijoEncontrado == true){
                        padre->child_ptr[i] = hijos.at(j);
                        break;
                    }
                    else continue;
                }
                else{
                    hijoEncontrado = hijoCorrespondeAPuntero(padre->data[i - 1], padre->data[i],
                                                             AsignarPunteroAHijo);
                    if(hijoEncontrado == true){
                        padre->child_ptr[i] = hijos.at(j);
                        break;
                    }
                    else continue;
                }
            }
        }

    }

    int separarNodo(BpTreeNode* nodoRoot, BpTreeNode* nodoASeparar, int valorInsertado, bool recursiveCall){

        static int cantLlamadas =0;

        int valorMedio = buscarMedio(nodoASeparar,valorInsertado);
        bool valorMedioPertenceAlNodo = valorMedioPerteneceANodo(nodoASeparar,valorMedio);

        static int contadorDeRecursividad =0;
        if(recursiveCall == false){contadorDeRecursividad=0;}
        else if(recursiveCall== true){
            contadorDeRecursividad++;
        }

        if(recursiveCall == false){
            if(nodoRoot != nodoASeparar || contadorDeRecursividad == 0)///Este if contempla el caso en el que el Arbol solo teng aun nodo y alla que separarlo
            root = nodoRoot;///Esto es para cuando se hacen llamadas multiples como en el test. Actualiza
            root->leaf = false;
        }


        BpTreeNode* padre = getPadre(nodoRoot, nodoASeparar, false);

        if(getPadre(nodoRoot, nodoASeparar, false) == nullptr && cantLlamadas<=2){
            BpTreeNode* padreVacio;
            padreVacio = crearNodoVacio();
            padre = padreVacio;
        }
        cantLlamadas++;

        BpTreeNode* hijoMenor = crearNodoVacio();
        BpTreeNode* hijoMayor = crearNodoVacio();
        if( contadorDeRecursividad == 0){
            hijoMenor->leaf = true;
            hijoMayor->leaf = true;
        }
        else{
            hijoMenor->leaf = false;
            hijoMayor->leaf = false;
        }


        if(valorMedioPertenceAlNodo == true){

            int posicionDelValorMedio = posicionDelElementoMedio(nodoASeparar,valorInsertado);
            /**Rellenamos hijo menor**/
            for (int i = 0; i < posicionDelValorMedio ; ++i) {
                hijoMenor->data[i] = nodoASeparar->data[i];
                hijoMenor->n++;
            }
            int cantidadClavesLlenasHijoMenor = cantidadDeClavesOcupadas(hijoMenor);
            if( valorInsertado < valorMedio){
                hijoMenor->data[cantidadClavesLlenasHijoMenor] = valorInsertado;
                hijoMenor->n++;
                cantidadClavesLlenasHijoMenor++;
                sort(hijoMenor->data, cantidadClavesLlenasHijoMenor);
            }

            /**Rellenamos hijo mayor**/
            for (int j = posicionDelValorMedio+1; j < cantClaves ; ++j) {
                hijoMayor->data[j - posicionDelValorMedio-1] = nodoASeparar->data[j];
                hijoMayor->n++;
            }
            int cantidadClavesLlenasHijoMayor = cantidadDeClavesOcupadas(hijoMayor);
            if(valorMedio < valorInsertado){
                hijoMayor->data[cantidadClavesLlenasHijoMayor] = valorInsertado;
                hijoMayor->n++;
                cantidadClavesLlenasHijoMayor++;
                sort(hijoMayor->data,cantidadClavesLlenasHijoMayor);
            }
            /**Rellenamos Padre**/
            int cantidadClavesLlenasPadre1 = cantidadDeClavesOcupadas(padre);
            if(cantidadClavesLlenasPadre1 == cantClaves){
                separarNodo(nodoRoot,padre,valorMedio, true);
                BpTreeNode* padreNuevo;
                padreNuevo = crearNodoVacio();
                padreNuevo->leaf = false;
                padreNuevo->data[0] = valorMedio;
                padre = padreNuevo;

            }

            int cantidadClavesLlenasPadre = cantidadDeClavesOcupadas(padre);
            ///se debe hacer una funcion que ubique el valor en el padre en la pos correcta y mueva los chil_ptr
            padre->data[cantidadClavesLlenasPadre] = valorMedio;
            padre->n++;
            cantidadClavesLlenasPadre++;
            sort(padre->data, cantidadClavesLlenasPadre);



            if(0 < contadorDeRecursividad){
                root =padre;
                root->leaf =false;
            }
            if(root != padre){
                root =padre;
                root->leaf =false;
            }

            vector<BpTreeNode*>hijos;
            hijos.push_back(hijoMenor);
            hijos.push_back(hijoMayor);
            organizarPunterosHijosDePadre(padre,hijos);



            /*Para hacer el test*/
            cout<<"\n\nRoot del Arbol= ";
            root->print();
            cout<<"\nPadre: ";
            padre->print();
            cout<<"Hijo menor: ";
            hijoMenor->print();
            cout<<"Hijo mayor: ";
            hijoMayor->print();
            if(recursiveCall== false){
            cout<<"\n\nArbol obtenido\n";
            _printTree(root);
            }
        }

        if (valorMedioPertenceAlNodo == false){

            int posicionQueOcupariaValorMedio = posicionDelElementoMedio(nodoASeparar,valorInsertado);

            /**Rellenamos hijo menor**/
            for (int i = 0; i < posicionQueOcupariaValorMedio ; ++i) {
                hijoMenor->data[i] = nodoASeparar->data[i];
                hijoMenor->n++;
            }

            /**Rellenamos hijo mayor**/
            for (int j = posicionQueOcupariaValorMedio; j < cantClaves ; ++j) {
                hijoMayor->data[j - posicionQueOcupariaValorMedio] = nodoASeparar->data[j];
                hijoMayor->n++;
            }

            /**Rellenamos Padre**/
            int cantidadClavesLlenasPadre = cantidadDeClavesOcupadas(padre);
            if(cantidadClavesLlenasPadre == cantClaves){
                separarNodo(nodoRoot,padre,valorMedio, true);
                BpTreeNode* padreNuevo;
                padreNuevo = crearNodoVacio();
                padreNuevo->data[0] = valorMedio;
                padre = padreNuevo;
            }
            padre->data[cantidadClavesLlenasPadre] = valorMedio;
            padre->n++;
            cantidadClavesLlenasPadre++;
            sort(padre->data, cantidadClavesLlenasPadre);
            root =padre;
            root->leaf =false;

            vector<BpTreeNode*>hijos;
            hijos.push_back(hijoMenor);
            hijos.push_back(hijoMayor);
            organizarPunterosHijosDePadre(padre,hijos);

            /*Para hacer el test*/
            cout<<"\n\nRoot del Arbol= ";
            root->print();
            cout<<"\nPadre: ";
            padre->print();
            cout<<"Hijo menor: ";
            hijoMenor->print();
            cout<<"Hijo mayor: ";
            hijoMayor->print();
            if(recursiveCall == false){

            cout<<"\n\nArbol obtenido\n";
            _printTree(root);
            }
        }
        return valorMedio;
    }

    vector<BpTreeNode*> nodosHojasDelArbol(BpTreeNode* nodoRoot){
        vector<BpTreeNode*>vectorDeNodosHoja;
        static int  cantHijos = getChildCount(nodoRoot);
        int cantidadDeclavesDeHijo = cantidadDeClavesOcupadas(nodoRoot);
        //BpTreeNode* nodoHoja =crearNodoVacio();

        for(int k=0; k <cantHijos; k++){
            if (nodoRoot->child_ptr[k]->leaf == true) {
                vectorDeNodosHoja.push_back(nodoRoot->child_ptr[k]);
            } else nodosHojasDelArbol(nodoRoot->child_ptr[k]);
        }



        /**Pra hacer el test**/
        int cantidadDeNodosHoja = vectorDeNodosHoja.size();
        for (int j = 0; j < cantidadDeNodosHoja ; ++j) {
            cout << " | ";
            for (int i = 0; i < cantidadDeclavesDeHijo ; ++i) {
                if(vectorDeNodosHoja[j]->data[i] !=0 )
                cout <<" "<< vectorDeNodosHoja[j]->data[i];
            }
            cout << " | ";
        }
        /****/
        return vectorDeNodosHoja;
    }

};


#endif //FINAL2_BTREEP_H
