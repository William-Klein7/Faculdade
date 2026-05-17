import threading
import time
import random


TAMANHO_BUFFER = 5
buffer = []

mutex = threading.Semaphore(1)
empty = threading.Semaphore(TAMANHO_BUFFER)
full = threading.Semaphore(0)

def produtor():
    global buffer
    item_id = 0
    while True:
        time.sleep(random.uniform(0.5, 1.5))
        item = f"Item-{item_id}"
  
        empty.acquire()
        mutex.acquire()
        
        buffer.append(item)
        print(f"Produtor produziu {item}. Buffer: {buffer}")
        
        mutex.release()
        full.release()
        
        item_id += 1

def consumidor():
    global buffer
    while True:
        time.sleep(random.uniform(1, 2))
        
        full.acquire()
        mutex.acquire()
        
        item = buffer.pop(0)
        print(f"Consumidor consumiu {item}. Buffer: {buffer}")

        mutex.release()
        empty.release()


thread_produtora = threading.Thread(target=produtor)
thread_consumidora = threading.Thread(target=consumidor)

thread_produtora.start()
thread_consumidora.start()
