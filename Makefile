CXXFLAGS =	-g3 -Wall -fmessage-length=0 #-Werror

OBJS =		game-release.o  util.o #game.o

LIBS = -framework Carbon -framework OpenGL -framework GLUT



TARGET =	game-release


$(TARGET):	$(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
