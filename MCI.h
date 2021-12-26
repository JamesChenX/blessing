#pragma once
#include "mmsystem.h"
#include <Digitalv.h>
#pragma comment(lib,"winmm.lib")

class CMCI
{
private:
	MCIDEVICEID nDeviceID;
public:
	CMCI(void)
	{
		nDeviceID = -1;
	}
	~CMCI(void)
	{
		Close();
	}
	BOOL Open(LPTSTR lpszPath)
	{
		MCI_OPEN_PARMS mciOP;
		mciOP.lpstrDeviceType = NULL;
		mciOP.lpstrElementName = lpszPath;
		DWORD dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE, (DWORD)(LPVOID)&mciOP);
		if(dwReturn == 0)
		{
			nDeviceID = mciOP.wDeviceID;
			return TRUE;
		}
		else
		{
			nDeviceID = -1;
			return FALSE;
		}
	}
	BOOL Play()
	{
		MCI_PLAY_PARMS mciPP;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPP);
		if(dwReturn == 0)
			return TRUE;
		else
			return FALSE;
	}
	BOOL Pause()
	{
		MCI_GENERIC_PARMS mciGP;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PAUSE, MCI_NOTIFY | MCI_WAIT, (DWORD)(LPVOID)&mciGP);
		if(dwReturn == 0)
			return TRUE;
		else
	        return FALSE;
	}
	BOOL Stop()
	{
		MCI_SEEK_PARMS mciSP;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SEEK, MCI_WAIT | MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciSP);
		if(dwReturn == 0)
			return TRUE;
		else
			return FALSE;
	}
	BOOL Close()
	{
		MCI_GENERIC_PARMS mciGP;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_CLOSE, MCI_NOTIFY | MCI_WAIT, (DWORD)(LPVOID)&mciGP);
		if(dwReturn == 0)
			return TRUE;
		else
			return FALSE;
	}	
	DWORD GetCurrentPos()
	{
		MCI_STATUS_PARMS mciSP;
		mciSP.dwItem = MCI_STATUS_POSITION;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciSP);
		if (dwReturn == 0)
		{
			return mciSP.dwReturn;
		}
		else
		{
			return -1;
		}
	}
	BOOL SetVolume(int nVolumeValue)
	{
		if(nVolumeValue > 1000)
		{
			nVolumeValue = 1000;
		}
		else if(nVolumeValue < 0)
		{
			nVolumeValue = 0;
		}

		MCI_DGV_SETAUDIO_PARMS mciDSP;
		mciDSP.dwItem = MCI_DGV_SETAUDIO_VOLUME;
		mciDSP.dwValue = nVolumeValue;
		DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciDSP);
		if(dwReturn == 0)
			return TRUE;
		else
			return FALSE;
	}
};