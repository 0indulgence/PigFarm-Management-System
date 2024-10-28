#ifndef PIGFARM_H
#define PIGFARM_H

#include <QObject>
#include <pig.h>
#include <pigsty.h>
#include<bits/stdc++.h>
#include<QFile>
using namespace std ;

extern double Price[4] ; //调用main中声明的全局变量
extern ofstream fout ; //调用main中声明的输出文件流
extern ofstream dataout ;
extern ifstream datain ;
extern int pig_raisetime_count [5] ;
extern int pig_weight_count [5] ;
extern int SICK [101] [11] ;


class PigFarm : public QObject
{
    Q_OBJECT
public:
      PigFarm(QObject *parent = nullptr);
    ~PigFarm() ;

private:

public:

  int Farm_Time = 0 ; //农场时间，用于整体的操作

  int Sick_Time = 0 ; //瘟疫后时间

  Pigsty* pigstyhead ;  // 猪圈链表的指针

  //int black = 0 ;  //纪录农场中三色猪数量
  //int sflower = 0 ;
  //int bflower = 0 ;

public:

   static PigFarm* FirstCreatePigfarm (int b_number , int sf_number , int bf_flower  ) ;

   static PigFarm* LoadPigfarm () ;

   static Pigsty* LoadPigsty() ;

  static int calculate ( int b_number , int sf_number , int bf_number , int& b_equal , int& sbf_equal ) ;

  static Pigsty* CreatePigsty (  int id , int b_pigstynumber , int& cur1number ,int& cur2number , int& cur3number , int b_equal , int sbf_equal ,int b_number, int sf_number, int bf_number) ;

   void    pigfarm_grow (PigFarm* pigfarm ) ; // 农场每日增长

   void printpig (PigFarm farm , int pigstyID , int id ) ; //打印当前某一猪圈某头猪的状态信息到文件

   void print_pig (Pig pig , int pigstyID) ; //卖猪时写进文件所用的函数

   void printpigsty (PigFarm* farm ,int pigstyID ) ; //打印某一猪圈猪数量和种类

   double sell_pig ( Pigsty* pigsty , int id ) ;   //卖猪

   double pigfarm_sell (PigFarm* farm) ; //农场定期售卖猪

   int pigcolor_count (PigFarm* farm , Pig::Color color) ;  //数各颜色猪个数

   int blackpigsty_count (PigFarm* farm) ;  //数黑猪圈个数

   void pigraisetime_count (PigFarm* farm ) ;   //统计猪的饲养时间分布

   void pigweight_count (PigFarm* farm) ; //统计猪的体重分布

   void pigfarm_buy (PigFarm* farm , int addb_number , int addsf_number , int addbf_number , int b_pigsty_number) ; //买猪

   void Dataout (PigFarm* farm) ; //退出时存信息

   void getsick (PigFarm *farm) ; //感染猪瘟

   void sick_continue (PigFarm *farm) ; //瘟疫蔓延

   bool is_all_sick (PigFarm* pfarm) ; // 判断是否全部中招

   bool is_all_cut () ; // 判断是否全部解决

   void transform (PigFarm* pfarm) ; //将数组信息传递给实际的猪

   bool cut (PigFarm* pfarm , int pigstyID , int id) ;  //单头猪的治愈

    //   void Datain (PigFarm* farm) ; //进入时读取信息       //  思考，深入






signals:

};

#endif // PIGFARM_H
