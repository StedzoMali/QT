#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    idSpinBox = new QSpinBox(this);
    titleLineEdit = new QLineEdit(this);
    authorLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    yearSpinBox = new QSpinBox(this);
    copiesSpinBox = new QSpinBox(this);


    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);    //"podot" na noviot prozorec

    init();//konekcija na psql

    layout = new QVBoxLayout(centralWidget);//vertikalniot layout
    myButton1 = new QPushButton("Submit",this);
    layout->addWidget(myButton1);//kopceto go stava na stack

    myButton2 = new QPushButton("Cancel",this);
    layout->addWidget(myButton2);//2kopce se stava na stack


    connect(myButton1, &QPushButton::clicked,this, &MainWindow::close);

    submitButton = new QPushButton("Submit ",this);
    cancelButton = new QPushButton("cancel", this);

    layout->addWidget(idSpinBox);
    layout->addWidget(titleLineEdit);
    layout->addWidget(authorLineEdit);
    layout->addWidget(genreLineEdit);
    layout->addWidget(yearSpinBox);
    layout->addWidget(copiesSpinBox);
    layout->addWidget(submitButton);
    layout->addWidget(cancelButton);

    connect(submitButton, &QPushButton::clicked, this, &MainWindow::handleSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::close);
    titleLineEdit->setPlaceholderText("Book Title");
    authorLineEdit->setPlaceholderText("Author Name");
    genreLineEdit->setPlaceholderText("Genre");
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("localdb");
    db.setUserName("postgres");
    db.setPassword("1234");

    if (!db.open()) {
        qDebug() << "ERROR, Neuspesna konekcija ";
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Konekcijata e uspeshna";

    }
}
void MainWindow::handleSubmit(){
    QSqlQuery query;

    query.prepare("INSERT INTO books (book_id, title, author, genre, published_year, copies_available) "
     "VALUES (:id, :title, :author, :genre, :year, :copies)");

    query.bindValue(":id", idSpinBox->value());
    query.bindValue(":title", titleLineEdit->text());
    query.bindValue(":author", authorLineEdit->text());
    query.bindValue(":genre", genreLineEdit->text());
    query.bindValue(":year", yearSpinBox->value());
    query.bindValue(":copies", copiesSpinBox->value());

    if (!query.exec()){
        qDebug() << "Vnesuvanjeto e neuspeshno " << query.lastError().text();
    }else {
        qDebug() << "vnesuvanjeto e uspeshno ";
    }
}
