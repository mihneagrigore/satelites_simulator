typedef struct b_tree_node b_tree_node;
struct b_tree_node
{
    int frequency;
	char *name;

    struct b_tree_node *left;
    struct b_tree_node *right;
    struct b_tree_node *parent;

    int height;
};

typedef struct min_heap min_heap;
struct min_heap
{
	struct b_tree_node *array;
	int size;
	int capacity;
};

typedef struct b_tree b_tree;
struct b_tree
{
    struct b_tree_node *root;
    int size;
};

typedef struct queue queue;
struct queue
{
	b_tree_node *node;
	struct queue *next;
};
