TEMPLATE = app

CONFIG += console
# Make sure we do not accidentally #include files placed in 'resources'
CONFIG += no_include_pwd

SOURCES = $$files($$PWD/src/*.cpp)
SOURCES += $$files($$PWD/lib/*.cpp)

HEADERS = $$files($$PWD/src/*.h)
HEADERS += $$files($$PWD/lib/StanfordCPPLib/*.h)
HEADERS += $$files($$PWD/lib/*.h)

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/lib/StanfordCPPLib/
INCLUDEPATH += $$PWD/lib/

# Copies the given files to the destination directory
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$OUT_PWD

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        !win32 {
            QMAKE_POST_LINK += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
        }
        win32 {
            QMAKE_POST_LINK += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
        }
    }

    export(QMAKE_POST_LINK)
}
!win32 {
    copyToDestdir($$files($$PWD/res/*))
}
win32 {
    copyToDestdir($$PWD/res)
}

cache()
