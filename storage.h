#undef ITEM_INFO

#if defined(STORAGE_PASS1)

#include <stdio.h>
#include <stdlib.h>

#  define ITEM_INFO(label) label##State,

   enum ERR_CODES {SUCCESS, FAILURE, NO_DATA};

   enum ITEM_VALS {UnknownState = -1,
#else
#  define STORAGE_PASS1
#  include "storage.h"
#  undef STORAGE_PASS1
#  if defined(ENUM_ONLY)
#    define ITEM_INFO(label)
#  else
#    define ITEM_INFO(label) {#label, label##State},
#  endif

#if !defined(ENUM_ONLY)
#define MAX_DOC_ITEMS  500

typedef struct docItem {
  char   *data[MAX_DOC_ITEMS];
  int     size[MAX_DOC_ITEMS];
  int     count;
  int     retrieved;
} DOC_ITEM;

struct document {
  DOC_ITEM tag[NUM_ITEMS];
} bibDoc;

struct _itemLookup {
  char *itemName;
  enum ITEM_VALS itemVal;
} itemLookup[] = {

#endif
#endif

#include "item_defs.h"

#if defined(STORAGE_PASS1)
 NUM_ITEMS};

#else
#  if !defined(ENUM_ONLY)
  {NULL}};

#  endif
int            initItemLookup(void);
enum ITEM_VALS lookupItem(const char *itemName);
enum ERR_CODES storeItemData(enum ITEM_VALS type, char *itemText);
int            getItemCount(enum ITEM_VALS type);
char          *getItemData(enum ITEM_VALS type);
char          *lookupItemName(enum ITEM_VALS type);
void           dumpStorage(enum ITEM_VALS type);
char          *getItemName(enum ITEM_VALS type);

#define stringize(x)  #x


#endif

#undef ITEM_INFO



