import numpy as np
import os


def writer(history):
    """UI mac file writer
        history: int
            number of MC histories
    """
    with open('./run.mac', 'w') as f:
        s = """ # UI mac file for the MSND model. 

# Initialize kernel
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

/run/beamOn HISTORY
"""
        s = s.replace('HISTORY', '%i'%history)
        
        f.write(s)
                
if __name__ == '__main__':
    writer(100)
    os.system("./build/msnd run.mac > out.txt")
    
    
    
    
    
    
    
    
    
