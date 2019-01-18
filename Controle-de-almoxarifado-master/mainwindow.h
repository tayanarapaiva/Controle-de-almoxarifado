#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QFileDialog>
#include "item.h"
#include "almoxarifado.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString temp;
    QSerialPort serial;
    Almoxarifado almoxarifado;
    Item *novoItem;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getTemp() const;
    void setTemp(const QString &value);
    void inserirItemTabela(Item a, int row);
    void inserirItemTabelaEmprestismos(Item a, int row);
    bool salvarAlmoxarifado(QString nomeArquivo, Almoxarifado x);
    bool carregarAlmoxarifado(QString nomeArquivo, Almoxarifado x);

private slots:

    void leitura();

    void salvar();

    void carregar();

    void on_btn_okPortaSerial_clicked();

    void on_Inserir_clicked();

    void on_btn_emprestimo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
