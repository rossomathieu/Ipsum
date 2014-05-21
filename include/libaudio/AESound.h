#include <AL/al.h>
#include <AL/alc.h>
#include <string>

namespace aeoal {

	class AESound {

	public:

		AESound();
		~AESound();

		bool initializeAudio();
		bool loadWAVFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);
		
		void setSourcePitch(ALfloat *value);
		void setSourceGain(ALfloat *value);
		void setSourcePosition(ALfloat *x, ALfloat *y, ALfloat *z);
		void setSourceVelocity(ALfloat *x, ALfloat *y, ALfloat *z);
		void isLooping(ALboolean looping);

		void play();
		void pause();
		void stop();

		bool release();

	private:

		/** 
		 * A struct that holds the RIFF data of the WAVE file.
		 * The RIFF data is the metadata that hold information
		 * pertaining to the ID, size, and format of the WAVE file.
		 */
		struct RIFF_HEADER {

			char chunkID[4];
			long chunkSize;
			char format[4];
		};

		/**
		 * A struct that holds the fmt subchunk data for WAVE files.
		 */
		struct WAVE_FORMAT {

			char subChunkID[4];
			long subChunkSize;
			short audioFormat;
			short numChannels;
			long sampleRate;
			long byteRate;
			short blockAlign;
			short bitsPerSample;
		};

		/**
		 * A struct that hold the actual data of the WAVE file.
		 */
		struct WAVE_DATA {

			char subChunkID[4];
			long subChunk2Size;
		};

		struct FORM_HEADER {

			char chunkID[4];
			long chunkSize;
			char format[4];
			char chunks[];
		};

		struct COMM_FORMAT {

			char subChunkID[4];
			long subChunkSize;
			short numChannels;
			unsigned long numSampleFrames;
			short sampleSize;
			long double sampleRate;
		};

		struct AIFC_DATA {

			char subChunkID[4];
			long subChunk2Size;
			unsigned long offset;
			unsigned long blockSize;
			unsigned char soundData[];
		};

		ALfloat listenerOrient[6];
		ALuint buffer, source;
		ALenum format;
		ALsizei size, freq;
	};
}
