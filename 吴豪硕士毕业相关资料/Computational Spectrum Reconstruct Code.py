import matplotlib.pyplot as plt
from tensorflow import keras
import numpy as np
np.random.seed(1337)
from keras.models import Model
from tensorflow.keras.models import *
from keras.layers import Input, Dense, Reshape, Flatten, Dropout
import tensorflow as tf
import os
import cv2 as cv
import imutils
import scipy.io as scio
from keras.optimizers import adam_v2



#
# crop_x_start=858
# crop_w_start=180
# crop_y_start=671
# crop_h_start=180
# crop_round=1.4
# plot_x_start=7
# plot_y_start=7
# plot_interval=17
# plot_size=10
#
# XTrain=[]
# YTrainyuan=[]
# YTrain=[]



# def DataLoad(num,txt_path,img_path,txt_path_list,img_path_list,insert):
#     XTrain = []
#     YTrain = []
#     for n in range(num):
#         txt=np.loadtxt(txt_path+"/"+txt_path_list[n],dtype='float',delimiter=';')
#         crop_img = cv.imread(img_path + "/" + img_path_list[n])
#         x=txt[350:1700,0].reshape((-1,))
#         y=txt[350:1700,1].reshape((-1,))
#         for n1 in range(x.shape[0]):
#             if y[n1]<0:
#                 y[n1]=0
#
#         y = y / np.max(y)
#         x_insert = []
#         y_insert = []
#
#         for i in range(num):
#             x_insert.append(x[int(i*insert)])
#             y_insert.append(y[int(i*insert)])
#
#         YTrain.append(y_insert)
#         # y_new = make_interp_spline(x, y)(x_new)
#         # y_new = y_new / np.max(y_new)
#         crop_img=cv.cvtColor(crop_img,cv.COLOR_BGR2GRAY)
#         crop_img=imutils.rotate(crop_img,crop_round)
#         crop_img=crop_img[crop_y_start:crop_y_start+crop_h_start,crop_x_start:crop_x_start+crop_w_start]
#         data=[]
#         for j in range(10):
#             for i in range(10):
#                 temp=crop_img[int(plot_y_start+plot_interval*i):int(plot_y_start+plot_interval*i+plot_size),int(plot_x_start+plot_interval*j):int(plot_x_start+plot_interval*j+plot_size)]
#                 data.append(np.mean(temp))
#         data=np.array(data)
#         data = data/np.max(data)
#         XTrain.append(data)
#         # YTrain.append(y_new)
#     return np.array(XTrain),np.array(YTrain)

# img_path=r"E:\20211028\one\XTrain"
# img_path_list=os.listdir(img_path)
# img_path_list.sort(key=lambda x:int(x[4:-4]))
# txt_path=r"E:\20211028\one\YTrain"
# txt_path_list=os.listdir(txt_path)
# txt_path_list.sort(key=lambda x:int(x[10:-14]))
# DanXtrain,DanYtrain=DataLoad(344,txt_path,img_path,txt_path_list,img_path_list)
#
# img_path=r"E:\20211028\XTrain"
# img_path_list=os.listdir(img_path)
# img_path_list.sort(key=lambda x:int(x[4:-4]))
# txt_path=r"E:\20211028\YTrain"
# txt_path_list=os.listdir(txt_path)
# txt_path_list.sort(key=lambda x:int(x[10:-14]))
# KuanXtrain,KuanYtrain=DataLoad(249,txt_path,img_path,txt_path_list,img_path_list)


# X_train, X_test, y_train, y_test = train_test_split(XTrain, YTrainyuan, test_size=0.2,insert)
# print(len(X_train))


#定义的高斯函数
def func(x, a, b, c):
    return a * (-(np.exp((x-b)**2) / (2*c**2)))




def average(data):
    return np.sum(data)/len(data)
#标准差
def sigma(data,avg):
    sigma_squ=np.sum(np.power((data-avg),2))/len(data)
    return np.power(sigma_squ,0.5)
