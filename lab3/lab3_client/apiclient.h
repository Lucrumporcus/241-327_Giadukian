#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include "book.h"

class ApiClient : public QObject {
    Q_OBJECT
public:
    static ApiClient& instance();

    ApiClient(const ApiClient&) = delete;
    ApiClient& operator=(const ApiClient&) = delete;

    void listBooks();
    void retrieveBook(int id);
    void createBook(const Book &b);
    void updateBook(int id, const Book &b);
    void deleteBook(int id);

signals:
    void listReceived(QVector<Book> books);
    void bookReceived(Book book);
    void operationFinished(QString message);
    void errorOccurred(QString error);

private:
    explicit ApiClient(QObject *parent = nullptr);
    QNetworkAccessManager m_manager;
    QString m_baseUrl = "http://localhost/api/book/";

    void handleReply(QNetworkReply *reply, bool isList);
};

#endif // APICLIENT_H