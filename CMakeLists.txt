project(QOczko)

cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(OpenCV REQUIRED)


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(src src/mcv src/ui)

set(qoczkoalgorithm_SRCS src/qoczkoalgorithm.cpp)
set(opencvconnector_SRCS src/opencvconnector.cpp)
set(QOczko_SRCS src/ui/QOczko.cpp)
set(ParametrizedView_SRCS src/ui/ParametrizedView.cpp)
set(OpenView_SRCS src/ui/OpenView.cpp)
set(HotPointView_SRCS src/ui/HotPointView.cpp)
set(ShapeView_SRCS src/ui/ShapeView.cpp)
set(PatternsView_SRCS src/ui/PatternsView.cpp)
qt4_automoc(${PatternsView_SRCS})
qt4_automoc(${ShapeView_SRCS})
qt4_automoc(${HotPointView_SRCS})
qt4_automoc(${OpenView_SRCS})
qt4_automoc(${ParametrizedView_SRCS})
qt4_automoc(${QOczko_SRCS})
qt4_automoc(${opencvconnector_SRCS})
qt4_automoc(${qoczkoalgorithm_SRCS})

set(canny_SRCS src/mcv/canny.cpp) 
set(gray_SRCS src/mcv/gray.cpp)
set(gaussianblur_SRCS src/mcv/gaussianblur.cpp)
set(videograbber_SRCS src/mcv/videograbber.cpp)
set(matchshapes_SRCS src/mcv/matchshapes.cpp)
set(histogram_SRCS src/mcv/histogram.cpp)
set(backproject_SRCS src/mcv/backproject.cpp)
set(camshift_SRCS src/mcv/camshift.cpp)
set(equalizehist_SRCS src/mcv/equalizehist.cpp)
set(pointtracker_SRCS src/mcv/pointtracker.cpp)

qt4_automoc(${pointtracker_SRCS})
qt4_automoc(${equalizehist_SRCS})
qt4_automoc(${camshift_SRCS})
qt4_automoc(${backproject_SRCS})
qt4_automoc(${histogram_SRCS})
qt4_automoc(${matchshapes_SRCS})
qt4_automoc(${videograbber_SRCS})
qt4_automoc(${gaussianblur_SRCS})
qt4_automoc(${gray_SRCS})
qt4_automoc(${canny_SRCS})

add_executable(QOczko 
  ${QOczko_SRCS} 	
  ${ParametrizedView_SRCS}
  ${OpenView_SRCS}
  ${HotPointView_SRCS}
  ${ShapeView_SRCS}
  ${PatternsView_SRCS}
  ${canny_SRCS} 
  ${gray_SRCS}
  ${gaussianblur_SRCS}
  ${videograbber_SRCS}
  ${matchshapes_SRCS}
  ${histogram_SRCS}
  ${backproject_SRCS}
  ${camshift_SRCS}
  ${equalizehist_SRCS}
  ${pointtracker_SRCS}
  ${opencvconnector_SRCS}
  ${qoczkoalgorithm_SRCS}
  src/main.cpp 
  )

target_link_libraries(QOczko ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${OpenCV_LIBS})



