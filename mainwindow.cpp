#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->del1,       SIGNAL(triggered(bool)),this,SLOT(del_show0()));
    connect(ui->del2,       SIGNAL(triggered(bool)),this,SLOT(del_show1()));

    connect(ui->ins1,       SIGNAL(triggered(bool)),this,SLOT(ins_show0()));
    connect(ui->ins2,       SIGNAL(triggered(bool)),this,SLOT(ins_show1()));
    connect(ui->signout,    SIGNAL(triggered(bool)),this,SLOT(login_show()));
    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_1 = new QSqlTableModel(this);
    model_1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_2 = new QSqlQueryModel(this);
    ui->tableView->setModel(model);
    ui->tableView2->setModel(model_1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login_show()
{
    Login LOG(0);
    LOG.exec();
    return;
}

void MainWindow::del_show0()
{
    Delete DEL(0);
    DEL.setpage(0);
    if(DEL.exec()==QDialog::Accepted)
        return;

}

void MainWindow::del_show1()
{
    Delete DEL(0);
    DEL.setpage(1);
    if(DEL.exec()==QDialog::Accepted)
        return;
}

void MainWindow::ins_show0()
{
        insert INS(0);
        INS.setpage(0);
        if(INS.exec()==QDialog::Accepted)
            return;

}

void MainWindow::ins_show1()
{
        insert INS(0);
        INS.setpage(1);
        if(INS.exec()==QDialog::Accepted)
            return;

}



void MainWindow::on_query_p1_clear_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void MainWindow::on_query_p1_search_clicked()
{

    QString id = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    int type = ui->comboBox->currentIndex();
    QString major = ui->lineEdit_3->text();
    if(type==0)
    {
        model->setTable("undergraduate");
    }
    else if(type==1)
    {
        model->setTable("postgraguate");
    }
    else if(type==2)
    {
        model->setTable("PhD");
    }
    else
    {
        QMessageBox::warning(this,"type error",tr("no such type"));
        return ;
    }

    QString search="";

    if(ui->checkBox->isChecked())
        search += QString("id = '%1'").arg(id);
    if(ui->checkBox_2->isChecked())
        search+=QString("and name = '%1'").arg(name);
    if(ui->checkBox_4->isChecked())
        search+=QString("and major = '%1'").arg(major);

    this->model->setFilter(search);
    this->model->select();
}

void MainWindow::on_pushButton_clicked()
{
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) {
        model->database().commit(); //提交
    } else {
        model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    model->revertAll();
}

void MainWindow::on_query_p2_search_clicked()
{

    QString id = ui->lineEdit_4->text();
    int type = ui->comboBox_4->currentIndex();
    if(type==0)
    {
        model_1->setTable("u_course");
    }
    else if(type==1)
    {
        model_1->setTable("p_course");
    }
    else if(type==2)
    {
        model_1->setTable("PhD_course");
    }
    else
    {
        QMessageBox::warning(this,"type error",tr("no such type"));
        return ;
    }
    QString search="";
    search += QString("student_id = '%1'").arg(id);

    this->model_1->setFilter(search);
    this->model_1->select();

}

void MainWindow::on_pushButton_3_clicked()
{
    model_1->database().transaction(); //开始事务操作
    if (model_1->submitAll()) {
        model_1->database().commit(); //提交
    }
    else
    {
        model_1->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_1->lastError().text()));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    model_1->revertAll();
}


void MainWindow::on_query_p3_search_clicked()
{
    int type = ui->comboBox_2->currentIndex();
    int type_1 = ui->comboBox_3->currentIndex();
    QString type_s = ui->comboBox_2->currentText();
    QString site_s = "";
    QString site = ui->lineEdit_5->text();//the number of data
    if(type==0)
    {
        type_s = "u_course";
     //   model_1->setTable("u_course");
    }
    else if(type==1)
    {
        type_s = "p_course";
        model_1->setTable("p_course");
    }
    else if(type==2)
    {
        type_s = "PhD_course";
        model_1->setTable("PhD_course");
    }
    else
    {
        QMessageBox::warning(this,"type error",tr("no such type"));
        return ;
    }
    QString ke;
    if(type_1>=0 && type_1<=5)
    {
        ke = ui->comboBox_3->currentText();
    }
    else
    {
        QMessageBox::warning(this,"subject error",tr("no such subject"));
        return ;
    }

    if(!ui->checkBox_6->isChecked())
    {
        if(site != NULL)
            model_2->setQuery(QString("select * from '%1' where name = '%2' order by grade desc limit '%3'").arg(type_s).arg(ke).arg(site));
        else
            model_2->setQuery(QString("select * from '%1' where name = '%2' order by grade desc").arg(type_s).arg(ke));
        }
   else
   {
        if(site != NULL)
            model_2->setQuery(QString("select * from '%1' where name = '%2' order by grade limit '%3'").arg(type_s).arg(ke).arg(site));
        else
            model_2->setQuery(QString("select * from '%1' where name = '%2' order by grade").arg(type_s).arg(ke));
    }
    ui->tableView3->setModel(model_2);

}

void MainWindow::on_query_p3_clear_clicked()
{
    ui->lineEdit_5->clear();
}
