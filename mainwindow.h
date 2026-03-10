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
    void handleSubmit();// SUBMIT BUTTON VO SOURCE
    void handleQuery();// ZA SITE KNIGI POMLADI OD 2000 GOD

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSqlQueryModel *m_model;
    QSpinBox  *idSpinBox;//need for function
    QLineEdit *titleLineEdit;//need for function
    QLineEdit *authorLineEdit;//need for function
    QLineEdit *genreLineEdit;//need for function
    QSpinBox  *yearSpinBox;//need for function
    QSpinBox  *copiesSpinBox;//need for function



};
#endif // MAINWINDOW_H
