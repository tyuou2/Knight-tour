#include "login.h"
#include "ui_login.h"
#include"mainwindow.h"
#include<QDebug>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(400,280);
    set_icon();

    QPixmap pix1=QPixmap(":/image/1.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pix1));
    this->setPalette(palette);

    ui->password->setEchoMode(QLineEdit::Password);
    //设置密码输入框的占位符
     ui->password->setPlaceholderText(tr("请输入密码"));
     ui->username->setPlaceholderText(tr("请输入账号"));
}


void login::set_icon(){
    ui->clo->setIcon(QIcon(":/image/cuo_hao.png"));
    ui->clo->setStyleSheet("background-color: transparent;");

    ui->min_login->setIcon(QIcon(":/image/min.png"));
    ui->min_login->setStyleSheet("background-color: transparent;");

//    QPixmap pixmap_xiaohui(":/image/xiaohui2.png");
//    pixmap_xiaohui= pixmap_xiaohui.scaled(ui->xaohui->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    ui->xaohui->setPixmap(pixmap_xiaohui);

    QPixmap pixmap_hre_t(":/image/icons8_title_4.png");
    pixmap_hre_t= pixmap_hre_t.scaled(ui->hor_tit->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    ui->xaohui->setPixmap(pixmap_xiaohui);
    ui->hor_tit->setPixmap(pixmap_hre_t);
}
login::~login()
{
    delete ui;

}
void login::on_login_2_clicked()
{
        QString username = ui->username->text();
        QString password = ui->password->text();
        if (check_login(username, password)) {
            this->hide();
            MainWindow *mainWindow = new MainWindow; // 创建主窗口实例
            mainWindow->show(); // 显示主窗口
        } else {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle(tr("登陆失败"));  // 设置窗口标题
            msgBox.setIcon(QMessageBox::NoIcon);      // 设置图标为警告
            msgBox.setText(tr("账号或密码错误"));  // 告诉输入错了
            msgBox.setInformativeText(tr("请重新输入"));  //让用户重新输入

            // 设置自定义按钮
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.button(QMessageBox::Ok)->setText(tr("OK"));
            // 设置按钮的快捷键
            msgBox.button(QMessageBox::Ok)->setShortcut(Qt::Key_Return);
            msgBox.setStyleSheet(
                "QMessageBox { "
                "background-image: url(:/image/1.jpg); "
                "font-size: 12pt; "
                "background-size: cover; "
                "color: #222; "
                "background-color: #fff; "
                "border: 1px solid #ccc; "
                "}"
            );
            msgBox.exec();
        }
}
bool login::check_login(const QString &username, const QString &password) {
        // 使用测试账号登录验证
        if(username=="2307020323"&&password=="123456"){
            return true;
        }
        //其他登录验证
        QString filePath = QCoreApplication::applicationDirPath() + "/user.txt";
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 2 && fields[0] == username && fields[1] == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

bool login::registerUser(const QString &username, const QString &password) {
    QString filePath = QCoreApplication::applicationDirPath() + "/user.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }
    QTextStream out(&file);
    out << username << "," << password << "\n";
    file.close();
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("注册成功"));  // 设置窗口标题
    msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setText(tr("注册成功"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.button(QMessageBox::Ok)->setText(tr("OK"));
    // 设置按钮的快捷键
    msgBox.button(QMessageBox::Ok)->setShortcut(Qt::Key_Return);
    msgBox.setStyleSheet(
        "QMessageBox { "
        "background-image: url(:/image/1.jpg); "
        "font-size: 12pt; "
        "background-size: cover; "
        "color: #222; "
        "background-color: #fff; "
        "border: 1px solid #ccc; "
        "}"
    );
    msgBox.exec();
    return true;
}

void login::on_clo_clicked()
{
    this->close();
}

void login::on_min_login_clicked()
{
    this->showMinimized();
}
void login::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时的位置
        Position = event->globalPos() - frameGeometry().topLeft();
    }
}

void login::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // 根据鼠标的移动更新窗口的位置
        QPoint newPos = event->globalPos() - Position;
        this->move(newPos);
    }
}

void login::on_test_clicked()
{
    ui->username->setText("2307020323");
    ui->password->setText("123456");
}

void login::on_register_2_clicked()
{
    if(ui->username->text()==""||ui->password->text()==""){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("注册失败"));  // 设置窗口标题
        msgBox.setIcon(QMessageBox::NoIcon);
        msgBox.setText(tr("请重新输入您要注册的账号和密码"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.button(QMessageBox::Ok)->setText(tr("OK"));
        // 设置按钮的快捷键
        msgBox.button(QMessageBox::Ok)->setShortcut(Qt::Key_Return);
        msgBox.setStyleSheet(
            "QMessageBox { "
            "background-image: url(:/image/1.jpg); "
            "font-size: 12pt; "
            "background-size: cover; "
            "color: #222; "
            "background-color: #fff; "
            "border: 1px solid #ccc; "
            "}"
        );
        msgBox.exec();
    }
    else{
        registerUser(ui->username->text(), ui->password->text());
    }
}
