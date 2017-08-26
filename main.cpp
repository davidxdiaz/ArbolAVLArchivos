#include <iostream>
#include "arbolavl.h"
using namespace std;

int main()
{
    DataFile * archivo = new DataFile("C:\\Users\\David\\Desktop\\Indices.data");
    archivo->abrir();
    ArbolAVL * arbol = new ArbolAVL(archivo);
    arbol->add(10,0);
    arbol->add(5,0);
    arbol->add(13,0);
    arbol->add(1,0);
    arbol->add(6,0);
    arbol->add(17,0);
    //arbol->add(16);
    arbol->preOrden(arbol->raiz);
    archivo->cerrar();

    return 0;
}
