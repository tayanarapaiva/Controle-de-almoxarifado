#ifndef ITEM_H
#define ITEM_H
#include <QMainWindow>

class Item
{
public:
    Item();
    Item (QString n, QString tag);

    QString nomeDoItem;
    QString tagDoItem;
    bool dispo;
    QString data;
    QString nomeEmprestimo;

    QString getNome() const;
    void setNome(const QString &value);

    QString getTagDoItem() const;
    void setTagDoItem(const QString &value);

    bool getDispo() const;
    void setDispo(bool value);

    QString getData() const;
    QString getNomeEmprestimo() const;

    void setNomeEmprestimo(const QString &value);
    void setData(const QString &value);
};

#endif // ITEM_H
