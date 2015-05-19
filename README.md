leveldb_server
===============
    Leveldb simple udp server and test client.
    Data serialization with protobuf,and event loop by libev.
    Test on Kali Linux.

#####1.Install necessary libraries
    sudo apt-get install libleveldb-dev libprotobuf7 libprotobuf-dev protobuf-compiler libev-dev
#####2.generate protobuf files---This step can be ignored
    cd pb/
    protoc --cpp_out=./ ldbdata.proto
#####3.Compile the udp server
    cd testudpserver/
    make clean all
    ./test_udp_server
#####4.Compile the udp client
    cd testudpclient/
    make clean all
    ./test_udp_client

