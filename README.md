<h6>Copyright Grigore Mihnea - Andrei

---

## Table of Contents

- [Task 1](#task-1)
  - [Used functions in this task](#used-functions-in-this-task)
  - [Functionality](#functionality)
- [Task 2](#task-2)
  - [Functionality](#functionality-1)
  - [Memory management for decoding](#memory-management-for-decoding)
- [Task 3](#task-3)
  - [Used functions in this task](#used-functions-in-this-task-1)
  - [Functionality](#functionality-2)
- [Task 4](#task-4)
  - [Used functions in this task](#used-functions-in-this-task-2)
  - [Functionality](#functionality-3)

---

# Task 1

## Used functions in this task

### 1. create_min_heap(capacity)

- Creates an empty min-heap structure with space for a fixed number of nodes.
- The heap stores nodes so that the node with the smallest frequency (and then lexicographic order) is always at the top.

---

### 2. create_b_tree_node(name, frequency)

- Creates a new binary tree node.
- Stores the given name and frequency.
- Initializes the node left, right, and parent pointers to NULL.
- Sets the node height to zero.

---

### 3. insert_min_heap(heap, node)

- Adds a new node to the heap.
- Inserts it and maintains the heap property:
  - Nodes with smaller frequency come first.
  - If frequencies are equal, nodes with lexicographically smaller names come first.
- Ensures the smallest node is always at the root of the heap.

---

### 4. min_heap_pop(heap)

- Removes and returns the node at the root of the heap (the smallest node).
- Replaces the root with the last node in the heap.
- Restores the heap order.

---

### 5. prepare_transfer_node(node1, node2)

- Creates a new node that acts as the parent of node1 and node2.
- Combines the two node names by concatenation.
- Sets the frequency as the sum of the two child nodes frequencies.
- Sets left and right pointers to the two nodes.
- Updates child nodes to point back to this parent node.
- Sets the height of the new node as one greater than the child height.

---

### 6. print_tree_level_by_level(root, output)

- Prints the tree nodes level by level.
- Uses a queue to keep track of nodes at the current level.
- For each level:
  - Counts how many nodes are at that level.
  - Dequeues each node, prints its frequency and name.
  - Enqueues its children if they exist.
- Moves to the next level until all nodes are printed.

---

## Functionality

1. Create min-heap and tree structures.

2. Read input nodes (each with frequency and name) and insert them into the min-heap.

3. Build the binary tree:

   - While there is more than one node in the heap:
     - Pop the two smallest nodes.
     - Create a new parent node linking these two.
     - Insert the new node back into the min-heap.

4. After this process, the last node remaining in the heap is the root of the full binary tree.

5. Print the tree level by level using a queue.

---

# Task 2


## Functionality

The code performs the graph traversals in main and follows this logic:

- Start from the root node.
- For each character in the binary code:
  - If 0, move to the left child.
  - If 1, move to the right child.
- When reaching a leaf node, print its name.
- Then continue decoding the remaining part of the code starting again from the root.

---

### 2. Memory management for decoding

During traversal, the code uses a temporary string buffer (*aux*) to progressively shorten the code string as it moves through the tree. This ensures each iteration processes the next step of the path correctly.

---

# Task 3


## Used functions in this task

### 1. get_direction(b_tree_node *node, char *code, FILE *output)

- Recursively searches the tree starting from *node* to find the satellite whose name matches *code*.
- If the current name matches *code*, the function returns.
- Otherwise:
  - If the left child subtree contains the target satellite (*find_exact_string* returns true), it:
    - Prints 0 to the output.
    - Recursively calls itself on the left child.
  - Else if the right child subtree contains the target satellite, it:
    - Prints 1 to the output.
    - Recursively calls itself on the right child.
- It prints the path of 0 and 1 corresponding to the directions needed to reach the target.

---

### 2. find_exact_string(char *str, char *code)

- Checks if the exact satellite name appears in the string.
- Used to determine if a subtree contains the satellite with the given name.
- Ensures partial matches that are substrings of larger names are not mistakenly counted.
- Returns 1 if the exact name is found, 0 otherwise.

---

## Functionality

- For each satellite name read from input:
  - The program calls *get_direction* starting at the root of the tree.
  - *get_direction* prints the binary code leading to that satellite.
- The output is a sequence of binary codes corresponding to each satellite name.

---

# Task 4


## Used functions in this task

### 1. return_direction(b_tree_node *node, char *code)

- Determines on which side of the current node the satellite named *code* is.
- Returns:
  - 0 if the satellite is in the left subtree,
  - 1 if it is in the right subtree,
  - -1 if the satellite is not found in either subtree.
- Compares the satellite names to check where it is found using the helper function *find_exact_string*.

---

### 2. my_lca(b_tree_node *root, char *code1, char *code2)

- Recursively finds the LCA of two nodes named *code1* and *code2*.
- Base cases:
  - If the current *root* is *NULL*, returns *NULL*.
  - If the two nodes are on different sides of *root*, *root* is their LCA, so returns *root->name*.
- If both nodes are on the left subtree, recursively calls itself on the left child.
- If both nodes are on the right subtree, recursively calls itself on the right child.
- Returns the name of the LCA node.

---

## Functionality

- Reads a list of satellite names.
- Starts with the first two satellites, finds their LCA using *my_lca*.
- Then iteratively finds the LCA of the current LCA and the next satellite in the list.
- This process continues until the LCA for all nodes is found.
- Prints the final LCA name.

---
