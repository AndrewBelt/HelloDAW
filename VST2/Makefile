VST2_SDK ?= VST2_SDK
TARGET := HelloVST2

FLAGS += -g
FLAGS += -O3 -march=nocona -ffast-math
FLAGS += -Wall -Wextra
FLAGS += -fPIC
FLAGS += -I$(VST2_SDK)
CXXFLAGS += -std=c++11


# Detect architecture
MACHINE = $(shell $(CC) -dumpmachine)
else ifneq (, $(findstring apple, $(MACHINE)))
	ARCH ?= mac
else ifneq (, $(findstring mingw, $(MACHINE)))
	ARCH ?= win
ifneq (, $(findstring linux, $(MACHINE)))
	ARCH ?= lin
else
$(error Could not determine architecture)
endif


# Architecture-dependent variables
ifeq ($(ARCH), mac)
	FLAGS += -arch i386 -arch x86_64
	CXXFLAGS += -stdlib=libc++
	LDFLAGS += -stdlib=libc++
	FLAGS += -mmacosx-version-min=10.7
	LDFLAGS += -mmacosx-version-min=10.7
	LDFLAGS += -arch i386 -arch x86_64
	LDFLAGS += -bundle
	BUNDLE := $(TARGET).vst
endif
ifeq ($(ARCH), win)
	LDFLAGS += -shared -static
	TARGET := $(TARGET).dll
endif
ifeq ($(ARCH), lin)
$(error Build not available on Linux, although it's possible with modifications)
endif


SOURCES += HelloVST.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/audioeffect.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/audioeffectx.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/vstplugmain.cpp


all: dist

dist: $(TARGET)
ifeq ($(ARCH), mac)
	strip -S $(TARGET)
	mkdir -p $(BUNDLE)/Contents
	cp Info.plist $(BUNDLE)/Contents/Info.plist
	cp PkgInfo $(BUNDLE)/Contents/
	mkdir -p $(BUNDLE)/Contents/MacOS
	cp $(TARGET) $(BUNDLE)/Contents/MacOS/
endif
ifeq ($(ARCH), win)
	strip -s $(TARGET)
endif

clean:
	rm -rfv build $(TARGET)


OBJECTS := $(patsubst %, build/%.o, $(SOURCES)) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

build/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
