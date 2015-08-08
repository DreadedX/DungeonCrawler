#ifndef AUDIO_H
#define AUDIO_H

namespace Audio {

    struct LocationData{

	ALfloat   sourcePos[3];
	ALfloat   sourceVel[3];
	ALfloat   listenerPos[3];
	ALfloat   listenerVel[3];
	ALfloat   listernerOri[6];
    };

    void init();
    void play();
};

#endif

