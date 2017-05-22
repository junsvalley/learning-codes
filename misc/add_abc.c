#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct notify_change_callback {
  int reg; 
  int changes;
};

struct preserve_notify_changes {
  int num;
  struct notify_change_callback *c;
};

struct preserve_notify_changes preserve_nc;


void print_preserve_nc()
{
   int i=0;
   for(;i<preserve_nc.num;i++)
   {
     struct notify_change_callback *cc = &(preserve_nc.c[i]);
     printf("num[%d],id=%d, changes=%d\n", preserve_nc.num, cc->reg, cc->changes);
   }
   printf("-=-=-=-=-=-=-=-\n");
}

void stash_notify_away(int notify, int changes)
{
    if(preserve_nc.num == 0)
    {
        preserve_nc.c = malloc(sizeof(struct notify_change_callback) * 3);
        memset(preserve_nc.c, 0, sizeof(struct notify_change_callback) * 3);
    }
    else if (preserve_nc.num % 3 == 0)
    {
        preserve_nc.c = realloc(preserve_nc.c , (preserve_nc.num + 3) * sizeof(struct notify_change_callback));
        memset(preserve_nc.c + preserve_nc.num, 0, sizeof(struct notify_change_callback) * 3);
    }

    int i = 0;

    while(i <= preserve_nc.num)
    {
        struct notify_change_callback *cc = &(preserve_nc.c[i]);

        if(i == preserve_nc.num)
        {
            cc->reg = notify;
            cc->changes = changes;
            preserve_nc.num++;
            break;
        }
        else if(notify < cc->reg)/*insert before this*/
        {
            memcpy(cc + 1, cc, sizeof(struct notify_change_callback) * (preserve_nc.num - i) );
            cc->reg = notify;
            cc->changes = changes;
            preserve_nc.num++;
            break;
        }
        i++;
    }

    print_preserve_nc();
}

int main()
{
  stash_notify_away(10, 8);
  stash_notify_away(3, 8);
  stash_notify_away(5, 8);
  stash_notify_away(23, 8);
  stash_notify_away(8, 8);
  stash_notify_away(9, 8);
  stash_notify_away(2, 8);
  stash_notify_away(6, 8);
  stash_notify_away(18, 8);
  stash_notify_away(21, 8);
  stash_notify_away(14, 8);
  return 0;
}


