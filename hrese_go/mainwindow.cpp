#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"horse.h"

std::map<int,pii>hash_grid;
std::map<int,QString>img_path;
pii change_xy;
int img_horse=0;
int sec_chose=0;
int over=0;
std::vector<pii>sec;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_sec();
    init_Mainwindow();
    set_grid_pushbutton();
    init_img_horse();
}

MainWindow::~MainWindow()
{

    delete ui;
}
//遍历结果
void MainWindow::do_hores_traversal(){
    if(horse::begin_x<1||horse::begin_x>8||horse::begin_y<1||horse::begin_y>8){
        QMessageBox::warning(this, "不合法", "请重新选择起点！");
    }
    else{
        horse::init(horse::begin_x,horse::begin_y);
        horse::hores_traversal(horse::begin_x-1,horse::begin_y-1,2);
    }
}
//设置；绿色主题
void MainWindow::set_green_theme(){
    QPixmap pix1=QPixmap(":/image/1.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pix1));
    this->setPalette(palette);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
        ui->grid->setItem(i,j,new QTableWidgetItem(" "));
        if (!((i % 2 == 0 && j % 2  == 0) || (i % 2 != 0 && j % 2 != 0))) {
            ui->grid->item(i, j)->setBackground(QColor(222, 252, 249));
        }
        else{
           ui->grid->item(i, j)->setBackground(QColor(168, 230, 207));
        }
        }
    }
}
//初始化棋盘
void MainWindow::init_Mainwindow(){
    this->setWindowTitle("马踏棋盘");
    this->setFixedSize(800,700);
    this->setAutoFillBackground(true);
    set_green_theme();
    set_close_title_clu();
    set_pic_kongjian();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::delayedFunction);
    connect(this, &MainWindow::picSet, this, &MainWindow::delayedFunction, Qt::QueuedConnection);

}
//这是控件图片
void MainWindow::set_pic_kongjian(){
    //cuohao
    this->ui->cuohao->setIcon(QIcon(":/image/cuo_hao.png"));
    this->ui->cuohao->setStyleSheet("background-color: transparent;");
    //最小化
    this->ui->min->setIcon(QIcon(":/image/min.png"));
    this->ui->min->setStyleSheet("background-color: transparent;");
    //马——大图
    QPixmap pixmap_h1(":/image/h1.png");
    pixmap_h1= pixmap_h1.scaled(ui->title->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->title->setPixmap(pixmap_h1);
    //标题cone图片
    QPixmap pixmap_cone(":/image/icons8_title_4.png");
    pixmap_cone= pixmap_cone.scaled(ui->title_cone->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->title_cone->setPixmap(pixmap_cone);
}
//设置马的图片
void MainWindow::init_img_horse(){
    img_path[0]=":/image/h1.png";
}
//遍历的时间间隔
void MainWindow::init_sec(){
    sec.resize(2);
    sec[0]={300,250};
    sec[1]={1000,900};
}
//对于点击棋盘的单元格
void MainWindow::onBuClicked(int row, int column) {
    horse::begin_x=row+1;
    horse::begin_y=column+1;
//    QMessageBox msg(this);
//    QString row_s(row+'1');
//    QString column_s(column+'1');
//    QString x=row_s+","+column_s;
//    msg.setText(x);
//    msg.exec();

//    qDebug()<<horse::begin_x<<"  "<<horse::begin_y;
//        qDebug() << "Button at row" << row << "column" << column << "was clicked.";
   }

//给每一个网格上加的pushbutton，点击选初始位置
void MainWindow::set_grid_pushbutton(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            QPushButton *bu=new QPushButton("",this);
            ui->grid->setCellWidget(i,j,bu);
            bu->setStyleSheet("background-color: transparent;");
            connect(bu,&QPushButton::clicked, [=]() {
                onBuClicked(i, j);
            });
        }
    }
}


//在遍历过程中 设置显示已经遍历的单元格
void MainWindow::set_pic(pii xy){
    change_xy=xy;
    QPixmap pixmap0(img_path[img_horse]);
    MyDelegate *delegate = new MyDelegate;
    ui->grid->setItemDelegate(delegate);
    QIcon icon(QIcon::fromTheme(img_path[img_horse]));
    QTableWidgetItem* item1 = new QTableWidgetItem();
    item1->setData(Qt::UserRole + 1, QVariant::fromValue(icon));
    ui->grid->setItem(xy.first,xy.second,item1);
    emit picSet(xy); // 发送信号
    timer->stop();
    timer->start(sec[sec_chose].second);
}


//设置延迟显示
void MainWindow::delayedFunction(){
    if(change_xy.first>=0&&change_xy.first<8&&change_xy.second>=0&&change_xy.second<8){

        QColor background_color ;
        if (!((change_xy.first % 2 == 0 &&change_xy.second % 2  == 0) || (change_xy.first % 2 != 0 && change_xy.second % 2 != 0))) {
            background_color =QColor(222, 252, 249);
        }
        else{
            background_color =(QColor(168, 230, 207));

        }
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(horse::grid[change_xy.first][change_xy.second]));
    item2->setBackground(QBrush(background_color));
    ui->grid->setItem(change_xy.first, change_xy.second, item2);
    }
}

//遍历过程的动画展示
void MainWindow::show_horse_traversal(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            hash_grid[horse::grid[i][j]] = {i, j};
        }
    }
    for (int i = 0; i <= 64; i++) {
        if(i==64){
            i=65;
        }
            QTimer::singleShot(sec[sec_chose].first*i, this, [this, i]() {
                auto it = hash_grid.find((i + 1)%65);
                if (it != hash_grid.end()) {
                        set_pic(it->second);
                }
            });
        }

}
//设置标题栏不显示
void MainWindow::set_close_title_clu(){
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->cuohao->setVisible(true);
    ui->min->setVisible(true);
}
//窗口移动
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时的位置
        dragPosition = event->globalPos() - frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // 根据鼠标的移动更新窗口的位置
        QPoint newPos = event->globalPos() - dragPosition;
        this->move(newPos);
    }
}

//转到槽的槽函数
void MainWindow::on_begin_clicked()
{
    do_hores_traversal();
    show_horse_traversal();
    be_timer=new QTimer();
    be_timer->start(sec[sec_chose].first*64);
    if(over==0){
        ui->begin->setEnabled(false);
        ui->rebegin->setEnabled(false);
        ui->re1->setEnabled(false);
        ui->re2->setEnabled(false);
    }
    connect(be_timer, &QTimer::timeout, this, [=](){
        ui->begin->setEnabled(true);
        ui->rebegin->setEnabled(true);
        ui->re1->setEnabled(true);
        ui->re2->setEnabled(true);
    });
}

void MainWindow::on_cuohao_clicked()
{
    this->close();
}

void MainWindow::on_min_clicked()
{
    this->showMinimized();
}

void MainWindow::on_rebegin_clicked()
{
    horse::init(-1,-1);
    change_xy={-1,-1};
    set_green_theme();
    be_timer->stop();
}

void MainWindow::on_re2_clicked()
{
    sec_chose=1;
}

void MainWindow::on_re1_clicked()
{
    sec_chose=0;
}

