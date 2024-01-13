import threading
import queue
import serial
import re

# Global variables
gps_data_queue = queue.Queue()
stop_thread = threading.Event()  # Event to signal the threads to stop

def parse_nmea(sentence):
    match = re.match(r'\$([A-Z]+),(.+?)\*([0-9A-Fa-f]{2})', sentence)
    if match:
        sentence_type = match.group(1)
        sentence_data = match.group(2)
        checksum = match.group(3)

        # Verify checksum (optional but recommended)
        calculated_checksum = 0
        for char in sentence[1:-3]:  # Exclude '$', '*' and checksum characters
            calculated_checksum ^= ord(char)
        if calculated_checksum != int(checksum, 16):
            print(f"Checksum mismatch in {sentence_type} sentence.")
            return None
        return sentence_type, sentence_data
    return None

def extract_lat_lon(sentence_data):
    if sentence_data:
        fields = sentence_data.split(',')
        if fields[0] == 'GPGLL' or fields[0] == 'GPGGA' or fields[0] == 'GPRMC':
            latitude = float(fields[1][:2]) + float(fields[1][2:]) / 60.0
            if fields[2] == 'S':
                latitude *= -1
            longitude = float(fields[3][:3]) + float(fields[3][3:]) / 60.0
            if fields[4] == 'W':
                longitude *= -1
            return latitude, longitude

        elif fields[0] == 'GPVTG':
            # Extract latitude and longitude if available in GPVTG
            if fields[5] == 'N' and fields[7] == 'E':
                return float(fields[3]), float(fields[9])
    return None

def gps_listener(port, baud_rate):
    try:
        with serial.Serial(port, baud_rate) as ser:
            while not stop_thread.is_set():
                line = ser.readline().decode()
                gps_data_queue.put(line)
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")

def gps_consumer():
    while not stop_thread.is_set():
        try:
            data = gps_data_queue.get(timeout=1)  # Timeout to check for the stop event
            parsed_data = parse_nmea(data)
            if parsed_data:
                sentence_type, sentence_data = parsed_data
                position = extract_lat_lon(sentence_data)
                if position:
                    print(f"{sentence_type} - Latitude: {position[0]}, Longitude: {position[1]}")
        except queue.Empty:
            pass  # Queue is empty, continue looping
    print("Consumer thread stopped.")

# Example usage:
if __name__ == "__main__":
    port_name = "/dev/ttyAMA0"
    baud_rate = 9600
    # Start the producer (GPS listener) thread
    producer_thread = threading.Thread(target=gps_listener, args=(port_name, baud_rate), daemon=True)
    producer_thread.start()
    # Start the consumer thread
    consumer_thread = threading.Thread(target=gps_consumer, daemon=True)
    consumer_thread.start()
    # ... Your main application code ...
    # To stop the threads, set the stop_thread event
    stop_thread.set()
    producer_thread.join()
    consumer_thread.join()
