from hashlib import sha256
import time

def generateID(type,name):
	current_time = time.time()
	hashedString = sha256(type+name+str(current_time))
	
	return hashedString.hexdigest()
