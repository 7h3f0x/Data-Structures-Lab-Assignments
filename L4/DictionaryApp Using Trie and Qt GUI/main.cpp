#include "dictionaryapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DictionaryApplication w;
    w.show();

    return a.exec();
}
