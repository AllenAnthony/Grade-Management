#include "insert.h"
#include "ui_insert.h"
#include <QDebug>
#include <stdio.h>

using namespace std;
insert::insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insert)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    connect(ui->ins_ret,SIGNAL(clicked(bool)),this,SLOT(accept()));

}

insert::~insert()
{
    delete ui;
}

void insert::setpage(unsigned int N)
{
    ui->tab_ins->setCurrentIndex(N);
    return;
}



void insert::on_ins_p2_ins_clicked()
{

    QString id = ui->lineEdit_10->text();
    QString gredit = ui->lineEdit_8->text();
    QString name = ui->lineEdit_9->text();
    QString grade = ui->lineEdit_3->text();
    int type = ui->comboBox_2->currentIndex();
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

    if(id == NULL || gredit == NULL || name == NULL || grade == NULL)
    {
        QMessageBox::warning(this,"input error",tr("there are empty line"));
        return ;
    }
    QString search="";
    search += QString("id = '%1'").arg(id);

    this->model->setFilter(search);
    model->select();

    int row = model->rowCount();
    if(row == 0)
    {
        QMessageBox::warning(this,"input error",tr("id not exist"));
        return ;
    }

    if(type==0)
    {
        model->setTable("u_course");
        if(!ins.exec(QStringLiteral("insert into u_course values('%1', '%2', '%3', '%4')").arg(id).arg(name).arg(gredit).arg(grade)))
        {
            QMessageBox::warning(this,"input error",tr("grade already exists"));
            return ;
        }
    }
    else if(type==1)
    {
        model->setTable("p_course");
        if(!ins.exec(QStringLiteral("insert into p_course values('%1', '%2', '%3', '%4')").arg(id).arg(name).arg(gredit).arg(grade)))
        {
            QMessageBox::warning(this,"input error",tr("grade already exists"));
            return ;
        }
    }
    else if(type==2)
    {
        model->setTable("PhD_course");
        if(!ins.exec(QStringLiteral("insert into PhD_course values('%1', '%2', '%3', '%4')").arg(id).arg(name).arg(gredit).arg(grade)))
        {
            QMessageBox::warning(this,"input error",tr("grade already exists"));
            return ;
        }
    }

    this->model->setFilter(QString("student_id = '%1'").arg(id));
    model->select();
    row = model->rowCount();
    if(row == 0)
    {
        QMessageBox::warning(this,"input error",tr("id not exist"));
        return ;
    }
    float *a;
    float *b;
    float sum = 0;
    float result = 0;
    a= (float *)malloc(sizeof(float)*(row));
    b= (float *)malloc(sizeof(float)*(row));
    memset(a,0,sizeof(float)*row);
    memset(b,0,sizeof(float)*row);

    for(int i = 0; i < row; i ++)
    {
        a[i] = model->record(i).value("grade").toFloat();
        b[i] = model->record(i).value("gredit").toFloat();
        sum += b[i];
    }

    if(type == 0)
    {
        result = u_compGPA(a, b, row);
        ins.exec(QStringLiteral("update undergraduate set gpa = '%1' where id = '%2'").arg(result).arg(id));
        ins.exec(QStringLiteral("update undergraduate set gredit = '%1' where id = '%2'").arg(sum).arg(id));
    }
    else if(type == 1)
    {
        result = p_compGPA(a, b, row);
        ins.exec(QStringLiteral("update postgraguate set gpa = '%1' where id = '%2'").arg(result).arg(id));
        ins.exec(QStringLiteral("update postgraguate set gredit = '%1' where id = '%2'").arg(sum).arg(id));
    }
    else if(type == 2)
    {
        result = Phd_compGPA(a, b, row);
        ins.exec(QStringLiteral("update PhD set gpa = '%1' where id = '%2'").arg(result).arg(id));
        ins.exec(QStringLiteral("update PhD set gredit = '%1' where id = '%2'").arg(sum).arg(id));
    }
    QMessageBox::about(this,"imformation",tr("Insert success"));
}

void insert::on_ins_p2_clear_clicked()
{
    ui->lineEdit_10->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_3->clear();
}

void insert::on_ins_p1_ins_clicked()
{
    QString id = ui->lineEdit_2->text();
    QString name = ui->lineEdit->text();
    QString major = ui->lineEdit_6->text();

    QString sex = "";
    int type = ui->comboBox->currentIndex();
    if(type == 1 || type == 2)
    {
        ui->lineEdit_7->setEnabled(true);
    }
    QString instructor = ui->lineEdit_7->text();
    if(ui->radioButton->isChecked())
        sex = "male";
    else if(ui->radioButton_2->isChecked())
        sex = "female";
    if(id == NULL || name == NULL || major == NULL ||sex == NULL)
    {
            QMessageBox::warning(this,"input error",tr("there are empty line"));
            return ;

    }

    if(type == 1 || type == 2)
    {
        if( instructor == NULL)
        {
            QMessageBox::warning(this,"input error",tr("there are empty line"));
            return ;
        }
    }
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
    this->model->setFilter(QString("id = '%1'").arg(id));
    model->select();
    int row = model->rowCount();
    if(row != 0)
    {
        QMessageBox::warning(this,"input error",tr("id has existed!"));
        return ;
    }
    if(type == 0)
    {
        ins.exec(QStringLiteral("insert into undergraduate values('%1', '%2', '%3', '%4', '%5', 0, 0)").arg(id).arg(id).arg(name).arg(sex).arg(major));

    }
    else if(type == 1)
        ins.exec(QStringLiteral("insert into postgraguate values('%1', '%2', '%3', '%4', '%5', 0, 0, '%6')").arg(id).arg(id).arg(name).arg(sex).arg(major).arg(instructor));
    else if(type == 2)
        ins.exec(QStringLiteral("insert into PhD values('%1', '%2', '%3', '%4', '%5', 0, 0, '%6')").arg(id).arg(id).arg(name).arg(sex).arg(major).arg(instructor));
    QMessageBox::about(this,"imformation",tr("Insert success"));
}

void insert::on_ins_p1_clear_clicked()
{
    ui->lineEdit_2->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit->clear();
    ui->lineEdit_7->clear();
}
