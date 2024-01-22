# Arduino
* 


## Path Calibration:
* [Magnetometer-Reference](https://forum.arduino.cc/t/not-reading-a-magnetic-sensor/561257/2)

### ** Working: **
```
deviation1 = (heading_degrees - target_degrees) % 360
deviation2 = (target_degrees - heading_degrees) % 360.0
deviation = min(deviation1, deviation2);

if deviation > deviation_threshold:
    if (deviation1 < deviation2):
      left(duration);
    else {
      right(duration);
    }
note: duration is value proportional to deviation
```