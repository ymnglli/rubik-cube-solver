CC = gcc
CXX = g++
ifeq ($(OS), Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif
LDFLAGS = -g
ifeq ($(OS), Windows_NT)
	LDLIBS = -I/lib -lglfw3 -lopengl32 -lglew32
else
	LDLIBS = -lglfw -lGL -lGLEW -lpthread
endif
SRCS = *.cpp
OBJS = $(subst %.cpp, %.o, $(SRCS))

all: output

output: $(OBJS)
	$(CXX) $(LDFLAGS) -o rubix $(OBJS) $(LDLIBS)
	
clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool