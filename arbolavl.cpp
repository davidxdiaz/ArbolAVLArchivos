#include "arbolavl.h"
#include "nodo.h"
#include "datafile.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

ArbolAVL::ArbolAVL(DataFile * a)
{
    raiz=0;
    cant=0;
    archivo=a;
}

//Agregar
void ArbolAVL::add(Nodo * n)
{
    insertar(raiz,n);
    cant++;
}

//Agregar Recursivamente
void ArbolAVL::insertar(Nodo *&sraiz,Nodo * n)
{
    if(sraiz==0)
    {
        sraiz=n;
        return;
    }
    if(sraiz->valor > n->valor)
        insertar(sraiz->izquierdo,n);
    insertar(sraiz->derecho,n);
}

//Buscar
Nodo * ArbolAVL::buscar(int v)
{
    return buscarAux(v,raiz);
}

//Buscar Recursivamente
Nodo * ArbolAVL::buscarAux(int v,Nodo *&r)
{
    if(r==0)
        return 0;
    else if(r->valor==v)
    {
        return r;
    }
    else if(r->valor>v)
        return buscarAux(v,r->izquierdo);
    return buscarAux(v,r->derecho);
}

//Obtener Factor de equilibrio
int ArbolAVL::obtenerFE(Nodo * n)
{
    if(n==0)
    {
        return -1;
    }
    else
    {
        return n->fe;
    }
}

Nodo * ArbolAVL::rotacionIzquierda(Nodo *r)
{
    Nodo * hijoDer=r->derecho;
    r->derecho=hijoDer->izquierdo;
    hijoDer->izquierdo=r;
    int c=obtenerFE(r->izquierdo);
    int d=obtenerFE(r->derecho);
    r->fe=(c>d ? c:d)+1;
    int a=obtenerFE(hijoDer->izquierdo);
    int b=obtenerFE(hijoDer->derecho);
    hijoDer->fe= (a>b ? a:b)+1;
    return hijoDer;
}

Nodo* ArbolAVL::rotacionDerecha(Nodo *r)
{
    Nodo * hijoIz=r->izquierdo;
    r->izquierdo=hijoIz->derecho;
    hijoIz->derecho=r;
    int c=obtenerFE(r->izquierdo);
    int d=obtenerFE(r->derecho);
    r->fe=(c>d ? c:d)+1;
    int a=obtenerFE(hijoIz->izquierdo);
    int b=obtenerFE(hijoIz->derecho);
    hijoIz->fe= (a>b ? a:b)+1;
    return hijoIz;
}

Nodo * ArbolAVL::rotacionDIzquierda(Nodo *r)
{

}

Nodo * ArbolAVL::rotacionDDerecha(Nodo *r)
{

}

char * ArbolAVL::toChar()
{
    int pos=0;
    char * entry_data= new char[22*cant];
    return toCharAux(raiz,pos,entry_data);
}

char * ArbolAVL::toCharAux(Nodo *&r,int pos,char * data)
{
    if(r==0)
        return data;
    char * data_entry= r->toChar();
    memcpy(&data[pos],data_entry,22);
    pos+=22;
    toCharAux(r->izquierdo,pos,data);
    toCharAux(r->derecho,pos,data);
}

void ArbolAVL::initFromChar(char * data)
{
    int pos=0;
    Nodo * r=initAux(data,pos);
    add(r);
}

Nodo * ArbolAVL::initAux(char * data,int pos)
{
    char * data_entry= new char[22];
    memcpy(data_entry,&data[pos],22);
    Nodo * r=new Nodo(0,0);
    r->initFromChar(data_entry);
    pos+=22;
    if(r->iz)
        r->izquierdo=initAux(data,pos);
    else
        r->izquierdo=0;
    if(r->der)
        r->derecho=initAux(data,pos);
    else
        r->derecho=0;
    return r;
}

void ArbolAVL::escribir()
{
    char * data= this->toChar();
    int tam= cant*22;
    archivo->escribir(data,0,tam);
}

void ArbolAVL::cargar()
{
    char * data=archivo->leer(0,archivo->getTam());
    initFromChar(data);
}

void ArbolAVL::preOrden(Nodo *&r)
{
    if(r==0) return;
    cout << r->valor<<endl;
    preOrden(r->izquierdo);
    preOrden(r->derecho);
}




