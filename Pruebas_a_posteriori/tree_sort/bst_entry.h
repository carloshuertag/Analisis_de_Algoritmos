/**
 * defines entry data
*/
typedef int Entry;

/**
 * prints given entry in given file.
 * @param e entry.
 * @param out file pointer to print in.
*/
void fprintEntry(Entry e, FILE *out) { fprintf(out, "%d\n", e); }

/**
 * prints given entry in stdout
 * @param e binary search tree node.
*/
void printEntry(Entry e) { fprintEntry(e, stdout); }

/**
 * given second entry is lower than the first one.
 * @param e1 first entry.
 * @param e1 second entry.
 * @return whether the given second entry is lower than the first one.
*/
bool isEntryLower(Entry e1, Entry e2) { return e1 > e2; }

/**
 * given second entry is greater than the first one.
 * @param e1 first entry.
 * @param e1 second entry.
 * @return whether the given second entry is greater than the first one.
*/
bool isEntryGreater(Entry e1, Entry e2) { return e1 < e2; }