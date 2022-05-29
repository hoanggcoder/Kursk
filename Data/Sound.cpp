#include "Sound.h"
Sound* Sound::s_Instance=nullptr;

Sound::Sound()
{
    if(Mix_OpenAudio(FREQ,MIX_DEFAULT_FORMAT,2,CHUNK_SIZE)<0)
        std::cerr<<Mix_GetError()<<std::endl;
}

void Sound::PlayMusic(const char* filedir)
{
    if(Mix_PlayMusic(m_MusicMap[filedir],-1)==-1)
        std::cerr<<Mix_GetError()<<": "<<filedir<<std::endl;
}
void Sound::LoadMusic(const char* filedir)
{
    Mix_Music * music=Mix_LoadMUS(filedir);
    if(music!=nullptr)
    {
        m_MusicMap[filedir]=music;
    }
    else
    {
        std::cerr<<Mix_GetError()<<":"<<filedir<<std::endl;
    }
}
void Sound::PlayEffect(const char* filedir)
{
    if(Mix_PlayChannel(-1,m_EffectMap[filedir],0)==-1)
        std::cerr<<Mix_GetError()<<":"<<filedir<<std::endl;
}
void Sound::LoadEffect(const char* filedir)
{
    Mix_Chunk * effect=Mix_LoadWAV(filedir);
    if(effect!=nullptr)
    {
        m_EffectMap[filedir]=effect;
    }
    else
    {
        std::cerr<<Mix_GetError()<<": "<<filedir<<std::endl;
    }
}
void Sound::Clean()
{
    m_MusicMap.clear();
    m_EffectMap.clear();
    std::cout<<"Sound cleaned!!"<<std::endl;
}


