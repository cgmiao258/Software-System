CXX := g++

CXXFLAGS := -Wall -std=c++17

INCLUDES := -Iinclude 

SRCDIR := src

SOURCES := $(SRCDIR)/*.cpp

INCDIR := include

HEADERS := $(INCDIR)/*.h

TARGET := ./ElectionApp

$(TARGET): $(SOURCES) $(HEADERS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCES)

.PHONY: clean

clean:
	$(RM) $(TARGET)