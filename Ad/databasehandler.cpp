#include "databasehandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

Databasehandler::Databasehandler(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager( this );
}

Databasehandler::~Databasehandler()
{
    m_networkManager->deleteLater();
}

void Databasehandler::networkReplyReadyRead()
{
    qDebug() << "Ready read";
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

    qDebug("Test write done");
}

void Databasehandler::getChartData() {
    qDebug("Get chart data");

    QJsonObject query, from, collectionId;

    collectionId.insert("collectionId", "people");
    from.insert("from", collectionId);
    query.insert("structuredQuery", from);

    QJsonDocument jsonDoc(query);
    qDebug(jsonDoc.toJson());

    QNetworkRequest newpeopleRequest( QUrl("https://firestore.googleapis.com/v1beta1/projects/intcognito-advertising/databases/(default)/documents:runQuery"));
    newpeopleRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkReply = m_networkManager->post( newpeopleRequest, jsonDoc.toJson() );
    connect(m_networkReply, &QNetworkReply::readyRead, this, &Databasehandler::networkReplyReadyRead);

    qDebug() << m_networkReply->isFinished();
    qDebug("Test write done");
}
