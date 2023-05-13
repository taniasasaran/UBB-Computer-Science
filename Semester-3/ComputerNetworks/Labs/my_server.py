import socket
import threading
from time import sleep

mylock = threading.Lock()
threads = []


def workerThread(client_socket):
    while True:
        # mylock.acquire()

        rcvdData = client_socket.recv(1024).decode()
        if rcvdData.casefold() == "bye".casefold():
            # mylock.release()
            break
        print("S:", rcvdData)
        sendData = input("N: ")
        client_socket.send(sendData.encode())

        # mylock.release()
    client_socket.close()


server_socket = socket.socket()
port = 12345
server_socket.bind(('127.0.0.1', port))
server_socket.listen(5)

while True:
    client_socket, client_address = server_socket.accept()
    print("Socket Up and running with a connection from", client_address)
    t = threading.Thread(target=workerThread, args=(client_socket,))
    threads.append(t)
    t.start()
