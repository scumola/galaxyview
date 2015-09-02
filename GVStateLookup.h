#undef ITEM_INFO
#if defined(STATELOOKUP_PASS1)

#  define ITEM_INFO(label) label##State,

   enum XMLState {UnknownState = -1,
#else
#  define STATELOOKUP_PASS1
#  include "GVStateLookup.h"
#  undef STATELOOKUP_PASS1
#  if defined(ENUM_ONLY)
#    define ITEM_INFO(label)
#  else
#    define ITEM_INFO(label) {#label, label##State},
#  endif

#if !defined(ENUM_ONLY)
static struct _stateLookup {
  char *stateName;
  enum XMLState stateVal;
} stateLookup[] = {

#endif
#endif

#include "GVStateDefs.h"

#if defined(STATELOOKUP_PASS1)
 NbrStates};

#else
#  if !defined(ENUM_ONLY)
  {NULL}};
char *
lookupStateName (enum XMLState state);

#  endif


/*
  unimplimented - this will take a state name and return the value. In
  the code originally written (from another project) I was getting the
  name from a file and had to return a value.

  this function does a bsort() on the structure as the lookup does a
  bsearch(). 

  int            initStateLookup(void);
  enum XMLState lookupState(const char *stateName);

  original code for this comes from the storage.c and storage.h
  files which are archived here for reference. 

  *** THEY ARE NOT USED IN THE ACTUAL COMPILATION OF THE PROGRAM ***

*/

#define stringize(x)  #x


#endif

#undef ITEM_INFO



