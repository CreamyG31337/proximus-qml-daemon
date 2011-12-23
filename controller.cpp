#include "controller.h"
#include "profileclient.h"

Controller::Controller(QObject *parent) :
    QObject(parent), settings(new QSettings("/home/user/.config/FakeCompany/Proximus.conf",QSettings::NativeFormat,this))
    ,fswatcher(new QFileSystemWatcher(this))
    ,calTimer(new QSystemAlignedTimer(this))


{//important to init qsettings like that so it doesn't store in /home/root/ or whatever other account name
    qDebug() << "starting proximus";
    qDebug() << "1";
    fswatcher->addPath("/home/user/.config/FakeCompany/Proximus.conf");
    qDebug() << "2";
    connect(fswatcher, SIGNAL(fileChanged(QString)),
            this, SLOT(rulesStorageChanged()));//don't need the filename passed
    qDebug() << "3";
    QCoreApplication::setOrganizationName("FakeCompany");
    QCoreApplication::setOrganizationDomain("appcheck.net");
    QCoreApplication::setApplicationName("Proximus");
    qDebug() << "4";

    //call once now to populate initial rules
    rulesStorageChanged();

    //set up timer for calendar,
    #if defined(Q_WS_MAEMO_5)
        //worry about this later
    #else
        #if defined (Q_WS_SIMULATOR)
            //
        #else //harmattan or symbian...
           // QSystemAlignedTimer *newTimer = new QSystemAlignedTimer(this);
            connect (calTimer, SIGNAL(timeout()),this,SLOT(updateCalendar()));
            calTimer->start(60*45,60*60); //timer should fire every 45-60 min
        #endif
    #endif




    qDebug() << "init complete";
}

Controller::~Controller()
{
    delete settings;
}

