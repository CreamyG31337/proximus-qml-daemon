
contains(MEEGO_EDITION,harmattan) {
    target2.path = /etc/init/apps
    target2.files += proximus-daemon.conf
    INSTALLS += target2
    #target.path = /opt/proximus-daemon/bin
    #INSTALLS += target
}

SOURCES += \
    main.cpp \
    controller.cpp \
    profileclient.cpp

HEADERS += \
    controller.h \
    profileclient.h

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

CONFIG += mobility
QT += xml network svg dbus
MOBILITY += location
#profiles (read only?? whyyyyyyyy); SystemAlignedTimer
MOBILITY += systeminfo
#calendar
MOBILITY += organizer

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/proximus-daemon.postinst








