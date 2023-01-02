#include "databasehandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>
#include <QDateTime>

Databasehandler::Databasehandler(QObject *parent)
    : QObject(parent)
{
    qInfo("Dito simula");
    m_networkManager = new QNetworkAccessManager( this );

//    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://firestore.googleapis.com/v1/projects/intcognito-advertising/databases/(default)/documents/people/data")));
//    connect(m_networkReply, &QNetworkReply::readyRead, this, &Databasehandler::networkReplyReadyRead);
//    qInfo("Dito pagtapos");

}

Databasehandler::~Databasehandler()
{
    m_networkManager->deleteLater();
}

void Databasehandler::networkReplyReadyRead()
{
    qDebug() << m_networkReply->readAll();
}

void Databasehandler::testWrite() {
    qDebug("Test write");

    QVariantMap document, genderField, ageField, timeField, testPerson;
    genderField["stringValue"] = "Male";
    ageField["stringValue"] = "0-24 yrs old";
    timeField["timestampValue"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    testPerson["Age"] = ageField;
    testPerson["Gender"] = genderField;
    testPerson["Time"] = timeField;
    document["fields"] = testPerson;

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(document);
    qDebug(jsonDoc.toJson());

    QNetworkRequest newpeopleRequest( QUrl("https://firestore.googleapis.com/v1beta1/projects/intcognito-advertising/databases/(default)/documents/people/"));
    newpeopleRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkReply = m_networkManager->post( newpeopleRequest, jsonDoc.toJson() );
    connect(m_networkReply, &QNetworkReply::readyRead, this, &Databasehandler::networkReplyReadyRead);

    qDebug() << m_networkReply->readAll();
    qDebug("Test write done");
}
