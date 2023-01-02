#include "databasehandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

Databasehandler::Databasehandler(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager( this );

    //m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://firestore.googleapis.com/v1/projects/intcognito-advertising/databases/(default)/documents/people/data")));
    //connect(m_networkReply, &QNetworkReply::readyRead, this, &Databasehandler::networkReplyReadyRead);

    QVariantMap newpeople;
    newpeople[ "Gender" ] = "Male";
    newpeople[ "Age" ] = "23";
    //newpeople[ "Time" ] = "January 3, 2023 at 6:00:00 PM UTC+8";
    QJsonDocument jsonDoc = QJsonDocument::fromVariant( newpeople );


    QNetworkRequest newpeopleRequest( QUrl("https://firestore.googleapis.com/v1/projects/intcognito-advertising/databases/(default)/documents/people/data.json"));
    newpeopleRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkManager->post( newpeopleRequest, jsonDoc.toJson() );
}

Databasehandler::~Databasehandler()
{
    m_networkManager->deleteLater();
}

void Databasehandler::networkReplyReadyRead()
{
    qDebug() <<m_networkReply->readAll();
}
