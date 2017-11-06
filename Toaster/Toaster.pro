#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T21:11:31
#
#-------------------------------------------------

CONFIG += debug_and_release
QT       += core gui
unix:QMAKE_CXXFLAGS += -std=c++11
win32:QMAKE_CXXFLAGS += -bigobj
win32:LIBS += -lwinmm
win32:DEFINES += __WINDOWS_MM__
unix:!macx:DEFINES += __UNIX_JACK__ \
                      __LINUX_ALSA__

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toaster
TEMPLATE = app

VERSION = 1.0.100
QMAKE_TARGET_COMPANY = Thomas Langer
QMAKE_TARGET_PRODUCT = Toaster
QMAKE_TARGET_DESCRIPTION = Editor and remote control for Kemper profiling amplifier
QMAKE_TARGET_COPYRIGHT = Thomas Langer
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_STAGE=\\\"ALPHA\\\"
#win32:RC_ICONS = Toaster.ico

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}


INCLUDEPATH += $$PWD/../ToasterWidgets \
               $$PWD/../RtMidi \
               $$PWD/../Shared \
               $$PWD/../VirtualKPA

SOURCES += main.cpp\
    ToasterWindow.cpp \
    Midi.cpp \
    SysExMsgDispatcher.cpp \
    StompMidi.cpp \
    MainFrame.cpp \
    Stomp.cpp \
    AmpMidi.cpp \
    RigMidi.cpp \
    EqMidi.cpp \
    InputMidi.cpp \
    CabMidi.cpp \
    DelayMidi.cpp \
    ReverbMidi.cpp \
    GlobalMidi.cpp \
    Amp.cpp \
    Cab.cpp \
    Delay.cpp \
    Eq.cpp \
    Global.cpp \
    Input.cpp \
    Rig.cpp \
    Reverb.cpp \
    DebugMidi.cpp \
    NRPNBase.cpp \
    StompCtxMenu.cpp \
    SettingsDialog.cpp \
    Settings.cpp \
    ProfileMidi.cpp \
    Profile.cpp \
    ExtParamMidi.cpp \
    ExtParam.cpp \
    StompEditorFrame.cpp \
    BrowserFrame.cpp \
    TunerFrame.cpp \
    WahWahFrame.cpp \
    DummyStompFrame.cpp \
    LookUpTables.cpp \
    TunerIndex.cpp \
    TunerIndexMidi.cpp \
    RectiShaperFrame.cpp \
    PureBoosterFrame.cpp \
    WahPedalBoosterFrame.cpp \
    DriveAndToneDSFrame.cpp \
    DriveDSFrame.cpp \
    ToneAndDuckingDSFrame.cpp \
    MetalDSFrame.cpp \
    DebugCreateStringValuesDialog.cpp \
    WahPhaserFrame.cpp \
    WahNoPeakFrame.cpp \
    WahFormantShiftFrame.cpp \
    GraphicEqualizerFrame.cpp \
    StudioEqualizerFrame.cpp \
    MetalEqualizerFrame.cpp \
    CompressorFrame.cpp \
    GateFrame.cpp \
    VintageChorusFrame.cpp \
    HyperChorusFrame.cpp \
    AirChorusFrame.cpp \
    MicroPitchFrame.cpp \
    VibratoFrame.cpp \
    TremoloFrame.cpp \
    RotarySpeakerFrame.cpp \
    PhaserFrame.cpp \
    FlangerFrame.cpp \
    TransposeFrame.cpp \
    PedalPitchFrame.cpp \
    PedalVinylStopFrame.cpp \
    LoopDistortionFrame.cpp \
    LoopFrame.cpp \
    AnalogOctaverFrame.cpp \
    SpaceFrame.cpp \
    ChromaticPitchFrame.cpp \
    HarmonicPitchFrame.cpp \
    DelayFrame.cpp \
    ReverbFrame.cpp \
    ReverbCtxMenu.cpp \
    TapDelayFrame.cpp \
    DebugSettingsDialog.cpp \
    FlangerOnewayFrame.cpp \
    PhaserOnewayFrame.cpp \
    ConnectionStatusFrame.cpp \
    AboutDialog.cpp \ 
    AmpFrame.cpp \
    CabFrame.cpp \
    TunerMidi.cpp \
    Tuner.cpp \
    InputFrame.cpp \
    OutputFrame.cpp \ 
    MasterVolume.cpp \
    TapMidi.cpp \
    Tap.cpp \
    LegacyDelayFrame.cpp \
    MixValuesV4.cpp \
    StereoWidenerFrame.cpp \
    KPAOS4Checker.cpp

SOURCES += MainVolumeValues.cpp \
    RotaryDistanceValues.cpp \
    RigVolumeValues.cpp \
    MixValues.cpp \
    FrequencyValues.cpp \
    TremoloRateValues.cpp \
    QFactorValues.cpp \
    FlangerRateValues.cpp \
    VoiceIntervalValues.cpp

