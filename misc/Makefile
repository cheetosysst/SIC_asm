BUILD_DIR=../build/misc
HEADER_DIR=../headers

CC = gcc
CPP = g++
LD = ld

CPP_SRCS = $(wildcard *.cpp)
CPP_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPP_SRCS))

CFLAGS = -I $(HEADER_DIR) -g -Wall -Wextra -Werror

all: $(CPP_OBJS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	$(CPP) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*