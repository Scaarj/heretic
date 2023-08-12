################################################################################
##
## Copyright (C) 2022 ru.auroraos
## 
## This file is part of the My Aurora OS Application project.
##
## Redistribution and use in source and binary forms,
## with or without modification, are permitted provided
## that the following conditions are met:
##
## * Redistributions of source code must retain the above copyright notice,
##   this list of conditions and the following disclaimer.
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer
##   in the documentation and/or other materials provided with the distribution.
## * Neither the name of the copyright holder nor the names of its contributors
##   may be used to endorse or promote products derived from this software
##   without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
## IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
## FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
## OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS;
## OR BUSINESS INTERRUPTION)
## HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
## WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
## EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
################################################################################

TARGET = ru.auroraos.heretic

contains(QMAKE_HOST.arch, armv7l) {
    TARGET_BUILD_ARCH = armv7hl
	DEFINES += ARCH_ARMV7HL
} else {
    TARGET_BUILD_ARCH = i486
	DEFINES += ARCH_I486
}

CONFIG += sailfishapp warn_on exceptions

PKGCONFIG += \

INCLUDEPATH += \
	src \
	src/sound \
	src/qt \

SOURCES += \
	src/i_main.cpp \
	src/d_main.cpp \
	src/g_game.cpp \
	src/in_lude.cpp \
	src/i_system.cpp \
    src/qt/weaponmodel.cpp \
	src/z_zone.cpp \
	src/mn_menu.cpp \
	src/am_map.cpp \
	src/p_setup.cpp \
	src/r_things.cpp \
	src/r_bsp.cpp \
	src/r_plane.cpp \
	src/r_segs.cpp \
	src/r_data.cpp \
	src/w_wad.cpp \
	src/r_main.cpp \
	src/tables.cpp \
	src/d_net.cpp \
	src/i_net.cpp \
	src/m_misc.cpp \
	src/ct_chat.cpp \
	src/r_draw.cpp \
	src/v_video.cpp \
	src/p_spec.cpp \
	src/info.cpp \
	src/sb_bar.cpp \
	src/p_ceilng.cpp \
	src/p_tick.cpp \
	src/p_plats.cpp \
	src/p_pspr.cpp \
	src/f_finale.cpp \
	src/p_doors.cpp \
	src/p_maputl.cpp \
	src/p_map.cpp \
	src/p_floor.cpp \
	src/p_enemy.cpp \
	src/p_inter.cpp \
	src/p_lights.cpp \
	src/p_mobj.cpp \
	src/p_sight.cpp \
	src/p_switch.cpp \
	src/p_telept.cpp \
	src/p_user.cpp \
	src/sound/i_sound.cpp \
	src/sound/sounds.cpp \
	src/sound/soundst.cpp \
	src/graphic/graphic_qml.cpp \
	src/qt/scenepainter.cpp \
	src/qt/screencontroller.cpp \
	src/qt/context.cpp \
	src/qt/gamescreen.cpp \
	src/qt/introscreen.cpp \

HEADERS += \
    src/qt/weaponmodel.h \
	src/r_local.h \
	src/p_local.h \
	src/doomdef.h \
	src/doomtype.h \
	src/doomdata.h \
	src/dstrings.h \
	src/am_data.h \
	src/am_map.h \
	src/mn_menu.h \
	src/sound/sounds.h \
	src/sound/soundst.h \
	src/sound/i_sound.h \
	src/p_spec.h \
	src/ct_chat.h \
	src/info.h \
	src/sound/i_sound.h \
	src/sound/sounds.h \
	src/sound/soundst.h \
	src/qt/scenepainter.h \
	src/qt/screencontroller.h \
	src/qt/context.h \
	src/qt/gamescreen.h \
	src/qt/introscreen.h \
	src/qt/quitobserver.h \

DISTFILES += \
    rpm/ru.auroraos.heretic.spec \
	AUTHORS.md \
	CODE_OF_CONDUCT.md \
	CONTRIBUTING.md \
	LICENSE.BSD-3-CLAUSE.md \
	README.md \

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += sailfishapp_i18n

RESOURCES += res.qrc

wad_file.files = $$PWD/resource/Heretic.wad
wad_file.path = /usr/share/$${TARGET}
INSTALLS += wad_file

DEFINES += \
    __32BIT__ \
	sailfishapp \

TRANSLATIONS += \
    translations/ru.auroraos.heretic.ts \
	translations/ru.auroraos.heretic-ru.ts \
