#pragma once
#ifndef LOGIN_H
#define LOGIN_H
#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_sign_out_clicked(bool checked);

    void on_sign_in_clicked(bool checked);

    void on_password_textChanged(const QString &arg1);

private:
    Ui::Login *ui;
    QSqlTableModel *model;
};

#endif // LOGIN_H
