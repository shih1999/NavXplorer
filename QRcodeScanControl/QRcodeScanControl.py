import socket
import time

IP = "192.168.***.***"
PORT = 80
DEBUG = True  # debug message signal

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
        for attempt in range(5):  # max retry times: 5
            try:
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.sock.settimeout(30)
                self.sock.connect((self.esp32_ip, self.esp32_port))
                if DEBUG:
                    print("Successfully connected to ESP32")
                return True
            except Exception as e:
                if DEBUG:
                    print("Error connecting to ESP32:", e)
                self.sock = None
                time.sleep(5)
        return False

    def close_socket(self):
        if self.sock:
            self.sock.close()
            self.sock = None
            if DEBUG:
                print("Socket closed")

    def send_signal(self, command_type, signal):
        while not self.connect_socket():
            if DEBUG:
                print("Retrying to connect...")
            time.sleep(5)
        try:
            request = f"GET /{command_type}?{command_type}={signal} HTTP/1.1\r\nHost: {self.esp32_ip}\r\n\r\n"
            if DEBUG:
                print(f"Sending request: {request}")
            self.sock.sendall(request.encode())
            response = self.sock.recv(4096)
            if DEBUG:
                print(f"Received from ESP32: {response.decode()}")
        except Exception as e:
            if DEBUG:
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
            if len(self.area) > 1:
                print("area ok\n")
                break
            else:
                print("Error: Please scan the correct area qrcode.")
        
        while True:
            self.start = input("Enter start: ")
            if len(self.start) == 1:
                print("start ok\n")
                break
            else:
                print("Error: Please scan the correct start qrcode.")
        
        while True:
            self.end = input("Enter end: ")
            if self.start == self.end:
                print("Error: The start and end are the same.")
            elif len(self.end) == 1:
                print("end ok\n")
                break
            else:
                print("Error: Please scan the correct end qrcode.")
        
        print(f"from {self.start} to {self.end} in {self.area} \n")
        
    # forward: 0,  left: 1, right: 2
    def calculate_path(self):
        # ask OpenAI for shortest path
        print("Calculated path : ")
        self.path = {
            "A": [0, 0],
            "B": [1, 0],
            "C": [2, 0],
            "D": [3, 2],
            "E": [4, 0],
            "F": [5, 0],
            "G": [6, 1],
            "H": [7, 0],
            "I": [8, 2],
            "J": [9, 0],
            "K": [10, 0],
            "L": [11, 1],
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
            if arrive != self.end:
                if self.path[arrive][0] > self.visited:
                    print("turn", self.path[arrive][1], "\n")
                    self.send_turn_signal(self.path[arrive][1])
                    self.visited = self.path[arrive][0]
                else:
                    print("already passed")
            else:
                print("stop car\n")
                self.send_action_signal(0)  # stop car
                break


if __name__ == "__main__":
    controller = QRcodeScanControl()
    controller.run()