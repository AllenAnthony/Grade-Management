#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QDialog>
#include"delete.h"
#include"insert.h"
#include"login.h"
#include <QSqlError>
#pragma execution_character_set("UTF-8")
#include <QTableView>
#include <QMessageBox>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void del_show0();
    void del_show1();
    void ins_show0();
    void ins_show1();
    void login_show();

    void on_query_p1_clear_clicked();

    void on_query_p1_search_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_query_p2_search_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_query_p3_search_clicked();

    void on_query_p3_clear_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlTableModel *model_1;
    QSqlQueryModel *model_2;
};

#endif // MAINWINDOW_H
