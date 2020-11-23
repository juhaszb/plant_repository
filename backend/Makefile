# compile-time flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable
# add includes to cflags
INCLUDES = -I/usr/include/mysql -I/usr/include/mysql++
CXXFLAGS+= $(INCLUDES)

# define debug in cflags
ifdef DEBUG
	CXXFLAGS+= -Og -g -O0
endif

# Linker flags
LDFLAGS = -std=c++17 -l pthread -l pistache -l mysqlpp -l mysqlclient  

ifdef DEBUG
	LDFLAGS+= -g
endif

OBJS_COMMON := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET_NAME := run


# recipies
all: main


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: $(OBJS_COMMON)
	$(CXX) $^ $(LDFLAGS) -o $(TARGET_NAME) 

.PHONY: clean
# clean deletes every object file in the project and every binary from the "all" target
clean:
	$(RM) $(wildcard *.o) $(all) $(TARGET_NAME)
