#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates {
	int x;
	int y;
	//int visited;
} position_xy;

typedef struct positionList {
	position_xy position;
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
	int mapHeight = 100;
	int mapWidth = 100;

	// Map:
	int map[mapHeight][mapWidth];
	int map_visited[mapHeight][mapWidth];

	int i;
	int y;

	// Initialize "visited" array:
	for (i=0; i<mapWidth; i++) {
		for (y=0; y<mapHeight; y++) {
			map_visited[i][y]=0;
		}
	}

	position_xy * start = newPosition(x, y);
	addToFrontier(start);

	while(frontier_head!=NULL){
		list * current = frontier_head;

		checkNeighbors(current);
	}
}

void checkNeighbors(list * current){

	if (map_visited[current->position->x+1][current->position->y] != 1) {

		addToFrontier(new_position(current->position->x+1, current->position->y));
		map_visited[current->position->x+1][current->position->y] = 1
	}

	if (map_visited[current->position->x-1][current->position->y] != 1) {

		addToFrontier(new_position(current->position->x-1, current->position->y));
		map_visited[current->position->x-1][current->position->y] = 1;
	}

	if (map_visited[current->position->x][current->position->y+1] != 1) {

		addToFrontier(new_position(current->position->x, current->position->y+1));
		map_visited[current->position->x][current->position->y+1] = 1
	}

	if (map_visited[current->position->x][current->position->y-1] != 1) {

		addToFrontier(new_position(current->position->x, current->position->y-1));
		map_visited[current->position->x][current->position->y-1] = 1
	}
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