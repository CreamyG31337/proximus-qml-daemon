#############################################################################
# Makefile for building: proximus-daemon
# Generated by qmake (2.01a) (Qt 4.7.4) on: Wed Dec 21 19:55:33 2011
# Project:  proximus-daemon.pro
# Template: app
# Command: i:/qtsdk/madde/targets/harmattan_10.2011.34-1/bin/qmake.exe -spec ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/default -unix CONFIG+=debug -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc -o Makefile proximus-daemon.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DBUS_LIB -DQT_SVG_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/default -I. -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtCore -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtNetwork -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtGui -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtXml -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtSvg -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtDBus -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4 -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtOrganizer -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtSystemInfo -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtLocation -I/usr/include/qt4 -I/usr/include/applauncherd -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4 -I../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qt4/QtMobility -Imoc
LINK          = g++
LFLAGS        = -Wl,-rpath,I:/usr/lib
LIBS          = $(SUBLIBS)  -LI:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib -L/usr/lib -lQtLocation -lQtSystemInfo -lQtOrganizer -lQtDBus -lQtSvg -lQtXml -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = i:/qtsdk/madde/targets/harmattan_10.2011.34-1/bin/qmake.exe
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = main.cpp \
		controller.cpp \
		profileclient.cpp moc/moc_controller.cpp \
		moc/moc_profileclient.cpp
OBJECTS       = obj/main.o \
		obj/controller.o \
		obj/profileclient.o \
		obj/moc_controller.o \
		obj/moc_profileclient.o
DIST          = ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/g++.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/unix.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/linux.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/qconfig.pri \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_functions.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_config.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_pre.prf \
		deployment.pri \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/debug.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_post.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/mobility.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/warn_on.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/moc.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusinterfaces.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusadaptors.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/unix/thread.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/resources.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/uic.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/yacc.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/lex.prf \
		proximus-daemon.pro
QMAKE_TARGET  = proximus-daemon
DESTDIR       = 
TARGET        = proximus-daemon

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: proximus-daemon.pro  ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/default/qmake.conf ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/g++.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/unix.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/linux.conf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/qconfig.pri \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_functions.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_config.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_pre.prf \
		deployment.pri \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/debug.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_post.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/mobility.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/warn_on.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/moc.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusinterfaces.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusadaptors.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/unix/thread.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/resources.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/uic.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/yacc.prf \
		../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/lex.prf \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtDBus.prl \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtSvg.prl \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtXml.prl \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtGui.prl \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtNetwork.prl \
		i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtCore.prl
	$(QMAKE) -spec ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/default -unix CONFIG+=debug -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc -o Makefile proximus-daemon.pro
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/g++.conf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/unix.conf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/common/linux.conf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/qconfig.pri:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_functions.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt_config.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_pre.prf:
deployment.pri:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/debug.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/default_post.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/mobility.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/warn_on.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/qt.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/moc.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusinterfaces.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/dbusadaptors.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/unix/thread.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/resources.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/uic.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/yacc.prf:
../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/features/lex.prf:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtDBus.prl:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtSvg.prl:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtXml.prl:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtGui.prl:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtNetwork.prl:
i:/QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/share/qt4/mkspecs/default -unix CONFIG+=debug -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc -o Makefile proximus-daemon.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/proximus-daemon1.0.0 || $(MKDIR) obj/proximus-daemon1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/proximus-daemon1.0.0/ && $(COPY_FILE) --parents controller.h profileclient.h obj/proximus-daemon1.0.0/ && $(COPY_FILE) --parents main.cpp controller.cpp profileclient.cpp obj/proximus-daemon1.0.0/ && (cd `dirname obj/proximus-daemon1.0.0` && $(TAR) proximus-daemon1.0.0.tar proximus-daemon1.0.0 && $(COMPRESS) proximus-daemon1.0.0.tar) && $(MOVE) `dirname obj/proximus-daemon1.0.0`/proximus-daemon1.0.0.tar.gz . && $(DEL_FILE) -r obj/proximus-daemon1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc/moc_controller.cpp moc/moc_profileclient.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_controller.cpp moc/moc_profileclient.cpp
moc/moc_controller.cpp: controller.h
	I:/QtSDK/Madde/targets/harmattan_10.2011.34-1/bin/moc.exe $(DEFINES) $(INCPATH) controller.h -o moc/moc_controller.cpp

moc/moc_profileclient.cpp: profileclient.h
	I:/QtSDK/Madde/targets/harmattan_10.2011.34-1/bin/moc.exe $(DEFINES) $(INCPATH) profileclient.h -o moc/moc_profileclient.cpp

compiler_dbus_interface_source_make_all:
compiler_dbus_interface_source_clean:
compiler_dbus_adaptor_source_make_all:
compiler_dbus_adaptor_source_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: ui/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) ui/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_dbus_interface_header_make_all:
compiler_dbus_interface_header_clean:
compiler_dbus_interface_moc_make_all:
compiler_dbus_interface_moc_clean:
compiler_dbus_adaptor_header_make_all:
compiler_dbus_adaptor_header_clean:
compiler_dbus_adaptor_moc_make_all:
compiler_dbus_adaptor_moc_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

obj/main.o: main.cpp controller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o main.cpp

obj/controller.o: controller.cpp controller.h \
		profileclient.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/controller.o controller.cpp

obj/profileclient.o: profileclient.cpp profileclient.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/profileclient.o profileclient.cpp

obj/moc_controller.o: moc/moc_controller.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_controller.o moc/moc_controller.cpp

obj/moc_profileclient.o: moc/moc_profileclient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_profileclient.o moc/moc_profileclient.cpp

####### Install

install_target2: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/etc/init/apps/ || $(MKDIR) $(INSTALL_ROOT)/etc/init/apps/ 
	-$(INSTALL_FILE) i:/Qt/proximus-daemon/proximus-daemon.conf $(INSTALL_ROOT)/etc/init/apps/


uninstall_target2:  FORCE
	-$(DEL_FILE) -r $(INSTALL_ROOT)/etc/init/apps/proximus-daemon.conf
	-$(DEL_DIR) $(INSTALL_ROOT)/etc/init/apps/ 


install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/local/bin/ || $(MKDIR) $(INSTALL_ROOT)/usr/local/bin/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/local/bin/ 


install:  install_target2 install_target  FORCE

uninstall: uninstall_target2 uninstall_target   FORCE

FORCE:

