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
    cout << "Ingresar el grado (3,4,5,6): ";
    cin >> grado;
    BtreeP* arbol = new BtreeP(grado);
    int cantidadElementos, ValorIngresado;
    cout<<"Ingresar cantidad de elementos a insertar: ";
    cin>>cantidadElementos;
    for(int i = 0; i < cantidadElementos; i++)
    {
        cout << "Ingresar valor: ";
        cin >> ValorIngresado;
        arbol->insert(ValorIngresado);
    }
    cout << "Arbol trasversal:"<<endl;
    arbol->printTree();

    //getch();
}