#ifndef __C_LIST_H__
#define __C_LIST_H__

#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

typedef uint8_t bool;

#define true 1;
#define false 0;


//---------------------------------------------------------
// List Iterator
//---------------------------------------------------------

struct List_Iterator
{
  void		*data;
  struct List_Iterator *next;
  struct List_Iterator *prev;
};

typedef struct List_Iterator List_Iterator;

// Accessors
#define INC_IT(it) it = it->next
#define DEC_IT(it) it = it->prev
#define NEXT(it) it->next
#define PREV(it) it->prev
#define IS_LAST(it) (it->next == NULL)
#define IS_FIRST(it) (it->prev == NULL)

// foreach callback

typedef void (*list_cb)(void *data);
typedef bool (*list_predicate)(void *data, void *param);

//---------------------------------------------------------
// List
//---------------------------------------------------------

struct List
{
  int count;
  List_Iterator *first;
  List_Iterator *last;
};

typedef struct List List;

// Accessors
#define NEW(type) type##_new()
#define COUNT(l) l->count
#define FIRST(l) l->first
#define LAST(l) l->last


// construction.c

List		*List_new();
/*< Creates a new empty list. Can be used throught the NEW macro
  e.g List *l = NEW(List); */


// destruction.c

void		List_delete(List *l);
/*< Frees the list. Does not free the contained data */

// append.c

bool		List_append(List *l, void *data);
/*< Appends data to the list */

// foreach.c

void		List_foreach(List *l, list_cb cb);
/*< Loops through all the nodes and calls */

#endif // __C_LIST_H__
