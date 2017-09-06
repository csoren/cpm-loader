#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool writeDefine (FILE* includeFile, const char* name, uint32_t paragraph) {
    return fprintf (includeFile, "%s EQU $%02X00\n", name, paragraph) > 0;
}

bool copyBytes (FILE* dest, FILE* src, size_t count) {
    uint8_t bytes[count];
    if (count != fread (bytes, 1, count, src))
        return false;

    return count == fwrite (bytes, 1, count, dest);
}

bool copyRecord (FILE* dest, FILE* src) {
    return copyBytes (dest, src, 0x80);
}

bool writeInfoText (const char* filename, FILE* cpmSys) {
    bool r = false;
    FILE* file = fopen (filename, "wb");
    if (file != NULL) {
        r = copyRecord (file, cpmSys);
        fclose (file);
    }

    return r;
}


bool writeRecordsToFilename (const char* filename, FILE* cpmSys, uint32_t countRecords) {
    FILE* file = fopen (filename, "wb");
    if (!file)
        return false;

    bool r = copyBytes (file, cpmSys, countRecords * 128);
    fclose (file);

    return r;
}


bool writeReversedRecordsToFilename (const char* filename, FILE* cpmSys, uint32_t countRecords) {
    bool r = false;
    FILE* file = fopen (filename, "wb");
    if (file != NULL) {
        fseek (cpmSys, countRecords * 128, SEEK_CUR);
        for (int i = 0; i < countRecords; ++i) {
            fseek (cpmSys, -128, SEEK_CUR);
            if (!copyBytes (file, cpmSys, 128))
                break;
            fseek (cpmSys, -128, SEEK_CUR);
            r = (i == (countRecords - 1));
        }
        fseek (cpmSys, countRecords * 128, SEEK_CUR);
        fclose (file);
    }

    return r;
}


bool writeTables (FILE* cpmSys, FILE* includeFile, uint32_t startParagraphs, uint32_t countParagraphs) {
    if (!writeDefine (includeFile, "DATATABLES_START", startParagraphs))
        return false;

    return writeRecordsToFilename ("tables.bin", cpmSys, countParagraphs * 2);
}


bool writeCommon (FILE* cpmSys, FILE* includeFile, const char* define, const char* binFilename, uint32_t endParagraphs, uint32_t countParagraphs) {
    uint32_t startParagraphs = endParagraphs - countParagraphs;

    if (!writeDefine (includeFile, define, startParagraphs))
        return false;

    return writeReversedRecordsToFilename (binFilename, cpmSys, countParagraphs * 2);
}


bool writeCommonCode (FILE* cpmSys, FILE* includeFile, uint32_t endParagraphs, uint32_t countParagraphs) {
    return writeCommon (cpmSys, includeFile, "COMMONCODE_START", "commoncode.bin", endParagraphs, countParagraphs);
}


bool writeBankedCode (FILE* cpmSys, FILE* includeFile, uint32_t endParagraphs, uint32_t countParagraphs) {
    return writeCommon (cpmSys, includeFile, "BANKEDCODE_START", "bankedcode.bin", endParagraphs, countParagraphs);
}


bool writeBIOS8502Code (FILE* cpmSys, FILE* includeFile, uint32_t endParagraphs, uint32_t countParagraphs) {
    return writeCommon (cpmSys, includeFile, "BIOS8502CODE_START", "bios8502code.bin", endParagraphs, countParagraphs);
}


bool extractFromFile (FILE* file, FILE* includeFile) {
    int commonCodeLocationEnd = fgetc (file);
    int commonCodeSize = fgetc (file);
    int bankedCodeLocationEnd = fgetc (file);
    int bankedCodeSize = fgetc (file);
    int startAddressLo = fgetc (file);
    int startAddressHi = fgetc (file);
    int bios8502LocationEnd = fgetc (file);
    int bios8502CodeSize = fgetc (file);
    int dataTablesLocationStart = fgetc (file);
    int dataTablesCodeSize = fgetc (file);
    
    fprintf (includeFile, "CPM_START_ADDRESS EQU $%02X%02X\n", startAddressHi, startAddressLo);

    fseek (file, 0x80, SEEK_SET);
    if (!writeInfoText ("info.bin", file))
        return false;

    if (!writeTables (file, includeFile, dataTablesLocationStart, dataTablesCodeSize))
        return false;

    if (!writeCommonCode (file, includeFile, commonCodeLocationEnd, commonCodeSize))
        return false;

    if (!writeBankedCode (file, includeFile, bankedCodeLocationEnd, bankedCodeSize))
        return false;

    if (!writeBIOS8502Code (file, includeFile, bios8502LocationEnd, bios8502CodeSize))
        return false;

    return true;
}


bool extractFrom (const char* filename) {
    bool r = false;

    FILE* cpmSysfile = fopen (filename, "rb");
    if (cpmSysfile != NULL) {
        FILE* includeFile = fopen ("cpmsys.inc", "wt");        
        if (includeFile != NULL) {
            r = extractFromFile (cpmSysfile, includeFile);
            fclose (includeFile);
        }

        fclose (cpmSysfile);
    }

    return r;
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        printf ("Usage: extract CPM+.SYS\n");
        return 0;
    }

    return extractFrom (argv[1]) ? EXIT_SUCCESS : EXIT_FAILURE;
}
