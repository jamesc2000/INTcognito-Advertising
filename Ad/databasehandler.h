#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Databasehandler : public QObject
{
    Q_OBJECT
public:
    explicit Databasehandler(QObject *parent = nullptr);
    ~Databasehandler();

public slots:
    void networkReplyReadyRead();
    void testWrite();
signals:

private:
    QNetworkAccessManager * m_networkManager;
    QNetworkReply * m_networkReply;
};

#endif // DATABASEHANDLER_H
