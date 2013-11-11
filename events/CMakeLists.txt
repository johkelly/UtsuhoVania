CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(utsuhotroid)

SET(Event_Source UtsuhoGameEvent.cpp)
SET(Event_Test_Source UtsuhoGameEvent_test.cpp)

# Compilation intermediary
ADD_LIBRARY(u_events ${Event_Source})

# Testing executable
ENABLE_TESTING()
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} "..")
ADD_EXECUTABLE(u_events_test ${Event_Source} ${Event_Test_Source})
TARGET_LINK_LIBRARIES(u_events_test gtest gtest_main)
ADD_TEST(u_events_test u_events_test)