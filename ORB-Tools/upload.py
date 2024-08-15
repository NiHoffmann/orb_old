import subprocess
import sys
import os

address_offset = "0"
dfuse_address = " 0x080E0000"

if len(sys.argv) > 1:
	prog_name = sys.argv[1]
else:
	prog_name = 'program.py'

def rreplace(s, old, new, occurence = 1):

    if occurence == 0:
        return s

    left, found, right = s.rpartition(old)

    if found == "":
        return right
    else:
        return rreplace(left, old, new, occurence - 1) + new + right

subprocess.run(["./../micropython/mpy-cross/build/mpy-cross.exe", "./program/" + prog_name]) 

mpy_path = rreplace("./program/" + prog_name, '.py' , '.mpy' , 1);
mpy_size = os.stat(mpy_path).st_size.to_bytes(4,'big')
bin_path = rreplace("./program/" + prog_name, '.py' , '.bin' , 1);

with open(mpy_path,'rb') as mpy_file:
	with open(bin_path,'wb') as bin_file:
		bin_file.write(mpy_size)
		while True:
			b = mpy_file.read(1)
			if b: 
			# process b if this is your intent   
				n = bin_file.write(b)
			else: 
				break

subprocess.run([ ".\dfu-util.exe", "-a", address_offset , "--dfuse-address", dfuse_address ,"-D" , bin_path]) 

#os.remove(mpy_path)
#os.remove(bin_path)