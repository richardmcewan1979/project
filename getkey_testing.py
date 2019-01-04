"""This does what I want for now
	just need to integrate it into bluetooth
	need to check if this satisfies unicode so may need a patch for that
	Therefore might be easier to use raw_input
	alternatively this could all be pulled into event handling if I can get vpython working.
	That may indeed be necessary anyway.

	However for now. Let's use this to get the structure of the bluetooth exchange correct.
"""

from getkey import getkey, keys

print("Programme starting")

#key = "" required for raw_input method
key =""


while key !='r':
	#This works....
	#key = raw_input("please enter a key")
	key = getkey()

	if key == keys.UP:
		print("you pressed up")

	elif key == keys.DOWN:
		print("you pressed down")

	elif key == keys.RIGHT:
		print("you pressed right")

	elif key == keys.LEFT:
		print("you pressed left")

	else: #possible not helpful
		buffer += key
		print(buffer)
