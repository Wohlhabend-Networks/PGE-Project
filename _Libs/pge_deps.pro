TEMPLATE = subdirs
SUBDIRS = PGEServerAPI SDL2MixerModded OOLua Box2D

PGEServerAPI.file = $$PWD/../ServerLib/ServerAPI/ServerAPI.pro
SDL2MixerModded.file = SDL2_mixer_modified/SDL2_mixer.pro
OOLua.file = oolua/project/oolua.pro
Box2D.file = Box2D/project/box2d.pro

deplibs.path = bin
linux-g++: {
deplibs.files += $$PWD/_builds/linux/lib/*.so*
deplibs.files += $$PWD/_builds/sdl2_mixer_mod/*.so*
}
win32: {
deplibs.files += $$PWD/_builds/win32/bin/*.dll
deplibs.files += $$PWD/_builds/sdl2_mixer_mod/*.dll
}
macx: {
deplibs.files += $$PWD/_builds/macos/lib/*.dylib
deplibs.files += $$PWD/_builds/macos/frameworks/*
deplibs.files += $$PWD/_builds/sdl2_mixer_mod/*.dylib
}

!macx: {
deplibs.path = $$PWD/../bin
} else {
deplibs.path = $$PWD/../bin/_Libs
}

INSTALLS += deplibs

