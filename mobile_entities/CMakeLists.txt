CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(utsuhotroid)

SET(Mobile_Source PlatformerScreen.cpp MobileEntity.cpp)
SET(Mobile_Test_Source UtsuhoMobile_test.cpp)

# Include directories
SET(IDIRS ${CMAKE_SOURCE_DIR})
SET(IDIRS ${IDIRS} ${POLYROOT}/Core/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Modules/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Modules/Dependencies/include/)
INCLUDE_DIRECTORIES(${IDIRS})

# Compilation intermediary
ADD_LIBRARY(u_mobile ${Mobile_Source})