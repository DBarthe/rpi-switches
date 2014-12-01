
# compiler
CXX ?= clang++

# executable
TARGET = rpi-switches
TARGET_DESKTOP = $(TARGET)-desktop
TARGET_TEST_DESKTOP = test-desktop

# sources
MAIN_SRCDIR = src/main
MAIN_SRC = $(wildcard $(MAIN_SRCDIR)/*.cpp)
COMMON_SRCDIRS = src src/gpio src/channel
COMMON_SRC = $(foreach dir,$(COMMON_SRCDIRS),$(wildcard $(dir)/*.cpp))
RPI_SRCDIR = src/gpio/rpi
RPI_SRC = $(wildcard $(RPI_SRCDIR)/*.cpp)
DESKTOP_SRCDIR = src/gpio/desktop
DESKTOP_SRC = $(wildcard $(DESKTOP_SRCDIR)/*.cpp)
TEST_SRCDIR = src/test
TEST_SRC = $(wildcard $(TEST_SRCDIR)/*.cpp)

# includes
INCDIRS = $(COMMON_SRCDIRS) $(RPI_SRCDIR) $(DESKTOP_SRCDIR)
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
CXXFLAGS = $(OFLAGS) $(DBGFLAGS) $(INCFLAGS) -std=c++11


# objects files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)
RPI_OBJ = $(RPI_SRC:.cpp=.o)
DESKTOP_OBJ = $(DESKTOP_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

ALL_OBJ_FOR_RPI = $(MAIN_OBJ) $(COMMON_OBJ) $(RPI_OBJ)
ALL_OBJ_FOR_DESKTOP = $(MAIN_OBJ) $(COMMON_OBJ) $(DESKTOP_OBJ)
ALL_OBJ_FOR_TEST_DESKTOP = $(COMMON_OBJ) $(DESKTOP_OBJ) $(TEST_OBJ)

# default : desktop version
all:	desktop

desktop: $(TARGET_DESKTOP)

rpi: $(TARGET)

test: $(TARGET_TEST_DESKTOP)


$(TARGET): $(ALL_OBJ_FOR_RPI)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(ALL_OBJ_FOR_RPI) $(LIBS) $(RPI_GPIO_LIB)

$(TARGET_DESKTOP): CXXFLAGS += -DDESKTOP_MODE	
$(TARGET_DESKTOP): $(ALL_OBJ_FOR_DESKTOP)
	$(CXX) $(CXXFLAGS) -o $(TARGET_DESKTOP) $(ALL_OBJ_FOR_DESKTOP) $(LIBS)

$(TARGET_TEST_DESKTOP): CXXFLAGS += -DTEST_MODE -DDESKTOP_MODE
$(TARGET_TEST_DESKTOP): $(ALL_OBJ_FOR_TEST_DESKTOP)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_DESKTOP) $(ALL_OBJ_FOR_TEST_DESKTOP) $(LIBS)

clean:
	$(RM) $(TARGET) $(TARGET_TEST_DESKTOP)
	$(RM) $(MAIN_OBJ) $(COMMON_OBJ) $(RPI_OBJ) $(DESKTOP_OBJ) $(TEST_OBJ)

rebuild: clean all