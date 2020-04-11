#include "dictionaryapplication.h"
#include "ui_dictionaryapplication.h"


DictionaryApplication::DictionaryApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DictionaryApplication)
{
    ui->setupUi(this);
    dictionary = new Dictionary();
    dictionary->getFromFile("L4_P1_input.csv");
}

DictionaryApplication::~DictionaryApplication()
{
    delete ui;
}

void DictionaryApplication::on_pushButton_clicked()
{
    std::string key = ui->lineEdit_key->text().toStdString();
    std::string meaning = dictionary->retrieveMeaning(key);
    ui->textBrowser_meaning->setText(QString::fromStdString(meaning));
}
