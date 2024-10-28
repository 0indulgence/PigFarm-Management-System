#include "pigfarm.h"
#include <QDebug>



PigFarm::PigFarm(QObject *parent)
    : QObject{parent}
{

}


PigFarm::~PigFarm()
{

}

 PigFarm* PigFarm::FirstCreatePigfarm( int b_number, int sf_number, int bf_number)
{

    //初始化农场基本信息
    PigFarm* pfarm = new PigFarm ;
    pfarm->Farm_Time = 0 ;

    int b_equal , sbf_equal ;
    int  cur1number = 0 ,cur2number = 0 , cur3number = 0 ;
    int  b_pigstynumber = pfarm->calculate(b_number, sf_number,bf_number, b_equal , sbf_equal) ;

                        // Pigsty* temp_pigsty = new Pigsty ;          //未delete
                         // pfarm.pigstyhead = temp_pigsty ;
    pfarm->pigstyhead = NULL ;

    for(int i = 100 ; i >= 1 ; i--)
    {

       Pigsty* temp = CreatePigsty(i,b_pigstynumber,cur1number,cur2number,cur3number ,b_equal,sbf_equal,b_number,sf_number,bf_number ) ;
       temp->pigstynext = pfarm->pigstyhead ;
        pfarm->pigstyhead = temp ;
    }


    qDebug() << "建设完毕" << b_equal << "a" << sbf_equal <<"b" << b_pigstynumber ;


    return pfarm ;
 }


 PigFarm *PigFarm::LoadPigfarm()
 {
     //初始化农场基本信息
     PigFarm* pfarm = new PigFarm ;
     Pigsty* temp = LoadPigsty() ;
     pfarm->pigstyhead = temp ;
     Pigsty* Q = temp ;

     for(int i = 100 ; i >= 2 ; i--)
     {
         Pigsty* temp = LoadPigsty() ;
         Q->pigstynext = temp ;
         Q = temp ;
     }
     return pfarm ;
 }


 Pigsty *PigFarm::LoadPigsty()
 {
     Pigsty* temp = new Pigsty ;
     double exchange ;
      datain >> exchange ;
      temp->pigstyID = exchange ;
      for(int i = 0 ; i < 4 ; i++)
      {
          datain >> exchange ;
          temp->amount[i]= exchange ;
      }

         for (int k = 0 ; k < 10 ; k++)
         {
             datain >> exchange  ;
             temp->sty[k].id = exchange ;
             datain >> exchange;     // 颜色这里有些特别，得转成枚举类型Color
             temp->sty[k].color = Pig::Color(exchange) ;
             datain >> exchange ;
             temp->sty[k].raisetime = exchange ;
             datain >> exchange ;
             temp->sty[k].weight  = exchange ;
         }


     return temp ;

 }



  //计算应如何分配猪圈
int PigFarm::calculate(int b_number, int sf_number, int bf_number, int &b_equal, int &sbf_equal)
{
    //黑猪平均分配计算
    int b_pigstynumber ;
    if(b_number % 10 == 0)
    {
        b_pigstynumber = b_number / 10 ;
        b_equal = b_number / b_pigstynumber ;
    }
    else
    {
        int w = b_number / 10 ;
        b_pigstynumber = w + 1 ;
        b_equal = b_number / b_pigstynumber ; //尽量平均，存在小问题
        b_equal++ ;
    }

    //花猪尽量平均分配计算
    int sbf_number = sf_number + bf_number ;

    int a  ; //花猪占猪圈总数
    a = 100 - b_pigstynumber ;

    if(sbf_number % a == 0)
    {
       sbf_equal = sbf_number / a ;
    }
    else
    {
        sbf_equal = sbf_number / a ;

        sbf_equal++ ;
    }
     return b_pigstynumber ;


}




