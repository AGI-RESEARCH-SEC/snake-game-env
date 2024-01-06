import math

class PreProcess:
    '''
        PreProcesss for conversion between the snake_environment and DQN agent.
    '''
    @staticmethod
    def min_max_normalize(value, min_value, max_value):
            return (value - min_value) / (max_value - min_value)
    @staticmethod
    def euclidean_distance(source, destination):
        distance = math.sqrt((source[0] - destination[0]) ** 2 + (source[1] - destination[1]) ** 2)
        normalized_distance = PreProcess.min_max_normalize(distance, 0, 39.941)
        return normalized_distance

    @staticmethod
    def find_position(maze, element):
        """Find the position of a given element in the maze."""
        for i, row in enumerate(maze):
            for j, val in enumerate(row):
                if val == element:
                    return i, j
        return None

    @staticmethod
    def vector_representation(maze, source_element='S', destination_element='D'):
        """Calculate and normalize the vector representation from source to destination."""
        if type(source_element) == str and source_element.lower() == "s":
            source_pos = PreProcess.find_position(maze, source_element)
            destination_pos = PreProcess.find_position(maze, destination_element)
        else:
            source_pos = source_element
            destination_pos = destination_element

        if source_pos and destination_pos:
            vector_x = destination_pos[1] - source_pos[1]  # x-component (column difference)
            vector_y = destination_pos[0] - source_pos[0]  # y-component (row difference)

            # Normalize vector_x and vector_y
            normalized_vector_x = PreProcess.min_max_normalize(vector_x, -25, 25)
            normalized_vector_y = PreProcess.min_max_normalize(vector_y, -25, 25)

            return (normalized_vector_x, normalized_vector_y)
        else:
            return None
    @staticmethod
    def get_state(env):
        # Get the current state of the environment
        vector = PreProcess.vector_representation(maze)

        # Calculate the euclidean distance between source and destination
        # source_pos = PreProcess.find_position(maze, 'S')
        # destination_pos = PreProcess.find_position(maze, 'D')
        source_pos = env.snake[0]
        destination_pos = env.food

        distance = PreProcess.euclidean_distance(source_pos, destination_pos)

        # state
        state = torch.tensor([vector[0], vector[1], distance])
        return state

if __name__ == "__main__":

    maze = [
            ['0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '1', '0', '0', '0'],
            ['1', '1', '0', '0', '0', '0', '1', '1', '0', '0', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '0', '0', '0', '1', '0'],
            ['0', '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '0'],
            ['0', '0', '0', '1', '1', '1', '0', '1', '1', '1', '0', '0', '1', '0', '1', '0', '0', '1', '1', '0', '0', '0', '1', '0', '1'],
            ['0', '1', '1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0'],
            ['0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0'],
            ['0', '0', '1', '1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '1', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0', '0'],
            ['0', '1', '0', '0', '1', '0', '1', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '0', '1', '1', '0'],
            ['0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '0', '0'],
            ['1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '0', '0', '0', '1', '0'],
            ['0', '0', '0', '0', '1', '0', '0', '1', '0', '1', 'S', '1', '0', '0', '1', '0', '0', '1', '0', '0', '1', '1', '0', '0', '0'],
            ['0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1', '0'],
            ['1', '0', '0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '0', '1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0'],
            ['1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '0', '1', '0', '0', '1', '0'],
            ['0', '1', '0', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0'],
            ['0', '0', '0', '1', '0', '0', '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '1', '0', '0', '1', '0', '0', '1', '0'],
            ['1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '1', '0', '1', '1', '0', '0'],
            ['0', '1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['1', '0', '1', '0', '0', '1', '1', '0', '1', '0', '1', '0', '0', '1', '0', '1', '0', '1', '1', '0', '1', '1', '0', '1', '0'],
            ['0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0'],
            ['1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0'],
            ['0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '1', '1', '0', '0', '0'],
            ['0', '1', '1', '0', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0'],
            ['D', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0', '0', '1', '0', '0', '1', '1', '0']
       ]

    # Calculate the euclidean distance between source and destination
    source_pos = PreProcess.find_position(maze, 'S')
    destination_pos = PreProcess.find_position(maze, 'D')
    print(f'source position: {source_pos}, destination_pos: {destination_pos}')

    vector = PreProcess.vector_representation(maze, source_pos, destination_pos)
    print("Vector representation from 'S' to 'D':", vector)

    distance = PreProcess.euclidean_distance(source_pos, destination_pos)
    print("Euclidean distance between 'S' and 'D':", distance)