#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T19:09:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zebra
TEMPLATE = app
CONFIG += precompile_header
CONFIG += c++14

RESOURCES += resources/resources.qrc

PRECOMPILED_HEADER = src/precompiled/precompiled_header.h

SOURCES += src/main/main.cpp\
        src/gui/main_window.cpp \
    src/gui/sticker_widget.cpp \
    src/gui/sticker_painter.cpp \
    src/gui/sticker_colorline.cpp \
    src/gui/sticker_icon.cpp \
    src/gui/sticker_body_collapsed.cpp \
    src/gui/style_utils.cpp \
    src/gui/frame_border_handler.cpp \
    src/gui/sticker_button.cpp \
    src/gui/sticker_body_expanded.cpp \
    src/gui/sticker_next_button.cpp \
    src/gui/sticker_column_internal.cpp \
    src/gui/sticker_add_button.cpp \
    src/gui/sticker_column_scroll.cpp \
    src/gui/sticker_column.cpp \
    src/kernel/ticket_object.cpp \
    src/kernel/ticket_container.cpp \
    src/kernel/project_handler.cpp

HEADERS  += src/gui/main_window.h \
    src/common/enum_helper.h \
    src/common/enum_misc.h \
    src/common/enum_range.h \
    src/common/utils.h \
    src/containers/enum_bitset.h \
    src/containers/enum_vector.h \
    src/precompiled/precompiled_header.h \
    src/gui/sticker_widget.h \
    src/gui/sticker_painter.h \
    src/gui/sticker_colorline.h \
    src/gui/sticker_icon.h \
    src/gui/sticker_body_collapsed.h \
    src/gui/style_utils.h \
    src/gui/frame_border_handler.h \
    src/gui/sticker_button.h \
    src/gui/sticker_body_expanded.h \
    src/gui/sticker_next_button.h \
    src/gui/sticker_column_internal.h \
    src/gui/sticker_add_button.h \
    src/gui/sticker_column_scroll.h \
    src/gui/sticker_column.h \
    src/kernel/ticket_object.h \
    src/kernel/ticket_container.h \
    src/kernel/project_handler.h \
    src/slots/signal_helpers.h

INCLUDEPATH += src

DISTFILES +=
