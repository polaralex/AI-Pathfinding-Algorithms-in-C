#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates {
	int x;
	int y;
	//int visited;
} position_xy;

typedef struct positionList {
	struct coordinates position;
	struct positionList * previous;
	struct positionList * next;
} list;

list * frontier_head;

list * visited;
visited = malloc(sizeof(list));

int main() {

	// Current-run values:
	int xstart = 1;
	int ystart = 2;

	// Map:
	int map[100][100];
	int map_visited[100][100];

	position_xy * start = newPosition(x, y);
	addToFrontier(start);
}

void addToFrontier(position_xy * input) {
	
	if (frontier_head = NULL) {
		frontier_head = malloc(sizeof(list));
		frontier_head->previous = NULL;
		frontier_head->next = NULL;

		frontier_head->position = input;
	} else {
		list * new_node = malloc(sizeof(list));
		new_node->previous = frontier_head;
		new_node->position = input;
		new_node->next = NULL;
		frontier_head = new_node;
	}
}

position_xy * newPosition(int x, int y){
	position_xy * new_position = malloc(sizeof(position_xy));
	new_position->x = x;
	new_position->y = y;
	//new_position->visited = 0;
	return (new_position);
}