#include "bstviewer.h"
#include "ui_bstviewer.h"
#include <QDebug>
#include <QGraphicsEllipseItem>

BSTViewer::BSTViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BSTViewer)
{
    ui->setupUi(this);
    this->_scene = new QGraphicsScene();
    this->_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->_scene->setSceneRect(-500,-250,1000,500);
    ui->treeDisplay->fitInView(this->_scene->sceneRect());
    ui->treeDisplay->setScene(this->_scene);
    ui->treeDisplay->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    avl = new AVL();
    min_heap_ptr = new min_heap();
    bst = new binary_search_tree();
}

BSTViewer::~BSTViewer()
{
    delete ui;
}

void BSTViewer::on_stepbystepButton_clicked()
{
    // Clear screen
    this->_scene->clear();
    // Clear queue
    while(!this->_currentNodes.empty()) this->_currentNodes.pop();
    // Clear structures
    avl->makeEmpty();
    bst->makeEmpty();
    // Get values
    QStringList val = this->ui->treeValues->text().split(",");
    for(QString x : val)
    {
        std::cout << x.toStdString().c_str() << std::endl;
        // If the input is actually a value
        if(x != "")
        {
            node* n = new node(x.toInt());
            switch(this->ui->treetypeCombo->currentIndex())
            {
            case 0: avl->insert(n); avl->inorder(&this->_currentNodes); break;
            case 1: bst->insert(n); bst->inorderTraversal(&this->_currentNodes); break;
            case 2: std::cout << "minheap insert.." << std::endl; break;
            case 3: std::cout << "maxheap insert.." << std::endl; break;
            default: avl->insert(n);
            };
        }
    }
    // Loop through the queue of nodes and draw them
    while(!this->_currentNodes.empty())
    {
        node* n = this->_currentNodes.front();
        this->_scene->addItem(n);
        this->_scene->setSceneRect(this->_scene->itemsBoundingRect());
        this->_currentNodes.pop();
    }
}

void BSTViewer::on_treeValues_textChanged(const QString &arg1)
{

}
