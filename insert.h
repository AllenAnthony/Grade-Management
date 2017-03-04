#pragma once
#ifndef INSERT_H
#define INSERT_H
#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif
#include <QDialog>
#include "connection.h"
#include <QWidget>
#include <QDialog>

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>

#include <QTableView>
#include <QMessageBox>
namespace Ui {
class insert;
}

class insert : public QDialog
{
    Q_OBJECT

public:
    explicit insert(QWidget *parent = 0);
    ~insert();
    void setpage(unsigned int N);

private slots:


    void on_ins_p2_ins_clicked();

    void on_ins_p2_clear_clicked();

    void on_ins_p1_ins_clicked();

    void on_ins_p1_clear_clicked();

private:
    Ui::insert *ui;
    QSqlTableModel *model;
    QSqlQuery ins;
};

#endif // INSERT_H