#高斯分布概率
def prob(data,avg,sig):
    sqrt_2pi=np.power(2*np.pi,0.5)
    coef=1/(sqrt_2pi*sig)
    powercoef=-1/(2*np.power(sig,2))
    mypow=powercoef*(np.power((data-avg),2))
    return coef*(np.exp(mypow))


#样本数据

#根据样本数据求高斯分布的平均数
#
# reg= LinearRegression(positive=True)  # 此处使用
# T=[]
# avgs=[]
# sigs=[]
# for i in range(344):
#     ave=average(DanYtrain[i])
#     avgs.append(ave)
#     sigs.append(sigma(DanYtrain[i],ave))
#
# f=np.zeros((344,2))
# f[:,0]=np.array(avgs)
# f[:,1]=np.array(sigs)
# f=f.reshape(344,2)
# reg.fit(DanXtrain,f)
# T.append(reg.coef_)




#读取实测光谱数据
one_txt_path = r"E:\20211028\one\YTrain"
one_txt_path_list = os.listdir(one_txt_path)
one_txt_path_list.sort(key=lambda x: int(x[11:-11]))

#光滑曲线函数
def moving_average(interval, windowsize):
    window = np.ones(int(windowsize)) / float(windowsize)
    re = np.convolve(interval, window, 'same')
    return re


y_one_train = []
for n in range(190):
    txt = np.loadtxt(one_txt_path + "/" + one_txt_path_list[n], dtype='float',delimiter=";")
    y = txt[:, 1].reshape((-1,))
    for n1 in range(y.shape[0]):
        if y[n1] < 0:
            y[n1] = 0

    y = y / np.max(y)
    y_insert = []
    for i in range(201):
        y_insert.append(y[int(i * 5.19)])

    re = moving_average(y_insert, 20)
    y_one_train.append(y_insert)
y_one_train=np.array(y_one_train)


txt_path = r"E:\20220214\YTrain"
txt_path_list = os.listdir(txt_path)
txt_path_list.sort(key=lambda x: int(x[11:-11]))
y_orgin_train = []

for n in range(1000):
    txt = np.loadtxt(txt_path + "/" + txt_path_list[n], dtype='float')
    y = txt[:, 1].reshape((-1,))
    for n1 in range(y.shape[0]):
        if y[n1] < 0:
            y[n1] = 0

    y = y / np.max(y)
    y_insert = []
    for i in range(201):
        y_insert.append(y[int(i * 5.19)])

    re = moving_average(y_insert, 20)
    y_orgin_train.append(y_insert)
y_orgin_train=np.array(y_orgin_train)


y_test=np.concatenate((y_train,y_one_train),axis=0)



#高斯随机噪音函数
import random

def gauss_noisy(y,sigma):
    mu = 0
    y_noisy=[]
    for i in range(len(y)):
        y_noisy.append(np.abs(random.gauss(mu, sigma))+y[i])

    y_noisy=np.array(y_noisy)
    y_noisy=y_noisy/np.max(y_noisy)
    return y_noisy



#生成不同程度随机噪音光谱曲线
y_Expansion_train=[]

for j in range(1000):
    for i in range(20):
        re= moving_average((y_test[i+i*40]+y_test[j])/2, 10)
        yn1=gauss_noisy(re,0.05)
        yn2=gauss_noisy(re,0.1)
        yn3=gauss_noisy(re,0.15)
        yn4=gauss_noisy(re,0.2)
        y_Expansion_train.append(re)
        y_Expansion_train.append(yn1)
        y_Expansion_train.append(yn2)
        y_Expansion_train.append(yn3)
        y_Expansion_train.append(yn4)
y_Expansion_train=np.array(y_Expansion_train)








