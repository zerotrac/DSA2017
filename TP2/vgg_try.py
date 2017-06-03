# py-3.6 utf-8

from PIL import Image
import numpy as np
from keras.applications.vgg19 import VGG19
from keras.models import Model
from keras.layers import Dense, Dropout, Flatten
from os import listdir

eps = 1e-7

# categorize
group =\
[
    ("n01613177", "birds", 1826, 2320),
    ("n01923025", "insects", 2321, 2825),
    ("n02278980", "butterflies", 504, 1133),
    ("n03767203", "wheels", 3852, 4355),
    ("n03877845", "buildings", 0, 503),
    ("n04515003", "pianos", 2826, 3333),
    ("n04583620", "planes", 3334, 3851),
    ("n07897438", "wines", 4356, 4982),
    ("n10247358", "women", 4983, 5612),
    ("n11669921", "flowers", 1134, 1825)
]

# load vgg model
print("loading vgg model...")
base_model = VGG19(weights='imagenet', input_shape=(224, 224, 3), include_top=False)
x = base_model.get_layer('block5_pool').output
x = Flatten(name="flat_1")(x)
x = Dense(256, activation="relu", name="dense_relu_1")(x)
y = Dropout(0.5, name="drop_1/2")(x)
predictions = Dense(10, activation="softmax", name="dense_softmax_1")(y)
modelvec = Model(inputs=base_model.input, outputs=predictions)
modelvec.load_weights("modelvgg_3.h5")
modelfeature = Model(inputs=modelvec.input, outputs=y)

# load training set
print("loading training set...")
feature = open("vgg_features.txt", "r").readlines()
train = np.zeros((len(feature), len(feature[0].strip().split())-1), dtype="float32")
trainnames = []
for i in range(len(feature)):
    p = feature[i].strip().split()
    for j in range(1, len(p)):
        train[i][j-1] = float(p[j])
    trainnames.append(p[0])

# load query set
querynames = []
for i in listdir("query"):
    if i != ".DS_Store":
        querynames.append(i)

querynamecnt = len(querynames)
print("find", querynamecnt, "query images.")

def dist_cb(x, y, z):
    return sum(np.abs(x-y)/(np.abs(x)+np.abs(y)+z))

cnt = 0
z = np.zeros(256, dtype="float32")
for i in range(256):
    z[i] = eps

for name in querynames:
    cnt += 1
    print("query on "+str(cnt)+"/"+str(querynamecnt)+":", name)
    print(name[:name.index(".")], end=":")
    fet = np.array(Image.open("query/" + name).resize((224, 224)).getdata()).reshape((1, 224, 224, 3))
    vec = modelfeature.predict(fet)
    grad = vec.reshape(vec.size)

    aa = [(i, dist_cb(grad, train[i], z)) for i in range(len(trainnames))]
    bb = sorted(aa, key=lambda jsy: jsy[1])
    for i in range(0, 10):
        curname = trainnames[bb[i][0]]
        print(curname[:curname.index(".")], end="")
        if i == 9:
            print()
        else:
            print(end=",")
