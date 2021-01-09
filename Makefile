OBJS = raycaster.cpp # which files to compile as part of project

CC = g++ # compiler to use
COMPILER_FLAGS = -w # additional compilation option (-w suppresses warnings)
LINKER_FLAGS = -lSDL2 # specifies libraries we link against
OBJ_NAME = main # name of executable

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
