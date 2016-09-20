#include <AL/al.h>
#include <AL/alc.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std; 
const int SRATE = 44100;
const int SSIZE = 1024;
const int BSIZE = 1024*1024;
ALbyte buffer[BSIZE];
ALint sample;

int AudioVoiceMsgFrequency = 48000;

int main(int argc, char *argv[]) {
    alGetError();

    const ALCchar *dName = alcGetString(0, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
	cout<<"ready to open device :"<< dName <<endl;
    ALCdevice *device = alcCaptureOpenDevice(dName, AudioVoiceMsgFrequency, AL_FORMAT_MONO16, AudioVoiceMsgFrequency / 5);    
   	// 若挂掉，则注释上一行，替换下一行
	//ALCdevice *device = alcCaptureOpenDevice(NULL, AudioVoiceMsgFrequency, AL_FORMAT_MONO16, AudioVoiceMsgFrequency / 5);    
	if ( !device ){
		cout<<"open device error" <<endl;
		return 0;
	}

    alcCaptureStart(device);
										        
    int i = 20;
    while (i--) {
		//bzero(buffer, BSIZE*sizeof(ALbyte));

		sleep(1); 
		alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei)sizeof(ALint), &sample);
		cout<<"alcGetIntegerv sample:"<< sample << " ";
		if ( alcGetError(device) != ALC_NO_ERROR ){
			cout << endl << " alcGetIntegerv error "<<endl;
			break;
		}
		if ( sample <= 0 ) {
			cout << endl;
			continue;
		}
		alcCaptureSamples(device, (ALCvoid *)buffer, sample);
		cout<<"buffer size:"<< strlen((char *)buffer) <<endl;
		if ( alcGetError(device) != ALC_NO_ERROR ){
			cout << endl << " alcCaptureSamples error "<<endl;
			break;
		}
		
    }
	cout<<"capture stop"<<endl;
    alcCaptureStop(device);
	cout<<"capture stop success, close device:"<<endl;
    alcCaptureCloseDevice(device);
	cout<<"close device success"<<endl;
	device = 0;
	sleep(3);
	cout <<"exit";
	return 0;
 }