Filter_Datas=[]
for j in range(4):
    Temp=[]
    path = r"D:\Pythondemo01\t\T_mat+_h_" + str(j + 1) + "um_w_grating_"
    if(j==3):
        path = r"D:\Pythondemo01\t\T_mat+_h_" + str(6) + "um_w_grating_"
    for i in range(100,501):
        tempdata=np.loadtxt(path+str(i)+".txt")
        if (np.sum(tempdata) / 201 > 0.85):
            continue
        for n in range(201):
            if(tempdata[n]>1):
                tempdata[n]=1
        Temp.append(tempdata)
    Filter_Datas.append(Temp)

def Filter_Function():
    Start_Datas=np.zeros((4,401,201))
    for j in range(4):
        path = r"D:\Pythondemo01\t\T_mat+_h_" + str(j + 1) + "um_w_grating_"
        if(j==3):
            path = r"D:\Pythondemo01\t\T_mat+_h_" + str(6) + "um_w_grating_"
        for i in range(100,501):
            tempdata=np.loadtxt(path+str(i)+".txt")
            Start_Datas[j,i-100,:]=tempdata
    return Start_Datas
Start_Datas=Filter_Function()


#互相关函数
def Cross_Correlation_coefficient(x,y):
    XE = np.sum(x) / 201
    YE = np.sum(y) / 201
    shang = 0
    xia1 = 0
    xia2 = 0
    for k in range(201):
        shang += (x[k] - XE) * (y[k] - YE)
        xia1 += np.power(x[k] - XE, 2)
        xia2 += np.power(y[k] - YE, 2)
    r =np.abs(shang / (np.power(xia1, 0.5) * np.power(xia2, 0.5)))
    return r



FilterDataRs = []
for n in range(4):
    rs = []
    FilterDatas=np.array(Filter_Datas[n])
    for i in range(FilterDatas.shape[0]):
        r = 0
        for j in range(FilterDatas.shape[0]):
            r += Cross_Correlation_coefficient(FilterDatas[i,:],FilterDatas[j,:])
        rs.append(r / FilterDatas.shape[0])
    FilterDataRs.append(rs)







def DesignT(T,Temp):
    r=0
    minr=1
    for i in range(T.shape[0]):
        tempr=Cross_Correlation_coefficient(T[i],Temp)
        if(tempr<minr):
            minr=tempr
        r+=tempr
    return r,minr



FilterDataRs=np.array(FilterDataRs)
for n in range(4):
    XE=np.sum(FilterDatas[3,113])/201
    rbests=[]
    for i in range(401):
        YE=np.sum(FilterDatas[3,i])/201
        xia1=0
        xia2=0
        shang=0
        for j in range(201):
            shang += (FilterDatas[3,113,j]-XE)*(FilterDatas[3,i,j])
            xia1 += np.power(FilterDatas[3,113,j]-XE,2)
            xia2 += np.power(FilterDatas[3,i,j]-YE,2)
        r=np.abs(shang/np.power(xia1*xia2,0.5))
        rbests.append(r)



rbest=FilterDataRs[0].copy()
rIndex=[]
for i in range(224):
    min_index=rbest.index(min(rbest))
    rIndex.append(min_index)
    rbest[min_index]=1

rIndex=np.array(rIndex)
rbestIndex=rIndex[:100]
T=[]
for i in range(100):
    T.append(np.array(Filter_Datas[0])[rbestIndex[i]])
T=np.array(T)






x_Expansion_train=[]
for i in range(y_Expansion_train.shape[0]):
    X_Temp=[]
    for k in range(100):
        datatemp=0
        for n in range(201):
            datatemp +=T[k,n]*y_Expansion_train[i,n]
        X_Temp.append(datatemp)
    x_Expansion_train.append(X_Temp)
x_Expansion_train=np.array(x_Expansion_train)


x_test=[]
for i in range(y_test.shape[0]):
    X_Temp = []
    for k in range(100):
        datatemp = 0
        for n in range(201):
            datatemp += T[k, n] * y_test[i, n]
        X_Temp.append(datatemp)
    x_test.append(X_Temp)
