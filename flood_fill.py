class FloodFillAgent:
    def __init__(self, env):
        print('\n initialize FloodFillAgent \n')
        self.env = env

    def flood_fill(self, maze, start, goal):
        print('----------- flood fill -------------')
        visited = set()
        stack = [(start, [])]

        while stack:
            
            current, path = stack.pop()
            self.env.snake = [current]    # update current position in env

            if current == goal:
                return path + [current]

            if current in visited:
                continue

            visited.add(current)

            
            neighbors = self.env.valid_actions(actions=self.env.action_space, previous_action=None, return_co_ords=True)
            for neighbor in neighbors:
                stack.append((neighbor, path + [current]))
                # print(f'neighbours:{neighbors} stack:{stack} current:{current} path: {path} neighbor: {neighbor}')
            
            print(f'----------------------------------------- \n start:{start} \t goal:{goal} \t current: {current} \n neighbours: {neighbors} \n stack: {stack} \n current: {current} \n path: {path} \n neighbor: {neighbor} \n -----------------------------------------')
        return None

    def get_next_move(self, maze, current_pos, goal):
        print('----------- next move -------------')
        path = self.flood_fill(maze, current_pos, goal)
        print(f'path: {path}')
        if path and len(path) > 1:
            next_pos = path[1]
            print(f'path: {path[1]}')
            if next_pos[0] > current_pos[0]:
                return 3  # Move right
            elif next_pos[0] < current_pos[0]:
                return 2  # Move left
            elif next_pos[1] > current_pos[1]:
                return 1  # Move down
            else:
                return 0  # Move up
        return self.env.action_space.sample()  # Default to random action if no path found
