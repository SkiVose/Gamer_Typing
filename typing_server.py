#!/usr/bin/env python
from json.decoder import JSONDecodeError
import socketserver
from time import ctime
import os
import socket
import time
import threading
import queue
import json
import csv
from itertools import islice

HOST, PORT = '172.18.186.173', 5410
ADDR = (HOST, PORT)
filelist = []

def getFilelist():
    global filelist
    path = os.path.join(os.getcwd(), 'doc')
    # print(path)
    filelist = os.listdir(path)
    # print(type(filelist))


def retFilelist(idx):
    global filelist
    flist = []
    total = len(filelist)
    if(idx + 3 <= total):
        length = 3
    else:
        length = (total - idx) % 3
    
    for i in range(idx, idx + length):
        # print(filelist[i])
        flist.append(f'{filelist[i]}')
    # print(flist)
    msg = '#'.join(flist)
    # print(msg)
    return msg

def retFileData(name):
    filepath = os.path.join(os.getcwd(), 'doc')
    filepath = os.path.join(filepath, name)
    print(f'prepare to send {filepath}')
    
    with open(filepath, 'rb') as f:
        data = f.read()
    # print(data)
    return data
    

class MyRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        global filelist
        print('* connected from:', self.client_address)
        # while True:
        data = self.request.recv(1024)
        try:
            msg = data.decode('utf-8')
            print(msg)
            jsonData = json.loads(msg)
            print(f'{jsonData["method"]} {jsonData["idx"]}')
            if jsonData["method"] == "GET":
                print('now in get')
                for i in range(0, len(filelist), 3):
                    retMsg = json.dumps(retFilelist(i))
                    retMsg = retMsg.replace('"', '')
                    # print(retMsg)
                    self.request.sendall(retMsg.encode())
                    time.sleep(0.05)
                self.request.sendall(b'#END#')

            elif jsonData["method"] == "POST":
                print('now in post')
                fname = jsonData["idx"]
                dat = retFileData(fname)
                self.request.send(dat)

        except Exception as e:
            print(e)


if __name__ == '__main__':
    getFilelist()
    retFilelist(0)
    tcpServ = socketserver.ThreadingTCPServer(ADDR, MyRequestHandler)
    print('waiting for connection...')
    tcpServ.serve_forever()
