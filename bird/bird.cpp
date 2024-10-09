#include "bird.h"
#include<QMouseEvent>
Bird::Bird(QWidget *parent)
    : QWidget{parent}
{
    //加载图片
    for(int i=0;i<this->max;i++){
        QString str=QString(":/birdres/bird%1").arg(i+1);
        this->m_bird_pix.load(str);
    }
    //设置鸟的尺寸
    this->setFixedSize(this->m_bird_pix.width(),this->m_bird_pix.height());

    //实例化定时器对象
    timer=new QTimer;
    //监听定时器发出的信号，进行切图
    connect(this->timer,&QTimer::timeout,this,[=](){
        QString str=QString(":/birdres/bird%1").arg(this->min++);
        this->m_bird_pix.load(str);
        if(this->min>this->max){
            this->min=1;
        }
        emit changepix();
    });

    //创建菜单对象
    this->m_menu=new QMenu;
    //监听菜单所发出的信号
    connect(this->m_menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });
}
void Bird::running(){
    //启动定时器
    this->timer->start(50);
}
void Bird::mousePressEvent(QMouseEvent *e){
    //鼠标按下时，记录分量坐标：鼠标全局坐标减去边框父亲坐标
    //e代表鼠标,((QWidget *)this->parent())->frameGeometry().topLeft()代表获取当前窗口左上角坐标
    this->m_pos=e->globalPos()-((QWidget *)this->parent())->frameGeometry().topLeft();
    //鼠标按下时状态为真
    this->mousedown=true;

    //点击右键，弹出菜单,菜单坐标为光标处
    if(e->button()==Qt::RightButton){
        this->m_menu->popup(QCursor::pos());
    }
    //不退出，鸟要继续飞行，发出菜单隐藏的信号
    connect(this->m_menu,&QMenu::aboutToHide,this,[=](){
        this->mousedown=false;
    });
}
void Bird::mouseMoveEvent(QMouseEvent *e){
    //在移动过程中，反向获取窗口最终移动坐标，把坐标作为信号发出去
    emit moving(e->globalPos()-this->m_pos);
}
void Bird::mouseReleaseEvent(QMouseEvent *){
    //鼠标释放时鼠标按下的状态为假
    this->mousedown=false;
}
