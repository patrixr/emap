#include "list.h"

void		List_foreach(List *l, list_cb cb)
{
  List_Iterator *it = FIRST(l);

  if (!it)
    return;
  while (it)
    {
      cb(it->data);
      it = NEXT(it);
    }
}

void		List_foreach_param(List *l, list_cb_param cb, void *param)
{
  List_Iterator *it = FIRST(l);

  if (!it)
    return;
  while (it)
    {
      cb(it->data, param);
      it = NEXT(it);
    }
}