HEADERS  += ToasterWindow.h \
    Midi.h \
    SysExMsgDispatcher.h \
    StompMidi.h \
    MainFrame.h \
    Stomp.h \
    AmpMidi.h \
    RigMidi.h \
    EqMidi.h \
    InputMidi.h \
    CabMidi.h \
    DelayMidi.h \
    ReverbMidi.h \
    GlobalMidi.h \
    Amp.h \
    Cab.h \
    Delay.h \
    Eq.h \
    Global.h \
    Input.h \
    Rig.h \
    Reverb.h \
    DebugMidi.h \
    NRPNBase.h \
    StompCtxMenu.h \
    SettingsDialog.h \
    Settings.h \
    ProfileMidi.h \
    Profile.h \
    ExtParamMidi.h \
    ExtParam.h \
    StompEditorFrame.h \
    BrowserFrame.h \
    TunerFrame.h \
    WahWahFrame.h \
    DummyStompFrame.h \
    LookUpTables.h \
    TunerIndex.h \
    TunerIndexMidi.h \
    StompEditorPage.h \
    RectiShaperFrame.h \
    PureBoosterFrame.h \
    WahPedalBoosterFrame.h \
    DriveAndToneDSFrame.h \
    DriveDSFrame.h \
    ToneAndDuckingDSFrame.h \
    MetalDSFrame.h \
    DebugCreateStringValuesDialog.h \
    WahPhaserFrame.h \
    WahNoPeakFrame.h \
    WahFormantShiftFrame.h \
    GraphicEqualizerFrame.h \
    StudioEqualizerFrame.h \
    MetalEqualizerFrame.h \
    CompressorFrame.h \
    GateFrame.h \
    VintageChorusFrame.h \
    HyperChorusFrame.h \
    AirChorusFrame.h \
    MicroPitchFrame.h \
    VibratoFrame.h \
    TremoloFrame.h \
    RotarySpeakerFrame.h \
    PhaserFrame.h \
    FlangerFrame.h \
    TransposeFrame.h \
    PedalPitchFrame.h \
    PedalVinylStopFrame.h \
    LoopDistortionFrame.h \
    LoopFrame.h \
    AnalogOctaverFrame.h \
    SpaceFrame.h \
    ChromaticPitchFrame.h \
    HarmonicPitchFrame.h \
    DelayFrame.h \
    ReverbFrame.h \
    ReverbCtxMenu.h \
    TapDelayFrame.h \
    DebugSettingsDialog.h \
    RotaryDistanceValues.h \
    RigVolumeValues.h \
    MainVolumeValues.h \
    MixValues.h \
    TremoloRateValues.h \
    FrequencyValues.h \
    QFactorValues.h \
    FlangerRateValues.h \
    FlangerOnewayFrame.h \
    PhaserOnewayFrame.h \
    VoiceIntervalValues.h \
    ConnectionStatusFrame.h \
    AboutDialog.h \ 
    AmpFrame.h \
    CabFrame.h \
    Tuner.h \
    TunerMidi.h \
    InputFrame.h \
    OutputFrame.h \
    MasterVolume.h \
    TapMidi.h \
    Tap.h \
    LegacyDelayFrame.h \
    MixValuesV4.h \
    StereoWidenerFrame.h \
    KPAOS4Checker.h \
    ../Shared/Commons.h \
    ../Shared/Utils.h \
    ../Shared/SysExBase.h \
    ../Shared/MidiConsumer.h

FORMS    += \
    ToasterWindow.ui \
    MainFrame.ui \
    SettingsDialog.ui \
    BrowserFrame.ui \
    StompEditorFrame.ui \
    TunerFrame.ui \
    WahWahFrame.ui \
    DummyStompFrame.ui \
    RectiShaperFrame.ui \
    PureBoosterFrame.ui \
    WahPedalBoosterFrame.ui \
    DriveAndToneDSFrame.ui \
    DriveDSFrame.ui \
    ToneAndDuckingDSFrame.ui \
    MetalDSFrame.ui \
    DebugCreateStringValuesDialog.ui \
    WahPhaserFrame.ui \
    WahNoPeakFrame.ui \
    WahFormantShiftFrame.ui \
    GraphicEqualizerFrame.ui \
    StudioEqualizerFrame.ui \
    MetalEqualizerFrame.ui \
    CompressorFrame.ui \
    GateFrame.ui \
    VintageChorusFrame.ui \
    HyperChorusFrame.ui \
    AirChorusFrame.ui \
    MicroPitchFrame.ui \
    VibratoFrame.ui \
    TremoloFrame.ui \
    RotarySpeakerFrame.ui \
    PhaserFrame.ui \
    FlangerFrame.ui \
    TransposeFrame.ui \
    PedalPitchFrame.ui \
    PedalVinylStopFrame.ui \
    LoopDistortionFrame.ui \
    LoopFrame.ui \
    AnalogOctaverFrame.ui \
    SpaceFrame.ui \
    ChromaticPitchFrame.ui \
    HarmonicPitchFrame.ui \
    DelayFrame.ui \
    ReverbFrame.ui \
    TapDelayFrame.ui \
    DebugSettingsDialog.ui \
    FlangerOnewayFrame.ui \
    PhaserOnewayFrame.ui \
    ConnectionStatusFrame.ui \
    AboutDialog.ui \ 
    AmpFrame.ui \
    CabFrame.ui \
    InputFrame.ui \
    OutputFrame.ui \
    LegacyDelayFrame.ui \
    StereoWidenerFrame.ui

RESOURCES += \
    resources.qrc


DEPENDPATH += $$PWD/../ToasterWidgets \
              $$PWD/../RtMidi \
              $$PWD/../VirtualKPA

CONFIG(release, debug|release):LIBS += -L$$OUT_PWD/../RtMidi/release/ -lRtMidi
CONFIG(debug, debug|release):LIBS += -L$$OUT_PWD/../RtMidi/debug/ -lRtMidi

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/release/ -lqtoasterwidgetsplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/debug/ -lqtoasterwidgetsplugind
else:macx:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/release -lqtoasterwidgetsplugin
else:macx: CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/debug -lqtoasterwidgetsplugin_debug
else:unix: CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/release -lqtoasterwidgetsplugin
else:unix: CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ToasterWidgets/debug -lqtoasterwidgetsplugin

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VirtualKPA/release -lVirtualKPA
CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VirtualKPA/debug -lVirtualKPA

unix:!macx:LIBS += -lasound -ljack
macx:LIBS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
