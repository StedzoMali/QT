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
    QVBoxLayout *layout;
    QWidget *centralWidget;
    QSpinBox  *idSpinBox;
    QLineEdit *titleLineEdit;
    QLineEdit *authorLineEdit;
    QLineEdit *genreLineEdit;
    QSpinBox  *yearSpinBox;
    QSpinBox  *copiesSpinBox;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QTableView *tableView;
    QSqlQueryModel *m_model;
    QPushButton *queryButton;


};
#endif // MAINWINDOW_H