void Controller::rulesStorageChanged() {
    qDebug() << "rulesStorageChanged()" << settings->allKeys();
    qDebug() << "current group is " << settings->group();
    startGPS();//since settings could have changed, restart GPS to set the correct positioning method
    //setup memory structure used to keep track of rules being active or not

    //as this DOES NOT happen often, it's okay to recreate from scratch
    Rules.clear();
    settings->sync();//REALLY needed.
    //fill list
    settings->beginGroup("rules");
    Q_FOREACH(const QString &strRuleName, settings->childGroups()){//for each rule
        settings->beginGroup(strRuleName);
        //ui->listWidgetRules->addItem(strRuleName);//add name to screen list
        if (settings->value("enabled").toBool() == true){//if enabled
            Rule* newRule = new Rule();
            newRule->name = strRuleName;
            qDebug() << "loaded rule" << strRuleName;
            Rules.insert(strRuleName,newRule);
            newRule->enabled = true;
            DataLocation* ptrRuleDataLoc = new DataLocation;
            ptrRuleDataLoc->setParent(newRule);
            newRule->data.locationRule = ptrRuleDataLoc;
            connect(newRule->data.locationRule, SIGNAL(activeChanged(Rule*)),
                    this,SLOT(checkStatus(Rule*)));

            //fill them -- TODO: need to check if the paths exist, default them
            ptrRuleDataLoc->active = false;//we can default the status to false, it will be re-evaluated within a minute
            ptrRuleDataLoc->enabled = settings->value("Location/enabled").toBool();
            ptrRuleDataLoc->inverseCond = settings->value("Location/NOT").toBool();
            ptrRuleDataLoc->radius = settings->value("Location/RADIUS").toInt();
            ptrRuleDataLoc->location.setLongitude(settings->value("Location/LONGITUDE").toDouble());
            ptrRuleDataLoc->location.setLatitude(settings->value("Location/LATITUDE").toDouble());
            if (ptrRuleDataLoc->enabled)
            {
                ptrRuleDataLoc->areaMon = initAreaMonitor(ptrRuleDataLoc);
            }
            newRule->data.timeRule.setParent(newRule);
            newRule->data.timeRule.active = false;
            newRule->data.timeRule.enabled = settings->value("Time/enabled").toBool();
            newRule->data.timeRule.inverseCond = settings->value("Time/NOT").toBool();
            newRule->data.timeRule.time1 = settings->value("Time/TIME1").toTime();            
            newRule->data.timeRule.time2 = settings->value("Time/TIME2").toTime();
            qDebug() << "time1/time2" << newRule->data.timeRule.time1 << newRule->data.timeRule.time2 ;
            //time rule is somewhat simple, we can do it here
            if (newRule->data.timeRule.enabled)
            {
                qint32 startTimeDiff, endTimeDiff;
                startTimeDiff = QTime::currentTime().secsTo(newRule->data.timeRule.time1);
                endTimeDiff = QTime::currentTime().secsTo(newRule->data.timeRule.time2);
                qDebug()<< "start/end timediff: " << startTimeDiff << endTimeDiff; //27240 //34440
                if (startTimeDiff < 1)//can be negative if it occured < 12 hrs ago?
                    startTimeDiff = 86400 + startTimeDiff;// if was negative, that's not useful. we take the # seconds in a day (86,400) and subtract the # of seconds ago the event started to get the # of seconds when it starts next.
                if (endTimeDiff < 1)
                    endTimeDiff = 86400 + endTimeDiff;//same thing here
                newRule->data.timeRule.deactivateTimer.start(endTimeDiff * 1000);
                newRule->data.timeRule.deactivateTimer.setSingleShot(true);
                //ui->txtLog->appendPlainText("timer to deactivate rule set for " + QString::number(endTimeDiff) + "s");
                if (endTimeDiff < startTimeDiff)//means we are activated right now
                    newRule->data.timeRule.activated();
                else {
                    newRule->data.timeRule.activateTimer.start(startTimeDiff * 1000);//convert to ms
                    newRule->data.timeRule.activateTimer.setSingleShot(true);
                   // ui->txtLog->appendPlainText("timer to activate rule set for " +  QString::number(startTimeDiff) + "s");
                    if (newRule->data.timeRule.inverseCond == true) {//need to set directly
                        qDebug() << "time inverse - should be set active";
                        //newRule->data.timeRule.active = true;
                        checkStatus(newRule);
                    }
                }
            }

            newRule->data.calendarRule.setParent(newRule);
            newRule->data.calendarRule.active = false;
            newRule->data.calendarRule.enabled = settings->value("Calendar/enabled").toBool();
            newRule->data.calendarRule.inverseCond = settings->value("Calendar/NOT").toBool();
            newRule->data.calendarRule.keywords = settings->value("Calendar/KEYWORDS").toString();
        }
        else{//rule was not enabled, we skipped all of the above
          //  ui->listWidgetRules->item(ui->listWidgetRules->count() - 1)->setForeground(Qt::red);
        }
        settings->endGroup();
    }
    settings->endGroup();
    updateCalendar(); //call from here so rule changes trigger this again
}

