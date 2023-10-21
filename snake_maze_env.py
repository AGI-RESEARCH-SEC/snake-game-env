import gymnasium as gym
from gymnasium import spaces
import pygame
import random
import numpy as np

class MazeSnakeGameEnv(gym.Env):
    '''
    
    * info: a simple snake game implemented in gym environment using pygames.
    
    * Actions:
        '0': 'Up',
        '1': 'Left',
        '2': 'Down',
        '3': 'Right'

    * boundary_loop <True/False>: determines whether or not the snake can "appear from right side boundary on passing through left side boundary."
                                - <defined in 'get_new_head()' function>
    
    * snake_growth <True/False> :  determines whether or not to grow the size of snake on eating food.
                                - <defined in 'step()' function>
    
    note: '(each_action + 2) % 4' is the opposite action
    note: snake head coordinates are (x, y) = (column, row)
    note: if snake goes through boundary, it appears on the opposite side <defined in 'get_new_head()'>
    '''

    def __init__(self, maze, width, height, snake_growth = False, boundary_loop = False):
        super(MazeSnakeGameEnv, self).__init__()
        self.action_space = spaces.Discrete(4)  # Up, Left, Down, Right actions
        self.observation_space = spaces.Box(low=0, high=1, shape=(10, 10), dtype=np.float32)
        
        # self.grid_size = 25 # number of cells along the width and height of the game grid.
        # self.grid = np.zeros((self.grid_size, self.grid_size))
        self.height = height    # number of cells along the height
        self.width = width      # number of cells along the width 
        self.grid = np.zeros((self.height, self.width))
        self.score = 0

        # to determine whether or not to grow the size of snake on eating food.
        self.snake_growth = snake_growth

        # determines whether or not the snake can "comme from right boundary on passing through left boundary."
        self.boundary_loop = boundary_loop

        
        
        self.maze = maze  # Maze represented as a grid of 1s and 0s
        self.snake = [self.generate_food(True, True)]   # [(5, 5)]
        self.food = self.generate_food(True)

        # Define colors
        self.black = (0, 0, 0)
        self.white = (255, 255, 255)
        self.green = (0, 255, 0)
        self.blue = (50, 153, 213)
        self.yellow = (255, 255, 0)

        pygame.init()
        # Each cell is represented by a square with a size of 20x20 pixels.
        # self.screen = pygame.display.set_mode((self.grid_size * 20, self.grid_size * 20))
        self.screen = pygame.display.set_mode((self.width * 20, self.height * 20))
        pygame.display.set_caption('Maze Snake Game')

    def reset(self):
        # self.grid = np.zeros((self.grid_size, self.grid_size))
        self.grid = np.zeros((self.height, self.width))
        self.snake = [self.generate_food(True, True)]   # [(5, 5)]
        self.food = self.generate_food(True)
        self.score = 0
        return self.get_observation()

    def step(self, action, previous_action):
        # print('----------step-------------')
        new_head = self.get_new_head(action, previous_action)
        assert type(new_head) == tuple, '\n new_head:{' + str(new_head) + '}, type:{' + str(type(new_head)) + '}, action:{' + str(action) +'}, previous_action:{' + str(previous_action) + '}'
        print(f'\n got_new_head:{new_head}')
        print(f'\n types: {type(new_head)}, types:{type(self.food)}')
        if self.is_collision(new_head):
            reward = -1
            done = True
        else:
            self.snake.insert(0, new_head)
            if new_head == self.food:
                self.score += 1
                reward = 1
                self.food = self.generate_food()

                if not self.snake_growth:
                    self.snake.pop()
            else:
                reward = 0
                self.snake.pop()


            done = False
        
        return self.get_observation(), reward, done, {}

    def render(self, message = None):
        self.screen.fill((0, 0, 0))
        
        # Draw the snake
        for segment in self.snake:
            pygame.draw.rect(self.screen, self.white, pygame.Rect(segment[0] * 20, segment[1] * 20, 20, 20))
        
        # Draw the maze
        for row in range(len(self.maze)):
            for column in range(len(self.maze[0])):
                if self.maze[row][column] == 1 or self.maze[row][column] == '1':
                    pygame.draw.rect(self.screen, self.blue, pygame.Rect(column * 20, row * 20, 20, 20))
                    '''
                        `column * 20`: x-coordinate of the top-left corner of the rectangle. 
                                    It's multiplied by 20 to convert from grid cell coordinates to pixel coordinates
                        `row * 20`: y-coordinate of the top-left corner of the rectangle. 
                                    multiplied by 20 to convert from grid cell coordinates to pixel coordinates.
                        `20`: The width of the rectangle (20 pixels).
                        `20`: The height of the rectangle (20 pixels).
                    '''
        
        # Draw the food
        pygame.draw.rect(self.screen, self.green, pygame.Rect(self.food[0] * 20, self.food[1] * 20, 20, 20))

        
        
        # Display the semi-transparent Score on top-right corner
        font = pygame.font.Font('freesansbold.ttf', 32)
        score_text = "Your Score: " + str(self.score)
        
        # Create a semi-transparent text surface
        text_surface = font.render(score_text, True, self.yellow)
        text_surface.set_alpha(128)  # Adjust the alpha value for semi-transparency
        
        # Blit the semi-transparent text onto the screen
        self.screen.blit(text_surface, (self.width - text_surface.get_width(), 0))
        
        
        
        
        
        
        # Display the message if provided
        if message:
            lines = message.split('\n')  # Split the message into lines
            y_position = self.width * 20 / 2 - (len(lines) - 1) * 20 / 2  # Calculate y-position for each line

            for line in lines:
                text_surface = font.render(line, True, self.yellow)
                text_rect = text_surface.get_rect(center=(self.height * 20 / 2, y_position))
                self.screen.blit(text_surface, text_rect)
                y_position += 27  # Move to the next line (margin between lines)

        # Update the display
        pygame.display.flip()

    def generate_food(self, initial=False, is_snake=False):
        def valid_positions_of_maze(maze):
            valid_positions = []    # list of tuple
            for row in range(len(maze)):
                for column in range(len(maze[0])):
                    if (maze[row][column] == 0 or maze[row][column] == '0'):
                        valid_positions.append((column, row))
            return valid_positions
        valid_positions = valid_positions_of_maze(self.maze)
        # print(f'\n valid_positions:{valid_positions}')
         
        if initial:
            # initial food or snake
            if is_snake:
                # snake is generated prior to generation of food initially
                initial_snake = random.choice(valid_positions)
                return initial_snake                             # initial_sna

        for point in self.snake:
            try:
                valid_positions.remove(point)
            except Exception as Ex:
                print(f'\n Exception: {Ex}\n snake:{self.snake}, point:{point}, valid_positions:{valid_positions}')
        new_food = random.choice(valid_positions)
        print(f'\n new food: {new_food}')
        return new_food
                    
            
    def get_new_head(self, action,  previous_action):
        def move(x, y, action):
            if self.boundary_loop:
                if action == 0:  # Up
                    # return head_x, (head_y - 1) % self.grid_size
                    return head_x, (head_y - 1) % self.height
                elif action == 2:  # Down
                    # return head_x, (head_y + 1) % self.grid_size
                    return head_x, (head_y + 1) % self.width
                elif action == 1:  # Left
                    # return (head_x - 1) % self.grid_size, head_y
                    return (head_x - 1) % self.width, head_y
                elif action == 3:  # Right
                    # return (head_x + 1) % self.grid_size, head_y
                    return (head_x + 1) % self.width, head_y
            else:
                if action == 0:  # Up
                    return head_x, (head_y - 1)
                elif action == 2:  # Down
                    return head_x, (head_y + 1)
                elif action == 1:  # Left
                    return (head_x - 1), head_y
                elif action == 3:  # Right
                    return (head_x + 1), head_y
                
        head_x, head_y = self.snake[0]
        if len(self.snake) == 1:
            return move(head_x, head_y, action)
        else:
            if (action+2)%4 ==previous_action:
                return move(head_x, head_y, previous_action)
            else:
                return move(head_x, head_y, action)
        # if action == 0:  # Up
        #     return head_x, (head_y - 1) % self.grid_size
        # elif action == 1:  # Down
        #     return head_x, (head_y + 1) % self.grid_size
        # elif action == 2:  # Left
        #     return (head_x - 1) % self.grid_size, head_y
        # elif action == 3:  # Right
        #     return (head_x + 1) % self.grid_size, head_y

    def is_collision(self, position):
        # print(f'\n ------ collision posiition: {position}, type:{type(position)}')
        print(f'\n position:{position}, type:{type(position)} snake:{self.snake}, food:{self.food}')
        return (position[0] >= self.width or position[1] >= self.height) or \
               (position in self.snake) or \
               (self.maze[position[1]%self.width][position[0]%self.height] == 1 or self.maze[position[1]%self.width][position[0]%self.height] == '1')

    def get_observation(self):
        # observation = np.zeros((self.grid_size, self.grid_size))
        observation = np.zeros((self.height, self.width))
        for segment in self.snake:
            observation[segment] = 1
        # for y in range(self.grid_size):
        # for x in range(self.grid_size):
        for y in range(self.height):
            for x in range(self.width):
                if self.maze[y][x] == 1:
                    observation[y][x] = 0.7
        observation[self.food] = 0.5
        return observation
    
    def valid_actions(self, actions, previous_action, return_co_ords=False):
        valid_actions = []
        for action in range(actions.n):
            new_head = self.get_new_head(action,  previous_action)
            if not self.is_collision(new_head):
                if return_co_ords:
                    valid_actions.append(new_head)
                else:
                    valid_actions.append(action)
        return valid_actions