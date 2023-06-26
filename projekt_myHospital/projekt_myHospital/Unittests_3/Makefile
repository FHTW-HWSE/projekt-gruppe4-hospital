CXX = g++
CXXFLAGS = -std=c++11 -Wno-write-strings
INCLUDES = -I./catch2/
SOURCES = test_add_patient.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = test_add_patient

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(INCLUDES) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	/bin/rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
