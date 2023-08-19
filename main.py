from agents import Agents
from maze import Maze
from snake_maze_env import MazeSnakeGameEnv

# CONSTANTS:
HEIGHT = 25
WIDTH = 25
SNAKE_SPEED =1
SNAKE_GROWTH = False
BOUNDARY_LOOP = False

agents = Agents(HEIGHT, WIDTH, SNAKE_SPEED, SNAKE_GROWTH, BOUNDARY_LOOP)


# agents.random_walk()      # Random agent
agents.mannual_control()    # controlled by human