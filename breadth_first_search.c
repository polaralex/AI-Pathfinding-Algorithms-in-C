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
list * getFromQueue(list * node);

list * frontier_head;
list * visited;

int main() {

	// Current-run values:
	int xstart = 9;
	int ystart = 9;

	int i;
	int y;

	visited = malloc(sizeof(list));

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

	// Initialize "visited" array:
	for (i=0; i<mapWidth; i++) {
		for (y=0; y<mapHeight; y++) {
			map_visited[i][y]=0;
		}
	}

	position_xy * start = new_position(xstart, ystart);
	map_visited[xstart][ystart] = 1;
	addToFrontier(start);

	while (frontier_head != NULL){

		list * current = frontier_head;

		checkNeighbors(current, map_visited);

		frontier_head = frontier_head->next;

		printCurrentMap(map_visited, mapHeight, mapWidth);
	}
}

void checkNeighbors(list * current, int **map_visited){

	getFromQueue(current);

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

		list * temp_node;
		temp_node = frontier_head;

		while(temp_node->next != NULL) {
			temp_node = temp_node->next;
		}

		list * new_node = malloc(sizeof(list)); 
		temp_node->next = new_node;
		new_node->previous = temp_node;

		new_node->position = input;
		new_node->next = NULL;

	}
}

list * getFromQueue(list * node) {

	list * temp;
	temp = node;

	node = node->next;
	return(temp);
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
			if (map[i][z] == 0){
				printf("[ ]");
			} else {
				printf("[X]");
			}
		}
		printf("\n");
	}

	printf("\n\n");
}
