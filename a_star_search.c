#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct coordinates {
	int x;
	int y;
} position_xy;

typedef struct positionList {
	position_xy * position;
	int priority;
	struct positionList * previous;
	struct positionList * next;
} list;

// Constants for 'positionsAreValid':
int CENTER = 0;
int UP = 1;
int DOWN = 2;
int LEFT = 3;
int RIGHT = 4;

// Constants for MAP 'landmarks':
int STARTING_POSITION = 0;
int NOT_VISITED = -1;
int OBSTACLE = -2;
int BEST_PATH = -3;
int TARGET = -4;

// Possibility of Obstacle occurence:
int possibility = 2;

void checkNeighbors(list * current, int **map_visited);
void userInputInitialization();
void addToQueue(position_xy * input, int inputPriority);
void addToBestPathQueue(position_xy * input);
position_xy * new_position(int x, int y);
void printCurrentMap(int **map, int x, int y);
int positionsAreValid(list * current, int direction);
void checkPosition(list * current, int **map_visited, int direction, int addX, int addY, int addedCost);
int findShortestPath( int **map, int **best_route_map, int target_x, int target_y);
void earlyExitCheck(list * current);
void printFrontierQueue(list * node);
void printBestPathQueue(list * node);
void printShortestPaths();
list * getNextByPriority();
int heuristic(position_xy * a, position_xy * b);
int isValid(int input);
void printMapStatus(int **map_visited, int mapWidth, int mapHeight);

// Lists:
list * queue_head;
list * shortestPath;

// Map initialization:
int mapHeight;
int mapWidth;

// Other Global variables:
int userInputXstart, userInputYstart;
int userInputTargetX1, userInputTargetY1;
int userInputTargetX2, userInputTargetY2;
int target1_selected = 0;
int target2_selected = 0;

position_xy * target1;
position_xy * target2;
position_xy * currentTarget;

int target1found = 0;
int target2found = 0;

// -- Variables for UserInputInitialization --
int userInputXstart = 3;
int userInputYstart = 3;
position_xy * start;

int **map_visited;
int **best_route_map;

int i, y;
int random_int;

int main() {

	userInputInitialization();

	// First search for the path to the first target:
	currentTarget = target1;
	addToQueue(start, (0 + heuristic(start, currentTarget)) );

	// The main loop of the Algorithm:
	while (queue_head != NULL && (target1found != 1 || target2found != 1) ){

		list * current = getNextByPriority();

		checkNeighbors(current, map_visited);

		printMapStatus(map_visited, mapWidth, mapHeight);
	}

	printShortestPaths();
}

list * getNextByPriority() {

	int minimumPriority = 1000000000;
	list * pointer = queue_head;
	list * minimumCurrentElement;

	// If there is only one Node left:
	if (queue_head->next == NULL) {

		printf("Debug: Inside only one node left.\n");

		list * temporary = malloc(sizeof(list));

		temporary->position = queue_head->position;
		temporary->previous = NULL;
		temporary->next = NULL;
		queue_head = NULL;

		return(temporary);
	}

	// Find a Node with the smallest priority:
	while( pointer != NULL ) {

		if (pointer->priority < minimumPriority) {
			minimumPriority = pointer->priority;
			minimumCurrentElement = pointer;
			//printf("Debug: Found min priority = %d\n", pointer->priority);
		}

		pointer = pointer->next;
	}

	printf("Debug: Time to remove the node.\n");

	// Remove that Node from the Priority Queue:

	if (minimumCurrentElement == queue_head) {
		queue_head = queue_head->next;
	} else if(minimumCurrentElement->previous == NULL && minimumCurrentElement->next != NULL){
		queue_head = minimumCurrentElement->next;
	} else if (minimumCurrentElement->next == NULL && minimumCurrentElement->previous != NULL) {
		minimumCurrentElement->previous->next = NULL;
	} else {
		minimumCurrentElement->previous->next = minimumCurrentElement->next;
		minimumCurrentElement->next->previous = minimumCurrentElement->previous;
	}

	printf("Debug: Node removed.\n");
	return(minimumCurrentElement);
}

int heuristic(position_xy * a, position_xy * b) {

	// Manhattan distance on a square grid:
	int distance = (abs(a->x - b->x) + abs(a->y - b->y));
	return (distance);
}

