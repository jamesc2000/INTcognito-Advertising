#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gender1 = new QLineSeries();
    gender2 = new QLineSeries();

    gender1->setName("Female");
    gender2->setName("Male");
    //Mock Data
    //Data for 0-24
    //(timestamp,y axis


//    *gender1 << QPointF(1,2) << QPointF(2,3) << QPointF(3,6) << QPointF(4,3)<< QPointF(5,2);
//    *gender1 << QPointF(10000000, 100) << QPointF(10000000, 100) << QPointF(10000000, 100);
//    *gender2 << QPointF(3,1); /*<< QPointF(axisX,3) << QPointF(axisX,6) << QPointF(axisX,3)<< QPointF(axisX,2);*/

    chart = new QChart();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(gender1);
    chart->addSeries(gender2);
//    chart->createDefaultAxes();

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(5);
    axisX->setFormat("MMM dd | hh ap");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    gender1->attachAxis(axisX);
    gender2->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Number");
    axisY->setTickCount(10);
    axisY->setMax(10);
    axisY->setMin(0);
    chart->addAxis(axisY, Qt::AlignLeft);
    gender1->attachAxis(axisY);
    gender2->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

    //Age Group Chart
    age1 = new QLineSeries();
    age2 = new QLineSeries();
    age3 = new QLineSeries();
    age4 = new QLineSeries();
    age5 = new QLineSeries();
    age1->setName("0-24 yrs old");
    age2->setName("25-49 yrs old");
    age3->setName("50-74 yrs old");
    age4->setName("75-99 yrs old");
    age5->setName("100-124 yrs old");


    //mock data
    *age1 << QPointF(11,11) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);
    *age2 << QPointF(11,12) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);
    *age3 << QPointF(11,13) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);
    *age4 << QPointF(11,14) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);
    *age5 << QPointF(11,10) << QPointF(13,3) << QPointF(17,6) << QPointF(18,3)<< QPointF(20,2);

    chart2 = new QChart();
    chart2->legend()->setVisible(true);
    chart2->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart2->addSeries(age1);
    chart2->addSeries(age2);
    chart2->addSeries(age3);
    chart2->addSeries(age4);
    chart2->addSeries(age5);

    QDateTimeAxis *axisX2 = new QDateTimeAxis;
    axisX2->setTickCount(5);
    axisX2->setFormat("MMM dd | hh ap");
    axisX2->setTitleText("Date");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    age1->attachAxis(axisX2);
    age2->attachAxis(axisX2);
    age3->attachAxis(axisX2);
    age4->attachAxis(axisX2);
    age5->attachAxis(axisX2);

    QValueAxis *axisY2 = new QValueAxis;
    axisY2->setTitleText("Number");
    axisY2->setTickCount(10);
    axisY2->setMax(10);
    axisY2->setMin(0);
    chart2->addAxis(axisY2, Qt::AlignLeft);
    age1->attachAxis(axisY2);
    age2->attachAxis(axisY2);
    age3->attachAxis(axisY2);
    age4->attachAxis(axisY2);
    age5->attachAxis(axisY2);



    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setParent(ui->horizontalFrame_2);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::showEvent(QShowEvent *ev) {
    QMainWindow::showEvent(ev);
    qDebug() << "Window shown";
    manager = new QNetworkAccessManager();
    manager2 = new QNetworkAccessManager();
//    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));

    getChartData();
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
    ageButtonList.append(ui->r_75_99);
    ageButtonList.append(ui->r_100_124);
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

void MainWindow::getChartData() {
    qDebug("Get chart data");

    QJsonObject query, from, collectionId;

    collectionId.insert("collectionId", "people");
    from.insert("from", collectionId);
    query.insert("structuredQuery", from);

    QJsonDocument jsonDoc(query);
    qDebug() << jsonDoc.toJson();

    QNetworkRequest newpeopleRequest( QUrl("https://firestore.googleapis.com/v1beta1/projects/intcognito-advertising/databases/(default)/documents:runQuery"));
    newpeopleRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString("application/json"));
    windowNetworkReply2 = manager2->post( newpeopleRequest, jsonDoc.toJson() );
    // No such signal finished for networkReply
    QObject::connect(manager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(onChartResponse()), Qt::QueuedConnection);
}

