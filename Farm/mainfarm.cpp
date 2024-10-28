#include "mainfarm.h"
#include "ui_mainfarm.h"
#include <farmdialog.h>
#include <ui_farmdialog.h>
#include <QDebug>
#include <QPushButton>





MainFarm::MainFarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainFarm)
{
    ui->setupUi(this);
    this->setFixedSize( 1440, 760 ) ;
    setAutoFillBackground(true) ;

    // 使用调色板QPalette来设置图片
    QPalette pal = this->palette() ;
    pal.setBrush(backgroundRole(), QPixmap(":/farmpicture/farm_background")) ;
    setPalette( pal) ;

    PigFarm* pfarm ;
    //借助全局变量传参构建农场，全局变量只能在on_EnterButton_clicked中改写
        if (comeon[0] != 0)
        {
            QFile file ("sell.txt") ;
            file.open(QFile::WriteOnly | QFile::Truncate) ; //清空文件内容
            file.close() ;
            //借助全局变量传参构建农场，全局变量只能在on_EnterButton_clicked中改写
            pfarm = PigFarm::FirstCreatePigfarm( comeon[0] , comeon[1] , comeon[2]) ;
            b_pigsty_number = pfarm->blackpigsty_count(pfarm) ;
        }
        else if (comeon[0] == 0)
        {

            pfarm = new PigFarm ;
            datain >> b_pigsty_number ;
            pfarm = PigFarm::LoadPigfarm() ;
            timein >> pfarm->Farm_Time ;
        }

       /* //音乐整起来
         QSoundEffect effect ;
         effect.setSource(QUrl::fromLocalFile("C:\\Users\\Gezhaox-computer\\Desktop\\Farm\\Farm\\music.wav"));
         effect.setLoopCount(3);
         effect.setVolume(1);
         effect.play();*/

       /* QMediaPlayer player ;
        player.setSource(QUrl::fromLocalFile("C:\\Users\\Gezhaox-computer\\Desktop\\Farm\\Farm\\music.wav")) ;
        player.setLoops(-1) ;
        player.play();*/

        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(25) ;
        QPalette pal_1 ;
        pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
        char buffer[256] ;  //想输出的字符串
        //sprintf 字符串格式化命令 ，把想要的数据转化为字符串
        sprintf( buffer , "今天是猪场第%d天" , pfarm->Farm_Time) ;
        ui->Time_label->setText(buffer) ;
        ui->Time_label->setFont(font) ;
        ui->Time_label->setPalette(pal_1) ;

        // 100个按钮连接槽函数(借助容器）
    QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
    foreach(QPushButton* btn , button_list) //循环list中的所有按钮
    {
      btn->setChecked(true) ;
      int cur_pigstyID = btn->text().toInt() ;


      //第一次使用lambda表达式，第一次真正意义连接信号和槽，无参触及有参，参数的传递
      connect( btn , &QPushButton::clicked , this , [this,cur_pigstyID , pfarm]()
      {
          pigsty_button_clicked(pfarm , cur_pigstyID) ;
      }) ;
    }

    //定时器
    QTimer* timer = new QTimer (this) ;
    timer->start(2000) ;


    connect( ui->chart_Button , &QPushButton::clicked , this , [this , pfarm]()
    {
       chart_Button_clicked(pfarm) ;
    }) ;

    connect( ui->close_Button , &QPushButton::clicked , this , [this , pfarm]()
    {
       close_Button_clicked(pfarm) ;
    }) ;

    connect( ui->handgrow_Button , &QPushButton::clicked , this , [this , pfarm]()
    {
       handgrow_Button_clicked(pfarm) ;
    }) ;

    connect( ui->sell_Button , &QPushButton::clicked , this , [this , pfarm]()
    {
       sell_Button_clicked(pfarm) ;
    }) ;

    connect( ui->buy_Button , &QPushButton::clicked , this , [this , pfarm]()
    {
       buy_Button_clicked(pfarm) ;
    }) ;

    connect( ui->Sick_Button , &QPushButton::clicked , this , [this , pfarm , timer]()
    {
       Sick_Button_clicked(pfarm) ;
      // startTimer(2000) ; //2000ms执行一次定时器事件
       timer->start(2000) ;
       ui->measure_Button->setEnabled(true) ;

    }) ;

    connect( ui->text_Button , &QPushButton::clicked , this , [this]()
    {
       text_Button_clicked() ;

    }) ;

    if (SICK[0][10] == 0)
    {
        ui->measure_Button->setEnabled(false) ;
    }

    connect( ui->measure_Button , &QPushButton::clicked , this , [this , pfarm , timer]()
    {
        if (ui->measure_Button->text() == "处理猪场")
        {
            measure_Button_clicked (pfarm) ;
            timer->stop() ;
            ui->measure_Button->setText("处理完毕") ;
        }
        else if (ui->measure_Button->text() == "处理完毕")
        {
            timer->start(2000) ;
            ui->measure_Button->setText("处理猪场") ;
            ui->measure_Button->setEnabled(false) ;
        }



    }) ;



    //定时器连接
    connect(timer , &QTimer::timeout ,this ,  [this ,pfarm ](){

        if(SICK[0][10] == 0)
        {
            pfarm->pigfarm_grow(pfarm) ;


            QFont font ;
            font.setBold(true) ;
            font.setItalic(true) ;  //斜体
            font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
            font.setPointSize(25) ;
            QPalette pal_1 ;
            pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
            char buffer[256] ;  //想输出的字符串
            //sprintf 字符串格式化命令 ，把想要的数据转化为字符串
            sprintf( buffer , "今天是猪场第%d天" , pfarm->Farm_Time) ;
            ui->Time_label->setText(buffer) ;
            ui->Time_label->setFont(font) ;
            ui->Time_label->setPalette(pal_1) ;

        }
        else if (SICK[0][10] == 6)
        {

            pfarm->pigfarm_grow(pfarm) ; // farm_time++了

            pfarm->sick_continue(pfarm) ; // sick_time++了


            QFont font ;
            font.setBold(true) ;
            font.setItalic(true) ;  //斜体
            font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
            font.setPointSize(25) ;
            QPalette pal_1 ;
            pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
            char buffer[256] ;  //想输出的字符串
            sprintf( buffer , "今天是瘟疫的第%d天" , pfarm->Sick_Time) ;
            ui->Time_label->setText(buffer) ;
            ui->Time_label->setFont(font) ;
            ui->Time_label->setPalette(pal_1) ;


            // 100个按钮连接槽函数(借助容器）
            QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
            foreach(QPushButton* btn , button_list) //循环list中的所有按钮
                {
                    btn->setChecked(true) ;
                    int temp = btn->text().toInt() ;
                    if(SICK[temp][10] == 6)
                    {
                        btn->setStyleSheet("border-image:url(:/pigsty_sick.jpg)") ;
                    }
                    else
                    {
                         btn->setStyleSheet("border-image:url(:/farmpicture/stack.jpg)") ;
                    }
                }
        }


        //病猪全死后猪场状态调整
        if (pfarm->is_all_cut() == true && SICK[0][10] == 6)
        {
            SICK[0][10] = 0 ;
            QFont font ;
            font.setBold(true) ;
            font.setItalic(true) ;  //斜体
            font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
            font.setPointSize(15) ;
            QDialog dialog(this) ;
            dialog.setWindowTitle("成就") ;
            dialog.resize(300 , 50) ;
            dialog.move(200 , 0) ;
            QLabel loadLabel ( &dialog) ;
            loadLabel.resize(300 , 50) ;
            loadLabel.move( 0, 0) ;
            loadLabel.setText("正确的经营者") ;
            loadLabel.setFont(font) ;
            QPalette pal = dialog.palette() ;
            pal.setBrush(backgroundRole(), QPixmap(":/text.jpg")) ;
            dialog.setPalette( pal) ;
            fout << endl << "解锁成就：正确的经营者" << endl ;
            dialog.show() ;
            dialog.exec() ;
        }


        //能感染的全部感染，就弹出
        if (pfarm->is_all_sick(pfarm) == true && SICK[0][10] == 6)
        {
            for (int i = 0 ; i < 101 ; i++)
            {
                for(int j = 0 ; j < 11 ; j++)
                {
                    SICK[i][j] = 0 ;
                }
            }
            pfarm->transform(pfarm) ;
            QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
            foreach(QPushButton* btn , button_list) //循环list中的所有按钮
                {
                    btn->setChecked(true) ;
                    btn->setStyleSheet("border-image:url(:/farmpicture/stack.jpg)") ;
                }

            QDialog dialog(this) ;
            dialog.setWindowTitle("回家吧您") ;
            dialog.resize(400 ,400) ;
            QLabel loadLabel ( &dialog) ;
            loadLabel.resize(400 , 300) ;
            loadLabel.move( 0, 0) ;
            loadLabel.setScaledContents(true) ;
            QMovie* movie =  new QMovie (":/over.jpg") ;
            loadLabel.setMovie(movie) ;
            movie->start() ;

            QFont font ;
            font.setBold(true) ;
            font.setItalic(true) ;  //斜体
            font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
            font.setPointSize(15) ;

            QPushButton over_true(&dialog) ;
            over_true.setText("确定") ;
            over_true.move(80 , 350) ;
            over_true.resize(50 , 40) ;
            over_true.setFont(font) ;

            QLabel label (&dialog) ;

            label.setText("能死的都死了,建议回家种地") ;
            label.move( 50 , 310) ;
            label.resize( 300 , 40) ;
            label.setFont(font) ;

            connect( &over_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

            dialog.show() ;
            dialog.exec() ;
        }

        //30天自动卖猪
        if(pfarm-> Farm_Time % 30 == 0 && SICK[0][10] == 0)
        {
            emit ui->sell_Button->clicked() ;
        }
        return ;

    }) ;



        //测试过程的产物
    /*connect( ui->pushButton , &QPushButton::clicked , this , [this , pfarm]()
    {
        for(int i = 0; i < 2 ; i++)
        {
             pfarm->sick_continue(pfarm) ;
        }
        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(25) ;
        QPalette pal_1 ;
        pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
        char buffer[256] ;  //想输出的字符串
        sprintf( buffer , "今天是瘟疫的第%d天" , pfarm->Sick_Time) ;
        ui->Time_label->setText(buffer) ;
        ui->Time_label->setFont(font) ;
        ui->Time_label->setPalette(pal_1) ;

        // 100个按钮连接槽函数(借助容器）
        QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
        foreach(QPushButton* btn , button_list) //循环list中的所有按钮
            {
                btn->setChecked(true) ;
                int temp = btn->text().toInt() ;
                if(SICK[temp][10] == 6)
                {
                    btn->setStyleSheet("border-image:url(:/pigsty_sick.jpg)") ;
                }
            }



    }) ;*/



}

MainFarm::~MainFarm()
{
    delete ui;
}

void MainFarm::timerEvent(QTimerEvent * )   //可以直接用构造函数中的成员? 在此疯狂卡退,推断不知道pfarm是谁？
{                                              //但是为什么不报错，需要深入
    if(SICK[0][10] == 0)
    {
        pfarm.pigfarm_grow(&pfarm) ;


        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(25) ;
        QPalette pal_1 ;
        pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
        char buffer[256] ;  //想输出的字符串
        //sprintf 字符串格式化命令 ，把想要的数据转化为字符串
        sprintf( buffer , "今天是猪场第%d天" , pfarm.Farm_Time) ;
        ui->Time_label->setText(buffer) ;
        ui->Time_label->setFont(font) ;
        ui->Time_label->setPalette(pal_1) ;

    }
    else if (SICK[0][10] == 6)
    {

        pfarm.pigfarm_grow(&pfarm) ; // farm_time++了

        pfarm.sick_continue(&pfarm) ; // sick_time++了


        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(25) ;
        QPalette pal_1 ;
        pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
        char buffer[256] ;  //想输出的字符串
        sprintf( buffer , "今天是瘟疫的第%d天" , pfarm.Sick_Time) ;
        ui->Time_label->setText(buffer) ;
        ui->Time_label->setFont(font) ;
        ui->Time_label->setPalette(pal_1) ;


        // 100个按钮连接槽函数(借助容器）
        QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
        foreach(QPushButton* btn , button_list) //循环list中的所有按钮
            {
                btn->setChecked(true) ;
                int temp = btn->text().toInt() ;
                if(SICK[temp][10] == 6)
                {
                    btn->setStyleSheet("border-image:url(:/pigsty_sick.jpg)") ;
                }
            }
    }
    if (pfarm.is_all_sick(&pfarm) == true)
    {
        QDialog dialog(this) ;
        dialog.setWindowTitle("回家吧您") ;
        dialog.resize(400 ,400) ;
        QLabel loadLabel ( &dialog) ;
        loadLabel.resize(400 , 300) ;
        loadLabel.move( 0, 0) ;
        loadLabel.setScaledContents(true) ;
        QMovie* movie =  new QMovie (":/over.gif") ;
        loadLabel.setMovie(movie) ;
        movie->start() ;

        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(15) ;

        QPushButton over_true(&dialog) ;
        over_true.move(80 , 350) ;
        over_true.resize(50 , 40) ;
        over_true.setFont(font) ;

        QLabel label (&dialog) ;

        label.setText("农场已倒闭，建议回家种地") ;
        label.move( 50 , 310) ;
        label.resize( 300 , 40) ;
        label.setFont(font) ;

        connect( &over_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

        dialog.show() ;
        dialog.exec() ;
    }
    return ;
}



void MainFarm::on_LeftButton_clicked()
{
    int page = ui->Page_Stacked->currentIndex() ;
    if ( page > 0 )
    {
        page -= 1 ;
        ui->Page_Stacked->setCurrentIndex( page ) ;
    }
    else if (page == 0)
    {
        page = 9 ;
        ui->Page_Stacked->setCurrentIndex(page) ;
    }
    return ;


}


void MainFarm::on_RightButton_clicked()
{
    int page = ui->Page_Stacked->currentIndex() ;
    if ( page < 9 )
    {
        page += 1 ;
        ui->Page_Stacked->setCurrentIndex( page ) ;
    }
    else if (page == 9)
    {
        page = 0 ;
        ui->Page_Stacked->setCurrentIndex(page) ;
    }
    return ;
}



void MainFarm::pigsty_button_clicked( PigFarm* pfarm ,int pigstyID)
{
    //找猪圈
    Pigsty* temp = pfarm->pigstyhead ;
    for (int i = 1 ; i < pigstyID ; i++)            //pigstyID 1-100 ， pig的id 0-9
    {
        temp = temp->pigstynext ;
    }

    // 对话框和控件
    QDialog dialog(this) ;
    dialog.setWindowTitle("猪圈内部") ;
    dialog.resize(600 ,700) ;
    QTableWidget* tableInfo = new QTableWidget(&dialog);
    tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers) ; //只读
    tableInfo->resize(600 , 650) ;

    //很重要，若忽视，表格看不到，因为默认0行0列
    tableInfo->setColumnCount(4) ;
    tableInfo->setRowCount(10) ;

    //表头
    QTableWidgetItem * headerItem ;
    QStringList headerText ;
    headerText << "ID" << "颜色" << "体重" << "饲养时间" << "是否生病" ;
    tableInfo->setColumnCount(headerText.count()) ;
    for (int i = 0 ; i < tableInfo->columnCount() ; i++)
    {
        headerItem = new QTableWidgetItem (headerText.at(i)) ;
        QFont font = headerItem->font() ;
        font.setBold(true) ;
        font.setPointSize(12) ;
        headerItem->setFont(font) ;
        tableInfo->setHorizontalHeaderItem( i , headerItem) ;
    }
    //表身 ， **转成字符太重要了
    for (int i = 0 ; i < 10 ; i++)
    {


        if (temp->sty[i].weight != 0)
        {
            QTableWidgetItem * my_item  ;

            //ID
             my_item = new QTableWidgetItem(QString::number(temp->sty[i].id)) ;
             tableInfo->setItem( i ,0 , my_item) ;
            //颜色
            my_item = new QTableWidgetItem(QString::number(temp->sty[i].color)) ;
            tableInfo->setItem( i,1, my_item) ;
            //体重
            my_item = new QTableWidgetItem(QString::number(temp->sty[i].weight)) ;
            tableInfo->setItem( i ,2 , my_item) ;
            //饲养时间
            my_item = new QTableWidgetItem(QString::number(temp->sty[i].raisetime)) ;
            tableInfo->setItem( i ,3 , my_item) ;
            //是否生病
            my_item = new QTableWidgetItem(QString::number(temp->sty[i].issick)) ;
            tableInfo->setItem( i ,4 , my_item) ;
            //字体
            QFont font ;     //后置无警告，前置有警告，思考
            font.setBold(false) ;
            font.setPointSize(10) ;
            my_item->setFont(font) ;
        }
    }
   tableInfo->show();

   QFont font ;
   font.setBold(true) ;
   font.setItalic(true) ;  //斜体
   font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
   font.setPointSize(15) ;

   QLabel* id_label = new QLabel (&dialog) ;
   id_label->resize(300 , 40);
   id_label->move(50 , 350) ;
   id_label->setText("请输入要下手的编号") ;
   id_label->setFont(font) ;

   QSpinBox* id_box = new QSpinBox (&dialog) ;
   id_box->setMaximum(9) ;
   id_box->setMinimum(0) ;
   id_box->resize(50 , 30) ;
   id_box->move(300 , 350) ;

   QPushButton* cut_button = new QPushButton (&dialog) ;
   cut_button->resize(70 , 30) ;
   cut_button->move(400, 350) ;
   cut_button->setText("确定") ;

   QLabel quitLabel ( &dialog) ;
   quitLabel.resize(600 , 315) ;
   quitLabel.move( 0, 385) ;
   quitLabel.setScaledContents(true) ;  //此句的作用
   QMovie* movie =  new QMovie (":/in_pigsty.gif") ;
   quitLabel.setMovie(movie) ;
   movie->start() ;

   //此槽函数执行时，上面的dialog已经被析构？
   connect( cut_button , &QPushButton::clicked , &dialog , [id_box , this , pfarm , pigstyID]()
   {
     int id = id_box->value() ;
     bool is_ok = pfarm->cut( pfarm , pigstyID , id);
     //没有成功删掉
     if(! is_ok)
     {
         QDialog dialog1 (this) ;
         dialog1.setWindowTitle("安乐死失败") ;
         dialog1.resize(400 ,400) ;
         QLabel loadLabel ( &dialog1) ;
         loadLabel.resize(400 , 300) ;
         loadLabel.move( 0, 0) ;
         loadLabel.setScaledContents(true) ;
         QMovie* movie =  new QMovie (":/reject.gif") ;
         loadLabel.setMovie(movie) ;
         movie->start() ;

         QFont font ;
         font.setBold(true) ;
         font.setItalic(true) ;  //斜体
         font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
         font.setPointSize(15) ;

         QPushButton over_true(&dialog1) ;
         over_true.setText("确定") ;
         over_true.move(80 , 350) ;
         over_true.resize(50 , 40) ;
         over_true.setFont(font) ;

         QLabel label (&dialog1) ;

         label.setText("找茬是吧，别这样啊") ;
         label.move( 50 , 310) ;
         label.resize( 300 , 40) ;
         label.setFont(font) ;

         connect( &over_true , SIGNAL(clicked()) , &dialog1 , SLOT(close())) ;
         dialog1.show() ;
         dialog1.exec() ;
     }
     //成功删掉
     else
     {
         QDialog dialog2 (this) ;
         dialog2.setWindowTitle("辣手摧猪") ;
         dialog2.resize(400 ,400) ;
         QLabel loadLabel ( &dialog2) ;
         loadLabel.resize(400 , 300) ;
         loadLabel.move( 0, 0) ;
         loadLabel.setScaledContents(true) ;
         QMovie* movie =  new QMovie (":/success.gif") ;
         loadLabel.setMovie(movie) ;
         movie->start() ;

         QFont font ;
         font.setBold(true) ;
         font.setItalic(true) ;  //斜体
         font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
         font.setPointSize(15) ;

         QPushButton over_true(&dialog2) ;
         over_true.setText("确定") ;
         over_true.move(80 , 350) ;
         over_true.resize(50 , 40) ;
         over_true.setFont(font) ;

         QLabel label (&dialog2) ;

         label.setText("下手真快啊小伙子") ;
         label.move( 50 , 310) ;
         label.resize( 300 , 40) ;
         label.setFont(font) ;

         connect( &over_true , SIGNAL(clicked()) , &dialog2 , SLOT(close())) ;
         dialog2.show() ;
         dialog2.exec() ;
     }
   }) ;



   dialog.show() ;
   dialog.exec() ;

   return ;


}



void MainFarm::chart_Button_clicked(PigFarm* pfarm)
{
    //取数据
    float b_number = pfarm->pigcolor_count(pfarm ,Pig::black) ;
    float sf_number = pfarm->pigcolor_count(pfarm , Pig::sflower) ;
    float bf_number = pfarm->pigcolor_count(pfarm , Pig::bflower) ;
    pfarm->pigraisetime_count(pfarm) ;
    pfarm->pigweight_count(pfarm) ;
    float sum_weight = pig_weight_count[0] +pig_weight_count[1] + pig_weight_count[2] + pig_weight_count[3] + pig_weight_count[4] ;
    float sum_raisetime = pig_raisetime_count[0] +pig_raisetime_count[1] + pig_raisetime_count[2] + pig_raisetime_count[3] + pig_raisetime_count[4] ;


    QDialog dialog(this) ;
    dialog.setWindowTitle("图表之家") ;
    dialog.resize(1000 ,900) ;
    // 使用调色板QPalette来设置图片
    QPalette pal = dialog.palette() ;
    pal.setBrush(backgroundRole(), QPixmap(":/farmpicture/chart.jpg")) ;
    dialog.setPalette( pal) ;


         // button1
    QPushButton* number_button = new QPushButton (&dialog) ;
     number_button->resize(100 , 40 ) ;
     number_button->move(850 , 180) ;
     number_button->setText("猪的品种分布") ;
     number_button->show() ;
     connect(number_button , &QPushButton::clicked , &dialog , [&]
     {
         //创建ChartView
         QChartView* chartView = new QChartView(&dialog) ;
         chartView->move(0 , 0) ;
         chartView->resize(800 , 800) ;

         //创建chart
         QChart* number_chart = new QChart() ;
         number_chart->resize(400 , 400) ;
         number_chart->setTitle("猪的颜色种类") ;
         number_chart->setTheme(QChart::ChartThemeBlueIcy) ; //主题
         number_chart->setVisible(true) ;
         number_chart->legend()->hide();


         //创建饼图序列
         QPieSeries* series = new QPieSeries() ;

         //饼图分块
         QPieSlice* slice_01 = new QPieSlice(QStringLiteral("黑猪") , b_number/(b_number+sf_number+bf_number) , this ) ;
         slice_01->setLabelVisible(true) ;
         slice_01->setColor(QColor(255 , 0 , 0));
         slice_01->setExploded(true) ; //突出
         slice_01->setExplodeDistanceFactor(0.1) ; //间隔
         slice_01->setLabel(QString::asprintf("黑猪：%.0f头, %.1f%%", b_number ,100*b_number/(b_number+sf_number+bf_number) )) ;


         QPieSlice* slice_02 = new QPieSlice(QStringLiteral("小花猪") , sf_number/(b_number+sf_number+bf_number) , this ) ;
         slice_02->setLabelVisible(true) ;
         slice_02->setColor(QColor(0 , 255 , 0));
         slice_02->setExploded(true) ; //突出
         slice_02->setExplodeDistanceFactor(0.1) ; //间隔
         slice_02->setLabel(QString::asprintf("小花猪：%.0f头, %.1f%%", sf_number ,100*sf_number/(b_number+sf_number+bf_number) )) ;



         QPieSlice* slice_03 = new QPieSlice(QStringLiteral("大白花猪") , bf_number/(b_number+sf_number+bf_number) , this ) ;
         slice_03->setLabelVisible(true) ;
         slice_03->setColor(QColor(0 , 0 , 255));
         slice_03->setExploded(true) ; //突出
         slice_03->setExplodeDistanceFactor(0.1) ; //间隔
         slice_03->setLabel(QString::asprintf("大白花猪：%.0f头, %.1f%%", bf_number ,100*bf_number/(b_number+sf_number+bf_number) )) ;

         //分块加入series
         series->append(slice_01) ;
         series->append(slice_02) ;
         series->append(slice_03) ;

         //series加入Chart
         number_chart->addSeries(series) ;

         //  ChartView.show()
         chartView->setChart(number_chart) ;
         chartView->show() ;
     });


        //button2
     QPushButton* weight_button = new QPushButton (&dialog) ;
      weight_button->resize(100 , 40 ) ;
      weight_button->move(850 , 400) ;
      weight_button->setText("猪的体重分布") ;
      weight_button->show() ;
      connect(weight_button , &QPushButton::clicked , &dialog , [&]
      {
          //创建ChartView
          QChartView* chartView = new QChartView(&dialog) ;
          chartView->move(0 , 0) ;
          chartView->resize(800 , 800) ;

          //创建chart
          QChart* number_chart = new QChart() ;
          number_chart->resize(400 , 400) ;
          number_chart->setTitle("猪的体重分布") ;
          number_chart->setTheme(QChart::ChartThemeBlueIcy) ; //主题
          number_chart->setVisible(true) ;
          number_chart->legend()->hide();


          //创建饼图序列
          QPieSeries* series = new QPieSeries() ;

          //饼图分块
          QPieSlice* slice_11 = new QPieSlice(QStringLiteral("20-50") , pig_weight_count[0]/sum_weight , this ) ;
          slice_11->setLabelVisible(true) ;
          slice_11->setColor(QColor(255 , 0 , 0));
          slice_11->setExploded(true) ; //突出
          slice_11->setExplodeDistanceFactor(0.1) ; //间隔
          slice_11->setLabel(QString::asprintf("20-50k斤：%.0d头, %.1f%%", pig_weight_count[0] ,100*pig_weight_count[0]/sum_weight )) ;


          QPieSlice* slice_12 = new QPieSlice(QStringLiteral("50-80") , pig_weight_count[1]/sum_weight , this ) ;
          slice_12->setLabelVisible(true) ;
          slice_12->setColor(QColor(0 , 255 , 0));
          slice_12->setExploded(true) ; //突出
          slice_12->setExplodeDistanceFactor(0.1) ; //间隔
          slice_12->setLabel(QString::asprintf("50-80斤：%.0d头, %.1f%%", pig_weight_count[1] ,100*pig_weight_count[1]/sum_weight  )) ;



          QPieSlice* slice_13 = new QPieSlice(QStringLiteral("80-110") , pig_weight_count[2]/sum_weight  , this ) ;
          slice_13->setLabelVisible(true) ;
          slice_13->setColor(QColor(0 , 0 , 255));
          slice_13->setExploded(true) ; //突出
          slice_13->setExplodeDistanceFactor(0.1) ; //间隔
          slice_13->setLabel(QString::asprintf("80-110斤：%.0d头, %.1f%%", pig_weight_count[2] ,100*pig_weight_count[2]/sum_weight )) ;

          QPieSlice* slice_14 = new QPieSlice(QStringLiteral("110-150") , pig_weight_count[3]/sum_weight  , this ) ;
          slice_14->setLabelVisible(true) ;
          slice_14->setColor(QColor(120 , 0 , 200));
          slice_14->setExploded(true) ; //突出
          slice_14->setExplodeDistanceFactor(0.1) ; //间隔
          slice_14->setLabel(QString::asprintf("110-150斤：%.0d头, %.1f%%", pig_weight_count[3] ,100*pig_weight_count[3]/sum_weight )) ;

          QPieSlice* slice_15 = new QPieSlice(QStringLiteral("150+") , pig_weight_count[4]/sum_weight  , this ) ;
          slice_15->setLabelVisible(true) ;
          slice_15->setColor(QColor(50 , 50 , 100));
          slice_15->setExploded(true) ; //突出
          slice_15->setExplodeDistanceFactor(0.1) ; //间隔
          slice_15->setLabel(QString::asprintf("150+斤：%.0d头, %.1f%%", pig_weight_count[4] ,100*pig_weight_count[4]/sum_weight )) ;

          //分块加入series
          series->append(slice_11) ;
          series->append(slice_12) ;
          series->append(slice_13) ;
          series->append(slice_14) ;
          series->append(slice_15) ;

          //series加入Chart
          number_chart->addSeries(series) ;

          //  ChartView.show()
          chartView->setChart(number_chart) ;
          chartView->show() ;
      }) ;

        //button3
      QPushButton* raisetime_button = new QPushButton (&dialog) ;
       raisetime_button->resize(100 , 40 ) ;
       raisetime_button->move(850 , 620) ;
       raisetime_button->setText("猪的饲养时间分布") ;
       raisetime_button->show() ;
       connect(raisetime_button , &QPushButton::clicked , &dialog , [&]
       {
           //创建ChartView
           QChartView* chartView = new QChartView(&dialog) ;
           chartView->move(0 , 0) ;
           chartView->resize(800 , 800) ;

           //创建chart
           QChart* number_chart = new QChart() ;
           number_chart->resize(400 , 400) ;
           number_chart->setTitle("猪的饲养时间分布") ;
           number_chart->setTheme(QChart::ChartThemeBlueIcy) ; //主题
           number_chart->setVisible(true) ;
           number_chart->legend()->hide();


           //创建饼图序列
           QPieSeries* series = new QPieSeries() ;

           //饼图分块
           QPieSlice* slice_21 = new QPieSlice(QStringLiteral("0-90") , pig_raisetime_count[0]/sum_raisetime , this ) ;
           slice_21->setLabelVisible(true) ;
           slice_21->setColor(QColor(255 , 0 , 0));
           slice_21->setExploded(true) ; //突出
           slice_21->setExplodeDistanceFactor(0.1) ; //间隔
           slice_21->setLabel(QString::asprintf("0-90天：%.0d头, %.1f%%", pig_raisetime_count[0] ,100*pig_raisetime_count[0]/sum_raisetime )) ;


           QPieSlice* slice_22 = new QPieSlice(QStringLiteral("90-180") ,pig_raisetime_count[1]/sum_raisetime , this ) ;
           slice_22->setLabelVisible(true) ;
           slice_22->setColor(QColor(0 , 255 , 0));
           slice_22->setExploded(true) ; //突出
           slice_22->setExplodeDistanceFactor(0.1) ; //间隔
           slice_22->setLabel(QString::asprintf("90-180天：%.0d头, %.1f%%", pig_raisetime_count[1] ,100*pig_raisetime_count[1]/sum_raisetime )) ;



           QPieSlice* slice_23 = new QPieSlice(QStringLiteral("180-270") , pig_raisetime_count[2]/sum_raisetime  , this ) ;
           slice_23->setLabelVisible(true) ;
           slice_23->setColor(QColor(0 , 0 , 255));
           slice_23->setExploded(true) ; //突出
           slice_23->setExplodeDistanceFactor(0.1) ; //间隔
           slice_23->setLabel(QString::asprintf("180-270天：%.0d头, %.1f%%", pig_raisetime_count[2] ,100*pig_raisetime_count[2]/sum_raisetime)) ;

           QPieSlice* slice_24 = new QPieSlice(QStringLiteral("270-360") , pig_raisetime_count[3]/sum_raisetime  , this ) ;
           slice_24->setLabelVisible(true) ;
           slice_24->setColor(QColor(120 , 0 , 200));
           slice_24->setExploded(true) ; //突出
           slice_24->setExplodeDistanceFactor(0.1) ; //间隔
           slice_24->setLabel(QString::asprintf("270-360天：%.0d头, %.1f%%",pig_raisetime_count[3] ,100*pig_raisetime_count[3]/sum_raisetime)) ;

           QPieSlice* slice_25 = new QPieSlice(QStringLiteral("360+") , pig_raisetime_count[4]/sum_raisetime , this ) ;
           slice_25->setLabelVisible(true) ;
           slice_25->setColor(QColor(50 , 50 , 100));
           slice_25->setExploded(true) ; //突出
           slice_25->setExplodeDistanceFactor(0.1) ; //间隔
           slice_25->setLabel(QString::asprintf("360+天：%.0d头, %.1f%%", pig_raisetime_count[4] ,100*pig_raisetime_count[4]/sum_raisetime )) ;

           //分块加入series
           series->append(slice_21) ;
           series->append(slice_22) ;
           series->append(slice_23) ;
           series->append(slice_24) ;
           series->append(slice_25) ;

           //series加入Chart
           number_chart->addSeries(series) ;

           //  ChartView.show()
           chartView->setChart(number_chart) ;
           chartView->show() ;
       }) ;
    dialog.show() ;
    dialog.exec() ;
    return;


}


void MainFarm::close_Button_clicked( PigFarm* pfarm)
{

    pfarm->Dataout(pfarm) ;
    QFile file ("time.txt") ;
    file.open(QFile::WriteOnly | QFile::Truncate) ; //清空文件内容
    file.close() ;
    timeout << pfarm->Farm_Time ;
    this->close() ;
    return ;
}


void MainFarm::handgrow_Button_clicked(PigFarm* pfarm)
{
    for(int i = 0 ; i < 30 ; i++)
    {
         pfarm->pigfarm_grow(pfarm) ;
    }
    QFont font ;
    font.setBold(true) ;
    font.setItalic(true) ;  //斜体
    font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
    font.setPointSize(25) ;
    QPalette pal_1 ;
    pal_1.setColor(QPalette::WindowText , Qt::white) ; //设置字体颜色
    char buffer[256] ;  //想输出的字符串
    //sprintf 字符串格式化命令 ，把想要的数据转化为字符串
    sprintf( buffer , "今天是猪场第%d天" , pfarm->Farm_Time) ;
    ui->Time_label->setText(buffer) ;
    ui->Time_label->setFont(font) ;
    ui->Time_label->setPalette(pal_1) ;

    return ;
}


void MainFarm::buy_Button_clicked(PigFarm* pfarm )
{
    int b_number = pfarm->pigcolor_count(pfarm , Pig::black) ;
    int sf_number = pfarm->pigcolor_count(pfarm , Pig::sflower) ;
    int bf_number = pfarm->pigcolor_count(pfarm , Pig::bflower) ;
    int b_canbuy = 10 * b_pigsty_number - b_number ;
    int f_canbuy = 10 * (100 - b_pigsty_number) - sf_number - bf_number ;
   // qDebug() << b_canbuy << ' ' << f_canbuy  ;


    QDialog* dialog = new QDialog (this) ;
    dialog->setWindowTitle("买啥啊兄弟") ;
    dialog->resize(600 ,800) ;
    dialog->setAutoFillBackground(true) ;

    // 使用调色板QPalette来设置图片
    QPalette pal = dialog->palette() ;
    pal.setBrush(backgroundRole(), QPixmap(":/begin/Begin.jpg")) ;
    dialog->setPalette( pal) ;

    QFont font ;
    font.setBold(true) ;
    font.setItalic(true) ;  //斜体
    font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
    font.setPointSize(15) ;

    //滑块
    QSlider b_Slider (dialog) ;
    b_Slider.move(350 , 500) ;
    b_Slider.resize(215 , 25) ;
    b_Slider.setOrientation(Qt::Horizontal);  //设置为水平，默认竖直
    b_Slider.setMaximum(b_canbuy) ;
    b_Slider.setMinimum(0) ;


    QSlider sf_Slider (dialog) ;
    sf_Slider.move(350 , 600) ;
    sf_Slider.resize(210 , 25) ;
    sf_Slider.setOrientation(Qt::Horizontal);
    sf_Slider.setMaximum(f_canbuy) ;
    sf_Slider.setMinimum(0) ;

    QSlider bf_Slider (dialog) ;
    bf_Slider.move(350 , 700) ;
    bf_Slider.resize(210 , 25) ;
    bf_Slider.setOrientation(Qt::Horizontal);
    bf_Slider.setMaximum(f_canbuy) ;
    bf_Slider.setMinimum(0) ;

    //SpinBox
    QSpinBox b_spinBox (dialog) ;
    b_spinBox.move(250 , 500) ;
    b_spinBox.resize(60 , 25) ;
    b_spinBox.setMaximum(b_canbuy) ;
    b_spinBox.setMinimum(0) ;


    QSpinBox sf_spinBox (dialog) ;
    sf_spinBox.move(250 , 600) ;
    sf_spinBox.resize(60 , 25) ;
    sf_spinBox.setMaximum(f_canbuy) ;
    sf_spinBox.setMinimum(0) ;


    QSpinBox bf_spinBox (dialog) ;
    bf_spinBox.move(250 , 700) ;
    bf_spinBox.resize(60 , 25) ;
    bf_spinBox.setMaximum(f_canbuy) ;
    bf_spinBox.setMinimum(0) ;


    //Label
    QLabel b_label (dialog) ;
    b_label.move (100 , 500) ;
    b_label.resize(100 , 25) ;
    b_label.setText("黑猪") ;
    b_label.setFont(font) ;

    QLabel sf_label (dialog) ;
    sf_label.move (100 , 600) ;
    sf_label.resize(100 , 25) ;
    sf_label.setText("小花猪") ;
    sf_label.setFont(font) ;

    QLabel bf_label (dialog) ;
    bf_label.move (100 , 700) ;
    bf_label.resize(100 , 25) ;
    bf_label.setText("大白花猪") ;
    bf_label.setFont(font) ;


    // 初值选择的控件间槽函数链接
    connect( &b_Slider , SIGNAL(valueChanged(int)) , &b_spinBox , SLOT(setValue(int)) ) ; //ui->b_Slider 本身就是char*类型
    connect( &b_spinBox , SIGNAL(valueChanged(int)) , &b_Slider , SLOT(setValue(int)) ) ;
    connect( &sf_Slider , SIGNAL(valueChanged(int)) , &sf_spinBox , SLOT(setValue(int)) ) ;
    connect( &sf_spinBox , SIGNAL(valueChanged(int)) , &sf_Slider , SLOT(setValue(int)) ) ;
    connect( &bf_Slider , SIGNAL(valueChanged(int)) , &bf_spinBox , SLOT(setValue(int)) ) ; //ui->b_Slider 本身就是char*类型
    connect( &bf_spinBox , SIGNAL(valueChanged(int)) , &bf_Slider , SLOT(setValue(int)) ) ;

    QLabel label(dialog) ;
    label.move(50, 50) ;
    label.resize(600 , 100) ;
    label.setText("请输入你想购买猪的数量") ;
    label.setFont(font) ;

    QPushButton sure_button (dialog) ;
    sure_button.move(400 , 50) ;
    sure_button.resize(150 , 50) ;
    sure_button.setText("确定") ;
    sure_button.setFont(font) ;




    connect(&sure_button , &QPushButton::clicked , dialog ,[&]{
                int b_addnumber = b_Slider.value() ;
                int sf_addnumber = sf_Slider.value() ;
                int bf_addnumber = bf_Slider.value() ;
              //  qDebug() << b_addnumber ;
                if (bf_addnumber + sf_addnumber > f_canbuy)
                {
                    QDialog dialog(this) ;
                    dialog.setWindowTitle("购买失败") ;
                    dialog.resize(400 ,400) ;


                    QLabel quitLabel ( &dialog) ;
                    quitLabel.resize(300 , 300) ;
                    quitLabel.move( 50, 0) ;
                    quitLabel.setScaledContents(true) ;
                    QMovie* movie =  new QMovie (":/begin/Begin_quit.gif") ;
                    quitLabel.setMovie(movie) ;
                    movie->start() ;

                    QFont font ;
                    font.setBold(true) ;
                    font.setItalic(true) ;  //斜体
                    font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
                    font.setPointSize(15) ;

                    QPushButton quit_true ("确定", &dialog);
                    quit_true.move(80 , 350) ;
                    quit_true.resize(50 , 40) ;
                    quit_true.setFont(font) ;


                    QLabel label ("哪有那么多猪" , &dialog) ;
                    label.move( 80 , 310) ;
                    label.resize( 200 , 40) ;
                    label.setFont(font) ;


                    connect( &quit_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

                    dialog.show() ;
                    dialog.exec() ;

                }
                else
                {
                    pfarm->pigfarm_buy(pfarm ,b_addnumber ,sf_addnumber , bf_addnumber , b_pigsty_number) ;



                    QDialog* dialog1 = new QDialog (this) ;
                    dialog1->setWindowTitle("购买完毕") ;
                    dialog1->resize(400 ,400) ;
                    QLabel buyLabel ( dialog1) ;
                    buyLabel.resize(400 , 300) ;
                    buyLabel.move( 0, 0) ;
                    buyLabel.setScaledContents(true) ;
                    QMovie* movie =  new QMovie (":/buy.gif") ;
                    buyLabel.setMovie(movie) ;
                    movie->start() ;

                    QFont font ;
                    font.setBold(true) ;
                    font.setItalic(true) ;  //斜体
                    font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
                    font.setPointSize(15) ;

                    QPushButton back_true ("确定", dialog1);
                    back_true.move(80 , 350) ;
                    back_true.resize(50 , 40) ;
                    back_true.setFont(font) ;

                    QLabel label ("成功进货，对它们好点哈" , dialog1) ;
                    label.move( 50 , 310) ;
                    label.resize( 300 , 40) ;
                    label.setFont(font) ;

                    connect( &back_true , SIGNAL(clicked()) , dialog1 , SLOT(close())) ;
                    dialog1->show() ;
                    dialog1->exec() ;
                }


    }) ;

    dialog->show() ;
    dialog->exec() ;



}


void MainFarm::sell_Button_clicked(PigFarm* pfarm)
{
  if(SICK[0][10] != 6)
  {
    double income = pfarm->pigfarm_sell(pfarm) ;
    if (income > 0)
    {
        QDialog dialog(this) ;
        dialog.setWindowTitle("卖猪成功") ;
        dialog.resize(400 ,400) ;
        QLabel loadLabel ( &dialog) ;
        loadLabel.resize(400 , 300) ;
        loadLabel.move( 0, 0) ;
        loadLabel.setScaledContents(true) ;
        QMovie* movie =  new QMovie (":/farmpicture/sell.gif") ;
        loadLabel.setMovie(movie) ;
        movie->start() ;

        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(15) ;
        QLabel label ("赚了赚了，去交税吧" , &dialog) ;
        label.move( 50 , 310) ;
        label.resize( 300 , 40) ;
        label.setFont(font) ;
        QPushButton sell_true ("确定", &dialog);
        sell_true.move(80 , 350) ;
        sell_true.resize(50 , 40) ;
        sell_true.setFont(font) ;

        connect( &sell_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

        dialog.show() ;
        dialog.exec() ;

    }
    else
    {

        QDialog dialog(this) ;
        dialog.setWindowTitle("卖猪失败") ;
        dialog.resize(400 ,400) ;
        QLabel loadLabel ( &dialog) ;
        loadLabel.resize(400 , 300) ;
        loadLabel.move( 0, 0) ;
        loadLabel.setScaledContents(true) ;
        QMovie* movie =  new QMovie (":/begin/load.gif") ;
        loadLabel.setMovie(movie) ;
        movie->start() ;

        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(15) ;

        QPushButton sell_false ("确定", &dialog);
        sell_false.move(80 , 350) ;
        sell_false.resize(50 , 40) ;
        sell_false.setFont(font) ;

        QLabel label ("卖个der，再养养" , &dialog) ;
        label.move( 50 , 310) ;
        label.resize( 300 , 40) ;
        label.setFont(font) ;

        connect( &sell_false, SIGNAL(clicked()) , &dialog , SLOT(close())) ;

        dialog.show() ;
        dialog.exec() ;

    }
  }
  else
  {
      QDialog dialog(this) ;
      dialog.setWindowTitle("卖猪失败") ;
      dialog.resize(400 ,400) ;
      QLabel loadLabel ( &dialog) ;
      loadLabel.resize(400 , 300) ;
      loadLabel.move( 0, 0) ;
      loadLabel.setScaledContents(true) ;
      QMovie* movie =  new QMovie (":/begin/Begin_quit.gif") ;
      loadLabel.setMovie(movie) ;
      movie->start() ;

      QFont font ;
      font.setBold(true) ;
      font.setItalic(true) ;  //斜体
      font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
      font.setPointSize(15) ;

      QPushButton sell_false ("确定", &dialog);
      sell_false.move(80 , 350) ;
      sell_false.resize(50 , 40) ;
      sell_false.setFont(font) ;

      QLabel label ("猪瘟了还卖？举报了" , &dialog) ;
      label.move( 50 , 310) ;
      label.resize( 300 , 40) ;
      label.setFont(font) ;

      connect( &sell_false, SIGNAL(clicked()) , &dialog , SLOT(close())) ;

      dialog.show() ;
      dialog.exec() ;
   }
    return ;
}


void MainFarm::Sick_Button_clicked(PigFarm* pfarm)
{
    if (SICK[0][10] == 0)
    {
        pfarm->getsick(pfarm) ;
        ui->handgrow_Button->setCheckable(false) ;
        QList <QPushButton*> button_list = ui->Page_Stacked->findChildren <QPushButton*> () ;
        foreach(QPushButton* btn , button_list) //循环list中的所有按钮
            {
                btn->setChecked(true) ;
                int temp = btn->text().toInt() ;
                if(SICK[temp][10] == 6)
                {
                    btn->setStyleSheet("border-image:url(:/pigsty_sick.jpg)") ;
                }
            }

        QDialog dialog(this) ;
        dialog.setWindowTitle("瘟疫爆发") ;
        dialog.resize(400 ,400) ;
        QLabel loadLabel ( &dialog) ;
        loadLabel.resize(400 , 300) ;
        loadLabel.move( 0, 0) ;
        loadLabel.setScaledContents(true) ;
        QMovie* movie =  new QMovie (":/getSick.gif") ;
        loadLabel.setMovie(movie) ;
        movie->start() ;

        QFont font ;
        font.setBold(true) ;
        font.setItalic(true) ;  //斜体
        font.setFamily(QStringLiteral("幼圆")) ;  // 设置字体
        font.setPointSize(15) ;

        QPushButton sick_true ("确定", &dialog);
        sick_true.move(80 , 350) ;
        sick_true.resize(50 , 40) ;
        sick_true.setFont(font) ;

        QLabel label (&dialog) ;

        char buffer[256] ;  //想输出的字符串
        //sprintf 字符串格式化命令 ，把想要的数据转化为字符串
        sprintf( buffer , "死神降临第%d号猪圈第%d号猪感染" , SICK[0][0] , SICK[0][1]) ;
        label.setText(buffer) ;
        label.move( 50 , 310) ;
        label.resize( 300 , 40) ;
        label.setFont(font) ;

        connect( &sick_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

        dialog.show() ;
        dialog.exec() ;
    }

}


void MainFarm::text_Button_clicked()     // 需要深入
{

        QDialog dialog (this) ;
        dialog.resize(600,600) ;
        QPlainTextEdit plainTextEdit (&dialog) ;
        plainTextEdit.resize(600,600);

        //需要深化
      /*  QString curPath=QDir::currentPath(); //打开确定的不需要
        QString dlgTitle="历史售卖信息";
         QString filter="文本文件(*.txt)"; //打开确定的不需要
        QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,NULL,"Sell.txt");


        if(!aFileName.isEmpty())
        {
            QFile file (aFileName) ;
            file.open(QIODeviceBase::ReadOnly) ;
            QByteArray array = file.readAll() ;
            plainTextEdit.appendPlainText(array);
        }
                */
        QFile file ("Sell.txt") ;
        file.open(QIODeviceBase::ReadOnly) ;
        QByteArray array = file.readAll() ;
        plainTextEdit.appendPlainText(array);

        dialog.show();
        dialog.exec();
}


void MainFarm::measure_Button_clicked(PigFarm* pfarm) // 应该可以写进PigFarm里
{

    if (SICK[0][10] == 6)
    {
        //隔离左侧

        for (int i = 1 ; i <= SICK[0][0] ; i++)  //从没病到有病 ， 且病原大于1
        {
            if(SICK[i][10] == 6 ) // 最小侧病猪圈
            {
                 //第一个猪圈有病猪,左侧不隔离,啥也不用管

                if(i != 1)  //非第一个猪圈有病猪
                {
                    fout << endl << "隔离被迫卖猪" << endl ;
                    Pigsty* temp = pfarm->pigstyhead ;
                    for (int j = 1 ; j < i-1 ; j++)
                    {
                        temp = temp->pigstynext ;
                    }
                    for (int k = 0 ; k < 10 ; k++)      //卖前一猪圈的猪
                    {
                       if(temp->sty[k].weight > 0)
                       {
                           pfarm ->sell_pig(temp , k) ;
                       }
                    }
                }
                break ;
            }
        }


        //隔离右侧

        for (int i = SICK[0][0] ; i < 101 ; i++)    //从有病到没病或者到头
        {
            //到头什么也不干，也不进if
            if(SICK[i][10] == 0 ) // 最大侧病猪圈存在,遇到第一个没病猪圈直接卖
            {
               Pigsty* temp = pfarm->pigstyhead ;
               for (int j = 1 ; j < i ; j++)
               {
                    temp = temp->pigstynext ;
               }
               for (int k = 0 ; k < 10 ; k++)      //卖当前猪圈的猪
               {
                   if(temp->sty[k].weight > 0)
                   {
                       pfarm ->sell_pig(temp , k) ;
                   }
               }
               break ;
             }

        }
    }

}


