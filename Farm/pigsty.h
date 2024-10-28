#ifndef PIGSTY_H
#define PIGSTY_H

#include <QObject>
#include <pig.h>


class Pigsty : public QObject
{
    Q_OBJECT
public:
    explicit Pigsty(QObject *parent = nullptr);
    Pigsty(const Pigsty & t) ;
     ~Pigsty() ;

 private:




 public:

    // double sellpig (Pigsty) ; //猪圈中卖猪

 public:
     int pigstyID ; //猪圈编号

     int amount[4]; //猪圈中含有猪的数量0 , 黑猪1 , 小白花猪2 , 大花猪3

     Pigsty* pigstynext ; // 猪圈链表的指针


     Pig sty[10] ;
signals:

};

#endif // PIGSTY_H