//传黑猪所需圈数和当前生成黑猪花猪数目 , 存在小问题，比如空位的信息
Pigsty* PigFarm::CreatePigsty(   int id , int b_pigstynumber ,int& cur1number, int& cur2number , int& cur3number ,int b_equal , int sbf_equal  ,int b_number , int sf_number, int bf_number)
{

   Pigsty* newpigsty = new Pigsty ;
    newpigsty->pigstyID = id ; //设置猪圈id


    for(int i = 0 ; i < 4 ; i++)
    {
        newpigsty->amount[i] = 0 ;
        //在构造函数里做此，目的初始化
    }



    if(id <= b_pigstynumber)      //黑猪猪圈
    {
        for(int i = 0 ; i < b_equal; i++)
        {
            //黑猪猪初始化
            if(cur1number < b_number)
            {
                newpigsty->sty[i].id = i ;
                newpigsty->sty[i].raisetime = 0 ;
                newpigsty->sty[i].weight = (double)(rand()%31 + 20) ; //初始化体重20到50斤
                newpigsty->sty[i].color = (Pig::Color)1 ; //颜色初始化
                newpigsty->amount[1]++ ;
                newpigsty->amount[0]++ ;
                cur1number++  ;
            }

            if(cur1number > b_number )
            {
                newpigsty->sty[i].id = i ;
                newpigsty->sty[i].raisetime = 0 ;
                newpigsty->sty[i].weight = 0.0 ;
                newpigsty->sty[i].color = (Pig::Color)1 ;
            }
        }
        for (int j = b_equal ;  j < 10 ; j++)
        {
            newpigsty->sty[j].id = j ;
            newpigsty->sty[j].raisetime = 0 ;
            newpigsty->sty[j].weight = 0.0 ;
            newpigsty->sty[j].color = (Pig::Color)1 ;

        }


     }
    else //花猪猪圈
    {
        for(int i = 0 ; i < sbf_equal ; i++)
        {
            //花猪猪初始化
            newpigsty->sty[i].id = i ;
            newpigsty->sty[i].raisetime = 0 ;
            newpigsty->sty[i].weight = (double)(rand()%31 + 20) ; //初始化体重20到50斤

            //随机分配颜色
            if(cur2number < sf_number && cur3number < bf_number )
            {
                int RandomColor = rand()%2+2 ;
                newpigsty->sty[i].color = (Pig::Color)(RandomColor) ; //颜色初始化
                newpigsty->amount[RandomColor]++ ;
                 newpigsty->amount[0]++ ;
                if(RandomColor == 2)
                {
                    cur2number++  ;
                }
                else
                {
                    cur3number++ ;
                }
            }
            else if (cur2number < sf_number)
            {
                newpigsty->sty[i].color = (Pig::Color)2 ;
                newpigsty->amount[2]++ ;
                newpigsty->amount[0]++ ;
                cur2number++  ;
            }
            else if(cur3number < bf_number)
           {
                newpigsty->sty[i].color = (Pig::Color)3 ;
                newpigsty->amount[3]++ ;
                newpigsty->amount[0]++ ;
                cur3number++  ;
            }
            else
            {
                newpigsty->sty[i].id = i ;
                newpigsty->sty[i].raisetime = 0 ;
                newpigsty->sty[i].weight = 0.0 ;
            }
        }
        for ( int j = sbf_equal ; j < 10 ; j++)
        {
            newpigsty->sty[j].id = j ;
            newpigsty->sty[j].raisetime = 0 ;
            newpigsty->sty[j].weight = 0.0 ;
            newpigsty->sty[j].color = (Pig::Color)2 ;

        }

    }
    newpigsty->pigstynext = NULL ;
    return newpigsty ;
}




//农场每日增长
void PigFarm::pigfarm_grow(PigFarm *pigfarm)
{
    Farm_Time++ ;
  Pigsty* cur_pigsty = pigfarm->pigstyhead ;
  for (int i = 1 ; i <= 100 ; i++)
  {
        for(int j = 0 ; j < 10 ; j++)
        {
            if (cur_pigsty->sty[j].weight > 0)
            {
               cur_pigsty->sty[j].grow ( &cur_pigsty->sty[j]) ;
            }
        }
        cur_pigsty = cur_pigsty->pigstynext ;
  }
  return ;
}




