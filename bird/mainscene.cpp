#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QScreen>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon(":/birdres/birdIcon.ico"));
    //设置标题
    this->setWindowTitle(QString("bird"));
    //创建鸟对象
    this->m_Bird=new Bird;
    this->m_Bird->setParent(this);
    //设置窗口大小
    this->setFixedSize(this->m_Bird->m_bird_pix.width(),this->m_Bird->m_bird_pix.height());

    //启动鸟飞翔的动画
    this->m_Bird->running();
    //监听鸟切图的信号
    connect(m_Bird,&Bird::changepix,this,[=](){
        update();//重新调用绘图事件函数，重新画图
    });

    //监听鸟拖拽移动的信号
    connect(this->m_Bird,&Bird::moving,this,[=](QPoint point){
        this->move(point);
        this->m_auto_pos=point;//鼠标拖拽时，更新当前窗口的值
    });

    //获取屏幕
    QScreen *screen=QGuiApplication::primaryScreen();
    //创建定时器对象
    timer=new QTimer(this);
    //启动定时器
    this->timer->start(30);
    //监听定时器发出的信号
    connect(this->timer,&QTimer::timeout,this,[=](){
        //让鸟在按下时不向前移动，释放时向前移动
        if(this->m_Bird->mousedown==false){
            this->m_auto_pos.setX(this->m_auto_pos.x()+5);
        }

        if(this->m_auto_pos.x()>screen->geometry().width()){
            this->m_auto_pos.setX(-this->m_Bird->width());
        }
        //更新窗口的坐标，窗口同步移动
        this->move(this->m_auto_pos);
    });

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置透明窗口，120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口顶层
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);
    //设置起始y坐标
    this->m_auto_pos.setY(screen->geometry().height()*0.5-this->m_Bird->height());
}
void MainScene::paintEvent(QPaintEvent *){
    QPainter *painter=new QPainter(this);
    painter->drawPixmap(0,0,this->m_Bird->m_bird_pix);

}
MainScene::~MainScene()
{
    delete ui;
}
