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
    cout <<"Indicar el grado de variable: ";
    cin >> grado;
    BtreeP* arbol = new BtreeP(grado);

    //-----------------TEST-------------------
    //arbol->test_getPadre();
    //arbol->test_valorMedioPerteneceANodo();
    //arbol->test_posicionDelElementoMedio();
    //arbol->test_buscarMedio();//para hacer este test correctamente se debe descomentar
    // los cout en la funcion buscarMedio.
    //arbol->test_cantidadDeClavesOcupadas();
    //arbol->test_buscarValor();
    //arbol->test_buscarNodoEnDondeInsertarValorIngresado();
    //arbol->test_separarNodo();
    arbol->test_organizarPunterosHijosDePadre();
    //--------------------------------------------

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