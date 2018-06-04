VST2_SDK ?= VST2_SDK
TARGET := HelloVST2

FLAGS += -g
FLAGS += -O3 -march=nocona -ffast-math
FLAGS += -Wall -Wextra -Wno-unused-parameter
FLAGS += -fPIC
FLAGS += -I$(VST2_SDK)
CXXFLAGS += -std=c++11


# Detect architecture
MACHINE = $(shell $(CC) -dumpmachine)
ifneq (, $(findstring apple, $(MACHINE)))
	ARCH_MAC = 1
else ifneq (, $(findstring mingw, $(MACHINE)))
	ARCH_WIN = 1
else ifneq (, $(findstring linux, $(MACHINE)))
	ARCH_LIN = 1
else
$(error Could not determine architecture)
endif


# Architecture-dependent variables
ifdef ARCH_MAC
	FLAGS += -arch i386 -arch x86_64
	CXXFLAGS += -stdlib=libc++
	LDFLAGS += -stdlib=libc++
	FLAGS += -mmacosx-version-min=10.7
	LDFLAGS += -mmacosx-version-min=10.7
	LDFLAGS += -arch i386 -arch x86_64
	LDFLAGS += -bundle
	BUNDLE := $(TARGET).vst
endif
ifdef ARCH_WIN
	LDFLAGS += -shared -static
	TARGET := $(TARGET).dll
endif
ifdef ARCH_LIN
$(error Build not available on Linux, although it's possible. If you can figure it out, send a PR)
endif


CFLAGS += $(FLAGS)
CXXFLAGS += $(FLAGS)

SOURCES += HelloVST2.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/audioeffect.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/audioeffectx.cpp
SOURCES += $(VST2_SDK)/public.sdk/source/vst2.x/vstplugmain.cpp


all: dist

dist: $(TARGET)
ifdef ARCH_MAC
	strip -S $(TARGET)
	mkdir -p $(BUNDLE)/Contents
	cp Info.plist $(BUNDLE)/Contents/Info.plist
	cp PkgInfo $(BUNDLE)/Contents/
	mkdir -p $(BUNDLE)/Contents/MacOS
	cp $(TARGET) $(BUNDLE)/Contents/MacOS/
endif
ifdef ARCH_WIN
	strip -s $(TARGET)
endif

install: dist
ifdef ARCH_MAC
	sudo cp -R $(BUNDLE) /Library/Audio/Plug-Ins/VST/
endif
ifdef ARCH_WIN
	mkdir -p /c/Program\ Files/Steinberg/VstPlugins
	cp -R $(TARGET) /c/Program\ Files/Steinberg/VstPlugins/
endif

uninstall:
ifdef ARCH_MAC
	sudo rm -rfv /Library/Audio/Plug-Ins/VST/$(BUNDLE)
endif
ifdef ARCH_WIN
	rm /c/Program\ Files/Steinberg/VstPlugins/$(TARGET)
endif

clean:
	rm -rfv build $(TARGET) $(BUNDLE)


OBJECTS := $(patsubst %, build/%.o, $(SOURCES)) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

build/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
