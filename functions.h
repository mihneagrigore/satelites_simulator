// Create and initialize the min heap
min_heap *create_min_heap(int capacity)
{
	min_heap *heap = malloc(sizeof(min_heap));
	DIE_MALLOC(heap);

	heap->array = malloc(capacity * sizeof(b_tree_node *));
	DIE_MALLOC(heap->array);

	heap->size = 0;
	heap->capacity = capacity;

	return heap;
}

// Create and intialize a node
b_tree_node *create_b_tree_node(char *name, int frequency)
{
	b_tree_node *node = malloc(sizeof(b_tree_node));
	DIE_MALLOC(node);

	int len = strlen(name);

	node->name = malloc(len * sizeof(char) + 1);
	DIE_MALLOC(node->name);

	memcpy(node->name, name, len);
	node->name[len] = '\0';
	node->frequency = frequency;

	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->height = 0;

	return node;
}

// Create and initialize the binary tree
b_tree *create_b_tree()
{
	b_tree *tree = malloc(sizeof(b_tree));
	DIE_MALLOC(tree);

	tree->root = NULL;
	tree->size = 0;

	return tree;
}

// Free a binary tree node
void free_b_tree_node(b_tree_node *node)
{
	if (node == NULL)
		return;

	free_b_tree_node(node->left);
	free_b_tree_node(node->right);

	free(node->name);
	free(node);
}

// Swap two nodes
void swap_min_heap_node(b_tree_node *a, b_tree_node *b)
{
	b_tree_node temp = *a;
	*a = *b;
	*b = temp;
}

// Generate the transfer node
b_tree_node *prepare_transfer_node(b_tree_node *node1, b_tree_node *node2)
{
	DIE_NODE(node1);
	DIE_NODE(node2);

	char *aux = malloc((strlen(node1->name) + strlen(node2->name) + 1) * sizeof(char));
	DIE_MALLOC(aux);

	strcpy(aux, node1->name);
	strcat(aux, node2->name);

	// Create the new node with the concatenated name
	b_tree_node *node = create_b_tree_node(aux, node1->frequency + node2->frequency);
	node->left = node1;
	node->right = node2;
	node1->parent = node;
	node2->parent = node;
	node->height = node1->height + 1;

	free(aux);

	return node;
}

// Insert a node in the min heap
void insert_min_heap(min_heap *heap, b_tree_node *node)
{
    if (heap->size == heap->capacity)
        return;

    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = *node;

    while (i > 0) {
        // First compare frequency
		// If frequencies are equal compare the name
        if (heap->array[i].frequency < heap->array[i - 1].frequency ||
            (heap->array[i].frequency == heap->array[i - 1].frequency &&
            strcmp(heap->array[i].name, heap->array[i - 1].name) < 0)) {
            swap_min_heap_node(&heap->array[i], &heap->array[i - 1]);
            i--;
        } else {
            break; // No more swaps needed
        }
    }
}

// Print the min heap (for debugging purposes)
void print_min_heap(min_heap *heap, FILE *output)
{
	for (int i = 0; i < heap->size; i++)
		fprintf(output, "%d %s\n", heap->array[i].frequency, heap->array[i].name);
}

// Rearrange the min heap
void min_heapify(min_heap *heap)
{
	// Sort the heap
	for (int i = 0; i < heap->size - 1; i++)
		for (int j = 0; j < heap->size - i - 1; j++)
			if (heap->array[j].frequency > heap->array[j + 1].frequency ||
				(heap->array[j].frequency == heap->array[j + 1].frequency &&
				strcmp(heap->array[j].name, heap->array[j + 1].name) > 0))
				swap_min_heap_node(&heap->array[j], &heap->array[j + 1]);
}

// Extract the minimum from the min heap (first element)
b_tree_node *min_heap_pop(min_heap *heap)
{
	DIE_NODE(heap);
	DIE_NODE(heap->array);

    b_tree_node *root = malloc(sizeof(b_tree_node));
    DIE_MALLOC(root);

    *root = heap->array[0];

    if (heap->size == 1) {
        heap->size--;
        return root;
    }

    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    min_heapify(heap);

    return root;
}

