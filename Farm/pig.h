#ifndef PIG_H
#define PIG_H

#include <QObject>

//头文件不要互相包含


class Pig : public QObject
{
    Q_OBJECT
public:
    explicit Pig(QObject *parent = nullptr);
    Pig(const Pig & d) ;
    ~Pig() ;


private:
public:

    static int pigID ; //总编号

    int id ; //圈中id

    double weight ; //体重

    int raisetime ; //饲养时间

    int issick = 0 ; //零正常，一生病

    enum Color {black = 1 , sflower , bflower } color ; //颜色

    // Pig* pignext ; //链表指针

public:
    bool iscansell (Pig pig) ; // 判断是否可以售卖

    void grow (Pig* pig ) ; //猪的体重和养殖时长增长


signals:

};

#endif // PIG_H
