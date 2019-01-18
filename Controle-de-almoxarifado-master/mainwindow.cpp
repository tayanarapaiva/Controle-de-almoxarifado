#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serial, SIGNAL(readyRead()), this, SLOT(leitura()));
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(salvar()));
    connect(ui->actionCarregar,SIGNAL(triggered()), this, SLOT(carregar()));
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}


QString MainWindow::getTemp() const
{
    return temp;
}

void MainWindow::setTemp(const QString &value)
{
    temp = value;
}

void MainWindow::inserirItemTabela(Item a, int row)
{
    QTableWidgetItem *dispo;
    ui->tabela->setItem(row, 0, new QTableWidgetItem(a.getNome()));
    ui->tabela->setItem(row, 1, new QTableWidgetItem(a.getTagDoItem()));
    if(a.getDispo()){
        dispo = new QTableWidgetItem("Disponível");
        dispo->setTextColor("green");
        ui->tabela->setItem(row, 2, dispo);
    }else{
        dispo = new QTableWidgetItem("Não disponível");
        dispo->setTextColor("red");
        ui->tabela->setItem(row, 2, dispo);
    }
}

void MainWindow::inserirItemTabelaEmprestismos(Item a, int row)
{

    ui->tabelaEmprestimo->setItem(row, 0, new QTableWidgetItem(a.getNomeEmprestimo()));
    ui->tabelaEmprestimo->setItem(row, 1, new QTableWidgetItem(a.getNome()));
    ui->tabelaEmprestimo->setItem(row, 2, new QTableWidgetItem(a.getData()));
}

bool MainWindow::salvarAlmoxarifado(QString nomeArquivo, Almoxarifado x)
{
    QFile file(nomeArquivo);
    novoItem = new Item;
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QTextStream out(&file);

    for(int i=0;i<x.tamanho();i++){
        novoItem = almoxarifado.retornoItem(i);
        out << novoItem->getNome() <<","<<novoItem->getTagDoItem()<<",";
        out <<novoItem->getDispo()<<","<<novoItem->getNomeEmprestimo()<<",";
        out <<novoItem->getData()<<"\n";
    }

    file.close();
    delete novoItem;
    return true;

}

bool MainWindow::carregarAlmoxarifado(QString nomeArquivo, Almoxarifado x)
{
    QFile file(nomeArquivo);
    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }else{
        QTextStream in(&file);
        QString linha;
        novoItem = new Item;
        while(!in.atEnd()){
            linha = in.readLine();
            QStringList dados = linha.split(",");
            novoItem->setNome(dados[0]);
            novoItem->setTagDoItem(dados[1]);
            if(dados[2]=='1'){
                novoItem->setDispo(true);
            }else{
                novoItem->setDispo(false);
            }
            novoItem->setNomeEmprestimo(dados[3]);
            novoItem->setData(dados[4]);

            x.pushBackItem(*novoItem);
        }
    }
    file.close();
    delete novoItem;
    return true;

}


void MainWindow::on_btn_okPortaSerial_clicked()
{
    QString nomePorta = ui->le_portaSerial->text();
    serial.setPortName(nomePorta);
    serial.setBaudRate(QSerialPort::Baud115200);

    if(serial.open(QIODevice::ReadWrite)){
        QMessageBox::information(this, " ", "Conectado com sucesso!");
        ui->lbl_leitura->setText("Aproxime o item do leitor... ");
        ui->lbl_msgEmprestimo->setText("Aproxime o item do leitor... ");

    }else{
        QMessageBox::warning(this, " ","Não foi possivel conectar com a porta!");
    }
}


void MainWindow::leitura()
{
    QString tag = serial.readAll();
    if(tag.startsWith("{") && tag.endsWith("}")){

        setTemp(tag.replace("{",""));
        setTemp(tag.replace("}",""));

        if(almoxarifado.compareItem(getTemp())==-1){
            ui->lbl_leitura->setText("Leitura concluida!");
            ui->lbl_msgEmprestimo->setText("Item não encontrado!");

        }else{
            ui->lbl_leitura->setText("Esse item já foi cadastrado, tente novamente.");
            ui->lbl_msgEmprestimo->setText("Leitura concluída!");
        }
    }
}

