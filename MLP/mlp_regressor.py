import numpy as np
import matplotlib.pyplot as plt
from sklearn.neural_network import MLPRegressor
from sklearn import preprocessing
from scipy import stats

X_data = np.load('./data/X_train.npy')
y_data = np.load('./data/y_train.npy')

X_data_scaled = preprocessing.scale(X_data)

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

reg = MLPRegressor(hidden_layer_sizes=(int(nfeatures/2)), 
                  activation='relu', solver='adam', alpha=1e-1, verbose=True, tol=1e-4)#lbfgs, adam, sgd for solver

reg.fit(X_train, y_train)

#import pickle
#pickle.dump(reg, open('eeg_nn_full_ss.sav', 'wb'))

y_pred = reg.predict(X_test)

residuals = (y_pred - y_test)/y_test
for ii, rr in enumerate(residuals):
    print(y_pred[ii], y_test[ii], rr)
