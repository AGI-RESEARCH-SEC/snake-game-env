class NeuralNetAgent:
    def __init__(self, env):
        print('\n initialize FloodFillAgent \n')
        self.env = env
    
    def nn_model(self):
        '''
        returns probability_of_path and probability_of_no_path
        
        probability_of_path = 1 if entire row/column in front of snake is empty
        probability_of_no_path = 1 if immidiate row/column in front of snake is blocked
        '''


    def get_next_move(self, maze, current_pos, goal):
         pass