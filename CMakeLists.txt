CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Utsuhotroid)

# User settings
# Probably /home/${USER}/Polycode/Release/Linux/Framework/
SET(POLYROOT "" CACHE FILEPATH "Root directory containing Release-compiled Core/ and Modules/ for including and linking.")

# Subdirectories

# Include folders
SET(IDIRS "")
SET(IDIRS ${IDIRS} ${POLYROOT}/Core/Dependencies/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Core/Dependencies/include/AL/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Core/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Modules/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Modules/Dependencies/include/)
SET(IDIRS ${IDIRS} ${POLYROOT}/Modules/Dependencies/include/bullet/)
INCLUDE_DIRECTORIES(${IDIRS})

# Link folders
SET(LDIRS "")
SET(LDIRS ${LDIRS} ${POLYROOT}/Core/lib/)
SET(LDIRS ${LDIRS} ${POLYROOT}/Core/Dependencies/lib/)
SET(LDIRS ${LDIRS} ${POLYROOT}/Modules/lib/)
SET(LDIRS ${LDIRS} ${POLYROOT}/Modules/Dependencies/lib/)
LINK_DIRECTORIES(${LDIRS})

# Declare the target
ADD_EXECUTABLE(utsuhotroid main.cpp utsuho.cpp)

# Link libraries
SET(LIBS "")
SET(LIBS ${LIBS} rt)
SET(LIBS ${LIBS} dl)
SET(LIBS ${LIBS} pthread)
SET(LIBS ${LIBS} Polycore)
SET(LIBS ${LIBS} freetype)
SET(LIBS ${LIBS} openal)
SET(LIBS ${LIBS} png15)
SET(LIBS ${LIBS} physfs)
SET(LIBS ${LIBS} z)
SET(LIBS ${LIBS} GL)
SET(LIBS ${LIBS} GLU)
SET(LIBS ${LIBS} SDL)
SET(LIBS ${LIBS} Polycode2DPhysics)
SET(LIBS ${LIBS} Box2D)
SET(LIBS ${LIBS} Polycode3DPhysics)
SET(LIBS ${LIBS} BulletDynamics)
SET(LIBS ${LIBS} BulletCollision)
SET(LIBS ${LIBS} LinearMath)
SET(LIBS ${LIBS} X11)
TARGET_LINK_LIBRARIES(utsuhotroid ${LIBS})

# Version Number
SET(Utsuhotroid_VERSION_MAJOR 0)
SET(Utsuhotroid_VERSION_MINOR a)