x_test = np.array(x_test)

# for i in range(401):
    # plt.plot(np.linspace(8,12,201),np.array(Start_Datas[0])[i])
plt.xlim(8,12)
plt.ylim(0,1)
plt.xlabel("Wavelength/um")
plt.ylabel("Transmissivity")
plt.title("Transmittance function library")
plt.show()






from numpy import array, diag, dot, maximum, empty, repeat, ones, sum
from numpy.linalg import inv

def IRLS(y, X, maxiter, w_init = 1, d = 0.0001, tolerance = 0.001):
    n,p = X.shape
    delta = array( repeat(d, n) ).reshape(1,n)
    w = repeat(1, n)
    W = diag( w )
    B = dot( inv( X.T.dot(W).dot(X) ),
             ( X.T.dot(W).dot(y) ) )
    for _ in range(maxiter):
        _B = B
        _w = abs(y - X.dot(B)).T
        w = float(1)/maximum( delta, _w )
        W = diag( w[0] )
        B = dot( inv( X.T.dot(W).dot(X) ),
                 ( X.T.dot(W).dot(y) ) )
        tol = sum( abs( B - _B ) )
        print("Tolerance = %s" % tol)
        if tol < tolerance:
            return B
    return B


model=keras.Sequential([
    keras.layers.Dense(100,activation=tf.nn.relu),
    keras.layers.Dense(120,activation=tf.nn.relu),
    keras.layers.Dense(150,activation=tf.nn.relu),
    keras.layers.Dense(170,activation=tf.nn.relu),
    keras.layers.Dropout(rate=0.2),
    keras.layers.Dense(201,activation=tf.nn.relu),
])
model.compile(optimizer="adam",loss=tf.losses.mean_squared_error,metrics=['accuracy'])
model.fit(x_train[:900],y_train[:900],epochs=2000,batch_size=100)


input_img = Input(shape=(201,))

# encoder layers
encoded = Dense(200, activation=tf.nn.relu)(input_img)
encoded = Dense(150, activation=tf.nn.relu)(encoded)
encoded = Dense(120, activation=tf.nn.relu)(encoded)
encoder_output = Dense(100)(encoded)

# decoder layers
decoded = Dense(120, activation=tf.nn.relu)(encoder_output)
decoded = Dense(150, activation=tf.nn.relu)(decoded)
decoded = Dropout(rate=0.2)(decoded)
decoded = Dense(200, activation=tf.nn.relu)(decoded)
decoded = Dense(201, activation=tf.nn.relu)(decoded)

# construct the autoencoder model
autoencoder = Model(inputs=input_img, outputs=decoded)
decoder=Model(inputs=encoder_output, outputs=decoded)
encoder=Model(inputs=input_img, outputs=encoder_output)

autoencoder.compile(optimizer="adam",loss=tf.losses.mean_squared_error,metrics=['accuracy'])

epochs = 1000
batch_size = 1000

history = autoencoder.fit(y_train,y_test,batch_size=batch_size,epochs=epochs, verbose=1)



# 定义编码器网络
encoder_inputs = tf.keras.layers.Input(shape=(100,))
x = tf.keras.layers.Dense(64, activation='relu')(encoder_inputs)
x = tf.keras.layers.Dense(32, activation='relu')(x)
encoder_outputs = tf.keras.layers.Dense(16, activation='relu')(x)

# 定义解码器网络
decoder_inputs = tf.keras.layers.Input(shape=(16,))
x = tf.keras.layers.Dense(32, activation='relu')(decoder_inputs)
x = tf.keras.layers.Dense(64, activation='relu')(x)
decoder_outputs = tf.keras.layers.Dense(100, activation='sigmoid')(x)

# 定义整个自编码器模型
autoencoder = tf.keras.models.Model(inputs=encoder_inputs, outputs=decoder_outputs)

# 编译模型
autoencoder.compile(optimizer='adam', loss='binary_crossentropy')

