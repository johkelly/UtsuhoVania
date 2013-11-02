CC=g++
POLYROOT="/home/jack/polycode/Release/Linux/Framework/"
CFLAGS=\
-I${POLYROOT}Core/Dependencies/include \
-I${POLYROOT}Core/Dependencies/include/AL \
-I${POLYROOT}Core/include \
-I${POLYROOT}Modules/include \
-I${POLYROOT}Modules/Dependencies/include \
-I${POLYROOT}Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread \
${POLYROOT}Core/lib/libPolycore.a \
${POLYROOT}Core/Dependencies/lib/libfreetype.a \
${POLYROOT}Core/Dependencies/lib/liblibvorbisfile.a \
${POLYROOT}Core/Dependencies/lib/liblibvorbis.a \
${POLYROOT}Core/Dependencies/lib/liblibogg.a \
${POLYROOT}Core/Dependencies/lib/libopenal.so ${POLYROOT}Core/Dependencies/lib/libphysfs.a \
${POLYROOT}Core/Dependencies/lib/libpng15.a \
${POLYROOT}Core/Dependencies/lib/libz.a \
-lGL -lGLU -lSDL ${POLYROOT}Modules/lib/libPolycode2DPhysics.a \
${POLYROOT}Modules/Dependencies/lib/libBox2D.a \
${POLYROOT}Modules/lib/libPolycode3DPhysics.a \
${POLYROOT}Modules/Dependencies/lib/libBulletDynamics.a \
${POLYROOT}Modules/Dependencies/lib/libBulletCollision.a \
${POLYROOT}Modules/Dependencies/lib/libLinearMath.a \
-lX11

default: utsuho

clean:
	rm -f utsuho
	
utsuho:
	$(CC) $(CFLAGS) -Iutsuho main.cpp utsuho.cpp -o utsuho $(LDFLAGS)