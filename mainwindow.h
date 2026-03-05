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

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void handleSubmit();// SUBMIT BUTTON VO SOURCE
    void handleCancel();// CANCEL BUTTON VO SOURCE

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QVBoxLayout *layout;
    QWidget *centralWidget;
    QPushButton *myButton1;
    QPushButton *myButton2;
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



};
#endif // MAINWINDOW_H
