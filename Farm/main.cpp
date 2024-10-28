#include "farmdialog.h"
#include <pigfarm.h>
#include <QApplication>
#include <bits/stdc++.h> //万能头文件，相当于一系列头文件代码的总和
#include <fstream>
using namespace std ;


double Price[4] = {0.0 , 15.0 , 7.0 , 6.0} ; //全局变量，记录卖猪价钱
ofstream fout ("Sell.txt", ios::app|ios::out  ) ;  // 全局变量，输出流1
ofstream dataout ("data.txt" , ios::app|ios::out) ;  //退出时
ofstream timeout ("time.txt" , ios::app|ios::out) ;  //退出时
ifstream datain ("data.txt" , ios::in) ;
ifstream timein ("time.txt" , ios::in) ;
PigFarm pfarm ; //全局变量创建农场
int SICK [101][11] = {{0}} ;  // 模拟瘟疫，初始化零
int comeon [3] = {0 , 0 , 0} ;
int pig_raisetime_count [5] ;  // 0-90,90-180,180-270,270-360,360-  只有pigraisetime_count可改变
int pig_weight_count [5] ; // 20-50,50-80,80-110,110-150,150-  只有pigweight_count可改变
int b_pigsty_number ;

//1号猪圈有点问题


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

  /*  int b_number = 132 ;
    int sf_number = 155 ;
    int bf_number = 245 ;
            PigFarm* pfarm ;



  pfarm = PigFarm::FirstCreatePigfarm( b_number,  sf_number,  bf_number) ;*/



   farmDialog w;




                                      //  PigFarm* pfarm ;

/*
    Pigsty* text = pfarm->pigstyhead ;
    for (int i = 1 ; i < 98 ; i++)            //pigstyID 1-100 ， pig的id 0-9
    {
        text = text->pigstynext ;
    }
     qDebug() << text->sty[4].color << text->sty[7].weight << text->sty[7].id ;
*/
   w.show();




    return a.exec();
    fout.close() ;
    return 0 ;
}
