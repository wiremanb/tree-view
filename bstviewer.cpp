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
    ui->treeDisplay->setSceneRect(-500,-250,1000,500);
    //    this->_scene->setSceneRect();
    //    ui->treeDisplay->fitInView(this->_scene->sceneRect());
    ui->treeDisplay->setScene(this->_scene);
    ui->treeDisplay->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    avl = new AVL();
    min_heap_ptr = new min_heap();
    bst = new binary_search_tree();

    ui->treeValues->setText("1,2,3,4");
}

BSTViewer::~BSTViewer()
{
    delete ui;
}

void BSTViewer::on_stepbystepButton_clicked()
{

}

void BSTViewer::on_treeValues_textChanged(const QString &arg1)
{
    this->updateTree();
}

void BSTViewer::updateTree()
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
        //std::cout << x.toStdString().c_str() << std::endl;
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
        this->_currentNodes.pop();
    }
    QRectF bounds = this->_scene->itemsBoundingRect();
    bounds.setWidth(bounds.width()*0.9);         // to tighten-up margins
    bounds.setHeight(bounds.height()*0.9);       // same as above
    this->_scene->update(bounds);
    ui->treeDisplay->centerOn(0, 0);
}

void BSTViewer::on_treetypeCombo_currentIndexChanged(int index)
{
    this->updateTree();
}
