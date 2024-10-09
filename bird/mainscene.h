#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include"bird.h"
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    Bird *m_Bird;
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //记录自动移动的坐标
    QPoint m_auto_pos;
    //自动移动的定时器
    QTimer *timer;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
