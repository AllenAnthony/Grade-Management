#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->model = new QSqlTableModel(this);
    this->model->setTable("Administator");
}

Login::~Login()
{
    delete ui;
}

void Login::on_sign_out_clicked(bool checked)
{
    close();

}

void Login::on_sign_in_clicked(bool checked)
{

    QSqlQuery query;
    query.exec("select * from Administator");

    int rowCount = model->rowCount();

    while (query.next())
    {
        if(query.value(0).toString() == ui->lineEdit->text() && query.value(1).toString() == ui->password->text())\
        {
            accept();
            break;
        }

        rowCount--;
    }

    if(!rowCount)
        QMessageBox::warning(this, tr("错误"), QString(tr("用户名或密码错误")),QMessageBox::Ok);
    accept();
    return;
}


void Login::on_password_textChanged(const QString &arg1)
{
    ui->sign_in->setEnabled(ui->password->hasAcceptableInput());
    return;
}
