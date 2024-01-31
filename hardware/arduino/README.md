# Arduino

## async.
- define motor speed within forward/left/right functions seperately


## Path Calibration:
* [Magnetometer-Reference](https://forum.arduino.cc/t/not-reading-a-magnetic-sensor/561257/2)
* Install two libraries: `Adafruit HMC5883 Unified` and `Adafruit Unified Sensor`
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