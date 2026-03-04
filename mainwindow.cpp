#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include <QPushButton>
#include "sqlstore.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();//konekcija na psql

    tableView = new QTableView(this);
    tableView->setModel(m_model);

    m_model = new QSqlQueryModel(this);
    m_model->setQuery(SqlStore::Support::get("PODATOCITE_OD_BAZATA"));
    tableView->setModel(m_model);
    tableView->resizeColumnsToContents();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSortingEnabled(true);
    tableView->setFrameStyle(1);


    if (m_model->lastError().isValid()) {
        qDebug()<<"Greska vo SQL"<< m_model->lastError().text();
    }




    idSpinBox = new QSpinBox(this);
    titleLineEdit = new QLineEdit(this);
    authorLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    yearSpinBox = new QSpinBox(this);
    copiesSpinBox = new QSpinBox(this);


    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);    //"podot" na noviot prozorec



    layout = new QVBoxLayout(centralWidget);//vertikalniot layout
    layout->addWidget(tableView);// DODAVANJE NA LAYOUTOT

    submitButton = new QPushButton("Submit ",this);//SUBMIT BUTTON + HANDLE SUBMIT DOLE
    cancelButton = new QPushButton("cancel", this);//CANCEL BUTTON + HANDLE CANCEL DOLE

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
    m_model = new QSqlQueryModel(this);
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
void MainWindow::handleCancel(){
    this->close();
}


