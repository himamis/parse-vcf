CC=g++

SOURCES = \
	DefaultHandler.cpp \
	VCFParser.cpp \
	MetaParser.cpp \
	EntryParser.cpp \
	Lexer.cpp \
	Common.cpp
	
INCLUDES = \
	DefaultHandler.h \
	MetaInformation.h \
	Sample.h \
	SNVEntry.h \
	VCFParser.h \
	Common.h \
	Lexer.h \
	MetaParser.h \
	EntryParser.h \

TEST_SOURCES = \
	main.cpp \
	test-simple.cpp

SRCDIR = src
OBJDIR = obj
TESTSDIR = test

CFLAGS =-Isrc

OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
TEST_OBJECTS := $(addprefix $(OBJDIR)/,$(TEST_SOURCES:.cpp=.o))

all: dirs tests

dirs:
	mkdir -p $(OBJDIR)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS)  -g -O0 -c $< -o $@
	
$(OBJDIR)/%.o: $(TESTSDIR)/%.cpp
	$(CC) $(CFLAGS) -g -O0 -c $< -o $@
	
tests: $(TEST_OBJECTS) $(OBJECTS) $(addprefix $(SRCDIR)/,$(INCLUDES))
	$(CC) $(CFLAGS) -o test_run $(OBJECTS) $(TEST_OBJECTS) $(LFLAGS) $(LIBS)
	./test_run -r compact

clean:
	rm -rf obj test_run
