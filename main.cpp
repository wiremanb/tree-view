#include "bstviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BSTViewer w;
    w.show();

    return a.exec();
}
