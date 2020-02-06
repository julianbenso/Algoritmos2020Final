//
// Created by julian on 6/2/20.
//

#ifndef FINAL2_BTREEP_H
#define FINAL2_BTREEP_H


class BtreeP {
    struct BpTreeNode
    {
        int *data; // NO SE PUEDEN INSERTAR CEROS 0, no se va a imprimir
        BpTreeNode **child_ptr;
        bool leaf;
        int n;//cantidad de lugares ocupados en el nodo
    }

};


#endif //FINAL2_BTREEP_H
