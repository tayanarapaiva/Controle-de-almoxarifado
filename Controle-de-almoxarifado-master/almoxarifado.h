#ifndef ALMOXARIFADO_H
#define ALMOXARIFADO_H

#include "item.h"
#include <QVector>
#include <algorithm>

class Almoxarifado
{
public:
    Almoxarifado();
    QVector <Item> almoxarifado;

    void pushBackItem(Item a);
    int compareItem(QString tag);
    void emprestimo (QString nome, QString data, int x);
    Item *retornoItem(int x);
    void clear();
    int tamanho();

};

#endif // ALMOXARIFADO_H
