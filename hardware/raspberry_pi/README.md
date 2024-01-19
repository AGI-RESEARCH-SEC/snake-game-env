# Raspberry pi
https://www.raspberrypi.com/

# install and Connect pi to laptop (SSH)
* [Setup Raspberry PI OS with SSH and WIFI ](https://www.youtube.com/watch?v=nZyyfJYOhbM)
* download raspberry pi image writer [here](https://www.raspberrypi.com/software/)
* plug in microsd or 
* <opt.> Connect Ethernet cable to pi.
ctrl + shift + x => enable ssh => set password:<> 
check configure wifi => Enter wifi namee and password
select country code

<default> check enable telemetery

=> pi os other:
	* Full: Full Desktop with GUI
	* lite: lite: No GUI
select storage to store => Write

* Connect using ssh:
`ssh piQ@raspberrypi	<where raspberrypi is hostname>
<enter the password>


# Raspberry PI:
* [pi.5 pinout](https://vilros.com/pages/raspberry-pi-5-pinout)
* [control with bluetooth android](https://forums.raspberrypi.com/viewtopic.php?t=245587)
* [bluedot: android to pi controller](https://bluedot.readthedocs.io/en/latest/)

# Motor Driver
* [vid. Pi + Motor Driver + Motor](https://www.collvy.com/blog/controlling-dc-motor-with-raspberry-pi)
* [Blog. Pi + Motor Driver + Motor](https://www.collvy.com/blog/controlling-dc-motor-with-raspberry-pi)

* [vid. pi + Motor Driver + ](https://www.youtube.com/watch?v=-PCuDnpgiew)


# Connecting GPS Sensor
* [Blog xarg](https://www.xarg.org/2016/06/neo6mv2-gps-module-with-raspberry-pi/)
* [blog.maker.pro](https://maker.pro/raspberry-pi/tutorial/how-to-use-a-gps-receiver-with-raspberry-pi-4)
* [blog instructables](https://www.instructables.com/Raspberry-Pi-the-Neo-6M-GPS/)
* [youtube](https://www.youtube.com/watch?v=R-6PqdmiBPE)
* [gps-python](https://forums.raspberrypi.com/viewtopic.php?t=244020)

sudo raspi-config -> 5 interfacing -> serial -> no login accessable over serial -> serial port hardware enable -> reboot

* GPSD: Collect data gps and provides the data via ip protocol.
sudo apt-get install gpsd gpsd-clients

* Read serial por to access o/p from GPS receiver model

cat /dev/serial0	<you will see the data>
cat /dev/ttyAMA0	<older version of pi>

* Analyze data packets from GPS receiver using CPSMPN and CGPS (real time data monitor)

* sudo gpsd /dev/serial0 -F /var/run/gpsd.sock	# <redirect data from serial port to gpsd socket>
sudo cgps -s	<monitor using cgps>
sudo gpssmon	<monitor using gpsmon>







# Magnetometer
* [blog](https://peppe8o.com/magnetometer-with-raspberry-pi-computers-gy-271-hmc5883l-wiring-and-code/)
* [Blog. HMC5883L](https://www.instructables.com/Interfacing-Digital-Compass-HMC5883L-with-Raspberr/)
* [Blog HMC5883L](https://how2electronics.com/interfacing-hmc5883l-magnetometer-with-raspberry-pi/#:~:text=Upon%20integrating%20the%20HMC5883L%20magnetometer,degrees%20becomes%20a%20straightforward%20computation.)
* [video. piconet magnetometr](https://www.youtube.com/watch?v=mfqQAHXnZpA)

* [Himalayan solution: HMC5883L:himalayansolution-Rs.600-](https://himalayansolution.com/product/gy-271-digital-compass-module)
* [Daraz: HMC5883L:daraz-Rs.1020-](https://www.daraz.com.np/products/hmc5883l-triple-axis-compass-magnetometer-sensor-gy271-i115091197.html)




# Ultrasonic sensor:
* [vid. sentdex](https://www.youtube.com/watch?v=udu6i1I0mqQ)
* [Blog HC-SR04 pytho](https://randomnerdtutorials.com/micropython-hc-sr04-ultrasonic-esp32-esp8266/)
* [vid. HC-SR04 Ultrasonic Sensor with Raspberry Pi (Python](https://www.youtube.com/watch?v=JvQKZXCYMUM)
* [vid. HC-SR04 python](https://www.youtube.com/watch?v=lrC-o_YE9zI)
* [hc-sr04:daraz: Rs.190](https://himalayansolution.com/product/ultrasonic-sensor-hc-sr04)
* [hc-sr04:daraz: Rs.290](https://www.daraz.com.np/products/ultrasonic-sensor-hc-sr04-i103568524.html)
