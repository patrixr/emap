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
typedef int (*list_cmp_fct)(void *data1, void *data2);
/*< A cmp function returns -1 if data1 > data2, 0 is data1 == data2 and 1 if data1 < data2 */

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

//-------------------------------------------------
// API
//-------------------------------------------------

//------
// CONSTRUCTION.c
//------
List		*List_new();
/*< Creates a new empty list. Can be used throught the NEW macro
  e.g List *l = NEW(List); */
void		List_delete(List *l);
/*< Frees the list. Does not free the contained data */


//------
// APPEND.c
//------
bool		List_append(List *l, void *data);
/*< Appends data to the list */
bool		List_prepend(List *l, void *data);
/*< Inserts an element at the beginning of the list */
bool		List_append_it(List *l, List_Iterator * new_it);
bool		List_prepend_it(List *l, List_Iterator * new_it);

//------
// FOREACH.c
//------
void		List_foreach(List *l, list_cb cb);
/*< Loops through all the nodes and calls */

//------
// REMOVE.c
//------
void		*List_remove_it(List *l, List_Iterator *it);
/*< Removes the item from the list */
bool		List_remove(List *l, list_predicate fct, void *param);
/*< Removes every item that fill the predicate */

//------
// GET.c
//------
void		*List_get(List *l, int idx);
/*< Returns the element at a precise index */
void		*List_get_first(List *l, list_predicate fct, void * param);
/*< Returns the first element that matches the predicate */
List		*List_get_all(List *l, list_predicate fct, void *param);
/*< Returns a list of all the elements that match the predicate */

//------
// SORT.c
//------

void		List_sort(List *l, list_cmp_fct cmpf);
/*< Simple built-in bubble sort */
void		List_merge_sort(List *l, list_cmp_fct cmpf);

//------
// CUT.c
//------

void		List_cut_half(List *in, List **out1, List **out2);
void		List_merge(List *l1, List*l2, List *out);

#endif // __C_LIST_H__
