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
    int i;
    for (i = 0; i < code[1]; i++)
    {
        if(*offset < 0)
        {
            *offset = 7;
            ++(*index);
        }
        if (getBitAt(code[0], code[1] - i - 1))
        {
            //printf("AAALLAAVVVV\n");
            printf("1");
            //printf(" en pos %d y offset %d \n", *index, *offset);
            turnBitOnAt(buffer[*index], (*offset)--);
        }
        else
        {
            printf("0");
            turnBitOffAt(buffer[*index], (*offset)--);
        }
    }
}

/**
 *  writes a byte in given indexed output from code at indexed input
 *  with given offset decoding using given Huffman tree.
 *  @param node Huffman tree node to decode bytes
 *  @param iptBuff given buffer for codes to be read from
 *  @param otpBuff given buffer for bytes to be written in
 *  @param offs bit current offset to write in buffer
 *  @param iptIdx current position index in input buffer
 *  @param optIdx current position index in output buffer
 *  @param codeLen decoded code length
*/
void writeBytes (Node node, unsigned char *iptBuff,
                    unsigned char *otpBuff, short *offs,
                    unsigned int *iptIdx,
                    unsigned int *optIdx, short* codeLen)
{
    if(node->byte != NOITEM)
    { // leaf node
        otpBuff[(*optIdx)++] = node->byte;
        return;
    }
    (*codeLen)++;
    if(*offs < 0)
    {
        *offs = 7;
        (*iptIdx)++;
    }
    if(getBitAt(iptBuff[*iptIdx], (*offs)--) & 1)
        writeBytes(node->right, iptBuff, otpBuff,
                    offs, iptIdx, optIdx, codeLen);
    else
        writeBytes(node->left, iptBuff, otpBuff,
                    offs, iptIdx, optIdx, codeLen);
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
