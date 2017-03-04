#include "delete.h"
#include "ui_delete.h"
#include <Qstring>
Delete::Delete(QWidget *parent) :QDialog(parent),ui(new Ui::Delete)
{
    ui->setupUi(this);
    this->model = new QSqlTableModel(this);
    this->model_course=new QSqlTableModel(this);

    //this->model_undergraduate->setTable("undergraduate");
    //this->model_postgraguate->setTable("postgraguate");
    //this->model_PhD->setTable("PhD");

    this->model->setEditStrategy(QSqlTableModel::OnFieldChange);
    this->model_course->setEditStrategy(QSqlTableModel::OnFieldChange);
//    this->model_PhD->setEditStrategy(QSqlTableModel::OnFieldChange);
//    this->model_postgraguate->setEditStrategy(QSqlTableModel::OnFieldChange);
//    this->model_undergraduate->setEditStrategy(QSqlTableModel::OnFieldChange);
    connect(ui->del_ret,SIGNAL(clicked(bool)),this,SLOT(accept()));



    //model1->setTable("BOOK");
    //model1->select();
    ui->tableView_del1->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView_del2->setEditTriggers(QTableView::NoEditTriggers);

    ui->tableView_del1->setModel(model);
    ui->tableView_del2->setModel(model_course);
    for(int cou=0;cou<9;cou++)
    {
        ui->tableView_del1->setColumnWidth(cou,50);
    }

    for(int cou=0;cou<4;cou++)
    {
        ui->tableView_del2->setColumnWidth(cou,100);
    }

    record.clear();
    row.clear();
    record_sub.clear();
    row_sub.clear();
    QSqlQuery undergraduate;
    undergraduate.exec(QStringLiteral("insert into undergraduate values(20, '傻逼', '傻叉',  '1', 'aa', 1, 1)"));
}

Delete::~Delete()
{
    QString query;
    QSqlQuery Q0;
    //std::string str;
    while(!tablename.empty())
    {
        QString ID=del_id.back();
        if(tablename.back()=="undergraduate")
            query=QString("delete from u_course where student_id = %1").arg(ID);
        else if(tablename.back()=="postgraguate")
            query=QString("delete from p_course where student_id = %1").arg(ID);
        else if(tablename.back()=="PhD")
            query=QString("delete from PhD_course where student_id = %1").arg(ID);

        del_id.pop_back();
        tablename.pop_back();
        //str=query.toStdString();
        Q0.exec(query);
    }

    delete ui;
}


void Delete::setpage(unsigned int N)
{
    ui->tab_del->setCurrentIndex(N);
    return;



}

void Delete::on_del_p1_search_clicked()
{
    QString id = ui->lineEdit_1->text();
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

    if(ui->check_id->isChecked())
        search+=QString("id = '%1'").arg(id);
    if(ui->check_name->isChecked())
        search+=QString("and name = '%1'").arg(name);
    if(ui->check_pro->isChecked())
        search+=QString("and major = '%1'").arg(major);

    this->model->setFilter(search);
    this->model->select();
}

void Delete::on_del_p1_del_clicked()
{
    int curRow = ui->tableView_del1->currentIndex().row();
    QString ID=model->record(curRow).value(0).toString();
    del_id.push_back(ID);
    row.push_back(curRow);
    record.push_back(model->record(curRow));
    tablename.push_back(model->tableName());


    if(model->removeRow(curRow))
        QMessageBox::warning(this, tr("删除书籍"), QString(tr("删除成功")),QMessageBox::Ok);
    else
        QMessageBox::warning(this, tr("删除书籍"), QString(tr("删除失败")),QMessageBox::Ok);

    model->select();
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) // 提交所有被修改的数据到数据库中
    {
       model->database().commit(); //提交成功，事务将真正修改数据库数据
    } else
    {
       model->database().rollback(); //提交失败，事务回滚
       QMessageBox::warning(this, tr("tableModel"),QString(tr("数据库错误")),QMessageBox::Ok);
    }
    return;

}

void Delete::on_del_p1_cel_clicked()
{
    if(record.empty())
    {
        QMessageBox::warning(this, tr("撤销失败"), QString(tr("都撤销完咯~")),QMessageBox::Ok);
        return;
    }
    QSqlRecord backrecord=record.back();
    record.pop_back();
    int backrow=row.back();
    row.pop_back();

    del_id.pop_back();
    model->setTable(tablename.back());
    tablename.pop_back();
    model->insertRecord(backrow,backrecord);

    model->select();
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) // 提交所有被修改的数据到数据库中
    {
       model->database().commit(); //提交成功，事务将真正修改数据库数据
    } else
    {
       model->database().rollback(); //提交失败，事务回滚
       QMessageBox::warning(this, tr("tableModel"),QString(tr("数据库错误: %1")),QMessageBox::Ok);
    }
    return;


}

