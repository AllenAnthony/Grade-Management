#pragma once
#ifndef CONNECTION_H
#define CONNECTION_H

#pragma execution_character_set("UTF-8")


#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include "compute.h"

extern int UserLogin;

static bool createConnection(){
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");

    DB.setHostName("localhost");
    DB.setDatabaseName("DB.db");

    if(!DB.open())
    {
        return false;
    }

    QSqlQuery Administator;
    QSqlQuery undergraduate;
    QSqlQuery postgraguate;
    QSqlQuery PhD;
    QSqlQuery u_course;
    QSqlQuery p_course;
    QSqlQuery PhD_course;

    Administator.exec(QStringLiteral("create table Administator(ad_id varchar(20) primary key,ad_pw varchar(20),name varchar(20))"));
    undergraduate.exec(QStringLiteral("create table undergraduate(id varchar(20) primary key,pw varchar(20),name varchar(20),sex varchar(20),major varchar(20),gredit float,gpa float)"));
    postgraguate.exec(QObject::tr("create table postgraguate(id varchar(20) primary key,pw varchar(20),name varchar(20),sex varchar(20),major varchar(20),gredit float,gpa float,instructor varchar(20))"));
    PhD.exec(QStringLiteral("create table PhD(id varchar(20) primary key,pw varchar(20),name varchar(20),sex varchar(20),major varchar(20),gredit float, gpa float,instructor varchar(20))"));

    u_course.exec(QStringLiteral("create table u_course(student_id varchr(20),name varchar(20),gredit float,grade float, constraint pk_t2 primary key (student_id,name))"));
    p_course.exec(QStringLiteral("create table p_course(student_id varchr(20),name varchar(20),gredit float,grade float, constraint pk_t2 primary key (student_id,name))"));
    PhD_course.exec(QStringLiteral("create table PhD_course(student_id varchr(20),name varchar(20),gredit float,grade float, constraint pk_t2 primary key (student_id,name))"));

    undergraduate.exec(QStringLiteral("insert into undergraduate values(9, '那', '11',  '1', 'aa', 1, 1)"));
    undergraduate.exec(QStringLiteral("insert into undergraduate values('12', '女', '12',  '2', 'aa', 1.1, 1.2)"));
    undergraduate.exec(QStringLiteral("insert into undergraduate values('3', 'admin', '13',  '1', 'aa', 1.1, 1.2)"));
    undergraduate.exec(QStringLiteral("insert into undergraduate values('4', 'admin', '14',  '2', 'aa', 1.1, 1.2)"));
    undergraduate.exec(QStringLiteral("insert into undergraduate values('5', 'admin', '15',  '1', 'aa', 1.1, 1.2)"));
    u_course.exec(QStringLiteral("insert into u_course values('3', 'math', 2.5, 99.5)"));
    u_course.exec(QStringLiteral("insert into u_course values('4', '微积分', 2.5, 90.5)"));
    return true;
}



#endif // CONNECTION_H
