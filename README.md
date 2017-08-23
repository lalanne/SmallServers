
[![Build Status](https://travis-ci.org/lalanne/SmallServers.svg?branch=develop)](https://travis-ci.org/lalanne/SmallServers)

# SmallServers
Just Small Servers for fun  and profit. 
The main idea is to have small servers that show the main features of the languages to write this kind 
of apps. To have several in different languages will be able to compare performace and to learn more about 
the the low level characteristics of these languages.

## cpp
    Boost should be installed in the system, this is for mt and st
### Compilation:
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
###     Execution
*           * inside go's directory
*           $ go install common
            $ go install st
            $ go install mt
*           $ bin/mt or bin/st

## python
    This is for mt and st
###     Execution
*           $ enter mt or st folder
*           $ python server.py
