CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = midi-generator
JGRS := $(wildcard *.jgr)
JPGS := $(JGRS:.jgr=.jpg)

all: clean build run convert tidy

clean:
	chmod +x clean.sh
	./clean.sh

build:
	$(CXX) $(CXXFLAGS) midi-generator.cpp -o $(TARGET)

run: build
	for number in 1 2 3 4 5 ; do \
		./$(TARGET) sample$$number.txt ; \
	done

convert:
	@for file in *.jgr; do \
		if [ -f "$$file" ]; then \
			base=$${file%.jgr}; \
			echo "Converting $$file -> $$base.jpg"; \
			jgraph -P "$$file" | ps2pdf - - | magick -density 300 - -quality 100 "$$base.jpg"; \
		fi \
	done

tidy: 
	chmod +x tidy.sh
	./tidy.sh