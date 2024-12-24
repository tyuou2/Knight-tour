#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStack>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <string.h>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextStream>
#include <QFileDialog>
#include<QProgressBar>
#include <QFont>
#include<set>
#include<QTimer>
#include<QThread>
#include<QFontDatabase>
#include <QMovie>
#include <QVBoxLayout>
#include<cmath>
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include"MyDelegate.h"
typedef std::pair<int,int> pii;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;
    QTimer *be_timer;
private slots:
    void on_begin_clicked();
    void init_Mainwindow();
    void set_grid_pushbutton();
    void do_hores_traversal();
    void show_horse_traversal();
    void set_pic(pii xy);
    void init_img_horse();
    void delayedFunction();
    void mousePressEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event);
    void set_close_title_clu();
    void on_cuohao_clicked();
    void set_pic_kongjian();
    void set_green_theme();
    void on_min_clicked();
    void on_rebegin_clicked();
    void init_sec();

    void on_re2_clicked();
void onBuClicked(int row, int column);
    void on_re1_clicked();

private: signals:
    void picSet(pii& xy);
private:
    Ui::MainWindow *ui;
    QPoint dragPosition;
};
#endif // MAINWINDOW_H