# 打印模型概述
autoencoder.summary()

autoencoder.fit(X, y, epochs=10, batch_size=32)

y_average_train=[]
for i in range(1010):
    re=moving_average(y_train[i],10)
    y_average_train.append(re)
y_average_train=np.array(y_average_train)


import torch
import torch.nn as nn
from torch.utils.data import TensorDataset, DataLoader
import numpy as np


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
class SelfAttention(nn.Module):
    def __init__(self, input_dim):
        super(SelfAttention, self).__init__()
        self.query = nn.Linear(input_dim, input_dim)
        self.key = nn.Linear(input_dim, input_dim)
        self.value = nn.Linear(input_dim, input_dim)
        self.softmax = nn.Softmax(dim=-1)
    def forward(self, x):
        query = self.query(x)
        key = self.key(x)
        value = self.value(x)
        scores = torch.matmul(query, key.transpose(-2, -1))
        attention_weights = self.softmax(scores)
        attended_values = torch.matmul(attention_weights, value)
        return attended_values
class FullyConnectedNetwork(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(FullyConnectedNetwork, self).__init__()
        self.attention1 = SelfAttention(input_dim)
        self.fc1 = nn.Linear(input_dim, 120)
        self.attention2 = SelfAttention(120)
        self.fc2 = nn.Linear(120, 150)
        self.attention3 = SelfAttention(150)
        self.fc3 = nn.Linear(150, output_dim)
        self.relu = nn.ReLU()
        self.Droupt=nn.Dropout(0.2)
    def forward(self, x):
        x= self.attention1(x)
        x = self.relu(self.fc1(x))
        x = self.attention2(x)
        x = self.relu(self.fc2(x))
        x = self.attention3(x)
        x=self.Droupt(x)
        x = self.relu(self.fc3(x))
        return x

x_train=np.loadtxt(r"D:\Pythondemo01\x_Expansion_train.csv",delimiter=',')
y_train=np.loadtxt(r"D:\Pythondemo01\y_Expansion_train.csv",delimiter=',')
input_data = torch.from_numpy(x_train).to(torch.float32).to(device)
output_data = torch.from_numpy(y_train).to(torch.float32).to(device)
dataset = TensorDataset(input_data, output_data)
# 定义超参数和模型实例
batch_size = 300
num_epochs = 100
learning_rate = 0.001
weight_decay=0.001
model = FullyConnectedNetwork(100, 201).to(device)
# 定义损失函数和优化器
criterion = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate,weight_decay=weight_decay)
# 创建数据加载器
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True)
# 训练模型
total_step = len(dataloader)
for epoch in range(num_epochs):
    for i, (inputs, labels) in enumerate(dataloader):
        # 将数据移动到GPU
        inputs = inputs.to(device)
        labels = labels.to(device)
        # 前向传播
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        # 反向传播和优化
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        # 打印训练信息
        if (i + 1) % 100 == 0:
            print(f'Epoch [{epoch + 1}/{num_epochs}], Step [{i + 1}/{total_step}], Loss: {loss.item()}')
# 在训练完成后，你可以使用训练好的模型进行预测
test_input = torch.randn(1, 100).to(device)
predicted_output = model(test_input)
print(predicted_output.shape)  # 输出: torch.Size([1, 201])

def R2_fun(y, y_forecast):
    # 拟合优度R^2
    y_mean=np.mean(y)
    return 1 - (np.sum((y_forecast - y) ** 2)) / (np.sum((y - y_mean) ** 2))

def MSE_fun(y,y_forecast):
    return np.sum((y-y_forecast)**2)/(y.shape[0])