//打印当前某一猪圈某头猪的状态信息 , 不记得用到了
void PigFarm::printpig(PigFarm farm, int pigstyID, int id)
{
                                    //  std::ofstream fout ; //std 是一个输入输出标准类 ，使用其之前加作用域解析
                                    //  fout.open("Sell.txt", ios::app|ios::out  ) ;
   Pigsty* temp = farm.pigstyhead ;
   for (int i = 1 ; i < pigstyID ; i++)            //pigstyID 1-100 ， pig的id 0-9
   {
       temp = temp->pigstynext ;
   }
   fout << "    猪圈编号：" << pigstyID << "     猪的编号：" << id << "     品种：" ;
   if (temp->sty[id].color == 1)
   {
       fout << "黑猪" ;
   }
   else if(temp->sty[id].color == 2)
   {
       fout << "小花猪" ;
   }
   else
   {
       fout << "大花白猪" ;
   }
   fout << "    饲养时间："  << temp->sty[id].raisetime << "     体重：" << temp->sty[id].weight << endl ;
                                       //fout.close() ;
}




//卖猪时可用
void PigFarm::print_pig(Pig pig, int pigstyID)
{
                            // std::ofstream fout ; //std 是一个输入输出标准类 ，使用其之前加作用域解析
                            // fout.open("Sell.txt", ios::app|ios::out  ) ;
    fout << "    猪圈编号：" << pigstyID << "     猪的编号：" << pig.id << "     品种：" ;
    if (pig.color == 1)
    {
        fout << "黑猪" ;
    }
    else if(pig.color == 2)
    {
        fout << "小花猪" ;
    }
    else if(pig.color == 3)
    {
        fout << "大花白猪" ;
    }
    fout << "    饲养时间："  << pig.raisetime << "     体重：" << pig.weight << endl ;
                             //  fout.close() ;
}




//打印某一猪圈主动数量和种类
void PigFarm::printpigsty(PigFarm* farm, int pigstyID)
{
                                //std::ofstream fout ; //std 是一个输入输出标准类 ，使用其之前加作用域解析
                                //fout.open("Sell.txt", ios::app|ios::out  ) ;
    Pigsty* temp = farm->pigstyhead ;
   for (int i = 1 ; i < pigstyID ; i++)            //pigstyID 1-100 ， pig的圈中id 0-9
   {
       temp = temp->pigstynext ;
   }
    fout << "第" << pigstyID << "个猪圈，当前猪圈中猪数目为：" << temp->amount[0] ;
   if(temp->amount[1] > 0)
   {
       fout << "黑猪数量：" << temp->amount[1]  << endl ;
   }
   else
   {
        fout << "小花猪数量：" << temp->amount[2] << "     大白花猪数量：" << temp->amount[3]  << endl ;
   }
    fout << "当前猪圈中可被出售猪的编号： " ;
   int count = 0 ;
   for (int i = 0  ; i < 10 ; i++)
   {
        if ( temp->sty[i].iscansell (temp->sty[i]))
        {
             fout << i << " " ;
            count ++ ;
        }
   }
   if (count == 0 )
   {
        fout << "无" ;
   }
  fout << endl ;
                                    //fout.close() ;
}




//卖猪
double PigFarm::sell_pig(Pigsty* pigsty, int id)
{
    Pig pig = pigsty->sty[id] ;
    print_pig( pig , pigsty->pigstyID ) ;
    double price = pig.weight * Price[pig.color] ;
                                 // fout << "卖猪得到" << price << "元 "  << endl ;
    pigsty->sty[id].raisetime = 0 ;
    pigsty->sty[id].weight = 0.0 ;
    pigsty->amount[0]-- ;
    pigsty->amount[pig.color]-- ;
   // pigsty->sty[id].issick = 0 ;
    return price ;
}





double PigFarm::pigfarm_sell(PigFarm* farm)
{
    fout << endl << "今天是农场第" << Farm_Time << "天" << endl ;
    Pigsty* temp = farm->pigstyhead ;
    double income = 0 ;
    fout << "   卖猪信息：   " << endl ;
    for (int i = 0 ; i < 100 ; i++)     //猪场内猪圈循环
    {
        for (int j = 0 ; j < 10 ; j++)      //猪圈内猪循环
        {
            if (temp->sty[j].iscansell(temp->sty[j]))
            {
                income += sell_pig(temp , j) ;
            }
        }
        temp = temp->pigstynext ;
    }
    fout << "卖猪总共得到" << income << "元" << endl ;
    return income ;
}




