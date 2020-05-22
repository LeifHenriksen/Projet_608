CC := g++
CFLAGS := -Wall -g
TARGET := run


SRCS := $(wildcard naive.cpp boyer_moore.cpp main.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -std=c++11 -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -std=c++11 -c $<
clean:
	rm -rf $(TARGET) *.o
