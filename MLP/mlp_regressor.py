import numpy as np
import matplotlib.pyplot as plt
from sklearn.neural_network import MLPRegressor
from sklearn import preprocessing
from scipy import stats
import pickle

"""
reminders: 
 - X_data is a numpy ndarray with rows of constant size (fill hit info until out of hits and then fill 0s)
"""
X_data = np.load('./data/protons-0-300/X_train.npy')
y_data = np.load('./data/protons-0-300/y_train.npy')

X_data_scaled = preprocessing.scale(X_data)
std_scaler = preprocessing.StandardScaler()
std_scaler.fit(X_data)
pickle.dump(std_scaler, open('protons_300_nn_full_ss_std_scaler.sav', 'wb'))
X_data_scaled = std_scaler.transform(X_data)

ntrain = 0
ntest = 0
for ii, xx in enumerate(X_data):
    if ii%10 == 0:
        ntest += 1
    else:
        ntrain += 1

nfeatures = len(X_data_scaled[0])

X_train = np.ndarray((ntrain,nfeatures))
y_train = np.ndarray(ntrain)

X_test = np.ndarray((ntest,nfeatures))
y_test = np.ndarray(ntest)

itrain = 0
itest = 0
for ii, xx in enumerate(X_data_scaled):
    if ii%10 == 0:
        for jj, yy in enumerate(xx):
            X_test[itest][jj] = yy
        y_test[itest] = y_data[ii]
        itest += 1
    else:
        for jj, yy in enumerate(xx):
            X_train[itrain][jj] = yy
        y_train[itrain] = y_data[ii]
        itrain += 1

#reg = MLPRegressor(hidden_layer_sizes=(int(nfeatures/2),int(nfeatures/4),int(nfeatures/8)), 
reg = MLPRegressor(hidden_layer_sizes=(100), 
                  activation='logistic', solver='adam', alpha=1e-3, verbose=True, tol=5e-6)#lbfgs, adam, sgd for solver

"""
for choices on parameters, see the documentation at: https://scikit-learn.org/stable/modules/generated/sklearn.neural_network.MLPRegressor.html
"""

reg.fit(X_train, y_train)

pickle.dump(reg, open('protons_300_nn_full_ss.sav', 'wb'))

y_pred = reg.predict(X_test)

np.save('y_pred.npy', y_pred)
np.save('y_test.npy', y_test)