int PigFarm::pigcolor_count(PigFarm* farm, Pig::Color color)
{
    int num = 0 ;
    Pigsty* temp = farm->pigstyhead ;
    if (color == 1)
    {
        for ( int i = 1 ; i <= 100 ; i++)
        {
            num += temp->amount[1] ;
            temp = temp->pigstynext ;
        }
        return num ;
    }
    else if(color == 2)
    {
        for ( int i = 1 ; i <= 100 ; i++)
        {
            num += temp->amount[2] ;
            temp = temp->pigstynext ;
        }
        return num ;
    }
    else if (color == 3)
    {
        for ( int i = 1 ; i <= 100 ; i++)
        {
            num += temp->amount[3] ;
            temp = temp->pigstynext ;
        }
        return num ;
    }
    else
    {
        return 0 ;
    }
}




int PigFarm::blackpigsty_count(PigFarm* farm)
{
    Pigsty* temp = farm->pigstyhead ;
    int count = 0 ;
    for ( int i = 1 ; i <= 100 ; i++)
    {
        if (temp->amount[1] != 0)
        {
            count++ ;
        }
        temp = temp->pigstynext ;
    }
    return count ;


}


void PigFarm::pigraisetime_count(PigFarm *farm)
{
    for(int w= 0 ; w < 5 ; w++)   //数组归零
    {
        pig_raisetime_count[w] = 0 ;
    }

    Pigsty* temp = farm->pigstyhead ;
    for ( int i = 1 ; i <= 100 ; i++)
    {
       for(int j = 0 ; j < 10 ; j++)
      {
           if (temp->sty[j].raisetime >= 0 && temp->sty[j].raisetime < 90)
           {
               pig_raisetime_count[0]++ ;
           }
           else if(temp->sty[j].raisetime >= 90 && temp->sty[j].raisetime < 180)
           {
               pig_raisetime_count[1]++ ;
           }
           else if(temp->sty[j].raisetime >= 180 && temp->sty[j].raisetime < 270)
           {
               pig_raisetime_count[2]++ ;
           }
           else if(temp->sty[j].raisetime >= 270 && temp->sty[j].raisetime < 360)
           {
               pig_raisetime_count[3]++ ;
           }
           else if(temp->sty[j].raisetime >= 360)
           {
               pig_raisetime_count[4]++ ;
           }
      }
       temp = temp->pigstynext ;
    }
    return ;
}


void PigFarm::pigweight_count(PigFarm *farm)
{
    for(int w= 0 ; w < 5 ; w++)   //数组归零
    {
        pig_weight_count[w] = 0 ;
    }

    Pigsty* temp = farm->pigstyhead ;
    for ( int i = 1 ; i <= 100 ; i++)
    {
       for(int j = 0 ; j < 10 ; j++)
      {
           if (temp->sty[j].weight >= 20.0 && temp->sty[j].weight < 50.0)
           {
               pig_weight_count[0]++ ;
           }
           else if(temp->sty[j].weight >= 50.0 && temp->sty[j].weight < 80.0)
           {
               pig_weight_count[1]++ ;
           }
           else if(temp->sty[j].weight >= 80.0 && temp->sty[j].weight < 110.0)
           {
               pig_weight_count[2]++ ;
           }
           else if(temp->sty[j].weight >= 110.0 && temp->sty[j].weight < 150.0)
           {
               pig_weight_count[3]++ ;
           }
           else if(temp->sty[j].weight >= 150)
           {
               pig_weight_count[4]++ ;
           }
      }
       temp = temp->pigstynext ;
    }
    return ;
}


