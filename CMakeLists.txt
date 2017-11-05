cmake_minimum_required(VERSION 3.1.0)

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
    set(CXX_CLANG_TIDY ${DO_CLANG_TIDY})
endif()


project(RtMidi LANGUAGES CXX)

add_library(rtmidi rtmidi/RtMidi.cpp)
target_include_directories(rtmidi PUBLIC RtMidi)
target_link_libraries(rtmidi "-framework CoreFoundation" "-framework CoreAUDIO" "-framework CoreMIDI")

project(VirtualKPA LANGUAGES CXX)

find_package(Qt5Core REQUIRED)

add_library(VirtualKPA
    VirtualKPA/VirtualBlobParam.cpp
    VirtualKPA/VirtualExtendedParam.cpp
    VirtualKPA/VirtualKPA.cpp
    VirtualKPA/VirtualModule.cpp
    VirtualKPA/VirtualMultiParam.cpp
    VirtualKPA/VirtualParam.cpp
    VirtualKPA/VirtualRig.cpp
    VirtualKPA/VirtualSingleParam.cpp
    VirtualKPA/VirtualStringParam.cpp
    VirtualKPA/VirtualUnknownParam.cpp)

target_link_libraries(VirtualKPA Qt5::Core)
target_include_directories(VirtualKPA PUBLIC VirtualKPA shared)

project(ToasterWidgets LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets UiPlugin Gui REQUIRED)

add_library(ToasterWidgets SHARED
    ToasterWidgets/icons.qrc
    ToasterWidgets/skins.qrc
    ToasterWidgets/LCDControls.ui
    ToasterWidgets/qbigdial.cpp
    ToasterWidgets/qbigdialplugin.cpp
    ToasterWidgets/qchickenheaddial.cpp
    ToasterWidgets/qchickenheaddialplugin.cpp
    ToasterWidgets/qlcddisplay.cpp
    ToasterWidgets/qlcddisplayplugin.cpp
    ToasterWidgets/qmulticolorled.cpp
    ToasterWidgets/qmulticolorledplugin.cpp
    ToasterWidgets/qsmalldial.cpp
    ToasterWidgets/qsmalldialplugin.cpp
    ToasterWidgets/qsmallknob.cpp
    ToasterWidgets/qsmallknobplugin.cpp
    ToasterWidgets/QToasterBrowserLCD.cpp
    ToasterWidgets/QToasterBrowserLCD.ui
    ToasterWidgets/QToasterBrowserLCDPlugin.cpp
    ToasterWidgets/qtoasterbutton.cpp
    ToasterWidgets/qtoasterbuttonplugin.cpp
    ToasterWidgets/qtoasterdial.cpp
    ToasterWidgets/qtoasterdialplugin.cpp
    ToasterWidgets/qtoasterenumdial.cpp
    ToasterWidgets/qtoasterenumdialplugin.cpp
    ToasterWidgets/QToasterLCD.cpp
    ToasterWidgets/QToasterLCD.ui
    ToasterWidgets/QToasterLookUpTableDial.cpp
    ToasterWidgets/QToasterLookUpTableDialPlugin.cpp
    ToasterWidgets/QToasterStompEditLCD.cpp
    ToasterWidgets/QToasterStompEditLCD.ui
    ToasterWidgets/QToasterStompEditLCDPlugin.cpp
    ToasterWidgets/QToasterTunerLCD.cpp
    ToasterWidgets/QToasterTunerLCD.ui
    ToasterWidgets/QToasterTunerLCDPlugin.cpp
    ToasterWidgets/qtoasterwidgets.cpp
)

target_include_directories(ToasterWidgets PUBLIC ToasterWidgets shared)

qt5_use_modules(ToasterWidgets
    Core
    Widgets
    UiPlugin
    Gui
)

