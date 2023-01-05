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
//    *gender1 << QPointF(QDateTime::currentDateTime().toMSecsSinceEpoch(),2)
//             << QPointF(QDateTime::currentDateTime().addDays(1).toMSecsSinceEpoch(),3)
//             << QPointF(QDateTime::currentDateTime().addDays(2).toMSecsSinceEpoch(),6)
//             << QPointF(QDateTime::currentDateTime().addDays(3).toMSecsSinceEpoch(),3)
//             << QPointF(QDateTime::currentDateTime().addDays(4).toMSecsSinceEpoch(),2);

//    *gender1 << QPointF(QDateTime::currentDateTime().addDays(5).toMSecsSinceEpoch(),10);
//    *gender1 << QPointF(10000000, 100) << QPointF(10000000, 100) << QPointF(10000000, 100);
//    *gender2 << QPointF(3,1); /*<< QPointF(axisX,3) << QPointF(axisX,6) << QPointF(axisX,3)<< QPointF(axisX,2);*/

    chart = new QChart();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(gender1);
    chart->addSeries(gender2);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(6);
    axisX->setFormat("hh ap");
    axisX->setTitleText("Date");
//    chart->addAxis(axisX, Qt::AlignBottom);
    gender1->attachAxis(axisX);
    gender2->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Number");
    axisY->setTickCount(10);
    axisY->setMax(10);
    axisY->setMin(0);
//    chart->addAxis(axisY, Qt::AlignLeft);
    gender1->attachAxis(axisY);
    gender2->attachAxis(axisY);

    chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
    qDebug() << chartView;

//    testChart();

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
//    chart2->addAxis(axisX2, Qt::AlignBottom);
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
//    chart2->addAxis(axisY2, Qt::AlignLeft);
    age1->attachAxis(axisY2);
    age2->attachAxis(axisY2);
    age3->attachAxis(axisY2);
    age4->attachAxis(axisY2);
    age5->attachAxis(axisY2);



    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setParent(ui->horizontalFrame_2);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::testChart() {
//    *gender1 << QPointF(QDateTime::currentDateTime().toMSecsSinceEpoch(),2)
//             << QPointF(QDateTime::currentDateTime().addDays(1).toMSecsSinceEpoch(),3);
//             << QPointF(QDateTime::currentDateTime().addDays(2).toMSecsSinceEpoch(),6)
//             << QPointF(QDateTime::currentDateTime().addDays(3).toMSecsSinceEpoch(),3)
//             << QPointF(QDateTime::currentDateTime().addDays(4).toMSecsSinceEpoch(),2);
    gender1->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),2);
    gender2->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),2);
    qDebug() << chartView;
    chartView->update();
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

    QJsonObject query, from, collectionId, orderBy, orderByField, orderByDirection;

    collectionId.insert("collectionId", "counts");
    from.insert("from", collectionId);

    orderByField.insert("fieldPath", "Time");
    orderBy.insert("field", orderByField);
    orderBy.insert("direction", "ASCENDING");

    from.insert("orderBy", orderBy);

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

    qDebug() << "Object value\n";
    qDebug() << object;


    QList<QString> dateTimeList;
    foreach (const QJsonValue& arrEl, object) {
        QString tempTime;

        tempTime = arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Time")
                    .toObject().value("timestampValue").toString();
        dateTimeList.append(tempTime);

    }

    qDebug() << "281 after foreach";
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
        if (!dateTimeList[i].isEmpty()) {
            legitDateTimeList.append(QDateTime::fromString(dateTimeList[i], Qt::ISODate));
        }
    }

    qDebug() << "300 after for loop";
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

    qDebug() << "317 before for loop";
    qDebug() << startPeriod;
    qDebug() << legitDateTimeList[0];
    qDebug() << dateTimeList[0];
    for (QDateTime dt = startPeriod; dt < endPeriod; dt = dt.addSecs(3600)) {
        QVariantMap temp;
        temp["period"] = dt;
        qDebug() << temp;
        output.append(temp);
    }

    int n0_24;
    int n25_49;
    int n50_74;
    int n75_99;
    int n100_124;

    int nMale;
    int nFemale;

    chart->removeSeries(gender1);
    chart->removeSeries(gender2);
    gender1 = new QLineSeries;
    gender2 = new QLineSeries;

    chart2->removeSeries(age1);
    chart2->removeSeries(age2);
    chart2->removeSeries(age3);
    chart2->removeSeries(age4);
    chart2->removeSeries(age5);

    age1 = new QLineSeries;
    age2 = new QLineSeries;
    age3 = new QLineSeries;
    age4 = new QLineSeries;
    age5 = new QLineSeries;

    for (int i = 0; i < object.size(); ++i) {
        QJsonValue arrEl = object[i];
        // QString tempAge, tempGender;
        // QDateTime tempTime;

        // tempAge = arrEl.toObject().value("document")
        //             .toObject().value("fields")
        //             .toObject().value("Age")
        //             .toObject().value("stringValue").toString();

        // tempGender = arrEl.toObject().value("document")
        //             .toObject().value("fields")
        //             .toObject().value("Gender")
        //             .toObject().value("stringValue").toString();

        QJsonObject tempFields = arrEl.toObject().value("document")
                                    .toObject().value("fields").toObject();

        n0_24 = tempFields.value("n0_24").toObject().value("integerValue").toString().toInt();
        n25_49 = tempFields.value("n25_49").toObject().value("integerValue").toString().toInt();
        n50_74 = tempFields.value("n50_74").toObject().value("integerValue").toString().toInt();
        n75_99 = tempFields.value("n75_99").toObject().value("integerValue").toString().toInt();
        n100_124 = tempFields.value("n100_1").toObject().value("integerValue").toString().toInt();

        nMale = tempFields.value("nMale").toObject().value("integerValue").toString().toInt();
        nFemale = tempFields.value("nFemale").toObject().value("integerValue").toString().toInt();

        QDateTime tempTime = QDateTime::fromString(arrEl.toObject().value("document")
                    .toObject().value("fields")
                    .toObject().value("Time")
                    .toObject().value("timestampValue").toString(), Qt::ISODate);

        qDebug() << tempTime << " | " << nFemale;
        *gender1 << QPointF(tempTime.toMSecsSinceEpoch(), nFemale);
        *gender2 << QPointF(tempTime.toMSecsSinceEpoch(), nMale);

        *age1 << QPointF(tempTime.toMSecsSinceEpoch(), n0_24);
        *age2 << QPointF(tempTime.toMSecsSinceEpoch(), n25_49);
        *age3 << QPointF(tempTime.toMSecsSinceEpoch(), n50_74);
        *age4 << QPointF(tempTime.toMSecsSinceEpoch(), n75_99);
        *age5 << QPointF(tempTime.toMSecsSinceEpoch(), n100_124);
    }

    gender1->setName("Female");
    gender2->setName("Male");
    chart->addSeries(gender1);
    chart->addSeries(gender2);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(6);
    axisX->setFormat("hh ap");
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

    age1->setName("0-24 yrs old");
    age2->setName("25-49 yrs old");
    age3->setName("50-74 yrs old");
    age4->setName("75-99 yrs old");
    age5->setName("100-124 yrs old");
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
}