void PigFarm::pigfarm_buy(PigFarm *farm, int addb_number, int addsf_number, int addbf_number ,int b_pigsty_number) //在不动原猪位置的份上，尽量平均分配
{
    Pigsty* temp = farm->pigstyhead ;
    int sumb_number = addb_number + pigcolor_count( farm , Pig::black ) ;
    int sumsf_number = addsf_number + pigcolor_count(farm , Pig::sflower) ;
    int sumbf_number = addbf_number + pigcolor_count(farm , Pig::bflower) ;
    int b_equal = 0 , sbf_equal = 0 ;
    calculate(sumb_number , sumsf_number , sumbf_number , b_equal , sbf_equal) ; //要返回的b_equal,sbf_equal
    if (sumb_number % b_pigsty_number==0)
    {
      b_equal = sumb_number / b_pigsty_number ;
    }
    else
    {
         b_equal = sumb_number / b_pigsty_number ;
          b_equal++ ;
    }

    qDebug() << b_equal ;
    fout << " 今天是农场第" << Farm_Time <<"天" << endl ;
    fout << "   购猪信息：   " << endl ;

    for (int i = 1 ; i <= 100 ; temp = temp->pigstynext , i++) //猪圈循环
    {
        if(i <= b_pigsty_number) //黑猪圈
        {
            if (addb_number == 0)
            {
                continue ;
            }

            if (temp->amount[0] >= b_equal)
            {
                 //大于平均，不再加入 , 黑猪amount[0] == amount[1]
            }
            else
            {
                for(int j = 0 ; j < 10 ; j++) //猪圈内加猪
                {
                    if(temp->amount[1] == b_equal || addb_number == 0 )  //等于平均或者加够了退出猪圈
                    {
                        break ;      //个人感觉此break，在for前for后均可
                    }
                    if (temp->sty[j].weight == 0.0) //判断有没有猪
                    {
                        temp->sty[j].weight = (double)(rand()%31 +20) ;
                        temp->sty[j].raisetime = 0 ;
                        temp->sty[j].color = (Pig::Color)1 ;
                        temp->sty[j].id = j ;
                        temp->amount[0]++ ;
                        temp->amount[1]++ ;  //黑猪买入
                        addb_number-- ;
                        print_pig(temp->sty[j] , i) ;
                    }

                }
            }


        }
        else         // 花猪圈
        {
            if (addbf_number == 0 && addsf_number == 0)
            {
                continue ;
            }
            if(temp->amount[0] >= sbf_equal )
            {
                //大于平均，不再加入
            }
            else
            {
                for(int j = 0 ; j < 10 ; j++) //猪圈内加猪
                {
                    if(temp->amount[0] == sbf_equal || (addbf_number==0 && addsf_number==0) )  //等于平均或者加够了退出猪圈
                    {
                        break ;         //个人感觉此break，在for前
                    }
                    if (temp->sty[j].weight == 0.0) //判断有没有猪
                    {
                        temp->sty[j].weight = (double)(rand()%31 +20) ;
                        temp->sty[j].raisetime = 0 ;
                        temp->sty[j].id = j ;

                        if(addbf_number > 0 && addsf_number > 0 )         //随机分配颜色
                        {
                            int RandomColor = rand()%2+2 ;
                            temp->sty[j].color = (Pig::Color)(RandomColor) ; //颜色初始化
                            temp->amount[RandomColor]++ ;
                            temp->amount[0]++ ;
                            if(RandomColor == 2)
                            {
                                addsf_number-- ;
                            }
                            else
                            {
                                addbf_number-- ;
                            }
                        }
                        else if (addsf_number > 0) //小花猪还能分
                        {
                           temp->sty[j].color = (Pig::Color)2 ;
                           temp->amount[2]++ ;
                           temp->amount[0]++ ;
                           addsf_number--  ;
                        }
                        else if(addbf_number > 0)
                       {
                            temp->sty[j].color = (Pig::Color)3 ;
                            temp->amount[3]++ ;
                            temp->amount[0]++ ;
                            addbf_number-- ;
                        }
                       print_pig(temp->sty[j] , i) ;

                    }

                }
            }
        }
    }


}


void PigFarm::Dataout(PigFarm *farm)    //怎么写入怎么取，取到空格截止为一个数据
{
    QFile file ("data.txt") ;
    file.open(QFile::WriteOnly | QFile::Truncate) ; //清空文件内容
    file.close() ;

         dataout << 1  << ' ' ;    // 用于判断文件里有没有东西,两次判断
         dataout << farm->blackpigsty_count(farm) << ' ' ;
    Pigsty* temp = farm->pigstyhead ;
    for (int i = 1 ; i <= 100 ; i++)
    {
        dataout << temp->pigstyID << ' ' ;
        for (int j = 0 ; j < 4 ; j++)
        {
            dataout << temp->amount[j] << ' ';
        }
        for (int k = 0 ; k < 10 ; k++)
        {
            dataout << temp->sty[k].id << ' ' ;
            dataout << (int)temp->sty[k].color << ' ' ;
            dataout << temp->sty[k].raisetime << ' ' ;
            dataout << temp->sty[k].weight << ' ' ;
        }
        temp = temp->pigstynext ;
    }
    return;
}






