'''

'''

from compass.use_hmc5883l import get_angle
from ultrasonic.main import get_distance

print(f'angle: {get_angle()}')	# returns tuple (degree, minutes)
print(f'distances: {get_distance()}')
