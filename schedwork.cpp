

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool solveHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
DailySchedule& sched, unsigned int row, unsigned int col);

bool isValid(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
DailySchedule& sched, unsigned int row, unsigned int col, unsigned int id);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //initializing sched
    /*for(unsigned int a=0; a<sched.size(); a++)
    {
      for(unsigned int b=0; b<sched[0].size(); b++)
      {
        sched[a][b]=INVALID_ID;
      }
    }*/

    for(unsigned int a=0; a<avail.size(); a++)
    {
      vector<Worker_T> myVec;
      for(unsigned int b=0; b<dailyNeed; b++)
      {
        myVec.push_back(INVALID_ID);
      }
      sched.push_back(myVec);
    }

    unsigned int row=0;
    unsigned int col=0;

    bool answer = solveHelper(avail, dailyNeed, maxShifts, sched, row, col);
    return answer;



}

bool solveHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
DailySchedule& sched, unsigned int row, unsigned int col)
{
//reached the end of the schedule
 if(row==sched.size())
 {
   //checking if there are any invalid ids
  for(unsigned int a=0; a<sched.size(); a++)
   {
     for(unsigned int b=0; b<sched[0].size();b++)
     {
       if(sched[a][b]==INVALID_ID)
       {
         return false;
       }
     }
   }
   return true;
 }

 //iterate through the ids
  for(unsigned int id=0; id<avail[0].size(); id++)
  {
    if(isValid(avail, dailyNeed, maxShifts, sched, row, col, id))
    {
      sched[row][col]=id;
      if(col==dailyNeed-1)
      {
        if(solveHelper(avail, dailyNeed, maxShifts, sched, row+1, 0))
        {
          return true;
        }
        else
        {
          sched[row][col]=INVALID_ID;
        }
      }
      else
      {
        if(solveHelper(avail, dailyNeed, maxShifts, sched, row, col+1))
        {
          return true;
        }
        else
        {
          sched[row][col]=INVALID_ID;
        }
      }
    }
  }
  return false;
}

bool isValid(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
DailySchedule& sched, unsigned int row, unsigned int col, unsigned int id)
{
    bool valid=true;
    //checking if worker is available and hasn't already been scheduled and hasn't
    //reached maxShifts
    if(avail[row][id]==0)
    {
      valid=false;
    }
    else if(avail[row][id]==1)
    {
        unsigned int numAssigned = 0;
        for(unsigned int j=0; j<sched.size(); j++)
        {
          for(unsigned int k=0; k<dailyNeed; k++)
          {
            if(sched[j][k]==id)
            {
              numAssigned++;
            }
          }
        }
        if(numAssigned>=maxShifts)
        {
          valid = false;
        }

    //isValid is still true(available + less than max shifts), but we still need to check if worker hasn't already 
    //been scheduled for the same day
      if(valid==true)
      {
        for(unsigned int m=0; m<dailyNeed; m++)
        {
          if(sched[row][m]==id)
          {
            valid = false;
          }
        }
      }
    }

    return valid;

}