# Introduction:
 * snake game to test how a toy car can be made autonomous

# To Run the code:
* `pip install -r requirements.txt`

* `python3 main.py`

### **you can play game and it looks something like this:** <br><br><br>


![image](images/snake-maze.png)



### Note:
    * White is the snake
    * Green is the food
    * Blue is the maze wall


# Agents:

1. Neural-Nets Agent:
    * inputs:
         - current maze map
         - location and orientation of snake
    
    * output of neural_nets:
         - probability of path
         - probabilitiy of obstacle
    
    * Goal:
         - autonomy througn neural network + Path finding Algorithm
         - neural network: to classify whether the image infront car is path or obstacle
         - Path finding : To reach the goal


### References:
* [edureka-snake-game-with-pygame]( https://www.edureka.co/blog/snake-game-with-pygame/)
* chat-gpt

