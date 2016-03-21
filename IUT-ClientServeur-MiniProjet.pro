TEMPLATE = subdirs
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SUBDIRS = common server client

server.depends = common
client.depends = common

SOURCES += main.cpp
