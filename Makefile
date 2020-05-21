CC := g++
CFLAGS := -Wall -g
TARGET := test


SRCS := $(wildcard naive.cpp boyer_moore.cpp test.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o