#ifndef SLIST
#define SLIST   1

// This defines the maximum number of next pointers that can be stored in a
// single node. For good performance, a good rule of thumb is to set this to
// lg(N), where:
//      lg() is the base-2 logarithm function
//      N is the maximum number of entries in your list
//  If you set this to 1, you will get a slightly slower sorted linked list 
//  implementation.
#define MAX_SKIPLIST_HEIGHT     8

typedef struct sl_entry {
    char * key;
    char * value;
    int height;
    struct sl_entry * next[MAX_SKIPLIST_HEIGHT];
} sl_entry;

// Note: All of these functions copy the strings provided to avoid any internal
// dangling pointers. You still own the pointers you pass in, and are 
// responsible for managing that memory.
sl_entry * sl_init();
void sl_destroy(sl_entry * head);
char * sl_get(sl_entry * head, char * key);
void sl_set(sl_entry * head, char * key, char * value);
void sl_unset(sl_entry * head, char * key);
#endif
