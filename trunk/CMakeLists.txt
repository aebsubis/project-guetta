cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


project(proyecto)

find_package(PCL 1.1 REQUIRED)
FIND_PACKAGE(Qt4 REQUIRED)

SET(proyecto_SOURCES main.cpp Guetta.cpp GuettaViewer.cpp GLWidget.cpp Viewer.cpp StandardCamera.cpp GuettaFeatures.cpp GuettaCloud.cpp SiftGPUFeatureDetector.cpp GuettaICP.cpp GuettaTime.cpp Ramsac.cpp)
SET(proyecto_HEADERS Guetta.h GuettaViewer.h GLWidget.h Viewer.h)
SET(proyecto_FORMS Guetta.ui GuettaViewer.ui)

SET(QT_USE_QTOPENGL TRUE)
set(QT_USE_XML TRUE)

QT4_WRAP_CPP(proyecto_HEADERS_MOC ${proyecto_HEADERS})
QT4_WRAP_UI(proyecto_FORMS_HEADERS ${proyecto_FORMS})

INCLUDE(${QT_USE_FILE})

add_definitions(${PCL_DEFINITIONS})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${QT_INCLUDE_DIR})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(.)
include_directories(${PCL_INCLUDE_DIRS})
include_directories("/usr/local/include/opencv2/opencv")
include_directories("./siftgpu/src/")
include_directories("/usr/include/QGLViewer")
include_directories("/usr/include/qt4/QtXml")
link_directories(${PCL_LIBRARY_DIRS})
link_directories("~/NetBeansProjects/GuettaICP/siftgpu")
link_directories("/usr/local/lib")

LINK_DIRECTORIES( ${QT_LIBRARY_DIR} )
LINK_DIRECTORIES( ${QT_LIBRARIES} )



ADD_EXECUTABLE(GuettaGrabber ${proyecto_SOURCES} ${proyecto_HEADERS_MOC}  ${proyecto_FORMS_HEADERS} )
TARGET_LINK_LIBRARIES(GuettaGrabber ${PCL_LIBRARIES} ${QT_LIBRARIES} siftgpu opencv_core opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_features2d opencv_calib3d opencv_objdetect opencv_contrib opencv_legacy opencv_flann GLU QGLViewer flann hdf5)
