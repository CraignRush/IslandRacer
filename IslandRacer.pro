TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = Box2D src
src.depends = Box2D
