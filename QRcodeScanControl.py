import socket
import time

IP = "192.168.147.119"
PORT = 80

class QRcodeScanControl:
    def __init__(self):
        self.esp32_ip = IP
        self.esp32_port = PORT
        self.path = {}
        self.visited = -1
        self.area = None
        self.start = None
        self.end = None
        self.sock = None

    def connect_socket(self):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(10)
            self.sock.connect((self.esp32_ip, self.esp32_port))
            print("Successfully connected to ESP32")
            return True
        except Exception as e:
            print("Error connecting to ESP32:", e)
            self.sock = None
            return False

    def close_socket(self):
        if self.sock:
            self.sock.close()
            self.sock = None
            print("Socket closed")

    def send_signal(self, command_type, signal):
        while not self.connect_socket():
            print("Retrying to connect...")
            time.sleep(5)
        try:
            request = f"GET /?{command_type}={signal} HTTP/1.1\r\nHost: {self.esp32_ip}\r\n\r\n"
            self.sock.sendall(request.encode())
            response = self.sock.recv(4096)
            print(f"Received from ESP32: {response.decode()}")
        except Exception as e:
            print(f"Error sending {command_type} command to ESP32:", e)
        finally:
            self.close_socket()

    def send_action_signal(self, action_signal):
        self.send_signal("action", action_signal)

    def send_turn_signal(self, turn_signal):
        self.send_signal("turn", turn_signal)

    def get_path_settings(self):
        while True:
            self.area = input("Enter area: ")
            if len(self.area) == 1:
                print("Error: Please scan the correct area qrcode.")
            else:
                print("area ok\n")
                break
        
        while True:
            self.start = input("Enter start: ")
            if len(self.start) > 1:
                print("Error: Please scan the correct start qrcode.")
            else:
                print("start ok\n")
                break
        
        while True:
            self.end = input("Enter end: ")
            if len(self.start) > 1:
                print("Error: Please scan the correct end qrcode.")
            elif self.start == self.end:
                print("Error: The start and end are the same.")
            else:
                print("end ok\n")
                break
        
        print(f"from {self.start} to {self.end} in {self.area} \n")
    
    def calculate_path(self):
        print("Calculated path : ")
        self.path = {
            "A": [0, 0],
            "B": [1, 0],
            "C": [2, 0],
            "D": [3, 2],
            "E": [4, 0],
            "F": [5, 0],
            "G": [6, 2],
            "H": [7, 0],
            "I": [8, 0],
            "J": [9, 0],
            "K": [10, 1],
            "L": [11, 0],
            "M": [12, 0],
            "N": [13, 0]
        }
        print(self.path, "\n")

    def run(self):
        self.get_path_settings()
        self.calculate_path()

        self.send_action_signal(1)  # start car

        while True:
            arrive = input()
            print("arrive", arrive)
            if arrive == self.end:
                print("stop car\n")
                self.send_action_signal(0)  # stop car
                break
            else:
                if self.path[arrive][0] > self.visited:
                    print("turn", self.path[arrive][1], "\n")
                    self.send_turn_signal(self.path[arrive][1])
                    self.visited = self.path[arrive][0]
                else:
                    print("already passed")

if __name__ == "__main__":
    controller = QRcodeScanControl()
    controller.run()