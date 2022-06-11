CC=gcc
LD=ld

BUILD_DIR=build
HEADER_DIR=headers
SUBDIR=asm misc

C_SOURCES = $(foreach dir, $(SUBDIR), $(wildcard $(dir)/*.cpp))
BIN_OBJECTS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(C_SOURCES))

TARGET=sic

.PHONY: $(SUBDIR)

all: $(SUBDIR)
	g++ -o $(TARGET) $(BIN_OBJECTS)

$(SUBDIR):
	mkdir -p $(BUILD_DIR)/$@
	make -C $@

test:
	diff sampleObject.txt export.txt --color="always"

clean:
	rm -r build/*