// Enqueue a node in the queue
void enqueue(queue **q, b_tree_node *node)
{
    queue *new_node = (queue *)malloc(sizeof(queue));
	DIE_MALLOC(new_node);

    new_node->node = node;
    new_node->next = NULL;

    if (*q == NULL) {
        *q = new_node;
    } else {
        queue *temp = *q;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Dequeue a node from the queue
b_tree_node* dequeue(queue **q)
{
	DIE_NODE(*q);

    queue *temp = *q;
    *q = (*q)->next;
	b_tree_node *node = temp->node;

    free(temp);
	return node;
}

// Check if the queue is empty
int is_empty(queue *q)
{
    return q == NULL;
}

// Print the binary tree level by level (BFS)
void print_tree_level_by_level(b_tree_node *root, FILE *output)
{
    DIE_NODE(root);

    queue *q = NULL;
    enqueue(&q, root);

    while (!is_empty(q)) {
        int level_size = 0;
        queue *temp = q;
        while (temp != NULL) {
            level_size++;
            temp = temp->next;
        }

        for (int i = 0; i < level_size; i++) {
            b_tree_node *current = dequeue(&q);
            fprintf(output, "%d-%s ", current->frequency, current->name);

            if (current->left != NULL)
                enqueue(&q, current->left);

            if (current->right != NULL)
                enqueue(&q, current->right);
        }

        fprintf(output, "\n");
    }
}

// strstr but for exact string
int find_exact_string(char *str, char *code)
{
	int l = strlen(code);
	char *aux = malloc((strlen(str) + 1) * sizeof(char));
	DIE_MALLOC(aux);

	strcpy(aux, str);

	while (1) {
		char *found = strstr(aux, code);

		// If the string is not found, return 0
		if (found == NULL) {
			free(aux);
			return 0;
		}

		// Check to be the exact string
		if (found[l] >= '0' && found[l] <= '9') {
			char *temp = malloc((strlen(found) + 1) * sizeof(char));
			DIE_MALLOC(temp);

			strcpy(temp, found + 1);
			strcpy(aux, temp);

			free(temp);
		} else {
			free(aux);
			return 1;
		}
	}

	free(aux);
	return 1;
}

// Get the path of a node in the binary tree and print it
void get_direction(b_tree_node *node, char *code, FILE *output)
{
	if (strcmp(node->name, code) == 0)
		return;

	// Check if the node is to the left
	// Go to the left
	if (node->left != NULL) {
		if (find_exact_string(node->left->name, code) == 1) {
			fprintf(output, "0");
			get_direction(node->left, code, output);
		}
	}

	// Check if the node is to the right
	// Go to the right
	if (node->right != NULL) {
		if (find_exact_string(node->right->name, code) == 1) {
			fprintf(output, "1");
			get_direction(node->right, code, output);
		}
	}
}

// Get one direction of a node in the binary tree and return it
int return_direction(b_tree_node *node, char *code)
{
	if (strcmp(node->name, code) == 0)
		return 0;

	// Check if the node is to the left
	if (node->left != NULL)
		if (find_exact_string(node->left->name, code) == 1)
			return 0;

	// Check if the node is to the right
	if (node->right != NULL)
		if (find_exact_string(node->right->name, code) == 1)
			return 1;

	// Node not found
	return -1;
}

// LCA of two nodes in the binary tree
char *my_lca(b_tree_node *root, char *code1, char *code2)
{

	if (root == NULL)
		return NULL;

	// If one of the nodes is the root, return the root
    if (return_direction(root, code1) != return_direction(root, code2))
		return root->name;

	// If both nodes are in the left subtree
	if (return_direction(root, code1) == 0 && return_direction(root, code2) == 0)
		return my_lca(root->left, code1, code2);

	// If both nodes are in the right subtree
	return my_lca(root->right, code1, code2);
}
