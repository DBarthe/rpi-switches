
# compiler
CXX ?= clang++

# executable
TARGET = rpi-switches

# sources
COMMON_SRCDIRS = src
COMMON_SRC = $(foreach dir,$(COMMON_SRCDIRS),$(wildcard $(dir)/*.cpp))
RPI_SRCDIR = src/rpi
RPI_SRC = $(wildcard $(RPI_SRCDIR)/*.cpp)
DESKTOP_SRCDIR = src/desktop
DESKTOP_SRC = $(wildcard $(DESKTOP_SRCDIR)/*.cpp)

# includes
INCDIRS = $(COMMON_SRCDIRS)
INCFLAGS = $(foreach dir,$(INCDIRS),-I $(dir))

# libs (TODO)
# desktop version to allow testing on desktop.
DESKTOP_GPIO_LIB =
RPI_GPIO_LIB =
LIBDIRS =
LIBS = $(foreach dir,$(LIBDIRS),-L $(dir))

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
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)
RPI_OBJ = $(RPI_SRC:.cpp=.o)
DESKTOP_OBJ = $(DESKTOP_SRC:.cpp=.o)

# default : desktop version
all:	$(TARGET)-desktop

$(TARGET): $(COMMON_OBJ) $(RPI_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(COMMON_OBJ) $(RPI_OBJ) $(LIBS) $(RPI_GPIO_LIB)
	
$(TARGET)-desktop: $(COMMON_OBJ) $(DESKTOP_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET)-desktop $(COMMON_OBJ) $(DESKTOP_OBJ) $(LIBS)
	
clean:
	$(RM) $(TARGET) $(TARGET)-desktop
	$(RM) $(COMMON_OBJ) $(RPI_OBJ) $(DESKTOP_OBJ)

rebuild: clean all