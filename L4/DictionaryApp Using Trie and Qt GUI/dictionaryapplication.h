#ifndef DICTIONARYAPPLICATION_H
#define DICTIONARYAPPLICATION_H

#include <QMainWindow>
#include "prob1.cpp"
namespace Ui {
class DictionaryApplication;
}

class DictionaryApplication : public QMainWindow
{
    Q_OBJECT
public :
    Dictionary* dictionary;
public:
    explicit DictionaryApplication(QWidget *parent = nullptr);
    ~DictionaryApplication();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DictionaryApplication *ui;
};

#endif // DICTIONARYAPPLICATION_H
