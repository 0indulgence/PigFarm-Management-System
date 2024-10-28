#ifndef BUY_WINDOW_H
#define BUY_WINDOW_H

#include <QWidget>

namespace Ui {
class buy_window;
}

class buy_window : public QWidget
{
    Q_OBJECT

public:
    explicit buy_window(QWidget *parent = nullptr);
    ~buy_window();

private:
    Ui::buy_window *ui;
};

#endif // BUY_WINDOW_H
