#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLineSeries *series = new QLineSeries();

    //mock data
    series->append(0,6);
    series->append(2,4);
    series->append(3,8);
    series->append(7,4);
    series->append(10,5);

    *series << QPointF(11,1) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);

    QChart *chart = new QChart();
    //chart->legend()->hide();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
    qDebug() << answer;
}

void MainWindow::uploadAd(
    QString adName,
    QList<QString> ageGroups,
    QList<QString> genders,
    QString imageUrl
) {
    QVariantMap document, imageField, timeField, nameField, fieldsKey;
    QJsonObject agesArrayValue, gendersArrayValue;
    QJsonObject arrayValueValues;

//    "arrayValue": {
//	    "values": [
//		{
//		    "stringValue": "0-24 yrs old"
//		},
//		{
//		    "stringValue": "25-49 yrs old"
//		}
//	    ]
//	}

    QJsonArray agesStringValues;
    for (int i = 0; i < ageGroups.size(); ++i) {
        QJsonObject tempObj;
        tempObj.insert("stringValue", ageGroups[i]);
        agesStringValues.append(tempObj);
    }
    arrayValueValues.insert("values", agesStringValues);
    agesArrayValue.insert("arrayValue", arrayValueValues);

    QJsonArray gendersStringValues;
    for (int i = 0; i < genders.size(); ++i) {
        QJsonObject tempObj;
        tempObj.insert("stringValue", genders[i]);
        gendersStringValues.append(tempObj);
    }
    arrayValueValues.insert("values", gendersStringValues);
    gendersArrayValue.insert("arrayValue", arrayValueValues);

    nameField["stringValue"] = adName;
    imageField["stringValue"] = imageUrl;
    timeField["timestampValue"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

    fieldsKey["name"] = nameField;
    fieldsKey["age"] = agesArrayValue.toVariantMap();
    fieldsKey["genders"] = gendersArrayValue.toVariantMap();
    fieldsKey["image"] = imageField;
    fieldsKey["time"] = timeField;
    document["fields"] = fieldsKey;

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(document);
    qDebug(jsonDoc.toJson());

    QNetworkRequest createAdRequest( QUrl("https://firestore.googleapis.com/v1beta1/projects/intcognito-advertising/databases/(default)/documents/ads/"));
    createAdRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString("application/json"));
//    QNetworkReply m_networkReply = m_networkManager->post( createAdRequest, jsonDoc.toJson() );
//    connect(m_networkReply, &QNetworkReply::readyRead, this, &Databasehandler::networkReplyReadyRead);

    manager->post(createAdRequest, jsonDoc.toJson());
    qDebug("Ad upload done");
}


void MainWindow::on_pushButton_clicked()
{
    QList<QString> possibleAgeGroups = {
        "0-24 yrs old",
        "25-49 yrs old",
        "50-74 yrs old",
        "75-99 yrs old",
        "100-124 yrs old"
    };

    QList<QString> possibleGenders = {
        "male",
        "female"
    };

    // For Add Advertisement form
    QList<QCheckBox *> ageButtonList;
    ageButtonList.append(ui->r_0_24);
    ageButtonList.append(ui->r_25_49);
    ageButtonList.append(ui->r_50_74);
    QList<QString> checkedAges;
    for (int i = 0; i < ageButtonList.size(); ++i) {
        if (ageButtonList[i]->isChecked()) {
            checkedAges.append(possibleAgeGroups[i]);
        }
    }

    QList<QCheckBox *> genderButtonList;
    genderButtonList.append(ui->r_male);
    genderButtonList.append(ui->r_female);
    QList<QString> checkedGenders;
    for (int i = 0; i < genderButtonList .size(); ++i) {
        if (genderButtonList[i]->isChecked()) {
            checkedGenders.append(possibleGenders[i]);
        }
    }

    qDebug("Age groups:\n");
    qDebug() << checkedAges;

    qDebug("Genders:\n");
    qDebug() << checkedGenders;

    QString adName = ui->adNameEdit->displayText();
    QString imageUrl = ui->urlEdit->displayText();

    uploadAd(adName, checkedAges, checkedGenders, imageUrl);
}

