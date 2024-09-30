#include "TonePlayer.h"

TonePlayer::TonePlayer(/* args */) {
    toneplayer_cbf_t = nullptr;
    CurrentMusic = nullptr;
    Speed = SPEED_NORMAL;
    MusicLength = 0;
    CurrentPos = 0;
}

void TonePlayer::setSpeed(uint16_t speed) { Speed = speed; }

void TonePlayer::setMusic(const MusicNode_t* music, uint16_t size) {
    if (music == nullptr) {
        CurrentMusic = nullptr;
        MusicLength = 0;
        CurrentPos = 0;
        return;
    }

    if (CurrentMusic == music) {
        return;
    }

    CurrentMusic = music;
    MusicLength = size;
    CurrentPos = 0; // 從頭開始播放
}

void TonePlayer::Play() { CurrentPos = 0; }

void TonePlayer::Stop() { CurrentPos = MusicLength; }

bool TonePlayer::Update(uint32_t tickTime) {
    if (toneplayer_cbf_t == nullptr) {
        return false;
    }

    if (CurrentPos < MusicLength) {
        if (tickTime > NextTime) {
            toneplayer_cbf_t(CurrentMusic[CurrentPos].Freq,
                             CurrentMusic[CurrentPos].Volume);
                             
            NextTime =
                tickTime + CurrentMusic[CurrentPos].Time * Speed / SPEED_NORMAL;
            CurrentPos++;
        }
        return true;
    } else if (CurrentPos == MusicLength && tickTime > NextTime) {
        toneplayer_cbf_t(0, 0);
        CurrentPos++;
    }

    return false;
}