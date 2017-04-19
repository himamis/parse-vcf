CC=g++

SOURCES = \
	main.cpp \
	DefaultHandler.cpp \
	VCFParser.cpp \
	meta_parser.cpp \
	entries_parser.cpp \
	lexer.cpp \
	parser.cpp

SRCDIR = src
OBJDIR = obj

CFLAGS = -Iinclude -Isrc

OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))

all: dirs parsevcf

dirs:
	mkdir -p $(OBJDIR)

# Compile the binary 'parsevcf' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
parsevcf: $(OBJECTS)
	$(CC) $(CFLAGS) -o parsevcf $(OBJECTS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -g -O0 -c $< -o $@
	
clean:
	rm -rf obj parsevcf
