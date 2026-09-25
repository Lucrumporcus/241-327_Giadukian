#include "apiclient.h"

ApiClient& ApiClient::instance()
{
    static ApiClient s;
    return s;
}

ApiClient::ApiClient(QObject *parent) : QObject(parent) {}

void ApiClient::listBooks()
{
    auto *reply = m_manager.get(QNetworkRequest(QUrl(m_baseUrl)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply, true);
    });
}

void ApiClient::retrieveBook(int id)
{
    QUrl url(m_baseUrl + QString::number(id) + "/");
    auto *reply = m_manager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply, false);
    });
}

void ApiClient::createBook(const Book &b)
{
    QNetworkRequest req{QUrl(m_baseUrl)};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto *reply = m_manager.post(req, QJsonDocument(b.toJson()).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply, false);
    });
}

void ApiClient::updateBook(int id, const Book &b)
{
    QUrl url(m_baseUrl + QString::number(id) + "/");
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto *reply = m_manager.put(req, QJsonDocument(b.toJson()).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply, false);
    });
}

void ApiClient::deleteBook(int id)
{
    QUrl url(m_baseUrl + QString::number(id) + "/");
    auto *reply = m_manager.deleteResource(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply, false);
    });
}

void ApiClient::handleReply(QNetworkReply *reply, bool isList)
{
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        return;
    }

    const auto data = reply->readAll();
    const auto doc  = QJsonDocument::fromJson(data);

    if (isList && doc.isArray()) {
        QVector<Book> books;
        for (const auto &v : doc.array())
            books.append(Book::fromJson(v.toObject()));
        emit listReceived(books);
    } else if (doc.isObject()) {
        emit bookReceived(Book::fromJson(doc.object()));
    } else {
        emit operationFinished("OK");
    }
}