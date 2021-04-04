
Instructions to execute files of this repository : 
Binaries are available under the raspberry Pi 48 
- TD1a_main.cpp : ./TD1a_main_test \<duration in ms\> 
- TD1b_main.cpp : ./TD1b_main_test                                 --> you should see numbers from 1 to 15 printed on the screen each 0.5 seconds. 
- TD1c_main.cpp : ./TD1c_main_test \<number of desired loops\>       --> You should see printed the final value of the pointer and the total duration of the loop
- TD1d_main.cpp : ./TD1d_main_test \<duration of the timer in ms\>   --> You should see the final value of the counter after the expiration of the timer. 
- TD1d_main_bis.cpp : ./TD1d_main_bis_test                         --> You should see two calibrations : with Posix timers and with the real_time_clock. The
                                                                       execution may take few seconds. 
- TD1e_main.cpp : ./TD1e_main_test \<number of samples\> \<sampling period in ms\>    --> Here also you should see two walibrations with Posix Timers and ith the 
                                                                                      real_time_clock. The execution may take few seconds according to the sampling
                                                                                      period and the desired number of samples. 
