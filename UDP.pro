TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        console_error.cpp \
        main.cpp \
        mempool_my.cpp \
        multi_thread.cpp \
        tcp_client.cpp \
        tcp_server.cpp \
        udp_client.cpp \
        udp_server.cpp

LIBS += -lpthread

HEADERS += \
    mempool_my.h