void checkNeighbors(list * current, int **map_visited){

		earlyExitCheck(current);
		
		checkPosition(current, map_visited, RIGHT, 0, 1, 1);
		checkPosition(current, map_visited, LEFT, 0, -1, 1);
		checkPosition(current, map_visited, UP, -1, 0, 2);
		checkPosition(current, map_visited, DOWN, 1, 0, 2);
}

void checkPosition(list * current, int **map_visited, int direction, int addX, int addY, int addedCost) {

	if (positionsAreValid(current, direction) == 1 && map_visited[(current->position->x)+addX][(current->position->y)+addY] == NOT_VISITED) {

		position_xy * nextPosition = new_position( (current->position->x)+addX, (current->position->y)+addY);
		int current_cost = map_visited[current->position->x][current->position->y];

		// Add the new position to the Queue and mark the position as Visited:
		int priority = heuristic(nextPosition, currentTarget) + addedCost;
		addToQueue(nextPosition, priority);
		map_visited[(current->position->x)+addX][(current->position->y)+addY] = current_cost + addedCost;
	}
}

int positionsAreValid(list * current, int direction) {

	int x, y;
	x = current->position->x;
	y = current->position->y;

	if (direction == CENTER) {

		if (x < mapHeight && y < mapWidth && (x>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == UP) {

		if ( x-1 < mapHeight && y < mapWidth && (x-1>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == DOWN) {

		if ( x+1 < mapHeight && y < mapWidth && (x+1>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == LEFT) {

		if( x < mapHeight && y-1 < mapWidth && (x>=0) && (y-1>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == RIGHT) {

		if( x < mapHeight && y+1 < mapWidth && (x>=0) && (y+1>=0) ) {
			return(1);
		} else {
			return(0);
		}

	} else {
		return(0);
	}
}

void addToQueue(position_xy * input, int inputPriority) {
	
	if (queue_head == NULL) {

		queue_head = malloc(sizeof(list));
		queue_head->previous = NULL;
		queue_head->next = NULL;
		queue_head->position = input;
		queue_head->priority = inputPriority;

	} else {

		list * temp_node;
		temp_node = queue_head;

		while (temp_node->next != NULL) {
			temp_node = temp_node->next;
		}

		list * new_node = malloc(sizeof(list));

		temp_node->next = new_node;

		new_node->previous = temp_node;
		new_node->next = NULL;

		new_node->position = input;
		new_node->priority = inputPriority;
	}
}

void addToBestPathQueue(position_xy * input) {
	
	if (shortestPath == NULL) {

		shortestPath = malloc(sizeof(list));
		shortestPath->previous = NULL;
		shortestPath->next = NULL;
		shortestPath->position = input;
		// This is temporary:
		shortestPath->priority = 0;

	} else {

		list * temp_node;
		temp_node = shortestPath;

		while(temp_node->next != NULL) {
			temp_node = temp_node->next;
		}

		list * new_node = malloc(sizeof(list));

		temp_node->next = new_node;

		new_node->previous = temp_node;
		new_node->position = input;
		new_node->next = NULL;
		// This is temporary:
		new_node->priority = 0;
	}
}

position_xy * new_position(int x, int y){

	position_xy * new_position = malloc(sizeof(position_xy));
	new_position->x = x;
	new_position->y = y;
	return (new_position);
}

void earlyExitCheck(list * current) {

	if (current != NULL && current->position->x == userInputTargetX1 && current->position->y == userInputTargetY1){
		target1found = 1;
		currentTarget = target2;
		printf("\n --> Target 1 found! <--\n\n");
		printf("-> Current Target Changed to 'Target 2'.\n\n");
	}

	if (current != NULL && current->position->x == userInputTargetX2 && current->position->y == userInputTargetY2){
		target2found = 1;
		printf("\n -->Target 2 found! <--\n\n");
	}
}

int findShortestPath( int **map, int **best_route_map, int target_x, int target_y ) {

	int x = target_x;
	int y = target_y;
	int i, z;

	int total_cost = 0;

	// Initialize the base of the 'best-route map' array:
	for (i=0; i<mapHeight; i++) {
		for (z=0; z<mapWidth; z++) {
			best_route_map[i][z] = map[i][z];
		}
	}

	while( map[x][y] != STARTING_POSITION ) {

		int smallestValue = 1000000;
		int direction = UP;

		// First, find the best way to continue:
		// Look up:
		if( (x-1)>=0 && map[x-1][y] < smallestValue && (isValid(map[x-1][y]) == 1) ){
			smallestValue = map[x-1][y];
			direction = UP;
		}
		// Look down:
		if ( (x+1)<mapWidth && map[x+1][y] < smallestValue && (isValid(map[x+1][y]) == 1) ){
			smallestValue = map[x+1][y];
			direction = DOWN;
		}
		// Look left:
		if ( (y-1)>=0 && map[x][y-1] < smallestValue && (isValid(map[x][y-1]) == 1) ){
			smallestValue = map[x][y-1];
			direction = LEFT;
		}
		// Look right:
		if ( (y+1)<mapWidth && map[x][y+1] < smallestValue && (isValid(map[x][y+1]) == 1)){
			smallestValue = map[x][y+1];
			direction = RIGHT;
		}

		// Then, get the specific position in coordinates:
		position_xy * position = malloc(sizeof(position_xy));

		if ( direction == UP ) {

			position->x = x-1;
			position->y = y;

		} else if ( direction == DOWN ) {

			position->x = x+1;
			position->y = y;

		} else if ( direction == LEFT ) {

			position->x = x;
			position->y = y-1;

		} else if ( direction == RIGHT ) {

			position->x = x;
			position->y = y+1;
		}

		// And, finally, write this into the array and the queue:
		addToBestPathQueue(position);
		total_cost += best_route_map[position->x][position->y];
		best_route_map[position->x][position->y] = BEST_PATH;
		// And feed the next loop:
		x = position->x;
		y = position->y;
	}

	// Then, print the Best Route Queue and the Best Route Map:
	printf("-----------------\n");
	printBestPathQueue(shortestPath);
	printCurrentMap(best_route_map, mapWidth, mapHeight);
	printf("The Total Cost is: %d\n", total_cost);
	printf("-----------------\n\n");

	return(total_cost);
}

int isValid(int input) {
	if (input == NOT_VISITED || input == OBSTACLE || input == BEST_PATH) {
		return(0);
	} else {
		return(1);
	}
}

void userInputInitialization() {

	srand(time(NULL));
	
	// User-input:
	printf("\n\n-- Welcome to the Robot Pathfinding Program --\n");
	printf("What size of a map do you want?\n\n[INPUT] Please enter a WIDTH: ");
	scanf("%d", &mapWidth);
	printf("\n\n[Input] Please enter a HEIGHT: ");
	scanf("%d", &mapHeight);
	printf("\n\n");

	map_visited = (int **) malloc(mapHeight*sizeof(int *));

	for(i=0; i<mapHeight; i++){
		map_visited[i] = (int *) malloc(mapWidth*sizeof(int));
	}
	
	best_route_map = (int **) malloc(mapHeight*sizeof(int *));

	for(i=0; i<mapHeight; i++){
		best_route_map[i] = (int *) malloc(mapWidth*sizeof(int));
	}

	// Initialize "visited" array:
	for (i=0; i<mapHeight; i++) {
		for (y=0; y<mapWidth; y++) {
			map_visited[i][y]= NOT_VISITED;

			// This sets random squares as obstacles:
			if( (random_int = rand()%10) < possibility ) {
				map_visited[i][y] = OBSTACLE;
			}
		}
	}

	// User-input of start positions:
	printf("This is the current map:\n\n");
	printCurrentMap(map_visited, mapWidth, mapHeight);

	printf("\n[?] Where do you want the Starting Position to be?\n");
	printf("[INPUT] Enter the HEIGHT-axis position (1 - %d): ", mapHeight);
	scanf("%d", &userInputXstart);
	printf("\n[INPUT] Enter the WIDTH-axis position (1 - %d): ", mapWidth);
	scanf("%d", &userInputYstart);

	int xstart = userInputXstart-1;
	int ystart = userInputYstart-1;

	start = new_position(xstart, ystart);
	map_visited[xstart][ystart] = STARTING_POSITION;

	printf("This is the current map:\n\n");
	printCurrentMap(map_visited, mapWidth, mapHeight);

	// User-input of target positions:
	int temp_inputx;
	int temp_inputy;

	printf("\n[?] Where do you want the First Target to be?\n");
	printf("[INPUT] Enter the HEIGHT-axis position of the 1st target (1 - %d): ", mapHeight);
	scanf("%d", &temp_inputx);
	userInputTargetX1 = temp_inputx-1;

	printf("\n[INPUT] Enter the WIDTH-axis position of the 1st target (1 - %d): ", mapWidth);
	scanf("%d", &temp_inputy);
	userInputTargetY1 = temp_inputy-1;

	target1_selected = 1;

	target1 = malloc(sizeof(position_xy));
	target1->x = userInputTargetX1;
	target1->y = userInputTargetY1;

	printf("This is the current map:\n\n");
	printCurrentMap(map_visited, mapWidth, mapHeight);

	printf("\n[?] Where do you want the Second Target to be?\n");
	printf("[INPUT] Enter the HEIGHT-axis position of the 2nd target (1 - %d): ", mapHeight);
	scanf("%d", &temp_inputx);
	userInputTargetX2 = temp_inputx-1;

	printf("\n[INPUT] Enter the WIDTH-axis position of the 2nd target (1 - %d): ", mapWidth);
	scanf("%d", &temp_inputy);
	userInputTargetY2 = temp_inputy-1;

	target2_selected = 1;

	target2 = malloc(sizeof(position_xy));
	target2->x = userInputTargetX2;
	target2->y = userInputTargetY2;

	printf("This is the current map:\n\n");
	printCurrentMap(map_visited, mapWidth, mapHeight);
}

void printCurrentMap(int ** map, int width, int height) {

	int i, z;

	printf("    ");
	for(i=0; i<width; i++){
		if(i<9){
			printf(" %d  ", i+1);
		} else {
			printf(" %d ", i+1);
		}
	}
	printf("\n");

	for(i=0; i<height; i++) {

		if(i<9){
			printf(" %d  ", i+1);
		} else {
			printf(" %d ", i+1);
		}

		for(z=0; z<width; z++) {
			if ( i == userInputTargetX1 && z == userInputTargetY1 && target1_selected == 1 ) {
				printf("[T1]"); // It's the Target
			} else if ( i == userInputTargetX2 && z == userInputTargetY2 && target2_selected == 1 ) {
				printf("[T2]"); // It's the Target
			} else if (map[i][z] == NOT_VISITED){
				printf("[  ]");
			} else if (map[i][z] == OBSTACLE) {
				printf("[==]");
			} else if (map[i][z] == STARTING_POSITION) {
				printf("[st]");
			} else if (map[i][z] == BEST_PATH) {
				printf("[^^]");
			} else if (map[i][z] < 10) {
				printf("[%d ]", map[i][z]);
			} else {
				printf("[%d]", map[i][z]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printShortestPaths() {

	if (target1found == 1){
		printf("[PATH] The shortest path to the First Target is:\n");
		findShortestPath(map_visited, best_route_map, userInputTargetX1, userInputTargetY1);
		printf("\n");
	} else {
		printf("[ERROR] No path to the First Target could be found!\n\n");
	}

	if (target2found == 1){
		printf("[PATH] The shortest path to the Second Target is:\n");
		findShortestPath(map_visited, best_route_map, userInputTargetX2, userInputTargetY2);
	} else {
		printf("[ERROR] No path to the Second Target could be found!\n\n");
	}
}

void printFrontierQueue(list * node) {

	printf("Queue: ");
	if(node != NULL) {
		while (node->next != NULL) {
			printf("[%d](%d,%d)->", node->priority,(node->position->x)+1, (node->position->y)+1);
			node = node->next;
		}
	}
	printf("NULL");

	printf("\n-----------------\n\n");
}

void printBestPathQueue(list * node) {

	list * temp = node;

	printf("Best Path: ");
	while (temp->next != NULL) {
		printf("<-(%d,%d)", (temp->position->x)+1, (temp->position->y)+1);
		temp = temp->next;
	}
	printf("\n\n");
}

void printMapStatus(int **map_visited, int mapWidth, int mapHeight) {
	// Printing of the current state of the search:
	printCurrentMap(map_visited, mapWidth, mapHeight);

	if(queue_head != NULL){
		printFrontierQueue(queue_head);
	} else {
		printf("-> The Queue is EMPTY.\n\n");
	}
}
