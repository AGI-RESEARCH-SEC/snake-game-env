import numpy as np
from queue import PriorityQueue

class AStarAgent:
    def __init__(self, env):
        self.env = env

    def heuristic(self, current, goal):
        return abs(current[0] - goal[0]) + abs(current[1] - goal[1])

    def find_path(self, start, goal):
        open_set = PriorityQueue()
        open_set.put((0, start))
        came_from = {}
        g_score = {cell: float('inf') for row in self.env.maze for cell in row}
        g_score[start] = 0
        f_score = {cell: float('inf') for row in self.env.maze for cell in row}
        f_score[start] = self.heuristic(start, goal)

        while not open_set.empty():
            _, current = open_set.get()

            if current == goal:
                path = []
                while current in came_from:
                    path.append(current)
                    current = came_from[current]
                path.reverse()
                return path

            for neighbor in self.env.get_valid_neighbors(current):
                tentative_g_score = g_score[current] + 1  # Assuming each step has a cost of 1

                if tentative_g_score < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g_score
                    f_score[neighbor] = g_score[neighbor] + self.heuristic(neighbor, goal)
                    open_set.put((f_score[neighbor], neighbor))

        return None

    def get_next_move(self, current_pos, goal):
        path = self.find_path(current_pos, goal)
        if path and len(path) > 1:
            next_pos = path[1]
            if next_pos[0] > current_pos[0]:
                return 3  # Move right
            elif next_pos[0] < current_pos[0]:
                return 2  # Move left
            elif next_pos[1] > current_pos[1]:
                return 1  # Move down
            else:
                return 0  # Move up
        return self.env.action_space.sample()  # Default to random action if no path found
