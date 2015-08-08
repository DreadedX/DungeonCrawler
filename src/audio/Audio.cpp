# include "Standard.h"

namespace Audio {

    struct AudioData {
	ALenum      format;
	ALvoid*     data;
	ALsizei     size;
	ALsizei     freq;
	ALboolean   loop;
    };

    ALuint buffers[BUFFER_COUNT_AL];
    int error;

    void init() {

	// alGenBuffers(BUFFER_COUNT_AL, buffers);
	// if((error = alGetError()) != AL_NO_ERROR) {
	//     Log::print(String::format("alGenBuffers: %d", error), ERROR);
	//     exit(-1);
	//     return;
	// }
        //
	// AudioData jump;
        //
	// alutLoadWAVFile("audio/jump.wav", &jump.format, &jump.data, &jump.size, &jump.freq, &jump.loop);
	// if((error = alGetError()) != AL_NO_ERROR) {
	//     Log::print(String::format("alutLoadWAVFile: %d", error), ERROR);
	//     exit(-1);
	//     return;
	// }
        //
    }

    void play() {

    }
}
