# Make the three executables, one for each scheduler

CC = g++
CFLAGS = -Wall -Werror -std=c++20
FILES = driver.cpp loader.cpp simulator.cpp pcb.cpp

all: fifo sjf rr

fifo:
    $(CC) $(CFLAGS) -o fifo $(FILES)

sjf:
    $(CC) $(CFLAGS) -o sjf $(FILES)

rr:
    $(CC) $(CFLAGS) -o rr $(FILES)

clean:
    rm -f fifo sjf rr