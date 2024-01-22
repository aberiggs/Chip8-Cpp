CC := g++
CFLAGS := -Wall -g
TARGET := Chip8

SRCS := $(wildcard ./src/*.cpp)
OBJS := $(patsubst ./src/%.cpp,./output/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@.out $^

./output/%.o: ./src/%.cpp output
	$(CC) $(CFLAGS) -c $< -o $@

output:
	@echo Creating output dir
	mkdir output

clean:
	rm -rf $(TARGET) output/*.o
