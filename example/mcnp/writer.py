import os

s = """A simple MCNP example
c cell card
1 0           1    $ outside world
2 1 -0.001205 -1 2 $ air surrounding tank
3 2 -0.93     -2   $ in tank

c surface card
1 rpp -10 10 -10 10 -10 10 $ world
2 rpp  -5 5 -5 5 -5 5      $ tank

c data card
c material cards
c dry air, rho = 0.001205
m1 6000.70c   -0.000124 &
   7014.70c   -0.755268 &
   8016.70c   -0.231781 &
   18000.59c  -0.012827
c paraffin wax, C25H52, density = 0.93 g/cm3
m2 1001.70c  52 &
   6000.70c  25
c importance cards
imp:n 0 1 1
imp:h 0 1 1
imp:p 0 1 1
imp:# 0 1 1
imp:e 0 1 1
c mode card
mode p h # n e
c cut off card
cut:h j 0 $ default = 1 MeV
cut:# j 0 $ default = 5 MeV
c neutron physics
phys:n 6j 4
c tally card
+f6 3
sd6 1
c source card
sdef par=n erg=1 x=-6 y=0 z=0 vec=1 0 0 dir=1
nps 1000
print 110"""

os.system('rm simple.i simple.o')
with open('simple.i', 'w') as f:
    f.write(s)
os.system("mcnp6 i=simple.i o=simple.o ru=simple.ru")
os.system('rm simple.ru')










