Skip List
=========
A simple implementation in plain old C.

What is it?
-----------
A [skip list](http://en.wikipedia.org/wiki/Skip_list) is a simple associative data structure. That is, it maps keys to values, in very much the same way as a hash table/dictionary/HashMap/map from your favorite programming language. The beauty of skip lists is that they are relatively easy to understand and implement, and don't require a good hash function, only a total ordering of keys.

The average insert/update/delete performance of a skip list is O(log(n)), similar to that of a [balanced binary tree](http://en.wikipedia.org/wiki/Balanced_binary_tree). However, skip lists depend on probability to accomplish this result, so it's not guaranteed. In the worst case, which is very uncommon, an operation may be linear in the number of list elements. Because skip list performance is non-deterministic, they are less commonly seen in the wild than other associative data structures.

How can I use it?
-----------------
However you like! This version can store any data type you want, so long as it's a C-style string to C-style string mapping. It should be relatively easy to hack it up to work with other types, should you find yourself so inclined.

These lists also have a fixed pillar height (that is, each node can have at
most `MAX_SKIPLIST_HEIGHT` pointers to other nodes. As the base-2 logarithm of the number of elements in your list becomes larger than this value, your list's performance will degrade. The implementation will not (and indeed cannot) automatically grow these next pointer arrays, but it won't break, either.

With these caveats, usage is pretty simple:

```C
// Create a list
sl_entry * list = sl_init();

// Add some elements
sl_set(list, "Andy", "Apple");
sl_set(list, "Brian", "Banana");
sl_set(list, "Cindy", "Cherry");

// Perform a lookup
char * result = sl_get(list, "Brian");
// Remember to free the result!
free(result);
result = NULL;

// Remove an element
sl_unset(list, "Andy");

// Free the list and all its nodes
sl_destroy(list);
```

Why did you write it?
---------------------
A couple of years ago, I was writing a shell-like program that needed to store environment variables, and I decided a bit of overkill couldn't hurt and wrote this. Also, I love skip lists, and I hope you will, too!

Is it thread-safe?
------------------
No.
