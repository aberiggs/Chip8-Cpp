CC := g++
CFLAGS := -std=c++20 -Wall -g
TARGET := Chip8

SRCS := $(wildcard ./src/*.cpp)
OBJS := $(patsubst ./src/%.cpp,./output/%.o,$(SRCS))

all: output $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@.out $^ `sdl2-config --cflags --libs`

./output/%.o: ./src/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

output:
	@echo Creating output dir
	mkdir output

clean:
	rm -rf $(TARGET) output/*.o
