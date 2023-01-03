#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QList>
#include <QString>
#include <QCheckBox>

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
    void uploadAd(QString adName, QList<QString> ageGroups, QList<QString> genders, QString imageUrl);
};
#endif // MAINWINDOW_H
