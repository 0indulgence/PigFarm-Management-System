#include "pig.h"

#include <pigfarm.h>
using namespace std ;

  int pigID  = 1 ;

Pig::Pig(QObject *parent)
    : QObject{parent}
{

}

Pig::Pig(const Pig &d)
{
    id = d.id ;
    weight = d.weight ;
    raisetime = d.raisetime ;
    issick = d.issick ;
    color = d.color ;
}
Pig::~Pig()
{

}

bool Pig::iscansell(Pig pig)
{
    return (pig.weight >= 150 || pig.raisetime >= 360) ;        //可difine
}

void Pig::grow(Pig *pig)   //每头猪的每日增长
{
    pig->raisetime++ ;
    srand( (unsigned int )time(NULL)) ; //srand（int）函数是产生随机数种子的。在产生随机数rand（）被调用的时候
                                  // 会查看，如果用户之前调用过srand(seed)的话 ， 他会重新调用一遍srand(seed)
                                  // 以产生随机数种子，如果发现没有调用过srand（seed）的话，会调用srand(1)一次
                                  // 若希望每次rand()调用产生的值不一样，就需要每次调用srand（seed）一次，而且seed不能相同。
                                  //一般用for循环来设置种子
    pig->weight += (double)(rand()%12)/10.0 ; // 0到1.2kg增长
    return ;
}

