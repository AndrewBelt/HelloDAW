#include <stdio.h>
#include "public.sdk/source/vst2.x/audioeffectx.h"


static const int NUM_INPUTS = 8;
static const int NUM_OUTPUTS = 8;
static const int NUM_PARAMS = 8;


class HelloVST2 : public AudioEffectX {
private:
	float params[NUM_PARAMS];

public:
	HelloVST2(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, 0, NUM_PARAMS) {
		isSynth(true);
		setNumInputs(NUM_INPUTS);
		setNumOutputs(NUM_OUTPUTS);

		// Single quotes to create a unique 4-byte integer for your plugin
		setUniqueID('HELO');
		canProcessReplacing();
	}

	bool getVendorString(char *text) override {
		snprintf(text, kVstMaxProductStrLen, "Hello");
		return true;
	}

	bool getEffectName(char *name) override {
		snprintf(name, kVstMaxEffectNameLen, "HelloVST2");
		return true;
	}

	bool getProductString(char *text) override {
		snprintf(text, kVstMaxVendorStrLen, "HelloVST2");
		return true;
	}

	void setParameter(VstInt32 index, float value) override {
		params[index] = value;
		printf("Set parameter %d: %f\n", index, value);
	}

	float getParameter(VstInt32 index) override {
		return params[index];
	}

	void getParameterLabel(VstInt32 index, char *label) override {
		snprintf(label, kVstMaxParamStrLen, "");
	}

	void getParameterDisplay(VstInt32 index, char *text) override {
		snprintf(text, kVstMaxParamStrLen, "%0.2f", params[index]);
	}

	void getParameterName(VstInt32 index, char *text) override {
		snprintf(text, kVstMaxParamStrLen, "%d", index);
	}

	VstInt32 getVendorVersion() override {
		return 0;
	}

	VstInt32 processEvents(VstEvents *events) override {
		for (int i = 0; i < events->numEvents; i++) {
			VstEvent *event = events->events[i];
			if (event->type == kVstMidiType) {
				VstMidiEvent *midiEvent = (VstMidiEvent*) event;
				uint8_t status = midiEvent->midiData[0];
				uint8_t data1 = midiEvent->midiData[0];
				uint8_t data2 = midiEvent->midiData[0];
				printf("MIDI: %02x %02x %02x\n", status, data1, data2);
			}
		}
		return 0;
	}

	void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) override {
		// VstTimeInfo *timeInfo = getTimeInfo(0);
		// if (timeInfo->flags & kVstPpqPosValid)
		// 	printf("Transport position (in quarter notes): %f\n", timeInfo->ppqPos);

		// Apply gain of 0.5 to all samples
		for (int i = 0; i < sampleFrames; i++) {
			for (int c = 0; c < NUM_INPUTS; c++) {
				outputs[c][i] = inputs[c][i] * 0.5f;
			}
		}
	}
};


AudioEffect *createEffectInstance (audioMasterCallback audioMaster) {
	return new HelloVST2(audioMaster);
}
