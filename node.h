#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <QGraphicsEllipseItem>
#include <QPainter>

//struct node // the structure for representing tree nodes
//{
//    int key;
//    unsigned char height;
//    node* left;
//    node* right;
//    node(int k) { key = k; left = right = NULL; height = 1; }
//};

class node : public QGraphicsEllipseItem
{
private:
    int _key, _height;
    node* _left, *_right, *_parent;
    qreal _radius;
public:
    node(int key);
    node();
    ~node();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal getRadius();
    QRectF boundingRect() const;

    void setKey(int);
    void setHeight(int h);
    void setLeft(node*);
    void setRight(node*);
    void setParent(node*);

    bool isLeft();
    bool isRight();
    node* getLeft();
    node* getRight();
    node* getParent();
    int getHeight();
    int getKey();
    QPainterPath shape() const;
};

#endif // NODE_H
