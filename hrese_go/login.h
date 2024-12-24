#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QMessageBox>
#include<QFile>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_login_2_clicked();
    bool check_login(const QString &username, const QString &password);
    void set_icon();
    void on_clo_clicked();
    bool registerUser(const QString &username, const QString &password);
    void on_min_login_clicked();
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void on_test_clicked();

    void on_register_2_clicked();

private:
    Ui::login *ui;
    QPoint Position;
};

#endif // LOGIN_H
