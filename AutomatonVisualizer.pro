TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG   += c++11

unix:!macx: LIBS += -losgViewer
unix:!macx: LIBS += -losg
unix:!macx: LIBS += -losgGA

INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include


SOURCES += main.cpp \
    Error/ErrorHandler.cpp \
    Error/Exception.cpp \
    Simulator/Cell.cpp \
    Simulator/Particle.cpp \
    Simulator/Simulator.cpp \
    Simulator/Simulator_CA.cpp \
    Simulator/SpaceConfig.cpp \
    Simulator/SpaceConfig_CA.cpp \
    Simulator/SpacePoint.cpp \
    Visualizer/gridmatrix.cpp \
    Visualizer/objectmodel.cpp \
    Visualizer/particle.cpp \
    Visualizer/particledisplacer.cpp \
    Visualizer/spacegrid.cpp \
    Visualizer/viewer.cpp \
    Visualizer/viewerutils.cpp \
    Visualizer/worldviewer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Error/error.hpp \
    Error/ErrorHandler.hpp \
    Error/Exception.hpp \
    Simulator/Cell.hpp \
    Simulator/CellularAutomaton.hpp \
    Simulator/fluidInitParams.hpp \
    Simulator/Particle.hpp \
    Simulator/Simulator.hpp \
    Simulator/Simulator_CA.hpp \
    Simulator/Simulator_Interface.hpp \
    Simulator/SpaceConfig.hpp \
    Simulator/SpaceConfig_CA.hpp \
    Simulator/SpacePoint.hpp \
    Simulator/spacePointType.hpp \
    Visualizer/gridmatrix.hpp \
    Visualizer/objectmodel.hpp \
    Visualizer/particle.hpp \
    Visualizer/particledisplacer.hpp \
    Visualizer/particletype.hpp \
    Visualizer/spacegrid.hpp \
    Visualizer/viewer.hpp \
    Visualizer/viewerutils.hpp \
    Visualizer/worldviewer.hpp \
    Visualizer/gridmatrix.hpp \
    Visualizer/objectmodel.hpp \
    Visualizer/particle.hpp \
    Visualizer/particledisplacer.hpp \
    Visualizer/particletype.hpp \
    Visualizer/spacegrid.hpp \
    Visualizer/viewer.hpp \
    Visualizer/viewerutils.hpp \
    Visualizer/worldviewer.hpp