//triggered by a heartbeat timer object every 45 min or so,
//checks calendar for any keyword matches and sets more timers to change the rule to active when those become current.
//if this api made any sense, i could use signals too
void Controller::updateCalendar()
{//ugh so this thing opens the current users calendar... root / developer = bad
    QOrganizerManager defaultManager; //provides access to system address book, calendar
    qDebug() << "params: " << defaultManager.managerParameters().values().count(); // params:  0
    //qDebug() << "manager: " << defaultManager.managerUri(); // manager:  "qtorganizer:mkcal:"
    QMap<QString, QString> parameters;
    parameters["filename"] = "/home/user/.calendar/db"; // database??
    //QOrganizerManager userManager("",parameters);
    //get list of all upcoming calendar events
    QList<QOrganizerItem> entries =
             defaultManager.items(QDateTime::currentDateTime(),//not sure if this returns events already started
                                  QDateTime::currentDateTime().addSecs(3600)); //read next hour of calendar data
    //for each calendar rule
    Q_FOREACH(Rule* ruleStruct,  Rules) {
        bool foundMatch = false;
        QString keywords = ruleStruct->data.calendarRule.keywords;
        //seperate keywords string into list of keywords
        QStringList keywordList = keywords.split(" ");
        qDebug() << "found # keywords: " << keywordList.count();
        //then loop through all the upcoming calendar events
        qDebug() << "searching " << entries.count() << "calendar entries for the next hour";
        Q_FOREACH(QOrganizerItem orgItem, entries){
            //and each individual keyword
            Q_FOREACH(QString keyword, keywordList){
                qDebug() << "check for keyword " << keyword;
                if (orgItem.displayLabel().contains(keyword, Qt::CaseInsensitive) || orgItem.description().contains(keyword, Qt::CaseInsensitive)) {
                    //keyword match, set up timer to activate this rule
                    foundMatch = true;
                    qDebug() << "keyword match";
                    //find seconds until event
                    qint16 startTimeDiff, endTimeDiff;
                    QOrganizerEventTime eventTime = orgItem.detail<QOrganizerEventTime>();
                    startTimeDiff = QDateTime::currentDateTime().secsTo(eventTime.startDateTime());
                    endTimeDiff = QDateTime::currentDateTime().secsTo(eventTime.endDateTime());
                    if ((startTimeDiff < 1) && (endTimeDiff > 1)) //already started, but not ended yet or all day event
                    {
                        #ifdef Q_WS_SIMULATOR
                        ruleStruct->data.calendarRule.activateTimer.start(20 * 1000);//timer is in ms
                        ruleStruct->data.calendarRule.activateTimer.setSingleShot(true);
                        ruleStruct->data.calendarRule.deactivateTimer.start(40 * 1000);
                        ruleStruct->data.calendarRule.deactivateTimer.setSingleShot(true);
                        connect(&ruleStruct->data.calendarRule.activateTimer, SIGNAL(timeout()),
                                &ruleStruct->data.calendarRule, SLOT(activated()));
                        connect(&ruleStruct->data.calendarRule.deactivateTimer, SIGNAL(timeout()),
                                &ruleStruct->data.calendarRule, SLOT(deactivated()));
                        #else
                        ruleStruct->data.calendarRule.activated();
                        ruleStruct->data.calendarRule.deactivateTimer.start(endTimeDiff * 1000);
                        ruleStruct->data.calendarRule.deactivateTimer.setSingleShot(true);
                        connect(&ruleStruct->data.calendarRule.deactivateTimer, SIGNAL(timeout()),
                                &ruleStruct->data.calendarRule, SLOT(deactivated()));
                        //connect the signals emited from those slots back to this class
                        connect(&ruleStruct->data.calendarRule, SIGNAL(activeChanged(Rule*)),
                                this, SLOT(checkStatus(Rule*)));
                        #endif
                    }
                    else if (startTimeDiff > 1) //starts in future
                    {
                        //ui->txtLog->appendPlainText("start in " + QString::number(startTimeDiff));
                        ruleStruct->data.calendarRule.activateTimer.start(startTimeDiff * 1000);//timer is in ms
                        ruleStruct->data.calendarRule.activateTimer.setSingleShot(true);
                        ruleStruct->data.calendarRule.deactivateTimer.start(endTimeDiff * 1000);
                        ruleStruct->data.calendarRule.deactivateTimer.setSingleShot(true);
                        connect(&ruleStruct->data.calendarRule.activateTimer, SIGNAL(timeout()),
                                &ruleStruct->data.calendarRule, SLOT(activated()));
                        connect(&ruleStruct->data.calendarRule.deactivateTimer, SIGNAL(timeout()),
                                &ruleStruct->data.calendarRule, SLOT(deactivated()));
                        //connect the signals emited from those slots back to this class
                        connect(&ruleStruct->data.calendarRule, SIGNAL(activeChanged(Rule*)),
                                this, SLOT(checkStatus(Rule*))
                                );
                    }
                }
                //if keywords not found but rule is inversed, we still need to set to active (now)
                if (foundMatch == false && ruleStruct->data.calendarRule.inverseCond == true)
                {//need to set directly
                     ruleStruct->data.calendarRule.active = true;
                     checkStatus(ruleStruct);
                }
            }
        }
    }
}

//sets calendar rule to active
void DataCalendar::activated()
{
    qDebug() << "calendar activated";
    if (this->inverseCond == false)
        this->active = true;
    else
        this->active = false;
    Q_EMIT activeChanged((Rule*)this->parent());
}

//sets calendar rule to inactive
void DataCalendar::deactivated()
{
    qDebug() << "calendar deactivated";
    if (this->inverseCond == false)
        this->active = false;
    else
        this->active = true;
    Q_EMIT activeChanged((Rule*)this->parent());
}

