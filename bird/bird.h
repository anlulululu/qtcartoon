#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include<QPixmap>
#include<QTimer>
#include<QPoint>
#include<QMenu>
class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);
    //鸟显示图片
    QPixmap m_bird_pix;
    //最小下标
    int min=1;
    //最大下标
    int max=8;

    //设置一个定时器
    QTimer *timer;
    //执行动画，启动定时器
    void running();

    //记录分量坐标
    QPoint m_pos;
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *e);
    //重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *);
    //鼠标按下的状态
    bool mousedown=false;
    //创建菜单实现退出
    QMenu *m_menu;

signals:
    //自定义信号,代表正在切换图片的信号
    void changepix();
    //自定义信号，代表拖拽后主场景应移动的位置
    void moving(QPoint point);
};

#endif // BIRD_H
