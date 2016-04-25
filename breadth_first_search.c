#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates {
	int x;
	int y;
	//int visited;
} position_xy;

typedef struct positionList {
	position_xy * position;
	struct positionList * previous;
	struct positionList * next;
} list;

void checkNeighbors(list * current, int **map_visited);
void addToFrontier(position_xy * input);
position_xy * new_position(int x, int y);
void printCurrentMap(int **map, int x, int y);

list * frontier_head;
list * visited;

int main() {

	printf("Debug 1.\n");
	// Current-run values:
	int xstart = 1;
	int ystart = 2;

	int i;
	int y;

	printf("Debug 2.\n");
	visited = malloc(sizeof(list));

	printf("Debug 3.\n");

	// Map initialization:
	int mapHeight = 15;
	int mapWidth = 15;

	// 'Map' memory allocation:
	int **map;
	map = (int **) malloc(mapHeight*sizeof(int *));

	for(i=0; i<mapWidth; i++){
		map[i] = (int *) malloc(mapHeight*sizeof(int));
	}

	// 'Map-visited' memory allocation:
	int **map_visited;
	map_visited = (int **) malloc(mapHeight*sizeof(int *));

	for(i=0; i<mapWidth; i++){
		map_visited[i] = (int *) malloc(mapHeight*sizeof(int));
	}

	printf("Debug 4.\n");

	// Initialize "visited" array:
	for (i=0; i<mapWidth; i++) {
		for (y=0; y<mapHeight; y++) {
			map_visited[i][y]=0;
		}
	}

	printf("Debug 5.\n");
	position_xy * start = new_position(xstart, ystart);
	addToFrontier(start);

	printf("Debug 6.\n");
	while (frontier_head != NULL){

		list * current = frontier_head;
		printf("Debug 7.\n");
		checkNeighbors(current, map_visited);
		printf("Debug 8.\n");

		frontier_head = frontier_head->next;
		printf("Debug 9.\n");

		printCurrentMap(map_visited, mapHeight, mapWidth);
	}
}

void checkNeighbors(list * current, int **map_visited){

	if (map_visited[(current->position->x)+1][current->position->y] != 1) {

		addToFrontier(new_position((current->position->x)+1, current->position->y));
		map_visited[(current->position->x)+1][current->position->y] = 1;
	}

	if (map_visited[(current->position->x)-1][current->position->y] != 1) {

		addToFrontier(new_position((current->position->x)-1, current->position->y));
		map_visited[(current->position->x)-1][current->position->y] = 1;
	}

	if (map_visited[current->position->x][(current->position->y)+1] != 1) {

		addToFrontier(new_position(current->position->x, (current->position->y)+1));
		map_visited[current->position->x][(current->position->y)+1] = 1;
	}

	if (map_visited[current->position->x][(current->position->y)-1] != 1) {

		addToFrontier(new_position(current->position->x, (current->position->y)-1));
		map_visited[current->position->x][(current->position->y)-1] = 1;
	}
}

void addToFrontier(position_xy * input) {
	
	if (frontier_head == NULL) {
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

position_xy * new_position(int x, int y){
	position_xy * new_position = malloc(sizeof(position_xy));
	new_position->x = x;
	new_position->y = y;
	//new_position->visited = 0;
	return (new_position);
}

void printCurrentMap(int **
	map, int x, int y) {

	int i, z;

	for(i=0; i<x; i++) {
		for(z=0; z<y; z++) {
			printf("[%d]", map[i][z]);
		}
		printf("\n");
	}

	printf("\n\n");
}
