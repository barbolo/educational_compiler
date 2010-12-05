typedef struct ape_stack {
	int machine_state;
	struct ape_stack *next;
} APEStack;

APEStack *apestack_head;