//sets time rule to active
void DataTime::activated()
{
    qDebug() << "time activated";
    if (this->inverseCond == false)
        this->active = true;
    else
        this->active = false;
    Q_EMIT activeChanged((Rule*)this->parent());
}

//sets time rule to inactive
void DataTime::deactivated()
{
    qDebug() << " time deactivated";
    if (this->inverseCond == false)
        this->active = false;
    else
        this->active = true;
    Q_EMIT activeChanged((Rule*)this->parent());
}

void Controller::positionUpdated(QGeoPositionInfo geoPositionInfo)
{
    if (geoPositionInfo.isValid())
    {
        //gps never stops
        //locationDataSource->setUpdateInterval(30*1000);//30 sec //TODO: for meego we should sync this to WAKEUP_SLOT_30_SEC in MeeGo::QmHeartbeat
        // Get the current location as latitude and longitude
        QGeoCoordinate geoCoordinate = geoPositionInfo.coordinate();
        qreal latitude = geoCoordinate.latitude();
        qreal longitude = geoCoordinate.longitude();
//        ui->lblLongitude->setText(QString::number(longitude));
//        ui->lblLatitude->setText(QString::number(latitude));
//        ui->lblLastUpdatedTime->setText(geoPositionInfo.timestamp().toString());
//        ui->lblAccuracy->setText(QString::number(geoPositionInfo.attribute(QGeoPositionInfo::HorizontalAccuracy)) + "m");
        //qDebug() << Rules["Example Rule"]->data.timeRule.time1;
    }
}

void Controller::startGPS()
{
    // Obtain the location data source if it is not obtained already
    if (!locationDataSource){
        locationDataSource = QGeoPositionInfoSource::createDefaultSource(this);
        if (!locationDataSource){
            // Not able to obtain the location data source
            qDebug() << "GPS FAILURE";
            return;
        }
    }
    // Whenever the location data source signals that the current
    // position is updated, the positionUpdated function is called.
    QObject::connect(locationDataSource,
                     SIGNAL(positionUpdated(QGeoPositionInfo)),
                     this,
                     SLOT(positionUpdated(QGeoPositionInfo)));


    if (settings->value("/settings/GPS/enabled",false).toBool()) {
        locationDataSource->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
        qDebug() << "gps on";
    }
    else {
        locationDataSource->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
        qDebug() << "gps off";
    }
    locationDataSource->setUpdateInterval(settings->value("/settings/GPS/enabled",60).toInt() * 1000);

    // Start listening for position updates
    locationDataSource->startUpdates();


}

//called any time we activate / deactivate a rule setting
//this just does some boolean math to check if the whole rule is now active or inactive
void Controller::checkStatus(Rule* ruleStruct)
{

    bool locationCond = false;
    if (ruleStruct->data.locationRule->enabled)
    {
        if (ruleStruct->data.locationRule->active)
            locationCond = true;
        else
            locationCond = false;
        if (ruleStruct->data.locationRule->inverseCond)
            locationCond = !locationCond;
    }
    else
        locationCond = true;

    bool timeCond = false;
    if (ruleStruct->data.timeRule.enabled)
    {
        if (ruleStruct->data.timeRule.active)
            timeCond = true;
        else
            timeCond = false;
        if (ruleStruct->data.timeRule.inverseCond)
            timeCond = !timeCond;
    }
    else
        timeCond = true;

    bool calendarCond = false;
    if (ruleStruct->data.calendarRule.enabled)
    {
        qDebug() << "!";
        if (ruleStruct->data.calendarRule.active)
            calendarCond = true;
        else
            calendarCond = false;
        if (ruleStruct->data.calendarRule.inverseCond)
            calendarCond = !calendarCond;
    }
    else
        calendarCond = true;
    qDebug() << "checkStatus() loc/time/cal " << ruleStruct->name << locationCond << timeCond << calendarCond ;
    bool result = locationCond && timeCond && calendarCond;
    ruleStruct->active = result;

    //should write some info to the status tab    
    //if service is supposed to be disabled, just skip this next part.
    if (settings->value("/settings/Service/enabled",true).toBool() == false){
        qDebug() << "service supposed to be disabled, skipping actions";
        return;
    }

    if (result)
    {
        settings->beginGroup("rules");
        settings->beginGroup(ruleStruct->name);
        if (settings->value("Actions/Run/enabled",false).toBool() == true)
        {//run
            qDebug() << "supposed to run something";
        }
        if (settings->value("Actions/Profile/enabled",false).toBool() == true)
        {//set profile
            #ifndef Q_WS_SIMULATOR
            qDebug() << "attempting to switch to profile '" << settings->value("Actions/Profile/NAME","") << "'";
            //ui->txtLog->appendPlainText("attempt switch to profile " + settings->value("Actions/Profile/NAME","").toString());
            ProfileClient *profileClient = new ProfileClient(this);
            if (!profileClient->setProfile(settings->value("Actions/Profile/NAME","").toString()) )
                qDebug() << "failed to switch profile!!";
            #else

            #endif
        }
        settings->endGroup();
        settings->endGroup();
    }
}