project(Toaster LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_definitions(-DAPP_VERSION=\"0.0.1\" -DAPP_STAGE=\"beta\")

find_package(Qt5 COMPONENTS Core Widgets UiPlugin Gui REQUIRED)

add_executable(Toaster
    Toaster/AboutDialog.cpp
    Toaster/AboutDialog.ui
    Toaster/AirChorusFrame.cpp
    Toaster/AirChorusFrame.ui
    Toaster/Amp.cpp
    Toaster/AmpFrame.cpp
    Toaster/AmpFrame.ui
    Toaster/AmpMidi.cpp
    Toaster/AnalogOctaverFrame.cpp
    Toaster/BrowserFrame.cpp
    Toaster/BrowserFrame.ui
    Toaster/Cab.cpp
    Toaster/CabFrame.cpp
    Toaster/CabFrame.ui
    Toaster/CabMidi.cpp
    Toaster/ChromaticPitchFrame.cpp
    Toaster/ChromaticPitchFrame.ui
    Toaster/CompressorFrame.cpp
    Toaster/CompressorFrame.ui
    Toaster/ConnectionStatusFrame.cpp
    Toaster/ConnectionStatusFrame.ui
    Toaster/DebugCreateStringValuesDialog.cpp
    Toaster/DebugCreateStringValuesDialog.ui
    Toaster/DebugMidi.cpp
    Toaster/DebugSettingsDialog.cpp
    Toaster/DebugSettingsDialog.ui
    Toaster/Delay.cpp
    Toaster/DelayCtxMenu.cpp
    Toaster/DelayFrame.cpp
    Toaster/DelayFrame.ui
    Toaster/DelayMidi.cpp
    Toaster/DriveAndToneDSFrame.cpp
    Toaster/DriveAndToneDSFrame.ui
    Toaster/DriveDSFrame.cpp
    Toaster/DriveDSFrame.ui
    Toaster/DummyStompFrame.cpp
    Toaster/DummyStompFrame.ui
    Toaster/Eq.cpp
    Toaster/EqMidi.cpp
    Toaster/ExtParam.cpp
    Toaster/ExtParamMidi.cpp
    Toaster/FlangerFrame.cpp
    Toaster/FlangerFrame.ui
    Toaster/FlangerOnewayFrame.cpp
    Toaster/FlangerOnewayFrame.ui
    Toaster/FlangerRateValues.cpp
    Toaster/FrequencyValues.cpp
    Toaster/GateFrame.cpp
    Toaster/GateFrame.ui
    Toaster/Global.cpp
    Toaster/GlobalMidi.cpp
    Toaster/GraphicEqualizerFrame.cpp
    Toaster/GraphicEqualizerFrame.ui
    Toaster/HarmonicPitchFrame.cpp
    Toaster/HarmonicPitchFrame.ui
    Toaster/HyperChorusFrame.cpp
    Toaster/HyperChorusFrame.ui
    Toaster/Input.cpp
    Toaster/InputFrame.cpp
    Toaster/InputFrame.ui
    Toaster/InputMidi.cpp
    Toaster/KPAOS4Checker.cpp
    Toaster/LegacyDelayFrame.cpp
    Toaster/LegacyDelayFrame.ui
    Toaster/LookUpTables.cpp
    Toaster/LoopDistortionFrame.cpp
    Toaster/LoopDistortionFrame.ui
    Toaster/LoopFrame.cpp
    Toaster/LoopFrame.ui
    Toaster/main.cpp
    Toaster/MainFrame.cpp
    Toaster/MainFrame.ui
    Toaster/MainVolumeValues.cpp
    Toaster/MasterVolume.cpp
    Toaster/MetalDSFrame.cpp
    Toaster/MetalDSFrame.ui
    Toaster/MetalEqualizerFrame.cpp
    Toaster/MetalEqualizerFrame.ui
    Toaster/MicroPitchFrame.cpp
    Toaster/MicroPitchFrame.ui
    Toaster/Midi.cpp
    Toaster/MixValues.cpp
    Toaster/MixValuesV4.cpp
    Toaster/NRPNBase.cpp
    Toaster/OutputFrame.cpp
    Toaster/OutputFrame.ui
    Toaster/PedalPitchFrame.cpp
    Toaster/PedalPitchFrame.ui
    Toaster/PedalVinylStopFrame.cpp
    Toaster/PedalVinylStopFrame.ui
    Toaster/PhaserFrame.cpp
    Toaster/PhaserFrame.ui
    Toaster/PhaserOnewayFrame.cpp
    Toaster/PhaserOnewayFrame.ui
    Toaster/Profile.cpp
    Toaster/ProfileMidi.cpp
    Toaster/PureBoosterFrame.cpp
    Toaster/PureBoosterFrame.ui
    Toaster/QFactorValues.cpp
    Toaster/resources.qrc
    Toaster/RectiShaperFrame.cpp
    Toaster/RectiShaperFrame.ui
    Toaster/Reverb.cpp
    Toaster/ReverbCtxMenu.cpp
    Toaster/ReverbFrame.cpp
    Toaster/ReverbFrame.ui
    Toaster/ReverbMidi.cpp
    Toaster/Rig.cpp
    Toaster/RigMidi.cpp
    Toaster/RigVolumeValues.cpp
    Toaster/RotaryDistanceValues.cpp
    Toaster/RotarySpeakerFrame.cpp
    Toaster/RotarySpeakerFrame.ui
    Toaster/Settings.cpp
    Toaster/SettingsDialog.cpp
    Toaster/SettingsDialog.ui
    Toaster/SpaceFrame.cpp
    Toaster/SpaceFrame.ui
    Toaster/StereoWidenerFrame.cpp
    Toaster/StereoWidenerFrame.ui
    Toaster/Stomp.cpp
    Toaster/StompCtxMenu.cpp
    Toaster/StompEditorFrame.cpp
    Toaster/StompEditorFrame.ui
    Toaster/StompMidi.cpp
    Toaster/StudioEqualizerFrame.cpp
    Toaster/StudioEqualizerFrame.ui
    Toaster/SysExMsgDispatcher.cpp
    Toaster/Tap.cpp
    Toaster/TapDelayFrame.cpp
    Toaster/TapDelayFrame.ui
    Toaster/TapMidi.cpp
    Toaster/ToasterWindow.cpp
    Toaster/ToasterWindow.ui
    Toaster/ToneAndDuckingDSFrame.cpp
    Toaster/ToneAndDuckingDSFrame.ui
    Toaster/TransposeFrame.cpp
    Toaster/TransposeFrame.ui
    Toaster/TremoloFrame.cpp
    Toaster/TremoloFrame.ui
    Toaster/TremoloRateValues.cpp
    Toaster/Tuner.cpp
    Toaster/TunerFrame.cpp
    Toaster/TunerFrame.ui
    Toaster/TunerIndex.cpp
    Toaster/TunerIndexMidi.cpp
    Toaster/TunerMidi.cpp
    Toaster/VibratoFrame.cpp
    Toaster/VibratoFrame.ui
    Toaster/VintageChorusFrame.cpp
    Toaster/VintageChorusFrame.ui
    Toaster/VoiceIntervalValues.cpp
    Toaster/WahFormantShiftFrame.cpp
    Toaster/WahFormantShiftFrame.ui
    Toaster/WahNoPeakFrame.cpp
    Toaster/WahNoPeakFrame.ui
    Toaster/WahPedalBoosterFrame.cpp
    Toaster/WahPedalBoosterFrame.ui
    Toaster/WahPhaserFrame.cpp
    Toaster/WahPhaserFrame.ui
    Toaster/WahWahFrame.cpp
    Toaster/WahWahFrame.ui
)

qt5_use_modules(Toaster Core)
target_link_libraries(Toaster ToasterWidgets VirtualKPA rtmidi)
target_include_directories(Toaster PUBLIC Toaster)
