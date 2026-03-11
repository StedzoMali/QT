#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QString>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:



};
#endif // MAINWINDOW_H
