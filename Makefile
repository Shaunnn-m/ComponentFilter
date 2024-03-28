CXX = g++
CXXFLAGS = -Wall -std=c++20
TARGET = pgm_processor
TEST_TARGET = pgm_processor_test

# Object files for the main application
OBJS = main.o PGMimageProcessor.o ConnectedComponent.o

# Object files for the test suite
TEST_OBJS = TestMain.o PGMimageProcessor.o ConnectedComponent.o

# Rule to link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling and running the test suite
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)
	./$(TEST_TARGET)

# Phony target to clean the build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
