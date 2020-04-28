#ifndef ACC_MEMORY_READER_H
#define ACC_MEMORY_READER_H

#include <GL/gl3w.h>
#include "SharedFileOut.h"
 
namespace DaFACC 
{
	enum class AccDataSet {
		DASHBOARD,
		TELEMETRY,     
	};

	/**
	 * Structure containing only the data most commonly shown
	 * on a GT3 car electronic dashboard
	 */
	struct DashBoardData
	{
		// realtime dash data (from physics pagefile)
		int   currentGear = 0;
		int   currentRPM = 0;
		float currentKPH = 0;

		// realtime dash data (from graphics pagefile)
		char  currentTime[15] = "0.0";
		char  bestTime[15] = "0.0";
		char  split[15] = "0.0";
		int   ABSLevel = 0;
		int   EMLevel = 0;
		int   TCLevel = 0;
		int   currentPosition = 0;
		int   completedLaps = 0;

		// needed car specs (from statics pagefile)
		char  carModel[33] = "";
		int   maxRPM;
		float maxFuel;
	};

	/**
	* Structure containing most of the car telemetry data generally
	* accessible to race engineers but useful to a driver in a sim context
	* (ex: tires temparature, suspension damage, etc.).
	*/
	struct TelemetryData
	{
		// Todo
		// Idea here is to make a dashboard with the information a driver could
		// normally request from a race engineer through radio communication 
		// (which is obviously not an available option to sim racers).
	};

	struct AccMemoryElement
	{
		HANDLE hMapFile;
		unsigned char* mapFileBuffer;
	};

    /**
	 * Assetto Corsa Competizione data manager
	 * ----------------------------------------
	 * The objective of this class is mainly to abstract anything related
	 * to ACC from the the rest of our program. To do so, it reads data from
	 * the game's shared memory and organizes the obtained data in easy to 
	 * read data structures. 
	 */
	class AccDataManager {
	public:
		bool updateDataset(AccDataSet toUpdate);
		bool updateAll();

		void reset(AccDataSet toReset);
		void resetAll();

		const DashBoardData& getDashboardData() const;

		AC_STATUS currentStatus = AC_OFF;

	private:
		AccMemoryElement _graphics;
		AccMemoryElement _physics;
		AccMemoryElement _static;

		DashBoardData _dashData;
	};
}

#endif
