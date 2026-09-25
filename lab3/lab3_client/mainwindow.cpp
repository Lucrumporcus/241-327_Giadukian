#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnList,   &QPushButton::clicked, this, &MainWindow::onList);
    connect(ui->btnGet,    &QPushButton::clicked, this, &MainWindow::onGet);
    connect(ui->btnCreate, &QPushButton::clicked, this, &MainWindow::onCreate);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdate);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::onDelete);

    auto &api = ApiClient::instance();
    connect(&api, &ApiClient::listReceived,       this, &MainWindow::onListReceived);
    connect(&api, &ApiClient::bookReceived,       this, &MainWindow::onBookReceived);
    connect(&api, &ApiClient::operationFinished,  this, &MainWindow::onOperationFinished);
    connect(&api, &ApiClient::errorOccurred,      this, &MainWindow::onError);
}

MainWindow::~MainWindow() { delete ui; }

Book MainWindow::collectBookFromForm() const
{
    Book b;
    b.title       = ui->editTitle->text();
    b.author      = ui->editAuthor->text();
    b.year        = ui->editYear->text().toInt();
    b.price       = ui->editPrice->text().toDouble();
    b.isAvailable = true;
    return b;
}

void MainWindow::onList()   { ApiClient::instance().listBooks(); }
void MainWindow::onGet()    { ApiClient::instance().retrieveBook(ui->editId->text().toInt()); }
void MainWindow::onCreate() { ApiClient::instance().createBook(collectBookFromForm()); }
void MainWindow::onUpdate() { ApiClient::instance().updateBook(ui->editId->text().toInt(), collectBookFromForm()); }
void MainWindow::onDelete() { ApiClient::instance().deleteBook(ui->editId->text().toInt()); }

void MainWindow::onListReceived(QVector<Book> books)
{
    QString out;
    for (const auto &b : books) {
        out += QString("ID=%1 | %2 | %3 | %4\n")
        .arg(b.id).arg(b.title, b.author).arg(b.year);
    }
    ui->textOutput->setPlainText(out);
}

void MainWindow::onBookReceived(Book b)
{
    ui->textOutput->setPlainText(
        QString("ID: %1\nTitle: %2\nAuthor: %3\nYear: %4\nPrice: %5\nAvailable: %6")
            .arg(b.id).arg(b.title, b.author).arg(b.year).arg(b.price).arg(b.isAvailable));
}

void MainWindow::onOperationFinished(QString msg)
{
    ui->textOutput->append("OK: " + msg);
}

void MainWindow::onError(QString err)
{
    ui->textOutput->append("ERROR: " + err);
}
