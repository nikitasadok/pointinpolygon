#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Drawer;
}

class Drawer : public QWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = nullptr);
    ~Drawer();

protected:
    void paintEvent(QPaintEvent *event);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Drawer *ui;
};

#endif // DRAWER_H
