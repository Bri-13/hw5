#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool search(size_t spot, vector<size_t>& shifts, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t numDays, size_t numWorkers, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    vector<size_t> shifts(numWorkers, 0);

    sched.resize(numDays);
    for(size_t i=0; i<numDays; i++){
      sched[i].resize(dailyNeed);
      for(size_t j=0; j<dailyNeed; j++){
        sched[i][j] = INVALID_ID;
      }
    }

    // recursive helper function
    return search(0, shifts, avail, dailyNeed, maxShifts, numDays, numWorkers, sched);
}

bool search(size_t spot, vector<size_t>& shifts, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t numDays, size_t numWorkers, DailySchedule& sched){
  // base case
  if(spot == numDays*dailyNeed){
    return true;
  }
  
  size_t day = spot/dailyNeed;
  size_t position = spot%dailyNeed;

  for(size_t i=0; i<numWorkers; i++){
    // check if worker is available and has not reached max shifts
    if(!avail[day][i] || (shifts[i] >= maxShifts)){
      continue;
    }

    if(find(sched[day].begin(), sched[day].begin() + position, i) != sched[day].begin() + position){
      continue;
    }

    sched[day][position] = i;
    shifts[i]++;
    bool status = search(spot+1, shifts, avail, dailyNeed, maxShifts, numDays, numWorkers, sched);
    if(status){
      return true;
    }
    shifts[i]--;
    sched[day][position] = INVALID_ID;
  }

  return false;
}