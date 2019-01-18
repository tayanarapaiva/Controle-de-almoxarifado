#include "item.h"

Item::Item()
{

}

Item::Item(QString n, QString tag)
{
    setNome(n);
    setTagDoItem(tag);
}

void Item::setData(const QString &value)
{
    data = value;
}

void Item::setNomeEmprestimo(const QString &value)
{
    nomeEmprestimo = value;
}

QString Item::getNomeEmprestimo() const
{
    return nomeEmprestimo;
}

QString Item::getData() const
{
    return data;
}

bool Item::getDispo() const
{
    return dispo;
}

void Item::setDispo(bool value)
{
    dispo = value;
}

QString Item::getTagDoItem() const
{
    return tagDoItem;
}

void Item::setTagDoItem(const QString &value)
{
    tagDoItem = value;
}

QString Item::getNome() const
{
    return nomeDoItem;
}

void Item::setNome(const QString &value)
{
    nomeDoItem = value;
}
