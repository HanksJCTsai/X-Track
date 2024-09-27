#ifndef __TONEPLAYER_H
#define __TONEPLAYER_H

#include <stdint.h>

class TonePlayer {
        typedef void (*TonePlayer_CallbackFunction_t)(uint32_t, uint16_t);

    public:
        typedef struct MusicNote_t {
                uint16_t Freq;
                uint16_t Time;
                uint16_t Volume;
        };

        enum PlaySpeed {
            SPEED_HALF = 512,
            SPEED_NORMAL = 256,
            SPEED_DOUBLE = 128
        };

        TonePlayer();
        ~TonePlayer() {};
        void setSpeed(uint16_t speed);
        void setMusic(const MusicNote_t* music, uint16_t size);
        void setCallback(TonePlayer_CallbackFunction_t callback) {
            toneplayer_cbf_t = callback;
        };
        void Play();
        void Play(const MusicNote_t* music, uint16_t size) {
            setMusic(music, size);
            Play();
        };
        void Stop();
        bool Update(uint32_t tickTime);

    private:
        uint16_t MusicLength;
        uint16_t CurrentPos;
        uint32_t NextTime;
        uint16_t Speed;
        const MusicNote_t* CurrentMusic;
        TonePlayer_CallbackFunction_t toneplayer_cbf_t;
};

#endif