void PigFarm::getsick(PigFarm *farm)
{
    farm->Sick_Time = 1 ;
    //  每次感染，数组归0
  for (int i = 0 ; i < 101 ; i++)
  {
      for(int j = 0 ; j < 11 ; j++)
      {
          SICK[i][j] = 0 ;
      }
  }
  for ( ; ; )
  {
      srand( (unsigned int )time(NULL)) ;

      int x = rand()%100 + 1  ;  //1到100
      int y = rand()%10 ;   //0到9
      Pigsty* temp = farm->pigstyhead ;
      for (int i = 1 ; i < x ; i++)            //pigstyID 1-100 ， pig的id 0-9
      {
          temp = temp->pigstynext ;
      }
      if(temp->sty[y].weight > 0 )
      {
          SICK[0][0] = x ;
          SICK[0][1] = y ;
          SICK[x][y] = 1 ;
          SICK[x][10] = 6 ;
          SICK[0][10] = 6 ;
          break ;
      }

  }

  farm->transform(farm) ;

  return ;


}


void PigFarm::sick_continue(PigFarm *farm)
{
    Pigsty* curpigsty = farm->pigstyhead ;
    if (SICK[0][10] == 6)
    {
        //单独看1号猪圈
        if(SICK[1][10] == 6)
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                if(curpigsty->sty[i].weight > 0)
                {
                    //srand( (unsigned int )time(NULL)) ;
                    int judge = rand()%100 + 1 ; //1到100
                    if (judge > 50)
                    {
                        SICK[1][i] = 1 ;
                        SICK[1][10] = 6 ;
                    }
                }

            }
        }
        else if (SICK[2][10] == 6)
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                if(curpigsty->sty[i].weight > 0)
                {
                    //srand( (unsigned int )time(NULL)) ;
                    int judge = rand()%100 + 1 ; //1到100
                    if (judge > 85)
                    {
                        SICK[1][i] = 1 ;
                        SICK[1][10] = 6 ;
                    }
                }

            }
        }


       // 单独看100号猪圈
        if(SICK[100][10] == 6)
        {
            Pigsty* curpigsty = farm->pigstyhead ;
            for (int w = 1 ; w < 100 ; w++)            //pigstyID 1-100 ， pig的圈中id 0-9
            {
                curpigsty = curpigsty->pigstynext ;
            }

              for (int i = 0 ; i < 10 ; i++)
                {
                     if(curpigsty->sty[i].weight > 0)
                     {
                        // srand( (unsigned int )time(NULL)) ;
                         int judge = rand()%100 + 1 ; //1到100
                         if (judge > 50)
                         {
                             SICK[100][i] = 1 ;
                             SICK[100][10] = 6 ;
                         }
                     }

                }


        }
        else if (SICK[99][10] == 6)
        {
            Pigsty* curpigsty = farm->pigstyhead ;
            for (int w = 1 ; w < 100 ; w++)            //pigstyID 1-100 ， pig的圈中id 0-9
            {
              curpigsty = curpigsty->pigstynext ;
            }

                for (int i = 0 ; i < 10 ; i++)
                {
                    if(curpigsty->sty[i].weight > 0)
                    {
                        //srand( (unsigned int )time(NULL)) ;
                        int judge = rand()%100 + 1 ; //1到100
                        if (judge > 85)
                        {
                            SICK[100][i] = 1 ;
                            SICK[100][10] = 6 ;
                        }
                    }
                }


        }

       //2到99号猪圈

        for(int j = 2 ; j <= 99 ; j++)
        {
            curpigsty = farm->pigstyhead ;
            for (int w = 1 ; w < j ; w++)            //pigstyID 1-100 ， pig的圈中id 0-9
            {
                curpigsty = curpigsty->pigstynext ;
            }
            if(SICK[j][10] == 6)
            {


                    for (int i = 0 ; i < 10 ; i++)
                    {
                        if(curpigsty->sty[i].weight > 0)
                        {
                            //srand( (unsigned int )time(NULL)) ;
                            int judge = rand()%100 + 1 ; //1到100
                            if (judge > 50)
                            {
                                SICK[j][i] = 1 ;
                                SICK[j][10] = 6 ;
                            }
                        }
                    }


            }
            else if (SICK[j+1][10] == 6 || SICK[j-1][10] == 6)
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    if(curpigsty->sty[i].weight > 0)
                    {
                        //srand( (unsigned int )time(NULL)) ;
                        int judge = rand()%100 + 1 ; //1到100
                        if (judge > 85)
                        {
                            SICK[100][i] = 1 ;
                            SICK[j][10] = 6 ;
                        }
                    }

                }
            }
        }

        farm->Sick_Time++ ;
        farm->transform(farm) ;
    }
}