//create and return a (pointer to) a single QGeoAreaMonitor
QGeoAreaMonitor * Controller::initAreaMonitor(DataLocation *& Dataloc)
{
    // Create the area monitor
    qDebug() << "started create area monitor";
    QGeoAreaMonitor *monitor = QGeoAreaMonitor::createDefaultMonitor(Dataloc);
    if (monitor == NULL){
        qDebug() << "error - failed to create monitor";
         return NULL;
    }

    // Connect the area monitoring signals to the corresponding slots
    if (!connect(monitor, SIGNAL(areaEntered(QGeoPositionInfo)),
             Dataloc, SLOT(areaEntered(QGeoPositionInfo))))
        //QMessageBox::critical(this,"error","error connecting slots");
        qDebug() << "error connecting slots";

    connect(monitor, SIGNAL(areaExited(QGeoPositionInfo)),
            Dataloc, SLOT(areaExited(QGeoPositionInfo)));

    //connect the signals emited from those slots back to this class
    connect(Dataloc, SIGNAL(activeChanged(Rule*)),
            this, SLOT(checkStatus(Rule*))
            );

    monitor->setCenter(Dataloc->location);
    monitor->setRadius(Dataloc->radius);
    return monitor;
}

void DataLocation::areaEntered(const QGeoPositionInfo &update) {
    // The area has been entered
    qDebug() << "area entered";
    if (this->inverseCond == false)
        this->active = true;
    else
        this->active = false;
    Q_EMIT activeChanged((Rule*)this->parent());
}

void DataLocation::areaExited(const QGeoPositionInfo &update) {
    // The area has been exited
    qDebug() << "area exited";
     if (this->inverseCond == false)
         this->active = false;
     else
         this->active = true;
     Q_EMIT activeChanged((Rule*)this->parent());
}

Rule::Rule()
{

}

RuleData::RuleData()
    :locationRule(new DataLocation)
{
//init ptr to datalocation obj

}

DataLocation::DataLocation()
    //:areaMon(new QGeoAreaMonitor::createDefaultMonitor())
{

}


void Controller::startSatelliteMonitor()
{
    satelliteInfoSource =
        QGeoSatelliteInfoSource::createDefaultSource(this);
    // Whenever the satellite info source signals that the number of
    // satellites in use is updated, the satellitesInUseUpdated function
    // is called
    QObject::connect(satelliteInfoSource,
                     SIGNAL(satellitesInUseUpdated(
                             const QList<QGeoSatelliteInfo>&)),
                     this,
                     SLOT(satellitesInUseUpdated(
                             const QList<QGeoSatelliteInfo>&)));

    // Whenever the satellite info source signals that the number of
    // satellites in view is updated, the satellitesInViewUpdated function
    // is called
    QObject::connect(satelliteInfoSource,
                     SIGNAL(satellitesInViewUpdated(
                             const QList<QGeoSatelliteInfo>&)),
                     this,
                     SLOT(satellitesInViewUpdated(
                             const QList<QGeoSatelliteInfo>&)));

    // Start listening for satellite updates
    satelliteInfoSource->startUpdates();
}

void Controller::satellitesInUseUpdated(
        const QList<QGeoSatelliteInfo> &satellites) {
    // The number of satellites in use is updated
//    QMessageBox msgBox;
//    msgBox.setText("The number of satellites in use is updated: " +
//                   QString::number(satellites.count()));
//    msgBox.exec();
}