void MainWindow::onChartResponse() {
    qDebug() << "chart response";
    QByteArray rawResponse = windowNetworkReply2->readAll();
    qDebug() << rawResponse;
    QJsonDocument resDoc;
    QJsonParseError jsonErr;
    resDoc = QJsonDocument::fromJson(rawResponse, &jsonErr);

    if (jsonErr.error != QJsonParseError::NoError){
        qDebug() << jsonErr.errorString();
    }

    QJsonArray object = resDoc.array();

    QList<QString> dateTimeList;
    foreach (const QJsonValue& arrEl, object) {
        QString tempTime;

        tempTime = arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Time")
                    .toObject().value("timestampValue").toString();
        dateTimeList.append(tempTime);

    }

    QList<QVariantMap> output;

    // [{period: DateTime, maleCount: int, femaleCount, n0_24, etc etc}, ...]
    // 1. Sort date time list in ascending order
    // 2. First element of date time list will be our beginning period (round off to nearest hour)
    // 3. Last element of list+1 will be our end period
    // 4. From beginning period, count up, adding one minute each, until last element is reached
    //

    dateTimeList.sort();

    QList<QDateTime> legitDateTimeList;

    for (int i = 0; i < dateTimeList.size(); ++i) {
        qDebug() << dateTimeList[i];
        legitDateTimeList.append(QDateTime::fromString(dateTimeList[i], Qt::ISODate));
    }

    QDate startDate = legitDateTimeList[0].date();
    QTime startTime = legitDateTimeList[0].time();
    startTime.setHMS(startTime.hour(), 0, 0);

    QDateTime startPeriod;
    startPeriod.setDate(startDate);
    startPeriod.setTime(startTime);

    QDate endDate = legitDateTimeList.last().date();
    QTime endTime = legitDateTimeList.last().time().addSecs(3600*10);
    endTime.setHMS(endTime.hour(), 0, 0);

    QDateTime endPeriod;
    endPeriod.setDate(endDate);
    endPeriod.setTime(endTime);

    for (QDateTime dt = startPeriod; dt < endPeriod; dt = dt.addSecs(3600)) {
        QVariantMap temp;
        temp["period"] = dt;
        output.append(temp);
    }

    int n0_24 = 0;
    int n25_49 = 0;
    int n50_74 = 0;
    int n75_99 = 0;
    int n100_124 = 0;

    int nMale = 0;
    int nFemale = 0;


    foreach (const QJsonValue& arrEl, object) {
        QString tempAge, tempGender;
        QDateTime tempTime;

        tempAge = arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Age")
                    .toObject().value("stringValue").toString();

        tempGender = arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Gender")
                    .toObject().value("stringValue").toString();

        tempTime = QDateTime::fromString(arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Time")
                    .toObject().value("timestampValue").toString(), Qt::ISODate);

        for (int i = 0; i < output.size(); ++i) {
            n0_24 = 0;
            n25_49 = 0;
            n50_74 = 0;
            n75_99 = 0;
            n100_124 = 0;

            nMale = 0;
            nFemale = 0;

            QVariantMap currObj = output[i];
            QDateTime currTimePeriod = currObj["period"].toDateTime();
            QDateTime currTimePeriodPlus1 = currTimePeriod.addSecs(3600);

            if (currTimePeriod <= tempTime && tempTime < currTimePeriodPlus1) {
                qDebug() << "INside time";
                if (tempAge == "0-24 yrs old") {
                    qDebug() << "add 024";
                    n0_24++;
                } else if (tempAge == "25-49 yrs old") {
                    n25_49++;
                } else if (tempAge == "50-74 yrs old") {
                    n50_74++;
                } else if (tempAge == "75-99 yrs old") {
                    n75_99++;
                } else if (tempAge == "100-124 yrs old") {
                    n100_124++;
                }

                if (tempGender == "Male") {
                    nMale++;
                } else if (tempGender == "Female") {
                    nFemale++;
                }
            }

            qDebug() << "AAAAAAAA notice me";
            qDebug() << n0_24;
            output[i]["n0_24"] = n0_24;
            output[i]["n25_49"] = n25_49;
            output[i]["n50_74"] = n50_74;
            output[i]["n75_99"] = n75_99;
            output[i]["n100_124"] = n100_124;

            output[i]["nMale"] = nMale;
            output[i]["nFemale"] = nFemale;
        }
    }

    qDebug() << dateTimeList[0];
    qDebug() << legitDateTimeList[0];
    qDebug() << startPeriod;
    qDebug() << startDate;

    qDebug() << "Out";
    qDebug() << output;

    int maxGender = 0;
    for (int i = 0; i < output.size(); ++i) {
        QDateTime tempDate = output[i]["period"].toDateTime();
        int tempNFemale = output[i]["nFemale"].toInt();
        qDebug() << tempDate;
        qDebug() << tempNFemale;

        gender1->append(tempDate.toMSecsSinceEpoch(), tempNFemale);
        gender2->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["nMale"].toInt());

        if (output[i]["nMale"].toInt() > 0) {
            qDebug() << "Add male to chart " << output[i];
        }

        if (output[i]["nFemale"].toInt() > 0) {
            qDebug() << "Add female to chart " << output[i];
        }

        age1->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["n0_24"].toInt());
        age2->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["n25_49"].toInt());
        age3->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["n50_74"].toInt());
        age4->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["n75_99"].toInt());
        age5->append(output[i]["period"].toDateTime().toMSecsSinceEpoch(), output[i]["n100_124"].toInt());

        if (output[i]["nFemale"].toInt() > maxGender) {
            maxGender = output[i]["nFemale"].toInt();
        }

        if (output[i]["nMale"].toInt() > maxGender) {
            maxGender = output[i]["nMale"].toInt();
        }

        chart->scroll(chart->plotArea().width() / 10, 0);
    }
    qDebug() << "Last appended";
    qDebug() << output.last()["period"] << " " << output.last()["nFemale"] << " " << output.last()["nMale"];

}
