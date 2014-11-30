
# compiler
CXX ?= clang++

# executable
TARGET = rpi-switches

# sources
SRCDIRS = src
SRC = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))

# includes
INCDIRS = src/
INCFLAGS = $(foreach dir,$(INCDIRS),-I $(dir))

# libs (TODO)
# desktop version to allow testing on desktop.
DESKTOP_GPIO_LIB =  # ...
RPI_GPIO_LIB = # ...
LIBDIRS =  # ...
LIBS = $(foreach dir,$(LIBDIRS),-L $(dir)) # ...

# compilation
CXXFLAGS = $(INCFLAGS) $(OFLAGS) $(DBGFLAGS)

# debug mode
DEBUG ?= 1 # always enable debug for the moment
ifeq ($(DEBUG),1)
    DBGFLAGS=-ggdb3 -DDEBUG
    OPTI = 0
else
    DBGFLAGS=-DNDEBUG
endif

# optimizations
OPTI ?= 0 # default is disable
ifeq ($(OPTI),0)
    OFLAGS = -O0
else
    OFLAGS = -O3
endif

# objects files
OBJ = $(SRC:.cpp=.o)

# default : desktop version
all:	$(TARGET)-desktop
	echo "hello world !"

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS) $(RPI-GPIO-LIB)
	
$(TARGET)-desktop: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET)-desktop $(OBJ) $(LIBS)
	
clean:
	$(RM) $(TARGET) $(TARGET)-desktop
	$(RM) $(OBJ)

rebuild: clean all