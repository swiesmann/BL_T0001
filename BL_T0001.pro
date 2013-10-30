TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/simpleserial.cpp \
    src/main.cpp \
    src/commands.c \
    src/cmd_def.c

HEADERS += \
    inc/simpleserial.h \
    inc/cmd_def.h \
    inc/apitypes.h

# C++11
QMAKE_CXXFLAGS += -std=c++0x

# libraries
unix|win32: LIBS += -lpthread -lboost_system -lboost_regex

OTHER_FILES += \
    README.md \
    LICENSE
