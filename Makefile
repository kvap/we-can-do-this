CXX = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system 
CFLAGS = -Wfatal-errors -c -g -std=c++14 -Isources
ifeq ($(THEOS),Darwin)
    LIBS += -lGL
else
    LIBS += -framework OpenGL -L/usr/local/Cellar/sfml/2.4.2/lib
    CFLAGS += -framework OpenGL -I/usr/local/Cellar/sfml/2.4.2/include
endif
LDFLAGS = -Wall $(LIBS)

TARGET_DIR = target
SOURCE_DIR = sources
OBJECT_DIR = objects

SOURCE_DIRS = $(sort $(dir $(wildcard $(SOURCE_DIR)/ $(SOURCE_DIR)/*/ $(SOURCE_DIR)/*/*/)))
OBJECT_DIRS = $(patsubst $(SOURCE_DIR)%, $(OBJECT_DIR)%, $(SOURCE_DIRS))

SOURCE_FILES = $(filter %.cpp, $(wildcard $(addsuffix *.cpp, $(SOURCE_DIRS))))
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

TARGET = $(TARGET_DIR)/wcdt

.PHONY: build rebuild clean

build: $(TARGET)
	@cp -r resources/* $(TARGET_DIR)/
	@echo $(TARGET) successfully built!

rebuild: clean build

$(TARGET): $(OBJECT_DIRS) $(TARGET_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECT_DIRS) $(TARGET_DIR):
	@mkdir $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECT_DIR)
	rm -rf $(TARGET_DIR)
