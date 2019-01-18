#include "almoxarifado.h"

Almoxarifado::Almoxarifado()
{

}

void Almoxarifado::pushBackItem(Item a)
{
    almoxarifado.push_back(a);
}

int Almoxarifado::compareItem(QString tag)
{
    for(int i=0; i < almoxarifado.size(); i++){
        if(almoxarifado[i].getTagDoItem() == tag){
            return i;
        }
    }
    return -1;
}

void Almoxarifado::emprestimo(QString nome, QString data, int x)
{
    if(almoxarifado[x].getDispo()){
        almoxarifado[x].setNomeEmprestimo(nome);
        almoxarifado[x].setData(data);
        almoxarifado[x].setDispo(false);
    }else{
        almoxarifado[x].setNomeEmprestimo(" ");
        almoxarifado[x].setData(" ");
        almoxarifado[x].setDispo(true);
    }
}

Item *Almoxarifado::retornoItem(int x)
{
    return &almoxarifado[x];
}

void Almoxarifado::clear()
{
    almoxarifado.clear();
}

int Almoxarifado::tamanho()
{
    return almoxarifado.size();
}
