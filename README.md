# AI-Pathfinding-Implementation-in-C
Implementations of Uniform Cost Search and A*-search Algorithms in C, for pathfinding on a two-dimensional array map.

# Specifications

We want to find an optimal path (if it exists) that a robot must follow to get from a starting position (S) to the nearest one of the two final states (T1 or T2). The coordinates of all S, T1, T2 are given by the user.

The robot can move either Horizontally (cost of movement: 1) or Vertically (cost of movement: 2) in a neighbooring free position.

Obstacles are created in the map using a random variable. In the end, we want to see the the optimal path.

The two pathfinding algorithms to be implemented are Uniform Cost Search (that searches the whole available map) and A*-search that uses a provided Heuristic function to make the search faster.

# How to use
1. Compile the .c file with GCC.
2. Open the a.out executable.
3. Insert the size of the array/map, the coordinates of the Starting Point and the two targets.
4. You will get a printout of every search extension, leading up to the final result, where the shortest path will be shown using the "^^" characters.

# Uniform Cost Search
![Uniform Cost Search result on Terminal](http://i.imgur.com/xagCqrK.png)

# A*-Search with Manhattan Distance Heuristic
![A*-Pathfinding result on Terminal](http://i.imgur.com/xagCqrK.png)


