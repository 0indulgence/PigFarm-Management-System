#ifndef FARMDIALOG_H
#define FARMDIALOG_H

#include <pigfarm.h>
#include <mainfarm.h>
#include <QDialog>
#include <QBrush>
#include <QMovie>

extern PigFarm pfarm ;


QT_BEGIN_NAMESPACE
namespace Ui { class farmDialog; }
QT_END_NAMESPACE

extern int comeon [3] ;
class farmDialog : public QDialog
{
    Q_OBJECT

public:
    farmDialog(QWidget *parent = nullptr);
    ~farmDialog();

private slots:
    void on_LoadButton_clicked();

    void on_EnterButton_clicked();

    void on_QuitButton_clicked();

public:
    Ui::farmDialog *ui;

signals:



};

#endif // FARMDIALOG_H
