QT       += core gui opengl openglwidgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # QtGifImage/examples/gifimage/creategif/main.cpp \
    # QtGifImage/examples/gifimage/extractFrames/main.cpp \
    QtGifImage/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage/src/3rdParty/giflib/egif_lib.c \
    QtGifImage/src/3rdParty/giflib/gif_err.c \
    QtGifImage/src/3rdParty/giflib/gif_font.c \
    QtGifImage/src/3rdParty/giflib/gif_hash.c \
    QtGifImage/src/3rdParty/giflib/gifalloc.c \
    QtGifImage/src/3rdParty/giflib/quantize.c \
    # QtGifImage/src/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    QtGifImage/src/gifimage/qgifimage.cpp \
    # QtGifImage/tests/auto/qgifimage/tst_qgifimagetest.cpp \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    # ../viewer.c \
    # ../matrix.c
    ../controller/controller.cpp \
    ../model/parser/parser.cpp \
    ../model/affineTransform/affineTransform.cpp \
    ../model/matrix/matrix.cpp

HEADERS += \
    QtGifImage/src/3rdParty/giflib/gif_hash.h \
    QtGifImage/src/3rdParty/giflib/gif_lib.h \
    QtGifImage/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage/src/gifimage/qgifglobal.h \
    QtGifImage/src/gifimage/qgifimage.h \
    QtGifImage/src/gifimage/qgifimage_p.h \
    mainwindow.h \
    myopenglwidget.h \
    # ../viewer.h \
    # ../matrix.h
    ../controller/controller.h \
    ../model/parser/parser.h \
    ../model/affineTransform/affineTransform.h \
    ../model/matrix/matrix.h \
    ../model/struct/struct.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    # QtGifImage/examples/examples.pro \
    # QtGifImage/examples/gifimage/creategif/creategif.pro \
    # QtGifImage/examples/gifimage/extractFrames/extractFrames.pro \
    # QtGifImage/examples/gifimage/gifimage.pro \
    QtGifImage/qtgifimage.pro \
    QtGifImage/src/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    QtGifImage/src/gifimage/gifimage.pro \
    QtGifImage/src/src.pro \
    # QtGifImage/tests/auto/auto.pro \
    # QtGifImage/tests/auto/qgifimage/qgifimage.pro \
    # QtGifImage/tests/tests.pro

DISTFILES += \
    # QtGifImage/README.md \
    # QtGifImage/examples/gifimage/creategif/doc/images/demo1.gif \
    # QtGifImage/examples/gifimage/creategif/doc/src/creategif.qdoc \
    # QtGifImage/examples/gifimage/extractFrames/doc/src/extractframes.qdoc \
    # QtGifImage/examples/gifimage/extractFrames/test.gif \
    QtGifImage/index.qdoc \
    QtGifImage/qtgifimage.qdoc \
    QtGifImage/src/3rdParty/giflib.pri \
    QtGifImage/src/3rdParty/giflib/AUTHORS \
    QtGifImage/src/3rdParty/giflib/COPYING \
    QtGifImage/src/3rdParty/giflib/README \
    QtGifImage/src/gifimage/doc/qtgifimage.qdocconf \
    QtGifImage/src/gifimage/doc/src/examples.qdoc \
    QtGifImage/src/gifimage/doc/src/index.qdoc \
    QtGifImage/src/gifimage/doc/src/qtgifimage.qdoc \
    QtGifImage/src/gifimage/doc/src/usage.qdoc \
    QtGifImage/src/gifimage/qtgifimage.pri \
    QtGifImage/sync.profile
    # QtGifImage/tests/auto/qgifimage/test.gif
