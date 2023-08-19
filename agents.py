# snake game: using maze
# Snake game : Random Agent
# <err. moving left while moving right and game-over>
# <Works>
import sys
import time
import pygame
import random
from maze import Maze
from snake_maze_env import MazeSnakeGameEnv

class Agents:
    def __init__(self, height=25, width=25, snake_speed=1, snake_growth=False, boundary_loop = False) -> None:
        self.height = height
        self.width = width
        
        # Create a maze
        self.maze = Maze(height, width).prims_algorithm()
        
        # Create an instance of the custom environment
        self.env = MazeSnakeGameEnv(self.maze, self.height, self.width, snake_growth = snake_growth, boundary_loop = boundary_loop)

        self.clock = pygame.time.Clock()
        self.snake_speed = snake_speed

    def random_walk(self):
        '''
            Snake moves randomly
        '''
        # Example of interacting with the environment
        observation = self.env.reset()
        done = False
        previous_action = None  # to maintain the previous action to avoid sudden left turn while moving right
        print(self.env.action_space.sample())

        while not done:
            # action = env.action_space.sample()  # Replace with your agent's action selection
            
            valid_actions = self.env.valid_actions(self.env.action_space, previous_action)
            action = random.choice(valid_actions)
            observation, reward, done, info = self.env.step(action, previous_action)
            self.env.render()
            self.clock.tick(self.snake_speed)
            previous_action = action
            print(f'valid_actions len: {len(valid_actions)}, actions: {valid_actions}')

        pygame.quit()
    
    def mannual_control(self):
        '''
            Snake is controlled by user
        '''
        self.env.render()
        game_over = False
        no_initial_action = True    # to wait for users initial action
        previous_action = None  # to maintain the previous action to avoid sudden left turn while moving right
        def exit():
            print('\n\n ----------- exit game ----------- ')
            pygame.quit()
            sys.exit()

        while not game_over:
            self.clock.tick(self.snake_speed)
            print(f'waiting for initial action')
            action = previous_action

            for event in pygame.event.get():
                # listen for click on cross button of window
                if event.type == pygame.QUIT:
                    game_over = True
                    exit()

                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_c:
                        game_over = True    # quit the game on pressing ctrl + q
                        exit()
                    if event.key == pygame.K_n:
                        self.env.reset()  # restart the game on pressing  ctrl + c
                        self.env.render()
                        no_initial_action = True

                    if event.key == pygame.K_LEFT:
                        # left arrow key pressed
                        action = 1
                    elif event.key == pygame.K_RIGHT:
                        # right arrow key pressed
                        action = 3
                    elif event.key == pygame.K_UP:
                        # up arrow key pressed
                        action = 0
                    elif event.key == pygame.K_DOWN:
                        # down arrow key pressed
                        action = 2
                    # pause the game on pressing p
                    print(f'\n action: {action}')
            
            if action != None:
                no_initial_action = False

            # wait for initial action by user
            if no_initial_action:
                continue
            
            observation, reward, game_over, info = self.env.step(action, previous_action)
            previous_action = action

            if game_over:
                self.env.render(message = "Game Over! \n ctrl+C : Exit \n ctrl + n: New Game")
                game_over = False   # wait for users response
                no_initial_action = True
            else:
                self.env.render()
            
        
        print('\n\n ----------- game over ----------- ')
        # time.sleep(3)   # sleep for 3 seconds before quitting
        pygame.quit()
    


if __name__ == '__main__':
    '''
    CONSTANTS:
    '''
    HEIGHT = 25
    WIDTH = 25
    SNAKE_SPEED =1
    SNAKE_GROWTH = False
    BOUNDARY_LOOP = False
    
    agents = Agents(HEIGHT, WIDTH, SNAKE_SPEED, SNAKE_GROWTH, BOUNDARY_LOOP)

    # agents.random_walk()
    agents.mannual_control()
