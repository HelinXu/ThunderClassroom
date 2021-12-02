QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Connection.cpp \
    Image.cpp \
    Message.cpp \
    Pixel.cpp \
    Server.cpp \
    admin.cpp \
    adminaddwindow.cpp \
    admindelwindow.cpp \
    adminprocess.cpp \
    adminreswindow.cpp \
    adminwindow.cpp \
    ansdatawindow.cpp \
    answerwindow.cpp \
    audio.cpp \
    audioframe.cpp \
    chattingwindow.cpp \
    chatwindow_student.cpp \
    client.cpp \
    log.cpp \
    loginprocess.cpp \
    loginwindow.cpp \
    main.cpp \
    multiplechoice.cpp \
    newmultiplechoicewindow.cpp \
    qnchatmessage.cpp \
    student.cpp \
    studentmainwindow.cpp \
    studentprocess.cpp \
    teacher.cpp \
    teachermainwindow.cpp \
    teacherprocess.cpp \
    user.cpp

HEADERS += \
    Connection.h \
    Image.h \
    Message.h \
    MessageType.h \
    Pixel.h \
    Server.h \
    admin.h \
    adminaddwindow.h \
    admindelwindow.h \
    adminprocess.h \
    adminreswindow.h \
    adminwindow.h \
    ansdatawindow.h \
    answerwindow.h \
    audio.h \
    audioframe.h \
    chattingwindow.h \
    chatwindow_student.h \
    client.h \
    log.h \
    loginprocess.h \
    loginwindow.h \
    multiplechoice.h \
    newmultiplechoicewindow.h \
    qnchatmessage.h \
    student.h \
    studentmainwindow.h \
    studentprocess.h \
    teacher.h \
    teachermainwindow.h \
    teacherprocess.h \
    user.h

FORMS += \
    adminaddwindow.ui \
    admindelwindow.ui \
    adminreswindow.ui \
    adminwindow.ui \
    ansdatawindow.ui \
    answerwindow.ui \
    chattingwindow.ui \
    chatwindow_student.ui \
    loginwindow.ui \
    newmultiplechoicewindow.ui \
    studentmainwindow.ui \
    teachermainwindow.ui

LIBS += -lws2_32 \
    -lgdi32 \
    -lgdiplus \
    -lwinmm \
    -lole32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
