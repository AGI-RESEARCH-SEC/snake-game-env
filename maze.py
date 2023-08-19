# prims algorithm

import random
class Maze:
    '''
    * 1 repsesents wall, 0 represents path
    '''
    def __init__(self, width, height) -> None:
        self.width = width
        self.height = height
        # self.maze = self.generate_maze(width, height)
    
    def prims_algorithm(self):
        # prims algorithm to generate maze
        width = self.width
        height = self.height
        
        # Initialize maze with walls
        maze = [['1' for _ in range(width)] for _ in range(height)]
        
        # Choose a random starting cell
        start_x = random.randint(0, width - 1)
        start_y = random.randint(0, height - 1)
        maze[start_y][start_x] = '0'
        
        # List of walls to consider
        walls = [(start_x + 1, start_y), (start_x - 1, start_y),
                (start_x, start_y + 1), (start_x, start_y - 1)]
        
        while walls:
            random_wall = random.choice(walls)
            x, y = random_wall
            
            # Count the number of neighbors with paths
            neighbors = 0
            if x > 0 and maze[y][x - 1] == '0':
                neighbors += 1
            if x < width - 1 and maze[y][x + 1] == '0':
                neighbors += 1
            if y > 0 and maze[y - 1][x] == '0':
                neighbors += 1
            if y < height - 1 and maze[y + 1][x] == '0':
                neighbors += 1
            
            if neighbors == 1:
                maze[y][x] = '0'
                
                # Add neighboring walls to the list
                if x > 0:
                    walls.append((x - 1, y))
                if x < width - 1:
                    walls.append((x + 1, y))
                if y > 0:
                    walls.append((x, y - 1))
                if y < height - 1:
                    walls.append((x, y + 1))
            
            walls.remove(random_wall)
        
        return maze

if __name__ == '__main__':
    # Example usage
    def print_maze(maze):
        for row in maze:
            print(' '.join(row))

    
    maze_width = 21
    maze_height = 21
    maze = Maze(maze_width, maze_height).prims_algorithm()
    print_maze(maze)
