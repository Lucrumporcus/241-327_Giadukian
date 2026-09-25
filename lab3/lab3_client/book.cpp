#include "book.h"

Book Book::fromJson(const QJsonObject &obj)
{
    Book b;
    b.id          = obj.value("id").toInt();
    b.title       = obj.value("title").toString();
    b.author      = obj.value("author").toString();
    b.year        = obj.value("year").toInt();
    b.price       = obj.value("price").toDouble();
    b.isAvailable = obj.value("is_available").toBool();
    b.description = obj.value("description").toString();
    return b;
}

QJsonObject Book::toJson() const
{
    QJsonObject obj;
    if (id >= 0) obj["id"] = id;
    obj["title"]        = title;
    obj["author"]       = author;
    obj["year"]         = year;
    obj["price"]        = price;
    obj["is_available"] = isAvailable;
    obj["description"]  = description;
    return obj;
}