CC=g++
SOURCES = main.cpp DefaultHandler.cpp VCFParser.cpp parser.cpp lexer.cpp
OBJS = $(SOURCES:.cpp=.o)

all: parsevcf

# Compile the binary 'parsevcf' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
parsevcf: $(OBJS)
	$(CC) $(CFLAGS) -o parsevcf $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -g -O0  -c $<
	
clean:
	rm -f *.o