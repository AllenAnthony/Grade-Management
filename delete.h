#pragma once
#ifndef DELETE_H
#define DELETE_H
#pragma execution_character_set("utf-8")


#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QSqlRecord>
#include <vector>
#include"connection.h"
namespace Ui {
class Delete;
}

class Delete : public QDialog
{
    Q_OBJECT

public:
    explicit Delete(QWidget *parent = 0);
    ~Delete();
    void updateGPA(QString id,QString TN);

    void setpage(unsigned int N);

private slots:
    void on_del_p1_search_clicked();
    void on_del_p1_del_clicked();
    void on_del_p1_cel_clicked();
    void on_del_p2_del_2_clicked();
    void on_del_p2_search_clicked();
    void on_del_p2_cel_clicked();


private:
    Ui::Delete *ui;
    QSqlTableModel *model;
    QSqlTableModel *model_course;
    std::vector<QSqlRecord> record;
    std::vector<int> row;
    std::vector<QString> del_id;
    std::vector<QString> tablename;

    std::vector<QSqlRecord> record_sub;
    std::vector<int> row_sub;
    std::vector<QString> tablename_sub;
    std::vector<QString> del_id_sub;
//    QSqlTableModel *model_postgraguate;
//    QSqlTableModel *model_undergraduate;
//    QSqlTableModel *model_PhD;
//    QSqlTableModel *model_course;
};

#endif
