#include "TonePlayer.h"

TonePlayer::TonePlayer(/* args */)
{
    toneplayer_cbf_t = nullptr;
    CurrentMusic = nullptr;
    Speed = SPEED_NORMAL;
    Length = 0;
    CurrentPos = 0;
}

void TonePlayer::setSpeed(uint16_t speed){
    Speed = speed;
}

void TonePlayer::setMusic(const MusicNote_t* music, uint16_t size){
    if(music == nullptr){
        CurrentMusic = nullptr;
        Length = 0;
        CurrentPos = 0;
        return;
    }

    if(CurrentMusic == music){
        return;
    }

    CurrentMusic = music;
    Length = size;
    CurrentPos = 0;//從頭開始播放
}

void TonePlayer::Play(){

}

