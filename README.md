# ofKinectPCLPublish

A proof concept of sending Kinect V2 point cloud data over the network via [zeroMQ](https://zeromq.org/).

See my other repository [ofKinectReceive](https://github.com/oneandonlyoddo/ofKinectPCLReceive) for the receiving and point cloud reconstructing part.

Written in c++ with [openFrameworks](https://openframeworks.cc/).

____

Tested on Windows 10



Requires:

+ openFrameWorks  (0.11.0)

+ [ofxZmqWindows](https://github.com/wearenocomputer/ofxZmqWindows) (make sure to follow the instructions about the .dll in the readme)
+ [ofxKinectV2](https://github.com/ofTheo/ofxKinectV2)
+ [ofxArgParser](https://github.com/satoruhiga/ofxArgParser)

____

Replace 

```c++
string serial = "502577241942";
string port = "13000";
int cloudDensity = 3;
```

with your KinectV2 serial, the zmq port you want to use and the cloud density to reduce the amount of data.

Alternatively you can pass that information as command line arguments.

```bash
ofKinectPublish.exe -serial 502577241942 -port 13000 -density 3
```



Cloud density is somewhat inverse. __int cloudDensity = 3;_ means only send every %3==0 point from the data. 



