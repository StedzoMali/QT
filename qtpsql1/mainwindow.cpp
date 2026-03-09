#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include <QPushButton>
#include "sqlstore.h"
#include "dbmanager.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//konekcijata otide vo dbmanager hehe(:
dbmanager::connect("localhost", 5432, "localdb", "postgres", "1234");
    m_model = new QSqlQueryModel(this);
    tableView = new QTableView(this);
    tableView->setModel(m_model);

    m_model->setQuery(SqlStore::Support::get("PODATOCITE_OD_TABELATA"));
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



    queryButton = new QPushButton("New Books",this);
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
    layout->addWidget(queryButton);

    connect(queryButton, &QPushButton::clicked,this,&MainWindow::handleQuery);
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::handleSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::close);
    titleLineEdit->setPlaceholderText("Book Title");
    authorLineEdit->setPlaceholderText("Author Name");
    genreLineEdit->setPlaceholderText("Genre");
}

MainWindow::~MainWindow()
{
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
        m_model->setQuery(SqlStore::Support::get("PODATOCITE_OD_TABELATA"));
        qDebug() << "vnesuvanjeto e uspeshno ";
    }
}
void MainWindow::handleQuery(){
    m_model->setQuery(SqlStore::Support::get("GET_ALL_BOOKS_BY_PUBLISHED_YEAR"));
}
