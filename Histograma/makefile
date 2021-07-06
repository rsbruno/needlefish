CC=gcc
#CCFLAGS=-Wall
CCFLAGS=-g
LDFLAGS=
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=histograma
IMG=mona.pgm

all: $(TARGET)

$(TARGET): $(OBJECTS);\
    $(CC) -g -o $@ $^ $(LDFLAGS);\
    ./$(TARGET) $(IMG);\
    eog saida.pgm

%.o: %.c %.h;\
    $(CC) $(CCFLAGS) -c $<

%.o: %.c;\
    $(CC) $(CCFLAGS) -c $<

clean:;\
    rm -f *.o *-*.pgm $(TARGET);\