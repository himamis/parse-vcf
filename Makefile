CC=g++
SOURCES = main.cpp
OBJS = $(SOURCES:.cpp=.o)

all: parsevcf

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
parsevcf: $(OBJS)
	$(CC) $(CFLAGS) -o t $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	
clean:
	rm -f *.o