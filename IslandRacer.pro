TEMPLATE = subdirs
CONFIG += c++11

CONFIG += ordered

SUBDIRS = Box2D src
src.depends = Box2D
