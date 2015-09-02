#include <iostream>
#include "GVStateLookup.h"

char *
lookupStateName (enum XMLState state)
{
  int loopVar;
                                                                                
  for (loopVar = 0; loopVar < NbrStates; loopVar++)
    if (stateLookup[loopVar].stateVal == state)
      return stateLookup[loopVar].stateName;
                                                                                
  return "UndefinedState";
}

