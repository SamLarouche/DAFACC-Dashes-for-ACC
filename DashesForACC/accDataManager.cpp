#include "accDataManager.h"

namespace DaFACC
{
	// updateDataSet(AccDataSet toUpdate)
	// updates a specific accDataSet member with latest data from shared memory.
	// return: true if updated, false if data had no reason to be updated (game is off or on pause).
	bool AccDataManager::updateDataset(AccDataSet toUpdate)
	{
		// read graphics data
		_graphics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileGraphic), TEXT("Local\\acpmf_graphics"));
		_graphics.mapFileBuffer = (unsigned char*)MapViewOfFile(_graphics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic));
		SPageFileGraphic* pfg = (SPageFileGraphic*)_graphics.mapFileBuffer;

		if (pfg->status == AC_OFF && currentStatus == AC_OFF)
		{
			UnmapViewOfFile(_graphics.mapFileBuffer);
			CloseHandle(_graphics.hMapFile);
			return false;
		}

		if (pfg->status == AC_OFF && currentStatus != AC_OFF)
		{
			currentStatus = AC_OFF;
			// reset();
			UnmapViewOfFile(_graphics.mapFileBuffer);
			CloseHandle(_graphics.hMapFile);
			return true;
		}

		if (pfg->status == AC_PAUSE)
		{
			currentStatus = AC_PAUSE; // in case it wasn't already
			UnmapViewOfFile(_graphics.mapFileBuffer);
			CloseHandle(_graphics.hMapFile);
			return false;
		}

		if (toUpdate == AccDataSet::DASHBOARD)
		{
			strcpy_s(_dashData.currentTime, (char*)pfg->currentTime);
			strcpy_s(_dashData.bestTime, (char*)pfg->bestTime);
			strcpy_s(_dashData.split, (char*)pfg->split);
			_dashData.ABSLevel = pfg->ABS;
			_dashData.EMLevel = pfg->EngineMap;
			_dashData.TCLevel = pfg->TC;
			_dashData.currentPosition = pfg->position;
			_dashData.completedLaps = pfg->completedLaps;
		}

		UnmapViewOfFile(_graphics.mapFileBuffer);
		CloseHandle(_graphics.hMapFile);

		// read static data
		_static.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileStatic), TEXT("Local\\acpmf_static"));
		_static.mapFileBuffer = (unsigned char*)MapViewOfFile(_static.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStatic));
		SPageFileStatic* pfs = (SPageFileStatic*)_static.mapFileBuffer;

		if (toUpdate == AccDataSet::DASHBOARD)
		{
			strcpy_s(_dashData.carModel, (char*)pfs->carModel);
			_dashData.maxRPM = pfs->maxRpm;
			_dashData.maxFuel = pfs->maxFuel;
		}

		UnmapViewOfFile(_static.mapFileBuffer);
		CloseHandle(_static.hMapFile);

		// read physics data
		_physics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), TEXT("Local\\acpmf_physics"));
		_physics.mapFileBuffer = (unsigned char*)MapViewOfFile(_physics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
		SPageFilePhysics* pfp = (SPageFilePhysics*)_physics.mapFileBuffer;

		if (toUpdate == AccDataSet::DASHBOARD)
		{
			_dashData.currentGear = pfp->gear;
			_dashData.currentRPM = pfp->rpms;
			_dashData.currentKPH = pfp->speedKmh;
		}

		UnmapViewOfFile(_physics.mapFileBuffer);
		CloseHandle(_physics.hMapFile);

		return true;
	}

	// updateDataSet()
	// updates all accDataSet members with latest data from shared memory.
	// return: true if updated, false if data had no reason to be updated (game is off or on pause).
	bool AccDataManager::updateAll()
	{
		// todo: implement function
		return false;
	}

	// reset(AccDataSet toReset)
	// reset a specific accDataSet member to its default values.
	void AccDataManager::reset(AccDataSet toReset)
	{
		if (toReset == AccDataSet::DASHBOARD)
		{
			DashBoardData defaultDashData;
			_dashData = defaultDashData;
		}
	}

	// resetAll()
	// reset all accDataSet members to their default values.
	void AccDataManager::resetAll()
	{
		DashBoardData defaultDashData;
		_dashData = defaultDashData;
	}

	const DashBoardData& AccDataManager::getDashboardData() const
	{
		return _dashData;
	}
}