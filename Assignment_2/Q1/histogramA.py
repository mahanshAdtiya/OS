import numpy as np
import matplotlib.pyplot as plt

file_pointer = open("threadA.txt","r");


xaxix = [1,2,3,4,5,6,7,7,8,9,10,12,13,14,15,16,17,18,19]
yaxis = []
for line in file_pointer:
    yaxis.append(float(line))


fig = plt.figure(figsize = (10, 5))
 
plt.bar(xaxix, yaxis, color ='maroon',width = 0.4)
plt.xlabel("Priorities")
plt.ylabel("Time taken by thread A")
plt.title("Change in time taken on changing priorities")
plt.show()