bool PigFarm::is_all_sick(PigFarm *pfarm)
{
    bool back = true ;
    Pigsty* curpigsty = pfarm->pigstyhead ;
    for (int i = 1 ; i <= 100 ; i++)
    {
        if(curpigsty->amount[0] == 0 && i < SICK[0][0])
        {
            back = true ;
        }
        if(curpigsty->amount[0] == 0 && i > SICK[0][0])
        {
            break ;
        }

        for( int j = 0 ; j < 10 ; j++)
        {
            if(curpigsty->sty[j].weight > 0  && SICK[i][j] == 0) //有猪且未病
            {
                back = false ;
            }
        }
        curpigsty = curpigsty->pigstynext ;
    }
    return back ;
}

bool PigFarm::is_all_cut()
{
    bool back = true ;
    for(int i = 1 ; i < 101 ; i++)
    {
        if (SICK[i][10] == 6)
        {
            back = false ;
            break ;
        }
    }
    return back ;
}

void PigFarm::transform(PigFarm *pfarm)
{
    Pigsty* curpigsty = pfarm->pigstyhead ;
    for (int i = 1 ; i <= 100 ; i++)
    {
        for( int j = 0 ; j < 10 ; j++)
        {
            if(curpigsty->sty[j].weight > 0 ) //有猪
            {
                curpigsty->sty[j].issick = SICK[i][j] ;
            }
        }
        curpigsty = curpigsty->pigstynext ;
    }
}

bool PigFarm::cut(PigFarm *pfarm, int pigstyID, int id)
{
    bool is_OK = false ;
    SICK[pigstyID][id] = 0 ; //有猪置零，没猪更得是零
    SICK[pigstyID][10] = 0 ; //假设这一个猪圈没病了

    Pigsty* temp = pfarm->pigstyhead ;
    for (int i = 1 ; i < pigstyID ; i++)            //pigstyID 1-100 ， pig的id 0-9
    {
        temp = temp->pigstynext ;
    }
    if (temp->sty[id].weight > 0)
    {
        fout << endl << "您安乐死了一头猪" << endl ;
        pfarm->print_pig(temp->sty[id] , pigstyID) ;
        temp->sty[id].raisetime = 0 ;
        temp->sty[id].issick = 0 ;
        temp->sty[id].weight = 0.0 ;
        temp->amount[0]-- ;
        temp->amount[temp->sty[id].color]-- ;
        is_OK = true ;

    }
    for (int i = 0 ; i < 10 ; i++)
    {
        if(SICK[pigstyID][i] == 1)  //有病则置6
        {
            SICK[pigstyID][10] = 6 ;
        }
    }
    return is_OK ;
}

/* void PigFarm::Datain(PigFarm *farm)
{
    double exchange ;
    Pigsty* temp = farm->pigstyhead ;
    for (int i = 1 ; i <= 100 ; i++)
    {
        datain >> exchange  ;
        temp->pigstyID = exchange ;
        for (int j = 0 ; j < 4 ; j++)
        {
            datain >> exchange ;
            temp->amount[j]= exchange ;
        }
        for (int k = 0 ; k < 10 ; k++)
        {
            datain >> exchange  ;
            temp->sty[k].id = exchange ;
            datain >> exchange;     // 颜色这里有些特别，得转成枚举类型Color
            temp->sty[k].color = Pig::Color(exchange) ;
            datain >> exchange ;
            temp->sty[k].raisetime = exchange ;
            datain >> exchange ;
            temp->sty[k].weight  = exchange ;
        }
        temp = temp->pigstynext ;
    }

    return;

}*/

