import re

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

# Example usage:
nmea_sentences = [
    '$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*42\r\n',
    '$GPGLL,4916.45,N,12311.12,W,225444,A\r\n',
    '$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A\r\n',
    '$GPVTG,054.7,T,034.4,M,005.5,N,010.2,K\r\n',
]

for sentence in nmea_sentences:
    parsed_data = parse_nmea(sentence)
    if parsed_data:
        sentence_type, sentence_data = parsed_data
        position = extract_lat_lon(sentence_data)
        if position:
            print(f"{sentence_type} - Latitude: {position[0]}, Longitude: {position[1]}")
