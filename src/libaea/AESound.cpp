#define _CRT_SECURE_NO_WARNINGS

#include "AESound.h"
#include <stdio.h>
#include <iostream>

using namespace aeoal;

AESound::AESound() {

}

AESound::~AESound() {

}

bool AESound::initializeAudio() {

	return true;
}

void AESound::play() {

	alSourcePlay(source);
}

void AESound::pause() {

	alSourcePause(source);
}

void AESound::stop() {

	alSourceStop(source);
}

bool AESound::release() {

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	return true;
}

bool AESound::loadWAVFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format) {

	FILE* soundFile = NULL;
	WAVE_FORMAT waveFormat;
	RIFF_HEADER riffHeader;
	WAVE_DATA waveData;
	unsigned char* data;

	try {

		soundFile = fopen(filename.c_str(), "rb");

		if (!soundFile) throw (filename);

		//Read the first chunk of data into the struct
		fread(&riffHeader, sizeof(RIFF_HEADER), 1, soundFile);

		//Check for the presence of the RIFF and WAVE tags
		if ((riffHeader.chunkID[0] != 'R' ||
			 riffHeader.chunkID[1] != 'I' ||
			 riffHeader.chunkID[2] != 'F' ||
			 riffHeader.chunkID[3] != 'F') ||
			(riffHeader.format[0] != 'W' ||
			 riffHeader.format[1] != 'A' ||
			 riffHeader.format[2] != 'V' ||
			 riffHeader.format[3] != 'E'))
			throw (std::string("Invalid RIFF or WAVE Header"));

		//Read in the 2nd chunk
		fread(&waveFormat, sizeof(WAVE_FORMAT), 1, soundFile);

		//Check for the 'fmt' tag
		if (waveFormat.subChunkID[0] != 'f' ||
			waveFormat.subChunkID[1] != 'm' ||
			waveFormat.subChunkID[2] != 't' ||
			waveFormat.subChunkID[3] != ' ')
			throw (std::string("Invalid WAVE Format"));

		//Check for extra parameters
		if (waveFormat.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		//Read in the last byte of data before the sound file
		fread(&waveData, sizeof(WAVE_DATA), 1, soundFile);

		//Check for the 'data' tag
		if (waveData.subChunkID[0] != 'd' ||
			waveData.subChunkID[1] != 'a' ||
			waveData.subChunkID[2] != 't' ||
			waveData.subChunkID[3] != 'a')
			throw (std::string("Invalid Data Header"));

		//Allocate memory for sound data
		data = new unsigned char[waveData.subChunk2Size];

		//Read in the sound data into the soundData variable
		if (!fread(data, waveData.subChunk2Size, 1, soundFile))
			throw (std::string("Error: Unable to load WAVE data into struct!"));

		//Assign the variables passed into function their proper
		//values from the structs
		*size = waveData.subChunk2Size;
		*frequency = waveFormat.sampleRate;

		//The format is determined by looking at the number of
		//channels and the bits per sample value.
		if (waveFormat.numChannels == 1) {
			if (waveFormat.bitsPerSample == 8)
				*format = AL_FORMAT_MONO8;
			else if (waveFormat.bitsPerSample == 16)
				*format = AL_FORMAT_MONO16;
		}
		else if (waveFormat.numChannels == 2) {
			if (waveFormat.bitsPerSample == 8)
				*format = AL_FORMAT_STEREO8;
			else if (waveFormat.bitsPerSample == 16)
				*format = AL_FORMAT_STEREO16;
		}

		std::cout << "Sound File: " << filename.substr(filename.find_last_of("/\\") + 1) << std::endl;
		std::cout << "Audio Format: " << waveFormat.audioFormat << std::endl;
		std::cout << "Byte Rate: " << waveFormat.byteRate << std::endl;
		std::cout << "Sample Rate: " << waveFormat.sampleRate << std::endl;
		std::cout << "Number of Channels: " << waveFormat.numChannels << std::endl;
		std::cout << "Bits Per Sample: " << waveFormat.bitsPerSample << std::endl;

		//Create an OpenAL buffer and check for success
		alGenBuffers(1, buffer);
		
		//Put the data into the OpenAL buffer and check for success
		alBufferData(*buffer, *format, (void*)data, *size, *frequency);

		//Clean up and return true if successful
		fclose(soundFile);
		return true;
	}
	catch (std::string & error) {

		//Catch statement if a string is thrown
		std::cerr << error << " in trying to load " << filename << std::endl;

		//Clean up memory if WAVE failed to load
		if (soundFile != NULL) 
			fclose(soundFile);

		//Return false to indicate WAVE failed to load.
		return false;
	}
}
