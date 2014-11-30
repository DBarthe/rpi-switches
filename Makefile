
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

# debug and optimizations
DEBUG = yes
OPTI = yes

ifeq ($(DEBUG),yes) 
    DBGFLAGS=-ggdb3 -DDEBUG
    OFLAGS = -O0
else
    DBGFLAGS=-DNDEBUG
    ifeq ($(OPTI),yes)
	OFLAGS := -O3
    else
	OFLAGS := -O0
    endif
endif

# compilation
CXXFLAGS = $(INCFLAGS) $(OFLAGS) $(DBGFLAGS)


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