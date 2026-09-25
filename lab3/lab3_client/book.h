#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QJsonObject>

class Book {
public:
    int id = -1;
    QString title;
    QString author;
    int year = 0;
    double price = 0;
    bool isAvailable = true;
    QString description;

    static Book fromJson(const QJsonObject &obj);
    QJsonObject toJson() const;
};

#endif // BOOK_H