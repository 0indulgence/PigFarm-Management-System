#ifndef MAINFARM_H
#define MAINFARM_H

#include <QWidget>
#include <pigfarm.h>
#include <QTableView>
#include <bits/stdc++.h>
#include <QTableWidget>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QLayout>
#include <QFile>
#include <QTimer>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QPlainTextEdit>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QDir> // 需要深入
#include <QFileDialog> // 需要深入





extern int comeon [3] ;
extern ofstream fout  ;
extern int b_pigsty_number ;
extern ofstream timeout ;  //退出时
extern ifstream timein ;


namespace Ui {
class MainFarm;
}

class MainFarm : public QWidget
{
    Q_OBJECT

public:
    explicit MainFarm(QWidget *parent = nullptr);
    ~MainFarm();

    //重写定时器事件 timerEvent
    void timerEvent (QTimerEvent*) ;

private slots:
    void on_LeftButton_clicked();

    void on_RightButton_clicked();

    void pigsty_button_clicked (PigFarm* pfarm,int pigstyID) ; //点击stack上按钮后引发的槽函数

    void chart_Button_clicked(PigFarm* pfarm); //制作图表

    void close_Button_clicked(PigFarm* pfarm); //退出按钮

    void handgrow_Button_clicked(PigFarm* pfarm); //手动增长

    void buy_Button_clicked(PigFarm* pfarm);

    void sell_Button_clicked(PigFarm* pfarm);

    void Sick_Button_clicked(PigFarm* pfarm);

    void text_Button_clicked(); // 查看历史信息

    void measure_Button_clicked( PigFarm* pfarm);  // 初步隔离措施

private:
    Ui::MainFarm * ui;







signals:


private:
    int  stacked_index ; // 栈控件索引
};

#endif // MAINFARM_H
