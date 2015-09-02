#include <string.h>

#include "storage.h"
#include "utcommon.h"

#define DEBUG            0
#define INBUF_SIZE    8192
#define ITEM_CODE_LEN   16
#define forever          1
/*====================================================================*/
/*            FUNCTION:  itemComp                                     */
/*--------------------------------------------------------------------*/

static int
itemComp (const void *item1, const void *item2)
{
  return strcmp (((struct _itemLookup *) item1)->itemName,
                 ((struct _itemLookup *) item2)->itemName);
}

/*====================================================================*/
/*            FUNCTION:  initItemLookup                               */
/*--------------------------------------------------------------------*/

int
initItemLookup ()
{
  static int initialized = 0;

  int tags;
  int items;

  if (!initialized)
    {
      initialized = 1;
      qsort ((char *) itemLookup, NUM_ITEMS, sizeof (struct _itemLookup),
             itemComp);

      memset ((void *) &bibDoc, '\0', sizeof (bibDoc));

      for (tags = 0; tags < NUM_ITEMS; tags++)
        {
          for (items = 0; items < MAX_DOC_ITEMS; items++)
            {
              bibDoc.tag[tags].data[items] = (char *) malloc (1);
            }
        }
    }
  else
    {
      for (tags = 0; tags < NUM_ITEMS; tags++)
        {
          bibDoc.tag[tags].count = bibDoc.tag[tags].retrieved = 0;
        }
    }

  return NUM_ITEMS;
}

/*====================================================================*/
/*            FUNCTION:  lookupItem                                   */
/*--------------------------------------------------------------------*/
enum ITEM_VALS
lookupItem (const char *itemName)
{
  struct _itemLookup srchItem;
  struct _itemLookup *dataItem;

  srchItem.itemName = strdup (itemName);

/*  fprintf(stderr, "Looking up TAG--->%s\n", itemName);  */

  dataItem = (struct item *) bsearch ((void *) &srchItem, (void *)
itemLookup,
                                    NUM_ITEMS,
                                sizeof (srchItem),
                                itemComp);

  free (srchItem.itemName);

  if (dataItem)
    return dataItem->itemVal;
  else
    return UNKNOWN_ITEM;
}

/*====================================================================*/
/*            FUNCTION: storeItemData                                 */
/*--------------------------------------------------------------------*/
enum ERR_CODES
storeItemData (enum ITEM_VALS type, char *itemText)
{
  int itemTextLen;              /* how much do we have to store? */
  int tagIdx;                   /* shortcut to the member element */
  int requiredTextSize;         /* how big do we make it? */

#if DEBUG == 1
  fprintf (stderr, "Came into STOREITEMDATA with ITEMTEXT-->%s\n",
           itemText);
#endif

  if (itemText == NULL)
    return NO_DATA;

  if ((itemTextLen = strlen (itemText)) == 0)
    return NO_DATA;

  if ((tagIdx = bibDoc.tag[type].count) >= MAX_DOC_ITEMS)
    return FAILURE;

/*    check to see if we have room to store this? */
#if DEBUG == 1
  fprintf (stderr, "itemTextLen:%d space available:%d tagIdx:%d\n",
           itemTextLen, bibDoc.tag[type].size[tagIdx], tagIdx);
#endif
  if (itemTextLen >= bibDoc.tag[type].size[tagIdx])
    {
/*   no, allocate the space */
      requiredTextSize = (itemTextLen + 1 +(itemTextLen >> 1));
#if DEBUG == 1
      fprintf (stderr, "requiredTextSize:%d\n", requiredTextSize);
#endif
      bibDoc.tag[type].data[tagIdx] =
        (char *) realloc (bibDoc.tag[type].data[tagIdx], requiredTextSize);

      bibDoc.tag[type].size[tagIdx] = requiredTextSize;
    }
#if DEBUG == 1
  fprintf (stderr, "ITEMTEXT Contains--->%s\n", itemText);
#endif
  strcpy (bibDoc.tag[type].data[tagIdx], itemText);
  bibDoc.tag[type].count++;

  return SUCCESS;
}
/*====================================================================*/
/*            FUNCTION:  getItemCount                                 */
/*--------------------------------------------------------------------*/

int
getItemCount (enum ITEM_VALS type)
{
  return bibDoc.tag[type].count;
}