void Controller::satellitesInViewUpdated(
        const QList<QGeoSatelliteInfo> &satellites) {
    // The number of satellites in view is updated
//    QMessageBox msgBox;
//    msgBox.setText("The number of satellites in view is updated: " +
//                   QString::number(satellites.count()));
//    msgBox.exec();
}

//void MainWindow::on_btnNewRule_clicked()
//{
//    qint8 intRuleToEdit =  ui->listWidgetRules->count() + 1;
//    if (Ruledialog == 0)
//    {
//        Ruledialog =  new Rule1(topLevelWidget(),"Rule " +  QString::number(intRuleToEdit),locationDataSource,settings);
//    }
//    #ifdef Q_OS_SYMBIAN
//         Ruledialog->showFullScreen();//modeless to keep GPS running
//    #elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
//         Ruledialog->showMaximized();//modeless to keep GPS running
//    #else
//         Ruledialog->show();//modeless to keep GPS running
//    #endif
//     //when child is destroyed we update the rules, although we shouldn't if they hit cancel, we do anyways...
//     connect(Ruledialog,
//             SIGNAL(destroyed()),
//             this,
//             SLOT(rulesStorageChanged())
//             );
//}

//void MainWindow::on_chkGPSMode_clicked()
//{
//    settings->setValue("settings/GPS",ui->chkGPSMode->isChecked());
//    startGPS();//(restart)
//}

//void MainWindow::on_btnEdit_clicked()
//{
//    if (!ui->listWidgetRules->currentItem()) return;//no item selected; could show messagebox, if even possible to end up in this situation
//    if (Ruledialog == 0)
//    {
//        Ruledialog =  new Rule1(window(), ui->listWidgetRules->currentItem()->text(),locationDataSource,settings);
//    }
//    #ifdef Q_OS_SYMBIAN
//         Ruledialog->showFullScreen();//modeless to keep GPS running
//    #elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
//         Ruledialog->showMaximized();//modeless to keep GPS running
//    #else
//         Ruledialog->show();//modeless to keep GPS running
//    #endif
//     //when child is destroyed we update the rules, although we shouldn't if they hit cancel, we do anyways...
//     connect(Ruledialog,
//             SIGNAL(destroyed()),
//             this,
//             SLOT(rulesStorageChanged())
//             );
//}

//void MainWindow::on_btnDelete_clicked()
//{
//    if (!ui->listWidgetRules->currentItem()) return;//no item selected; could show messagebox, if even possible to end up in this situation
//    int ret = (QMessageBox::question(this,
//                             "Please confirm",
//                             "Do you wish to delete rule: '"+ ui->listWidgetRules->currentItem()->text()+"'",
//                             QMessageBox::Yes | QMessageBox::No,
//                             QMessageBox::No)
//              );
//    if (ret == QMessageBox::Yes){
//        settings->remove("rules/" + ui->listWidgetRules->currentItem()->text());
//    }
//    settings->sync();
//    rulesStorageChanged();
//}

//void MainWindow::on_listWidgetRules_currentTextChanged(const QString &currentText)
//{
//    if (currentText.isNull())//nothing selected
//    {
//        ui->btnDelete->setEnabled(false);
//        ui->btnEnable->setEnabled(false);
//        ui->btnEdit->setEnabled(false);
//        return;
//    }
//    else
//    {
//        ui->btnDelete->setEnabled(true);
//        ui->btnEnable->setEnabled(true);
//        ui->btnEdit->setEnabled(true);
//    }
//    if (settings->value("rules/" + currentText + "/enabled").toBool())//enabled
//        ui->btnEnable->setText("Disable");
//    else//disabled
//        ui->btnEnable->setText("Enable");
//}

//void MainWindow::on_btnEnable_clicked()
//{
//    QString curr = ui->listWidgetRules->currentItem()->text();
//    if ( ui->btnEnable->text() == "Enable"){
//        settings->setValue("rules/" + curr + "/enabled",true);
//        ui->listWidgetRules->currentItem()->setForeground(Qt::green);
//        ui->btnEnable->setText("Disable");
//    }
//    else {
//        settings->setValue("rules/" + curr + "/enabled",false);
//        ui->listWidgetRules->currentItem()->setForeground(Qt::red);
//        ui->btnEnable->setText("Enable");
//    }
//}
