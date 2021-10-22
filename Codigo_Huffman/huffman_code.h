#define bitMask(bpos) 1 << bpos
#define getBitAt(var, bpos) (*(unsigned *)&var & bitMask(bpos)) ? 1 : 0
#define turnBitOnAt(var, bpos) *(unsigned *)&var |= bitMask(bpos)
#define turnBitOffAt(var, bpos) *(unsigned *)&var &= ~(bitMask(bpos))
#define flipBitAt(var, bpos) *(unsigned *)&var ^= bitMask(bpos)

/**
 *  gets the number of bits that will be needed to represent a given number
 *  @param n given number
 *  @return number of bits to represent given number
*/
int getBitsCount(int n) { return (n == 0) ? 1 : ((int)log2(n) + 1); }

/**
 *  writes a data in bytes buffer with given offset and index using bitmasks
 *  @param buffer given buffer for data to be written in
 *  @param data data to be written into buffer
 *  @param offset bit current offset to write in buffer
 *  @param index position current index in buffer
*/
void writeByte (unsigned char *buffer, int data, int *offset, unsigned int *index)
{
    int b, wrote = 0, tmp = 7;
    for(b = 128; b > 0; b >>= 1, tmp--)
    {
        if(*offset < 0)
        {
            *offset = 7;
            ++(*index);
            printf(" ");
        }
        if(data & b)
        {
            printf("1");
            turnBitOnAt(buffer[*index], (*offset)--);
            wrote = 1;
        }
        else if (wrote || tmp == 0)
        {
            printf("0");
            turnBitOffAt(buffer[*index], (*offset)--);
        }
    }
}

/** 
 *  strips the extension from a given file path.
 *  @param filePath is the file path to process.
 *  @param extension is the buffer to store extension stripped.
*/
void stripExtension(char *filePath, char* extension)
{
    if (filePath == NULL) return;
    char *end = filePath + strlen(filePath);
    while (end > filePath && *end != '.' && *end != '\\' && *end != '/')
        --end;
    if ((end > filePath && *end == '.') && (*(end - 1) != '\\' && *(end - 1) != '/'))
    {
        strcpy(extension, end);
        *end = '\0';
    }
}
