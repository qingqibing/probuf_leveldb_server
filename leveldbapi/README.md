leveldbapi
===========
leveldb simple C++ api, and it can be easy to use in C++ program,but only can be used in local machine, no tcp/udp server now.Test on Kali Linux.

####1.Install leveldb.
        sudo apt-get install libleveldb-dev
#####2.Change the compile path
        Change the compile path(/home/youzp) of Makefile and test.cpp to yours.
#####3.Compile the leveldbapi test program
        cd test/
        make clean all
        generating execute file : testldbapi
#####4.Exec the file
        ./testldbapi
        
        The exec resukt is:
        Enter Test01
        Open OK
        Put OK
        Value1:1234
        Delete OK
        Exit From Test01
        *********
        Enter Test02
        Put OK
        WriteBatch OK
        Value4:4444
        Exit From Test02
