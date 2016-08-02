#include "node.h"

node::node(int key)
{
    this->_key = key;
    this->_height = 1;
    this->_parent = NULL;
    this->_left = NULL;
    this->_right = NULL;
    this->_radius = 50;
}

node::node()
{
    this->_height = 1;
}

node::~node()
{
}

void node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // If it doesn't have a parent, then it is root..
    if(this->getParent() == NULL)
    {
        painter->setPen(QPen(QColor(Qt::red)));
        this->setPos(0, -100);
        painter->drawEllipse(0, -100, this->getRadius(), this->getRadius());
        painter->drawText(QRectF(this->mapToParent(0,0),QSizeF(50,50)), Qt::AlignCenter, QString::number(this->getKey()));
    }
    // Not root
    else
    {
        painter->setPen(QPen(QColor(Qt::black)));
        if(this->isLeft())
        {
            this->setPos(this->getParent()->x()-50, this->getParent()->y()+50);
            painter->drawEllipse(this->getParent()->x()-50, this->getParent()->y()+50, this->getRadius(), this->getRadius());
            painter->drawText(QRectF(this->mapToParent(0,0),QSizeF(50,50)), Qt::AlignCenter, QString::number(this->getKey()));
            painter->drawLine(QPointF(this->getParent()->x()+this->getRadius(), this->getParent()->y()), QPointF(this->x()+this->getRadius(), this->y()));
        }
        else if(this->isRight())
        {
            this->setPos(this->getParent()->x()+50, this->getParent()->y()+50);
            painter->drawEllipse(this->getParent()->x()+50, this->getParent()->y()+50, this->getRadius(), this->getRadius());
            painter->drawText(QRectF(this->mapToParent(0,0),QSizeF(50,50)), Qt::AlignCenter, QString::number(this->getKey()));
            painter->drawLine(QPointF(this->getParent()->x(), this->getParent()->y()), QPointF(this->x(), this->y()));
        }
    }
}

qreal node::getRadius()
{
    return this->_radius;
}

QRectF node::boundingRect() const
{
    qreal adjust = 1.0;
    return QRectF(-100/2 - adjust, -100/2 - adjust, 100 + adjust, 100 + adjust);
}

QPainterPath node::shape() const
{
    QPainterPath path;
    path.addRect(-100/2, -100/2, 100, 100);
    return path;
}

void node::setKey(int key)
{
    this->_key = key;
}

void node::setHeight(int h)
{
    this->_height = h;
}

void node::setLeft(node *l)
{
    this->_left = l;
}

void node::setRight(node *r)
{
    this->_right = r;
}

void node::setParent(node *p)
{
    if(p != NULL)
        this->_parent = p;
}

bool node::isLeft()
{
    if(this->getParent() != NULL)
        return (this->getKey() < this->getParent()->getKey());
    else
        return false;
}

bool node::isRight()
{
    if(this->getParent() != NULL)
        return (this->getKey() > this->getParent()->getKey());
    else
        return false;
}

node *node::getLeft()
{
    return this->_left;
}

node *node::getRight()
{
    return this->_right;
}

node *node::getParent()
{
    return this->_parent;
}

int node::getHeight()
{
    return this->_height;
}

int node::getKey()
{
    return this->_key;
}
