#ifndef BSTVIEWER_H
#define BSTVIEWER_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include "avl_tree/avl.h"
#include "min_heap/min_heap.h"
#include "bst/binary_search_tree.h"

namespace Ui {
class BSTViewer;
}

class BSTViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit BSTViewer(QWidget *parent = 0);
    ~BSTViewer();

private slots:
    void on_stepbystepButton_clicked();

    void on_treeValues_textChanged(const QString &arg1);

private:
    Ui::BSTViewer *ui;

    QGraphicsScene* _scene;
//    treeScene* _scene;
    AVL* avl;
    min_heap* min_heap_ptr;
    binary_search_tree* bst;
    std::queue<node*> _currentNodes;
};

#endif // BSTVIEWER_H
