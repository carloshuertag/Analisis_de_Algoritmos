#define bitMask(bpos) 1 << bpos
#define getBitAt(var, bpos) (*(unsigned *)&var & bitMask(bpos)) ? 1 : 0
#define turnBitOnAt(var, bpos) *(unsigned *)&var |= bitMask(bpos)
#define turnBitOffAt(var, bpos) *(unsigned *)&var &= ~(bitMask(bpos))
#define flipBitAt(var, bpos) *(unsigned *)&var ^= bitMask(bpos)

/**
 *  writes a code in indexed buffer with given offset
 *  @param buffer given buffer for data to be written in
 *  @param code code to be written into buffer
 *  @param offset bit current offset to write in buffer
 *  @param index current position index in buffer
*/
void writeCode (unsigned char *buffer, int code[2],
                short *offset, unsigned int *index)
{
    unsigned int i;
    for (i = 0; i < code[1]; i++)
    {
        if(*offset < 0)
        {
            *offset = 7;
            ++(*index);
        }
        if (getBitAt(code[0], (code[1] - i - 1)))
            turnBitOnAt(buffer[*index], (*offset)--);
        else
            turnBitOffAt(buffer[*index], (*offset)--);
    }
}

/** 
 *  strips the extension from a given file path.
 *  @param filePath file path string to process.
 *  @param extension string to store extension stripped.
*/
void stripExtension(char *filePath, char* extension)
{
    if (filePath == NULL) return;
    char *end = filePath + strlen(filePath);
    while (end > filePath && *end != '.'
            && *end != '\\' && *end != '/')
        --end;
    if ((end > filePath && *end == '.')
        && (*(end - 1) != '\\' && *(end - 1) != '/'))
    {
        strcpy(extension, end);
        *end = '\0';
    }
}
