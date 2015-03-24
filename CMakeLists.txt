cmake_minimum_required(VERSION 2.8)

#Nom du projet

project(MOOS)


SET( Boost_USE_MULTITHREAD ON )
SET( Boost_USE_STATIC_LIBS TRUE )
SET(BOOST_MIN_VERSION "1.53.0")

FIND_PACKAGE(Liblo)
IF(LIBLO_FOUND)
	message ("ok LIBLO found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${LIBLO_INCLUDE_DIR}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${LIBLO_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find LIBLO libraries!")
ENDIF(LIBLO_FOUND)

#FIND_PACKAGE(Gecode)
#IF(GECODE_FOUND)
#	message ("ok GECODE found")
#        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${Gecode_INCLUDE_DIRS}")
#        SET(MOOS_LIBS ${MOOS_LIBS} "${Gecode_LIBRARIES}")
#ELSE()
#  message (FATAL_ERROR "Could not find GECODE libraries!")
#ENDIF(GECODE_FOUND)

FIND_PACKAGE(Pcap)
IF(PCAP_FOUND)
	message ("ok PCAP found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${PCAP_INCLUDE_DIR}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${PCAP_LIBRARY}")
ELSE()
  message (FATAL_ERROR "Could not find PCAP libraries!")
ENDIF(PCAP_FOUND)



SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")



FIND_PACKAGE( Boost REQUIRED thread system serialization)

IF(Boost_FOUND)
	message ("ok boost found")
  SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${Boost_INCLUDE_DIR}")
  SET(MOOS_LIBS ${MOOS_LIBS} "${Boost_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find Boost libraries!")
ENDIF(Boost_FOUND)

FIND_PACKAGE(RtMidi)
if(RTMIDI_FOUND)
        message ("ok RtMIDI found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${RTMIDI_INCLUDE_DIR}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${RTMIDI_LIBRARIES}")
ELSE()
        message (FATAL_ERROR "Could not find RtMidi")
endif(RTMIDI_FOUND)


FIND_PACKAGE( PortAudio)

IF(PORTAUDIO_FOUND)
	message ("ok PORTAUDIO found")
        message ("${PORTAUDIO_LIBRARIES}")
  SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${PORTAUDIO_INCLUDE_DIRS}")
  SET(MOOS_LIBS ${MOOS_LIBS} "${PORTAUDIO_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find PORTAUDIO libraries!")
ENDIF(PORTAUDIO_FOUND)

#FIND_PACKAGE( Soci)

SET (SOCI_LIBRARY /opt/local/lib/libsoci_core.a)
SET (SOCI_odbc_PLUGIN /opt/local/lib/libsoci_odbc.a)
	message ("ok SOCI found")
        message ("${SOCI_LIBRARY}")
        message("${SOCI_odbc_PLUGIN}")
  SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${SOCI_INCLUDE_DIRS}" )
  SET(MOOS_LIBS ${MOOS_LIBS} "${SOCI_LIBRARY}")



#FIND_PACKAGE( LeapMotion)

#IF(LeapMotion_INCLUDE_DIR)
#	message ("ok LeapMotion found")
#        message ("${LeapMotion_LIBRARY_STATIC}")
#  SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${LeapMotion_INCLUDE_DIR}")
#  SET(MOOS_LIBS ${MOOS_LIBS} "${LeapMotion_LIBRARY_STATIC}")
#ELSE()
#  message (FATAL_ERROR "Could not find LeapMotion libraries!")
#ENDIF(LeapMotion_INCLUDE_DIR)

include_directories(
        "${MOOS_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/src/"
        "${PROJECT_SOURCE_DIR}/src/capture/"
        "${PROJECT_SOURCE_DIR}/src/input/"
        "${PROJECT_SOURCE_DIR}/src/mapping/"
        "${PROJECT_SOURCE_DIR}/src/output/"
        "${PROJECT_SOURCE_DIR}/src/output/granular_synth"
        "${PROJECT_SOURCE_DIR}/src/output/midi"
        "${PROJECT_SOURCE_DIR}/src/processing/"
        "${PROJECT_SOURCE_DIR}/src/processing/pcap/"
        "${PROJECT_SOURCE_DIR}/src/processing/leapmotion/"
        "${PROJECT_SOURCE_DIR}/src/utils/"
        "${PROJECT_SOURCE_DIR}/src/view/"
        "${PROJECT_SOURCE_DIR}/src/view/webserver"
        "${PROJECT_SOURCE_DIR}/src/view/websocket"
        "${PROJECT_SOURCE_DIR}/src/save/"
)
#link_directories(
#	${PROJECT_SOURCE_DIR}
#	${PROJECT_SOURCE_DIR}/capture/*
#	${PROJECT_SOURCE_DIR}/Inputs/*
#	${PROJECT_SOURCE_DIR}/mapping/*
#	${PROJECT_SOURCE_DIR}/outputs/*
#	${PROJECT_SOURCE_DIR}/processings/*
#	${PROJECT_SOURCE_DIR}/save/*
#	${PROJECT_SOURCE_DIR}/utils/*
#	${PROJECT_SOURCE_DIR}/view/server/*
#)



#TARGET_LINK_LIBRARIES(${LIBLO_LIBRARIES} ${Boost_LIBRARIES})
#Déclaration executable


file(
	GLOB_RECURSE
	source_files
	src/*

)


add_executable(
	MoOS
	${source_files}
)

target_link_libraries(MoOS ${MOOS_LIBS})
