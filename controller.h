#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtCore/QCoreApplication>
#include <QtGui/QMainWindow>
#include <QSystemDeviceInfo>
#include <QtCore/QPointer>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoSatelliteInfoSource>
#include <QGeoSatelliteInfo>
#include <QGeoCoordinate>
#include <QGeoAreaMonitor>
#include <QtGui/QMessageBox>
#include <QTime>
#include <QOrganizerManager>
#include <QOrganizerItem>
#include <QTimer>
#include <QOrganizerEventTime>
#include <QOrganizerItemDetail>
#include <QApplication>
#include <QSettings>
#include <QDebug>


#if defined(Q_WS_MAEMO_5)
    //dunno
#else
    #if defined (Q_WS_SIMULATOR)
        //i dunno what to do in this case.
    #else //harmattan or symbian...
        #include <QSystemAlignedTimer>
    #endif
#endif


QTM_USE_NAMESPACE

class Rule;
class DataLocation : public QObject
{
    Q_OBJECT
public:
    explicit DataLocation();//constructor
    bool enabled;
    bool inverseCond;
    bool active;//active means the conditions are all true
    QGeoCoordinate location;
    qint16 radius;
    QGeoAreaMonitor *areaMon;
public Q_SLOTS:
    /**
     * Called when the current position is in range of the area.
     */
    void areaEntered(const QGeoPositionInfo &update);
    /**
     * Called when the current position moves out of range of the area.
     */
    void areaExited(const QGeoPositionInfo &update);
Q_SIGNALS:
    void activeChanged(Rule* ruleStruct);
};
class DataTime : public QObject
{
    Q_OBJECT
public:
    bool enabled;
    bool inverseCond;
    bool active;
    QTime time1;
    QTime time2;
    QTimer activateTimer;
    QTimer deactivateTimer;
public Q_SLOTS:
    void activated();
    void deactivated();
Q_SIGNALS:
    void activeChanged(Rule* ruleStruct);
};

class DataCalendar : public QObject
{
    Q_OBJECT
public:
    bool enabled;
    bool inverseCond;
    bool active;
    QString keywords;
    QTimer activateTimer;
    QTimer deactivateTimer;
public Q_SLOTS:
    void activated();
    void deactivated();
Q_SIGNALS:
    void activeChanged(Rule* ruleStruct);
};
struct RuleData
{
    //constructor
    explicit RuleData();
    DataLocation* locationRule;
    DataTime timeRule;
    DataCalendar calendarRule;
};
class Rule : public QObject
{
    Q_OBJECT
public:
    //constructor
    explicit Rule();
    QString name;
    bool enabled;
    bool active;
    RuleData data;
};



class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    //destructor
    virtual ~Controller();
    QPointer<QGeoPositionInfoSource> locationDataSource;

signals:

public Q_SLOTS:
    /**
     * Called when the current position is updated.
     */
    void positionUpdated(QGeoPositionInfo geoPositionInfo);
    /**
     * Called when the number of satellites in use is updated.
     */
    void satellitesInUseUpdated(
            const QList<QGeoSatelliteInfo> &satellites);
    /**
     * Called when the number of satellites in view is updated.
     */
    void satellitesInViewUpdated(
            const QList<QGeoSatelliteInfo> &satellites);

    void rulesStorageChanged();

private Q_SLOTS:
    /**
     * Initializes one area monitor, returns pointer to it.
     */
    QGeoAreaMonitor * initAreaMonitor(DataLocation *& Dataloc);
    /**
     * Starts to monitor updates in the number of satellites.
     */
    void startSatelliteMonitor();

   // void on_btnNewRule_clicked();

   // void on_chkGPSMode_clicked();

   // void on_btnEdit_clicked();

  //  void on_btnDelete_clicked();

  //  void on_listWidgetRules_currentTextChanged(const QString &currentText);

  //  void on_btnEnable_clicked();

    void updateCalendar();

    void checkStatus(Rule* ruleStruct);

private:
    QPointer<QGeoSatelliteInfoSource> satelliteInfoSource;

    /**
     * Obtains the location data source and starts listening for position
     * changes.
     */
    void startGPS();
    QPointer<QSettings> settings;
    QHash<QString, Rule*> Rules;

};

#endif // CONTROLLER_H
