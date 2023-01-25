# Pathfinder
Implementation of A* algorithm for movement of game characters on a 2D map using SFML.

This is a visualization of a 2D A* pathfinding algorithm.
Given a 2D grid with each cell having (x,y) coordinates, a "start" cell, a "target" cell and several obstacle cells, the algorithm will find and visualize
the shortest path (if there's one) from start to target.

How does it work? (source: https://www.geeksforgeeks.org/a-search-algorithm/)
At each step the algorithm picks the cell according to a value ‘FCost’ which is a parameter equal to the sum of two other parameters: ‘GCost’
and ‘HCost’. At each step it picks the cell having the lowest ‘FCost’.
We define ‘GCost’ and ‘HCost’ as simply as possible below:
GCost = the movement cost to move from the start cell to a given cell on the grid, following the path generated to get there. 
HCost = the estimated movement cost to move from that given cell on the grid to the target cell.
I chose to calculate GCost as the distance from the start cell and HCost as the distance from the target cell.
There are two lists of cells: the 'available' list and the 'evaluated' list.
The 'available' list contains all the cells that can be reached at a given time, whereas the 'evaluated' list contains all the cells whose costs have benn calculated.
At the beginning only the start cell is available and its neighbors are evaluated and made available, then the algorithm picks the available cell with with the lowest
FCost and repeats the process until it has found the target or there are no more cells available.

Instructions:
Once you click 'Run', a Grid with default dimensions will be created with a 30% chance that each cell is an obstacle (black). The start cell (blue) and target cell (red)
are chosen randomly. The shortest path will be automatically visualized in dark yellow, whereas all the other cells which will have been evaluated will be shown in light
yellow. You can add obstacles with left click and remove them with right click, the path will automatically update
.


