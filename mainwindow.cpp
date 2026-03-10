#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include <QPushButton>
#include "sqlstore.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    m_model = new QSqlQueryModel(this);
    auto tableView = new QTableView(this);
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



    auto queryButton = new QPushButton("New Books",this);
    idSpinBox = new QSpinBox(this);
    titleLineEdit = new QLineEdit(this);
    authorLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    yearSpinBox = new QSpinBox(this);
    copiesSpinBox = new QSpinBox(this);

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto mainLayout = new QHBoxLayout(centralWidget);
    auto formLayout = new QVBoxLayout();

    mainLayout->addWidget(tableView);
    mainLayout->addLayout(formLayout);
    mainLayout->setStretchFactor(tableView, 2);
    mainLayout->setStretchFactor(formLayout, 1);

    // then add widgets to formLayout below...
    auto submitButton = new QPushButton("Submit ",this);//SUBMIT BUTTON + HANDLE SUBMIT DOLE
    auto cancelButton = new QPushButton("cancel", this);//CANCEL BUTTON + HANDLE CANCEL DOLE

    formLayout->addWidget(idSpinBox);//need for function
    formLayout->addWidget(titleLineEdit);//need for function
    formLayout->addWidget(authorLineEdit);//need for function
    formLayout->addWidget(genreLineEdit);//need for function
    formLayout->addWidget(yearSpinBox);//need for function
    formLayout->addWidget(copiesSpinBox);//need for function
    formLayout->addWidget(submitButton);
    formLayout->addWidget(cancelButton);
    formLayout->addWidget(queryButton);

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
