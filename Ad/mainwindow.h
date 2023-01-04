#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QList>
#include <QString>
#include <QCheckBox>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QVariantMap>

#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void managerFinished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply * m_networkReply;
    void uploadAd(QString adName, QList<QString> ageGroups, QList<QString> genders, QString imageUrl);
    void getChartData();
    void onChartResponse();

    QLineSeries *gender1;
    QLineSeries *gender2;

    QLineSeries *age1;
    QLineSeries *age2;
    QLineSeries *age3;
    QLineSeries *age4;
    QLineSeries *age5;

    QChart *chart;
    QChart *chart2;
};
#endif // MAINWINDOW_H
