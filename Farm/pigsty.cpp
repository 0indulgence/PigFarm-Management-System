#include "pigsty.h"

Pigsty::Pigsty(QObject *parent)
    : QObject{parent}
{

}

Pigsty::Pigsty(const Pigsty &t)
{
    pigstyID = t.pigstyID ;
    for(int i = 0 ; i < 4 ; i++)
    {
        amount[i] = t.amount[i] ;
    }
    for(int m = 0 ; m < 10 ; m++)
    {
        sty[m].id = t.sty[m].id ;
        sty[m].weight = t.sty[m].weight ;
        sty[m].raisetime = t.sty[m].raisetime ;
        sty[m].issick = t.sty[m].issick ;
        sty[m].color = t.sty[m].color ;
    }
    pigstynext = NULL ;
}


Pigsty::~Pigsty()
{

}
