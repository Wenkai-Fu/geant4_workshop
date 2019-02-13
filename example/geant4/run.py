import numpy as np
import os

def writer(history):
    """UI mac file writer
        history: int
            number of histories
    """
    with open('./run.mac', 'w') as f:
        s = """# Initialize kernel
/run/initialize

# verbose setting
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0

# GPS definition
# neutron
/gps/particle neutron

# position sampling
/gps/pos/centre -6 0 0 cm

# direction sampling
/gps/direction 1 0 0

/gps/ene/mono 1 MeV

/run/beamOn HISTORY"""
        s = s.replace('HISTORY', '%i'%history)
        
        f.write(s)
                
if __name__ == '__main__':
    writer(1000)
    os.system("cd build && rm -rf * && cmake .. && make -j20")
    os.system("./build/msnd run.mac > out.txt")