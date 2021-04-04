Instructions to execute files of this repository : Binaries are available under the raspberry Pi 48, repository /TD4
-
- TD4a_main.cpp : ./TD4a_main_test 
- main_td4b : ./test_td4b
- main_td4b_bis :  ./test_td4b_bis <nLoops> <nTasks> <protected_mode : bool> 
- main_td4c : ./test_td4c
- main_td4d : ./test_td4d

Compile code :
- main_td4b_bis :  arm-linux-g++ main_td4b_bis.cpp Mutex.cpp -o test_td4b_bis -lrt -lpthread
- main_td4c : arm-linux-g++ main_td4c.cpp Semaphore.cpp Mutex.cpp -o test_td4c -lrt -lpthread -Wall
- main_td4d : arm-linux-g++ main_td4d.cpp Fifo.hpp Mutex.cpp -o test_td4d -lrt -lpthread



