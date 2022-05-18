bool CheckLittleEndian() {
    union {
        short inum = 0x1234;
        char cnum;
    } dummy;
    return dummy.cnum != 0x12;
}