void MainWindow::on_Inserir_clicked()
{

    QString nome = ui->le_nomeObjeto->text();

    if(almoxarifado.compareItem(getTemp()) ==-1 && ui->le_nomeObjeto->text() != 0){

        Item a (nome, getTemp());
        a.setDispo(true);
        a.setNomeEmprestimo(" ");
        a.setData(" ");

        ui->le_nomeObjeto->clear();
        ui->le_nomeObjeto->setFocus();

        almoxarifado.pushBackItem(a);

        int linhas = ui->tabela->rowCount();
        ui->tabela->insertRow(linhas);
        inserirItemTabela(a, linhas);

        QMessageBox::information(this, "", "Item salvo com sucesso!");
        ui->lbl_leitura->setText("Aproxime o item do leitor...");
        ui->lbl_msgEmprestimo->setText("Aproxime o item do leitor...");

    }else{
        QMessageBox::critical(this, " ", "Item já existente, tente fazer a leitura novamente.");
    }

}



void MainWindow::on_btn_emprestimo_clicked()
{
    int aux = almoxarifado.compareItem(getTemp());
    Item *a = almoxarifado.retornoItem(aux);

    if(ui->le_nomeEmprestimo->text()!=0 && aux != -1 && a->getDispo()){

        QString nome = ui->le_nomeEmprestimo->text();
        ui->le_nomeEmprestimo->clear();

        QString data = ui->de_emprestimo->text();
        ui->le_nomeEmprestimo->setFocus();

        almoxarifado.emprestimo(nome, data, aux);
        QMessageBox::information(this, "Empréstimo", "Item emprestado ao almoxarifado com sucesso!");

    }else if(aux !=-1 && !a->getDispo()){
        almoxarifado.emprestimo(a->getNomeEmprestimo(), a->getData(), aux);
        QMessageBox::information(this, "Empréstimo", "Item devolvido ao almoxarifado com sucesso!");
    }else{
        QMessageBox::critical(this, "Empréstimo", "Esse item não foi encontrado no almoxarifado, tente novamente.");
    }

    ui->tabela->clearContents();
    ui->tabelaEmprestimo->clearContents();

    aux = 0;
    for(int i = 0; i < almoxarifado.tamanho(); i++){

        Item *x = almoxarifado.retornoItem(i);
        inserirItemTabela(*x, i);

        if(!x->getDispo()){
            inserirItemTabelaEmprestismos(*x, aux);
            aux++;
        }
    }
    ui->lbl_leitura->setText("Aproxime o item do leitor... ");
    ui->lbl_msgEmprestimo->setText("Aproxime o item do leitor... ");

}
            
void MainWindow::salvar(){
    QString nome = QFileDialog::getSaveFileName(this,"Almoxarifado","","Texto Puro(*.txt);;Arquivos Separado por Vírgulas(*.csv)");
    if( salvarAlmoxarifado(nome, almoxarifado) ){
        QMessageBox::information(this, "Salvar almoxarifado","Salvo com sucesso!");
    }else{
        QMessageBox::information(this, "Salvar almoxarifado","Infelizmente, não foi possível salvar os dados!");
    }
}

void MainWindow::carregar(){
    novoItem = new Item;
    almoxarifado.clear();
    QString nome = QFileDialog::getOpenFileName(this,"Almoxarifado", "", "Texto Puro(*.txt);;Arquivos Separados por Vírgulas(*.csv)");
    if(carregarAlmoxarifado(nome, almoxarifado)){

        ui->tabela->clearContents();
        ui->tabelaEmprestimo->clearContents();
        int aux =0;
        for(int i=0; i<almoxarifado.tamanho(); i++ ){
            if(i>=ui->tabela->rowCount()){
                ui->tabela->insertRow(i);
            }
            novoItem = almoxarifado.retornoItem(i);
            inserirItemTabela(*novoItem, i);
            if(!novoItem->getDispo()){
                ui->tabelaEmprestimo->insertRow(aux);
                inserirItemTabelaEmprestismos(*novoItem, aux);
                aux++;
            }
        }
    }else{
        QMessageBox::information(this, "Almoxarifado","Infelizmente, não foi possível carregar os dados!");
    }
}
