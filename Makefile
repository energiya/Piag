CC = cc
LFLAGS = -L/usr/local/lib
LIBS = -lwiringPi
MAIN = piag
SRCS = src/$(MAIN).c src/PCD8544/PCD8544.c
all:
	$(CC) -o $(MAIN) $(SRCS) $(LFLAGS) $(LIBS)
clean:
	$(RM) $(MAIN)

