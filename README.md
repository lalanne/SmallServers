
[![Build Status](https://travis-ci.org/lalanne/SmallServers.svg?branch=develop)](https://travis-ci.org/lalanne/SmallServers)

# SmallServers
Just Small Servers for fun  and profit. 
The main idea is to have small servers that show the main features of the languages to write this kind 
of apps. To have several in different languages will be able to compare performace and to learn more about 
the the low level characteristics of these languages.

## cpp
    Boost should be installed in the system, this is for mt and st
### Build:
```
$ cd cpp
$ cmake .
$ make
```
### Execution:
 - **target:** mt or st
 - **ip:** server ip
 - **port:** service port
```
$ cd target
$ ./target <ip> <port>
```
### Testing:
Root of the project
```
./build_cpp.sh
```
## go
    This is for mt and st
### dependencies
```
$ cd go
$ go get golang.org/x/net/html/charset
```
### Build
```
$ cd go
$ go install common
$ go install st
$ go install mt
```
### Execution:
 - **target:** mt or st
 - **ip:** server ip
 - **port:** service port
```
$ cd bin
$ ./target <ip> <port>
```
### Testing
Root of the project
```
./build_go.sh
```
## python
    This is for mt and st
### Execution
 - **target:** mt or st
 - **ip:** server ip
 - **port:** service port
```
$ cd target
$ python server.py <ip> <port>
```
### Testing
Root of the project
```
./build_py.sh
```


