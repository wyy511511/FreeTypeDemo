CXX=g++
CXXFLAGS=-I/opt/homebrew/include/freetype2 -I/opt/homebrew/opt/opencv/include/opencv4 -L/opt/homebrew/lib -L/opt/homebrew/opt/opencv/lib -lfreetype -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -std=c++17
TARGET=my_program
SRC=my_program.cpp

$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) $(CHARS) $(SCALAR)

.PHONY: clean run

