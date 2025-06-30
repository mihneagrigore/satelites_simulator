//Grigore Mihnea - Andrei

#define DIE_MALLOC(p) \
    do { \
        if ((p) == NULL) { \
            printf("Malloc error! (Line %d)\n", __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define DIE_FILE(p) \
    do { \
        if ((p) == NULL) { \
            printf("File error ! (Line %d)\n", __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define DIE_NODE(p) \
    do { \
        if ((p) == NULL) { \
            printf("Node is null! (Line %d)\n", __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

