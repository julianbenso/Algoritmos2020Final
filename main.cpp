#pragma once
#include<stdio.h>
#include<iostream>
#include <iomanip>
#include <vector>
#include "Test.h"
#include "BtreeP.h"

using namespace std;

int main()
{
    int grado;
    cout<<"Grados de variable admitidos: 3, 4, 5 y 6\n";
    cout << "Indicar el grado de variable: ";
    cin >> grado;
    cout<<" ";
    BtreeP* arbol = new BtreeP(grado);
    //arbol->test_getPadre();
    arbol->test_valorMedioPerteneceANodo();

    /*int cantidadElementos, ValorIngresado;
    cout<<"Ingresar cantidad de elementos a insertar: ";
    cin>>cantidadElementos;

    for(int i = 0; i < cantidadElementos; i++)
    {
        cout << "Ingresar valor: ";
        cin >> ValorIngresado;
        arbol->insert(ValorIngresado);
    }
    cout << "Arbol trasversal:"<<endl;
    arbol->printTree();*/

    //getch();
}