/*====================================================================*/
/*            FUNCTION:  getItemData                                  */
/*--------------------------------------------------------------------*/
char *
getItemData (enum ITEM_VALS type)
{
  int i;

  if (bibDoc.tag[type].count == 0)
    {
      bibDoc.tag[type].retrieved = 0;
      return NULL;
    }

  bibDoc.tag[type].count--;
  i = bibDoc.tag[type].retrieved;
  bibDoc.tag[type].retrieved++;
  return bibDoc.tag[type].data[i];

}

/*====================================================================*/
/*            FUNCTION:   lookupItemName                              */
/*--------------------------------------------------------------------*/
char *
lookupItemName (enum ITEM_VALS type)
{
  int loopVar;

  for (loopVar = 0; loopVar < NUM_ITEMS; loopVar++)
    if (itemLookup[loopVar].itemVal == type)
      return itemLookup[loopVar].itemName;

  return "No Name Found";
}

/*====================================================================*/
/*            FUNCTION:  readIPSDoc                                   */
/*--------------------------------------------------------------------*/
enum ERR_CODES
readIPSDoc (FILE * inFP, long *bytes, int error_on)
{
  static char inBuf[INBUF_SIZE];
  static long lineCount = 0;
  long begptr, endptr;
  char *itemText;
  char *ptr;
  char endtag[30];
  int endlen;

  enum ITEM_VALS itemVal;
  begptr = ftell (inFP);

  do
    {
      if (fgets (inBuf, INBUF_SIZE, inFP) == NULL)
        {
          *bytes = 0;
          return NO_DATA;
        }
      lineCount++;
      if (inBuf[0] == '\x1e')
        {
          endptr = ftell (inFP);
          *bytes = (endptr - begptr) + 1;
          return SUCCESS;
        }
      if ((ptr = strchr (inBuf, '>')) == NULL)
        {
          fprintf (stderr, "(storage.c)Missing '>' on tag (readIPSDoc)\n");
          exit (EXIT_FAILURE);
        }
      else
        *ptr = '\0';

      if ((itemVal = lookupItem (&inBuf[1])) == UNKNOWN_ITEM)
        {
          if (error_on)
          fprintf (stderr,
                   "(storage) Add \"%s\" to item_defs.h, no data saved\n",
                   &inBuf[1]);
        }

      else
        {
          memset (endtag, '\0', sizeof (endtag));
          sprintf (endtag, "</%s>", &inBuf[1]);         /* create the end
tag  */

          endlen = strlen (endtag);

          itemText = ++ptr;     /* point past the null */

          if ((ptr = strstr (itemText, endtag)) != NULL)
            *ptr = '\0';
          else if ((ptr = strchr (itemText, '\n')) != NULL)
            *ptr = '\0';

          if (error_on)
          fprintf (stderr, "Storing \"%s\" for THE item \"%s\"\n",
                   itemText, &inBuf[1]);

/* here we do special things to individual tag values */

          switch (storeItemData (itemVal, itemText))
            {
            case SUCCESS:
              break;

            case FAILURE:
              fprintf (stderr,
                       "Too many Data items for \"%s\""
                       ", change MAX_DOC_ITEMS in storage.h\n", &inBuf[1]);
              exit (EXIT_FAILURE);
              break;

            case NO_DATA:
                        if (error_on)
         fprintf(stderr, "No data for \"%s\" (%ld)\n",
   &inBuf[1], lineCount);
              break;

            }
        }
    }
  while (1);

  *bytes = 0;
  return NO_DATA;
}
/*====================================================================*/
/*            FUNCTION: dumpStorage                                   */
/*--------------------------------------------------------------------*/
void
dumpStorage (enum ITEM_VALS type)
{
  int i;

  fprintf (stderr, "bibDoc.tag[%s].count == %d\n",
           lookupItemName (type), bibDoc.tag[type].count);

  for (i = 0; i < bibDoc.tag[type].count; i++)
    fprintf (stderr, "%d %s\n", i, bibDoc.tag[type].data[i]);

}

/*====================================================================*/
/*            FUNCTION:  getItemName                                  */
/*--------------------------------------------------------------------*/
char *
getItemName (enum ITEM_VALS type)
{
  int i;

  for (i = 0; i < MAX_DOC_ITEMS; i++)
    {
      if (itemLookup[i].itemVal == type)
        {
          return itemLookup[i].itemName;
        }
    }
  return "UnknownItem";

}