class ResidualBlock(tf.keras.layers.Layer):
    def __init__(self, units, dropout_rate=0.2, l2_reg=0.01):
        super(ResidualBlock, self).__init__()
        self.units = units
        self.dropout_rate = dropout_rate
        self.l2_reg = l2_reg
        self.attention = SelfAttention(units)
        self.dense1 = tf.keras.layers.Dense(units, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l2_reg))
        self.dropout = tf.keras.layers.Dropout(dropout_rate)
        self.dense2 = tf.keras.layers.Dense(units, kernel_regularizer=tf.keras.regularizers.l2(l2_reg))
    def call(self, inputs, training=False):
        attention_output = self.attention(inputs)
        x = self.dense1(attention_output)
        x = self.dropout(x, training=training)
        x = self.dense2(x)
        output = tf.keras.layers.add([inputs, x])
        return output
class SelfAttention(tf.keras.layers.Layer):
    def __init__(self, units):
        super(SelfAttention, self).__init__()
        self.units = units
    def build(self, input_shape):
        self.W_q = self.add_weight(shape=(input_shape[-1], self.units),
                                   initializer=tf.keras.initializers.GlorotUniform(),
                                   trainable=True)
        self.W_k = self.add_weight(shape=(input_shape[-1], self.units),
                                   initializer=tf.keras.initializers.GlorotUniform(),
                                   trainable=True)
        self.W_v = self.add_weight(shape=(input_shape[-1], self.units),
                                   initializer=tf.keras.initializers.GlorotUniform(),
                                   trainable=True)
    def call(self, inputs):
        q = tf.matmul(inputs, self.W_q)
        k = tf.matmul(inputs, self.W_k)
        v = tf.matmul(inputs, self.W_v)
        attention_weights = tf.nn.softmax(tf.matmul(q, k, transpose_b=True))
        attention_output = tf.matmul(attention_weights, v)
        return attention_output
# 构建带有残差连接和正则化的自注意机制的全连接模型
model = tf.keras.Sequential([
    tf.keras.layers.Dense(100, activation='relu'),
    ResidualBlock(100, dropout_rate=0.2, l2_reg=0.001),
    tf.keras.layers.Dense(120, activation='relu'),
# ResidualBlock(120, dropout_rate=0.2, l2_reg=0.001),
    tf.keras.layers.Dense(150, activation='relu'),
    # ResidualBlock(150, dropout_rate=0.2, l2_reg=0.001),
    tf.keras.layers.Dense(170, activation='relu'),
    # tf.keras.layers.Dense(200, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(0.01)),
    # ResidualBlock(170, dropout_rate=0.2, l2_reg=0.001),
    tf.keras.layers.Dropout(0.15),
    tf.keras.layers.Dense(201, activation='relu'),
])
# 编译模型
model.compile(optimizer='adam',loss=tf.losses.mean_squared_error,metrics=['accuracy'])
# 训练模型
model.fit(x_Expansion_train[:90000], y_Expansion_train[:90000],
          epochs=500, batch_size=3000, validation_data=(x_Expansion_train[90000:], y_Expansion_train[90000:]))

p=1000
pre=model.predict((x_test[p].reshape((1,100))))

# pre=model(torch.from_numpy(x_train[p].reshape(1,100)).to(torch.float32).to(device))
# pre=torch.Tensor.cpu(pre)
# pre=pre.detach().numpy()

pre=pre.reshape((-1,))
R2=R2_fun(y_orgin_train[p],pre)
MSE=R2_fun(y_orgin_train[p],pre)
R2=round(R2,4)
MSE=round(MSE,4)
plt.plot(np.linspace(8,12,201),y_orgin_train[p],label='Measured spectrum')
plt.plot(np.linspace(8,12,201),pre,label="Reconstruction Result\n R2"+str(R2)+"\n MSE"+str(MSE))
plt.xlabel('Wavelength(nm)')
plt.ylabel('Intensity(a.u)')
plt.title("Reconstruction results")
plt.xlim(8,12)
plt.ylim(0,1)
plt.subplots_adjust(left=0.1, bottom=0.09, right=0.60, top=0.85)
plt.legend(bbox_to_anchor=(1.05,1), loc=3, borderaxespad=0)
plt.legend()
plt.show()