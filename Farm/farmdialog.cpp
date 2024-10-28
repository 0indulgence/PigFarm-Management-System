#include "farmdialog.h"
#include "ui_farmdialog.h"



farmDialog::farmDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::farmDialog)
{
    ui->setupUi(this);
    this->setFixedSize( 1000 , 760 ) ;
    setAutoFillBackground(true) ;

    // 使用调色板QPalette来设置图片
    QPalette pal = this->palette() ;
    pal.setBrush(backgroundRole(), QPixmap(":/begin/Begin.jpg")) ;
    setPalette( pal) ;

    /* 面罩还不会用
    QPixmap maskPixmap (":/begin/Beginbutton.jpg") ;
    ui->EnterButton->setMask(maskPixmap.mask()) ;
    */

    // 利用Qlabel添加动图
    ui->Run_label->setScaledContents(true) ;
    QMovie* movie =  new QMovie (":/begin/Begin_Run.gif") ;
    ui->Run_label->setMovie(movie) ;
    movie->start() ;

    // 初值选择的控件间槽函数链接
    connect( ui->b_Slider , SIGNAL(valueChanged(int)) , ui->b_spinBox , SLOT(setValue(int)) ) ; //ui->b_Slider 本身就是char*类型
    connect( ui->b_spinBox , SIGNAL(valueChanged(int)) , ui->b_Slider , SLOT(setValue(int)) ) ;
    connect( ui->sf_Slider , SIGNAL(valueChanged(int)) , ui->sf_spinBox , SLOT(setValue(int)) ) ;
    connect( ui->sf_spinBox , SIGNAL(valueChanged(int)) , ui->sf_Slider , SLOT(setValue(int)) ) ;
    connect( ui->bf_Slider , SIGNAL(valueChanged(int)) , ui->bf_spinBox , SLOT(setValue(int)) ) ; //ui->b_Slider 本身就是char*类型
    connect( ui->bf_spinBox , SIGNAL(valueChanged(int)) , ui->bf_Slider , SLOT(setValue(int)) ) ;


}

farmDialog::~farmDialog()
{
    delete ui;
}


void farmDialog::on_LoadButton_clicked()
{
    //亲身试验过，读而非取 ,前一次存入的数据会在下一次被取出来
    int text ;
    datain >> text ;
    if (datain.eof())
    {
        QDialog dialog(this) ;
        dialog.setWindowTitle("农场不存在") ;
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

        QPushButton load_true ("确定", &dialog);
        load_true.move(80 , 350) ;
        load_true.resize(50 , 40) ;
        load_true.setFont(font) ;

        QLabel label ("凭空变猪场？你个老六" , &dialog) ;
        label.move( 50 , 310) ;
        label.resize( 300 , 40) ;
        label.setFont(font) ;

        connect( &load_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;

        dialog.show() ;
        dialog.exec() ;

    }
    else
    {
        comeon[0] = 0 ;
        comeon[1] = 0 ;
        comeon[2] = 0 ;

        MainFarm* m ;
        m = new MainFarm ;           //动态创建避免函数作用域结束后，所生成的界面对象被一同回收
        m->show() ;
        this->hide() ;
    }

    return ;
}


void farmDialog::on_EnterButton_clicked()
{
    int b_number = ui->b_spinBox->text().toInt() ;
    int sf_number = ui->sf_spinBox->text().toInt() ;
    int bf_number = ui->bf_spinBox->text().toInt() ;
    if (b_number + sf_number +bf_number > 1000)
    {
        QDialog dialog(this) ;
        dialog.setWindowTitle("猪场会炸") ;
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
        QLabel label ("人不能贪得无厌哦" , &dialog) ;
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
    else if (b_number + sf_number +bf_number != 0)
    {
        comeon[0] = b_number ;
        comeon[1] = sf_number ;
        comeon[2] = bf_number ;


        MainFarm* m ;
        m = new MainFarm ;           //动态创建避免函数作用域结束后，所生成的界面对象被一同回收
        m->show() ;                    //界面建立失败会闪退
        this->hide() ;
    }


}


void farmDialog::on_QuitButton_clicked()
{
    QDialog dialog(this) ;
    dialog.setWindowTitle("退出") ;
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

    QPushButton quit_false ("取消" , &dialog) ;
    quit_false.move(280 , 350) ;
    quit_false.resize(50 , 40) ;
    quit_false.setFont(font) ;

    QLabel label ("确定要退出嘛~" , &dialog) ;
    label.move( 80 , 310) ;
    label.resize( 200 , 40) ;
    label.setFont(font) ;

    connect( &quit_true , SIGNAL(clicked()) , this , SLOT(close())) ;
    connect( &quit_true , SIGNAL(clicked()) , &dialog , SLOT(close())) ;
    connect( &quit_false , SIGNAL(clicked()) , &dialog , SLOT(close())) ;
    dialog.show() ;
    dialog.exec() ;

}

