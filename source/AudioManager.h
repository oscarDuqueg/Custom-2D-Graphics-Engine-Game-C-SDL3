#pragma once
#include "AtomicWrapper.h"
#include "Stream.h"

#include <SDL3/SDL_audio.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <exception>
#include <thread>

//Para controlar cuando hay que terminar los threads
static std::atomic<bool> shouldHaltAudio = false;
static std::vector<AtomicWrapper<bool>> threadsDone;

#define AM AudioManager::GetInstance()

class AudioManager {
	//singleton
public:
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

	//Abre un dispositivo de audio
	bool Init()
	{
		try
		{
			_audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

			if (_audioDevice == 0)
				throw std::runtime_error(SDL_GetError());

			SDL_ResumeAudioDevice(_audioDevice);

			return true;
		}
		catch (std::exception& exception)
		{
			std::cout << "Error: " << exception.what();
			return false;
		}

	}

	//Fundamental llamar antes de cerrar el programa
	void HaltAudio()
	{
		shouldHaltAudio = true;

		int size = threadsDone.size();
		for (int i = 0; i < size; )
		{
			if (threadsDone.at(i)._a)
				i++;
		}
	}

	//Lee y guarda datos de un .wav a partir de su ruta
	bool LoadSoundData(std::string path)
	{
		if (_soundData.find(path) != _soundData.end())
			return false;

		SoundData* soundData = new SoundData();

		try
		{
			//Cargar el wav desde la ruta
			if (!SDL_LoadWAV(
				path.c_str(),
				&soundData->spec,
				&soundData->wavData,
				&soundData->wavDataLenght
			))
			{
				throw SDL_GetError();
			}

			//Guardar la informacion de este sonido
			_soundData[path] = soundData;

			return true;
		}
		catch(std::exception& exception)
		{
			delete soundData;
			std::cout << "Error" << exception.what();
			return false;
		}
	}

	//Crear un nuevo stream a partir de los datos del .wav aociado a la rut
	void PlaySound(std::string path)
	{
		if (_soundData.find(path) == _soundData.end())
			return;

		//Creamos el thread
		threadsDone.push_back(std::atomic<bool>(false));

		std::thread thread(&AudioManager::PlaySoundCallBack, this, path, (threadsDone.size() - 1));
		thread.detach();
	}

	void Mute()
	{
		if (_muted)
			return;
		SDL_PauseAudioDevice(_audioDevice);
		_muted = true;
	}
	void UnMute()
	{
		if (!_muted)
			return;

		SDL_ResumeAudioDevice(_audioDevice);
		_muted = false;
	}

	SoundData* GetSoundData(std::string path)
	{
		if (_soundData.find(path) == _soundData.end())
			return nullptr;

		return _soundData[path];
	}

private:
	AudioManager() = default;
	AudioManager(AudioManager&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	~AudioManager()
	{
		//Limpiar los datos de sonido
		for (std::map<std::string, SoundData*>::iterator it = _soundData.begin(); it != _soundData.end(); it++)
		{
			delete it->second;
		}
		_soundData.clear();
	}

	void PlaySoundCallBack(std::string path, int pos)
	{
		Stream stream = Stream(_soundData[path]->spec, _audioDevice);
		stream.CheckPlayback(_soundData[path], shouldHaltAudio);
		threadsDone[pos] = AtomicWrapper<bool>(std::atomic<bool>(true));
	}

	bool _muted = false;
	SDL_AudioDeviceID _audioDevice = 0;

	std::map<std::string, SoundData*> _soundData;
};