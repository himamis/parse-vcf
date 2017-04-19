CC=g++

SOURCES = \
	DefaultHandler.cpp \
	VCFParser.cpp \
	meta_parser.cpp \
	entries_parser.cpp \
	lexer.cpp \
	parser.cpp

TEST_SOURCES = \
	main.cpp \
	test-simple.cpp

SRCDIR = src
OBJDIR = obj
TESTSDIR = test

CFLAGS = -Iinclude -Isrc

OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
TEST_OBJECTS := $(addprefix $(OBJDIR)/,$(TEST_SOURCES:.cpp=.o))

all: dirs tests

dirs:
	mkdir -p $(OBJDIR)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -g -O0 -c $< -o $@
	
$(OBJDIR)/%.o: $(TESTSDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -g -O0 -c $< -o $@
	
tests: $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) -o test_run $(OBJECTS) $(TEST_OBJECTS) $(LFLAGS) $(LIBS)
	./test_run

clean:
	rm -rf obj test_run
