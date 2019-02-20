"""
read_train_data turns the csv output of ./preprocessMLP.C into numpy arrays to toss at models
"""
import csv
import numpy as np

xdata_in = []
ydata_in = []

with open('../train.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        xdata_row = []
        for ii, rr in enumerate(row):
            if ii == 0:
                ydata_in.append(rr)
            else:
                xdata_row.append(rr)
        xdata_in.append(xdata_row)

xdata = np.ndarray((len(xdata_in),len(xdata_in[0])))
print(len(xdata_in), len(xdata_in[0]))
for ii, xx in enumerate(xdata_in):
    for jj, yy in enumerate(xx):
        xdata[ii][jj] = yy

ydata = np.ndarray(len(ydata_in))
for ii, xx in enumerate(ydata_in):
    ydata[ii] = xx

np.save('X_train.npy', xdata)
np.save('y_train.npy', ydata)
