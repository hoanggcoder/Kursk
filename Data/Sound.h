#ifndef SOUND_H
#define SOUND_H
#include<map>
#include<string>
#include<iostream>
#include<SDL_mixer.h>
#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap=std::map<const char*, Mix_Chunk*>;
using MusicMap=std::map<const char*,Mix_Music*>;
class Sound
{
public:
    void Clean();
    void PlayMusic(const char* filedir);
    void LoadMusic(const char* filedir);
    void PlayEffect(const char* filedir);
    void LoadEffect(const char* filedir);
    static Sound* Instance(){ return s_Instance=(s_Instance!=nullptr)? s_Instance:new Sound();}

private:
    Sound();
    MusicMap m_MusicMap;
    EffectMap m_EffectMap;
    static Sound* s_Instance;
};
#endif // SOUND_H