void Delete::on_del_p2_search_clicked()
{
    QString id = ui->lineEdit_id2->text();
    QString sub=ui->lineEdit_sub->text();

    int type = ui->comboBox_2->currentIndex();


    if(type==0)
    {
        this->model_course->setTable("u_course");
    }
    else if(type==1)
    {
        this->model_course->setTable("p_course");
    }
    else if(type==2)
    {
        this->model_course->setTable("PhD_course");
    }
    else
    {
        QMessageBox::warning(this,"type error",tr("no such type"));
        return ;
    }


    QString search="";

    search+=QString("student_id = '%1'").arg(id);
    if(ui->check_sub->isChecked())
        search+=QString("and name = '%1'").arg(sub);

    this->model_course->setFilter(search);

    if(!this->model_course->select())
        QMessageBox::warning(this, tr("搜索成绩"), QString(tr("搜索失败")),QMessageBox::Ok);
}

void Delete::on_del_p2_del_2_clicked()
{
    QString ID;
    int curRow = ui->tableView_del2->currentIndex().row();

    ID=model_course->record(curRow).value(0).toString();
    row_sub.push_back(curRow);
    record_sub.push_back(model_course->record(curRow));
    tablename_sub.push_back(model_course->tableName());
    del_id_sub.push_back(ID);

    if(model_course->removeRow(curRow))
        QMessageBox::warning(this, tr("删除成绩"), QString(tr("删除成功")),QMessageBox::Ok);
    else
        QMessageBox::warning(this, tr("删除成绩"), QString(tr("删除失败")),QMessageBox::Ok);




    model_course->select();
    model_course->database().transaction(); //开始事务操作
    if (model_course->submitAll()) // 提交所有被修改的数据到数据库中
    {
        model_course->database().commit(); //提交成功，事务将真正修改数据库数据
    } else {
        model_course->database().rollback(); //提交失败，事务回滚
    }
    updateGPA(ID,model_course->tableName());
    model_course->select();
    return;

}

void Delete::on_del_p2_cel_clicked()
{
    if(record_sub.empty())
    {
        QMessageBox::warning(this, tr("撤销失败"), QString(tr("都撤销完咯~")),QMessageBox::Ok);
        return;
    }
    QSqlRecord backrecord=record_sub.back();
    record_sub.pop_back();
    int backrow=row_sub.back();
    row_sub.pop_back();
    QString TN=tablename_sub.back();
    tablename_sub.pop_back();
    QString ID=del_id_sub.back();
    del_id_sub.pop_back();
    model_course->setTable(TN);
    model_course->insertRecord(backrow,backrecord);

    model_course->select();
    model_course->database().transaction(); //开始事务操作
    if (model_course->submitAll()) // 提交所有被修改的数据到数据库中
    {
        model_course->database().commit(); //提交成功，事务将真正修改数据库数据
    } else {
        model_course->database().rollback(); //提交失败，事务回滚
    }
    updateGPA(ID,TN);
    model_course->select();
    return;


}

void Delete::updateGPA(QString id,QString TN)
{
    int type;
    if(TN=="undergraduate" || TN=="u_course")
        type=0;
    else if(TN=="postgraguate" || TN=="p_course")
        type=1;
    else if(TN=="PhD" || TN=="PhD_course")
        type=2;
    QString name=model_course->tableName();
    if(type==0)
    {
        model_course->setTable("u_course");
    }
    else if(type==1)
    {
        model_course->setTable("p_course");
    }
    else if(type==2)
    {
        model_course->setTable("PhD_course");
    }
    QString search=QString("student_id = %1").arg(id);
    model_course->setFilter(search);
    model_course->select();
    int row = model_course->rowCount();
    float *a;
    float *b;
    float sum = 0;
    float result = 0;
    a= (float *)malloc(sizeof(float)*(row));
    b= (float *)malloc(sizeof(float)*(row));
    memset(a,0,sizeof(float)*row);
    memset(b,0,sizeof(float)*row);
    QSqlQuery ins;
    for(int i = 0; i < row; i ++)
    {
        a[i] = model_course->record(i).value("grade").toFloat();
        b[i] = model_course->record(i).value("gredit").toFloat();
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
    model_course->setTable(name);

    return;

}
