import numpy as np
# Define the maze
maze = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 0, 0, 0],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 0, 1, 1, 1],
    [1, 1, 1, 0, 0, 1, 1, 1, 1],
    [1, 1, 1, 0, 0, 1, 1, 1, 1],
    [1, 1, 1, 0, 0, 1, 1, 1, 1],
    [1, 1, 1, 0, 0, 1, 1, 1, 1],
    [1, 1, 1, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 1, 1, 1, 1, 1, 1]
]
source = (2,8)
destination = (13,8)

# Define the maze
maze = np.array([
    [1, 1, 0, 1],
    [1, 1, 0, 0],
    [1, 1, 0, 1],
    [1, 1, 0, 1],
    [1, 0, 0, 1],
    [1, 0, 0, 0]
])
source = (1,3)
destination = (5,3)
facing = "left"

maze = np.array([
    [0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1],
    [1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
    [1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1],
    [1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1],
    [1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1],
    [1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0],
    [1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0],
    [1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0],
    [1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1],
    [1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0]
])
source = (0,0)
destination = (14,11)


# [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]

# source = (0,0)
# destination = (49, 38)

def binary_to_decimal(binary):
    decimal = int(binary, 2)
    return decimal

def decimal_to_binary(decimal):
  """Converts a decimal number to its binary equivalent.

  Args:
      decimal: An integer representing the decimal number.

  Returns:
      A string representing the binary equivalent of the decimal number.
  """
    
  if decimal == 0:
    return "0"

  binary = ""
  while decimal > 0:
    remainder = decimal % 2
    binary = str(remainder) + binary
    decimal //= 2

  return binary
    

# Example usage:
binary_number = "101"
decimal_value = binary_to_decimal(binary_number)
print("Binary:", binary_number)
print("Decimal:", decimal_value)








def get_current_state(maze, current_location, facing):
    row, col = current_location
    # Calculate the next location based on the facing direction
    if facing == 'up':
        front_row, front_col = row - 1, col
        left_row, left_col = row, col - 1
        right_row, right_col = row, col + 1
        # Check if there is a path to the left
        left_value = 0 if left_col > 0 and maze[left_row][left_col] == 0 else 1
        # Check if there is a path to the right
        right_value = 0 if right_col < len(maze[0]) and maze[right_row][right_col] == 0 else 1
        # Check if there is a path to the front
        front_value = 0 if front_row > 0 and maze[front_row][front_col] == 0 else 1
        # Check if there is an obstacle in front
    elif facing == 'down':
        front_row, front_col = row + 1, col
        left_row, left_col = row, col + 1
        right_row, right_col = row, col - 1
        # Check if there is a path to the left
        left_value = 0 if left_col < len(maze[0]) and maze[left_row][left_col] == 0 else 1
        # Check if there is a path to the right
        right_value = 0 if right_col > 0 and maze[right_row][right_col] == 0 else 1
        # Check if there is a path to the front
        front_value = 0 if front_row < len(maze) and maze[front_row][front_col] == 0 else 1
    elif facing == 'left':
        front_row, front_col = row, col - 1
        left_row, left_col = row + 1, col
        right_row, right_col = row - 1, col
        # Check if there is a path to the left
        left_value = 0 if left_row < len(maze) and maze[left_row][left_col] == 0 else 1
        # Check if there is a path to the right
        right_value = 0 if right_row > 0 and maze[right_row][right_col] == 0 else 1
        # Check if there is a path to the front
        front_value = 0 if front_col > 0 and maze[front_row][front_col] == 0 else 1
    elif facing == 'right':
        front_row, front_col = row, col + 1
        left_row, left_col = row - 1, col
        right_row, right_col = row + 1, col
        # Check if there is a path to the left
        left_value = 0 if left_row >0 and maze[left_row][left_col] == 0 else 1
        # Check if there is a path to the right
        right_value = 0 if right_row <  len(maze) and maze[right_row][right_col] == 0 else 1
        # Check if there is a path to the front
        front_value = 0 if front_col <  len(maze[0]) and maze[front_row][front_col] == 0 else 1
    return (left_value, right_value, front_value), binary_to_decimal(str(left_value) + str(right_value) + str(front_value))

# Example usage:
# current_location = (2, 8)  # Example starting location
current_location = (1, 3)  # Example starting location
# facing_direction = 'up'    # Example starting facing direction
get_current_state(maze, current_location, facing='up') # output: [0, 1, 1]<binary>, 3 <decimal>
get_current_state(maze, current_location, facing='left') # output: [0, 1, 1]<binary>, 6 <decimal>
get_current_state(maze, current_location, facing='right') # output: [1, 1, 1]<binary>, 7 <decimal>
get_current_state(maze, current_location, facing='down') # output: [1, 0, 1] <binary> 5 <decimal>








def is_valid_coords(maze, coordinates):
    x, y = coordinates
    if (x>=0) and (x < len(maze)) and (y > 0) and (y < len(maze[0])) and maze[x][y]==0:
        return True
    else:
        return False

def move(maze, facing, action, current_coordinates, move_forward_on_turn=True):
    '''
      move_forward_on_turn=True makes it move forward towards direction of turn on every turn action.
    '''
    x, y = current_coordinates
    new_facing = facing
    new_coordinates = current_coordinates

    # Perform the chosen action
    if action == 0:
      action = "left"
    elif action == 1:
      action = "right"
    elif action == 2:
      action = "forward"
    elif action not in ["left", "right", "forward"]:
      raise ValueError(f"Amigo! action is not supposed to be \"{action}\". it is either of [left, right, forward]")  # Raises a ValueError

    if action == 'left':
        if facing == 'up':
            new_facing = 'left'
        elif facing == 'down':
            new_facing = 'right'
        elif facing == 'left':
            new_facing = 'down'
        elif facing == 'right':
            new_facing = 'up'
        # new_coordinates = current_coordinates
    elif action == 'right':
        if facing == 'up':
            new_facing = 'right'
        elif facing == 'down':
            new_facing = 'left'
        elif facing == 'left':
            new_facing = 'up'
        elif facing == 'right':
            new_facing = 'down'
        # new_coordinates = current_coordinates
    if move_forward_on_turn:
        facing = new_facing
    if action == "forward" or move_forward_on_turn:
        if facing == 'up':
            new_coordinates = (x - 1, y)
        elif facing == 'down':
            new_coordinates = (x + 1, y)
        elif facing == 'left':
            new_coordinates = (x, y - 1)
        elif facing == 'right':
            new_coordinates = (x, y + 1)
        if not is_valid_coords(maze, new_coordinates):
            new_coordinates = current_coordinates
        # new_facing = facing
    return new_coordinates, new_facing

# Example usage:
current_facing = 'up'      # Example current facing action
action = 'left'  # Example rotation action ('left' or 'right')

current_coordinates = (0, 0)  # Example starting coordinates
new_coordinates, new_facing = move(maze, current_facing, action, current_coordinates)

print("New Coordinates:", new_coordinates)
print("New Facing Direction:", new_facing)









from IPython.display import clear_output
def display(maze, source, destination, current_position, path=None):
    clear_output()
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if (i, j) == source:
                print('S', end=' ')
            elif (i, j) == destination:
                print('D', end=' ')
            elif (i, j) == current_position:
                print('C', end=' ')
            elif path and (i, j) in path:
                print('*', end=' ')  # Mark the path with '*'
            elif maze[i][j] == 1:
                print('#', end=' ')
            else:
                print('.', end=' ')
        print()



# Train q table

import numpy as np

# Define Q-learning parameters
num_actions = 4  # Up, Down, Left, Right
learning_rate = 0.05
discount_factor = 0.9
exploration_rate = 0.1
exploration_rate_decay = .90
num_episodes = 10000

# Define the number of states and actions
num_states = 2 ** 3  # 3 binary inputs
num_actions = 3      # left, right, forward
iteration_path_len_data = []


# Initialize Q-table with random values
q_values = np.zeros((num_states, num_actions))

for episode in range(num_episodes):
    # state = (0, 0)  # Starting position
    current_coordinates = source
    facing = "left" # For maze 2
    facing = "down" # For maze 3
    state_binary, state = get_current_state(maze, current_coordinates, facing)
    path = [current_coordinates]

    # while state != (maze.shape[0] - 1, maze.shape[1] - 1):  # Continue until reaching the goal
    while current_coordinates != destination:
        # Choose an action using epsilon-greedy strategy
        if np.random.rand() < exploration_rate:
            action = np.random.choice(num_actions)   # action is one of [0, 1, 2]
        else:
            action = np.argmax(q_values[state])      # action is one of [0, 1, 2]
        new_coordinates, new_facing = move(maze, facing, action, current_coordinates)
        new_state_binary, new_state = get_current_state(maze, new_coordinates, new_facing)


        # Update Q-value using the Bellman equation
        reward = -1 if maze[new_coordinates[0], new_coordinates[1]] == 0 else -5  # Penalize hitting a wall
        reward = +2 if new_coordinates == destination else reward # Reward for reaching destination
        q_values[state, action] += learning_rate * (
                reward + discount_factor * np.max(q_values[new_state]) - q_values[state, action])

        # Move to the new state
        facing = new_facing
        current_coordinates = new_coordinates
        state = new_state
        path.append(current_coordinates)
    iteration_path_len_data.append([episode, len(path)])

    # Decrease the exploration rate
    exploration_rate *= exploration_rate_decay
    if episode % 100 == 0:
        display(maze=maze, path=path, source = source, destination= (maze.shape[0] - 1, maze.shape[1] - 1), current_position=(maze.shape[0] - 1, maze.shape[1] - 1))
        print(f'{episode} path: len.{len(path)} {path}')

print("Training complete!")
# visualize_path(path)
display(maze=maze, path=path, source = source, destination= (maze.shape[0] - 1, maze.shape[1] - 1), current_position=(maze.shape[0] - 1, maze.shape[1] - 1))
print(f'path: len.{len(path)} {path}')


import matplotlib.pyplot as plt
import matplotlib.patches as patches
from IPython.display import clear_output, display

def render_colab(maze, snake, food):
    maze_height = len(maze)
    maze_width = len(maze[0])
    # fig_width = 8 * maze_width / maze_height
    # fig, ax = plt.subplots(figsize=(fig_width, 8))
    # fig, ax = plt.subplots(figsize=(8, 8))
    rect_size = min(8 / maze_width, 8 / maze_height)
    fig, ax = plt.subplots(figsize=(maze_width * rect_size, maze_height * rect_size))

    # Plot the maze
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if maze[i][j] == '1' or maze[i][j] == 1:
                ax.add_patch(patches.Rectangle((j, -i - 1), 1, 1, facecolor=(50/255, 153/255, 213/255)))
            # elif maze[i][j] == 'S':
            #     ax.add_patch(patches.Rectangle((j, -i - 1), 1, 1, facecolor='black'))  # snake_head
            # elif maze[i][j] == 'D':
            #     ax.add_patch(patches.Rectangle((j, -i - 1), 1, 1, facecolor='green')) # food
            elif maze[i][j] == '0' or maze[i][j] == 0:
                ax.add_patch(patches.Rectangle((j, -i - 1), 1, 1, facecolor='black')) # background

    # Plot the snake
    for segment in snake:
        ax.add_patch(patches.Rectangle((segment[1], -segment[0] - 1), 1, 1, facecolor='white')) # snake_body

    # Plot the food
    ax.add_patch(patches.Rectangle((food[1], -food[0] - 1), 1, 1, facecolor='green'))


    plt.axis('scaled')
    plt.gca().invert_yaxis()  # Invert y-axis to match the matrix coordinates

    # Clear the previous output and display the updated plot
    clear_output(wait=True)
    display(fig)
    plt.close(fig)
    plt.show()

import pygame
pygame.init()
pygame.font.init()

def render_pygame(maze, snake, food):
    # Each cell is represented by a square with a size of 20x20 pixels.
    # screen = pygame.display.set_mode((grid_size * 20, grid_size * 20))
    score=0
    maze_height = len(maze)
    maze_width = len(maze[0])
    screen = pygame.display.set_mode((maze_width * 20, maze_height * 20))
    pygame.display.set_caption('Maze Snake Game')
    black = (0, 0, 0)
    white = (255, 255, 255)
    green = (0, 255, 0)
    blue = (50, 153, 213)
    yellow = (255, 255, 0)
    screen.fill((0, 0, 0))
    
    # Draw the snake
    for segment in snake:
        pygame.draw.rect(screen, white, pygame.Rect(segment[1] * 20, segment[0] * 20, 20, 20))
    
    # Draw the maze
    for row in range(len(maze)):
        for column in range(len(maze[0])):
            if maze[row][column] == 1 or maze[row][column] == '1':
                pygame.draw.rect(screen, blue, pygame.Rect(column * 20, row * 20, 20, 20))
                '''
                    `column * 20`: x-coordinate of the top-left corner of the rectangle. 
                                It's multiplied by 20 to convert from grid cell coordinates to pixel coordinates
                    `row * 20`: y-coordinate of the top-left corner of the rectangle. 
                                multiplied by 20 to convert from grid cell coordinates to pixel coordinates.
                    `20`: The width of the rectangle (20 pixels).
                    `20`: The maze_height of the rectangle (20 pixels).
                '''
    
    # Draw the food
    pygame.draw.rect(screen, green, pygame.Rect(food[1] * 20, food[0] * 20, 20, 20))
    
    
    if score:
        # Display the semi-transparent Score on top-right corner
        font = pygame.font.Font('freesansbold.ttf', 32)
        score_text = "Your Score: " + str(score)
    
        # Create a semi-transparent text surface
        text_surface = font.render(score_text, True, yellow)
        text_surface.set_alpha(128)  # Adjust the alpha value for semi-transparency
    
        # Blit the semi-transparent text onto the screen
        screen.blit(text_surface, (maze_width - text_surface.get_width(), 0))
    
        # Display the message if provided
        if message:
            lines = message.split('\n')  # Split the message into lines
            y_position = width * 20 / 2 - (len(lines) - 1) * 20 / 2  # Calculate y-position for each line

            for line in lines:
                text_surface = font.render(line, True, yellow)
                text_rect = text_surface.get_rect(center=(maze_height * 20 / 2, y_position))
                screen.blit(text_surface, text_rect)
                y_position += 27  # Move to the next line (margin between lines)
    # Update the display
    pygame.display.flip()



current_coordinates = source
facing = "left" # For maze 2
facing = "down" # For maze 3
facing = "right"
state_binary, state = get_current_state(maze, current_coordinates, facing)
path = [current_coordinates]

# while state != (maze.shape[0] - 1, maze.shape[1] - 1):  # Continue until reaching the goal
while current_coordinates != destination:
    # Choose an action using epsilon-greedy strategy
    # if np.random.rand() < exploration_rate:
    #     action = np.random.choice(num_actions)
    # else:
    action = np.argmax(q_values[state])
    print(f'facing: {facing} state: {decimal_to_binary(state)} action: {action}')

    new_coordinates, new_facing = move(maze, facing, action, current_coordinates)
    new_state_binary, new_state = get_current_state(maze, new_coordinates, new_facing)
    print(f'new_coordinates:{new_coordinates} new_state_binary: {new_state_binary, new_state}, new_state:{new_state}, new_facing:{new_facing}')

    # Update Q-value using the Bellman equation
    # reward = -1 if maze[new_coordinates[0], new_coordinates[1]] == 0 else -5  # Penalize hitting a wall
    # reward = +5 if new_coordinates == destination else reward # Reward for reaching destination
    # q_values[state, action] += learning_rate * (
    #         reward + discount_factor * np.max(q_values[new_state]) - q_values[state, action])

    # Move to the new state
    facing = new_facing
    current_coordinates = new_coordinates
    state = new_state
    path.append(current_coordinates)
    # print(len(path))
    import sys, time
    if 'google.colab' in sys.modules:
        # display(maze=maze, path=path, source = source, destination= (maze.shape[0] - 1, maze.shape[1] - 1), current_position=(maze.shape[0] - 1, maze.shape[1] - 1))
        render_colab(maze, path, destination)
    else:
        print(f'path: {path}')
        # render_pygame(maze, path, destination)
        render_colab(maze, path, destination)
        pygame.quit()
    time.sleep(0.5)
    
    

# Decrease the exploration rate
exploration_rate *= exploration_rate_decay
if episode % 100 == 0:
    display(maze=maze, path=path, source = (0,0), destination= (maze.shape[0] - 1, maze.shape[1] - 1), current_position=(maze.shape[0] - 1, maze.shape[1] - 1))

print("Training complete!")
# visualize_path(path)
display(maze=maze, path=path, source = source, destination= (maze.shape[0] - 1, maze.shape[1] - 1), current_position=(maze.shape[0] - 1, maze.shape[1] - 1))
print(f'path: len.{len(path)} {path}')


import matplotlib.pyplot as plt

# Your data in the format: [ [iteration-1, length-1], [iteration-2, length-2], ... ]
# data = [[1, 10], [2, 15], [3, 20], [4, 25]]
data = iteration_path_len_data

# Extracting iterations and lengths into separate lists
iterations, lengths = zip(*data)

# Plotting the data
plt.plot(iterations, lengths, marker='o', linestyle='-')
plt.title('Iteration vs Length')
plt.xlabel('Iteration')
plt.ylabel('Length')
plt.grid(True)

# Display the plot
plt.show()

# Save the plot as a JPEG file
plt.savefig('iteration_vs_length_plot.jpg')

