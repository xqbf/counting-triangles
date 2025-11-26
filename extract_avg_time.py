import sys
import re

def extract_average_time(log_file):
    try:
        with open(log_file, 'r') as f:
            for line in f:
                if line.strip().startswith('Average:'):
                    match = re.search(r'Average:\s*(\d+(\.\d+)?)', line)
                    
                    if match:
                        avg_time_str = match.group(1)
                        avg_time_val = float(avg_time_str)
                        
                        print(f"Extracted Average Time (String): {avg_time_str}")
                        print(f"Extracted Average Time (Value): {avg_time_val}")
                        return avg_time_val
                        
    except FileNotFoundError:
        print(f"Error: Log file '{log_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
        
    print(f"Error: 'Average' time metric not found in the log file '{log_file}'.")
    return None

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python extract_avg_time.py <log_file_name>")
    else:
        extract_average_time(sys.argv[1])
