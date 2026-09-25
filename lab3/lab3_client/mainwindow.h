#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onList();
    void onGet();
    void onCreate();
    void onUpdate();
    void onDelete();

    void onListReceived(QVector<Book> books);
    void onBookReceived(Book b);
    void onOperationFinished(QString msg);
    void onError(QString err);

private:
    Ui::MainWindow *ui;
    Book collectBookFromForm() const;
};

#endif