import sys
import re

def extract_average_time(log_file):
    try:
        with open(log_file, 'r') as f:
            for line in f:
                if line.strip().startswith('Average:'):
                    parts = line.split()
                    if len(parts) >= 2:
                        avg_time = parts[1]
                        print(f"Extracted Average Time: {avg_time}")
                        return avg_time
                        
    except FileNotFoundError:
        print(f"Error: Log file '{log_file}' not found.")
        
    print(f"Error: 'Average' time metric not found in the log file '{log_file}'.")
    return None

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python extract_avg_time.py <log_file_name>")
        print("Example: python extract_avg_time.py gr_ottc_R_log_sample.txt")
    else:
        extract_average_time(sys.argv[1])
