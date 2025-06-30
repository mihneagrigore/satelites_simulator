#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "structs.h"
#include "errors.h"
#include "functions.h"

int main(int argc, char *argv[])
{
	// Get the arguments from the command line
	if (argc < 4) {
		printf("Run error\n");
		return 1;
	}

	char *task = argv[1];

	// Open files
	FILE *input = fopen(argv[2], "r");
	DIE_FILE(input);

	FILE *output = fopen(argv[3], "w");
	DIE_FILE(output);

	int n;
	min_heap *heap = NULL;
	b_tree *tree = NULL;

	fscanf(input, "%d", &n);

	heap = create_min_heap(10 * n);
	tree = create_b_tree();

	// Read the nodes from the input file
	for(int i = 0; i < n; i++) {
		char *name = malloc(STRINGLEN * sizeof(char));
		DIE_MALLOC(name);

		int frequency;
		fscanf(input, "%d %s", &frequency, name);

		b_tree_node *node = create_b_tree_node(name, frequency);

		insert_min_heap(heap, node);

		free(name);
		free(node);
	}

	// Create the tree from min heap
	while(heap->size > 1) {
		b_tree_node *node1 = min_heap_pop(heap);
		b_tree_node *node2 = min_heap_pop(heap);

		b_tree_node *node = prepare_transfer_node(node1, node2);
		insert_min_heap(heap, node);

		free(node);
	}

	// The root is the last node in heap
	tree->root = min_heap_pop(heap);

	if (task[2] == '1')
		// Task 1 = Print the tree level by level
		print_tree_level_by_level(tree->root, output);

	else if (task[2] == '2') {
		// Task 2 = Get the code of a node by its name
		int nr;
		fscanf(input, "%d", &nr);
		fgetc(input);

		for (int i = 0; i < nr; i++) {
			char code[1001];
			fscanf(input, "%s", code);

			if (code[strlen(code) - 1] == '\n')
				code[strlen(code) - 1] = '\0';

			// Iterate the code to find nodes
			int length = strlen(code);
			while (length > 0) {
				b_tree_node *node = tree->root;

				while ((node->left != NULL || node->right != NULL) && length > 0) {
					if (code[0] == '0')
						node = node->left;
					else
						node = node->right;

					char *aux =NULL;
					aux = malloc(1001 * sizeof(char));
					DIE_MALLOC(aux);

					strcpy(aux, code + 1);
					strcpy(code, aux);
					length--;

					free(aux);
				}

				if (node->left == NULL && node->right == NULL)
					fprintf(output, "%s ", node->name);
			}

			fprintf(output, "\n");
		}
	} else if (task[2] == '3') {

		// Task 3 = Get the direction of a node
		char code[STRINGLEN];
		int nr;
		fscanf(input, "%d", &nr);
		fgetc(input);

		for (int i = 0; i < nr; i++) {
			fgets(code, STRINGLEN, input);
			if (code[strlen(code) - 1] == '\n')
				code[strlen(code) - 1] = '\0';

			get_direction(tree->root, code, output);
		}

	} else if (task[2] == '4') {

		// Task 4 = Find the LCA of n nodes
		char code1[STRINGLEN], code2[STRINGLEN], *aux;
		int nr;
		fscanf(input, "%d", &nr);
		fgetc(input);

		fgets(code1, STRINGLEN, input);
		if (code1[strlen(code1) - 1] == '\n')
			code1[strlen(code1) - 1] = '\0';

		for (int i = 0; i < nr - 1; i++) {
			fgets(code2, STRINGLEN, input);
			if (code2[strlen(code2) - 1] == '\n')
				code2[strlen(code2) - 1] = '\0';

			aux = my_lca(tree->root, code1, code2);
			if (aux == NULL || !strcmp(aux, tree->root->name))
				break;

			strcpy(code1, aux);
		}
		if (aux == NULL || !strcmp(aux, tree->root->name)) {
			fprintf(output, "%s\n", tree->root->name);
		} else {
			fprintf(output, "%s\n", code1);
		}
	}

	// Free the memory
	free_b_tree_node(tree->root);
	free(tree);
	free(heap->array);
	free(heap);

	// Close the files
	fclose(input);
	fclose(output);

	return 0;
}
