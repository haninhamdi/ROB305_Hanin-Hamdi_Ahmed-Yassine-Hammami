Instructions to execute files of this repository : Binaries are available under the raspberry Pi 48, repository /TD2 
-

- main_td2a.cpp : ./test_td2a \<nLoops\> \<nTasks\> --> You should see the duration, the value of nLoops and nTasks and the final value of the counter.

- main_td2b.cpp : ./test_td2b \<nLoops\> \<nTasks\> \<schedPolicy\> --> You should see the duration, the value of nLoops and nTasks and the final value of the counter.
\<schedPolicy\> can be : SCHED_RR, SCHED_FIFO or SCHED_OTHER. If you don't specify \<schedPolicy\>, the default value is SCHED_OTHER.

- main_td2c.cpp : ./test_td2c \<nLoops\> \<nTasks\> \<protected_mode : bool\> --> You should see the duration, the value of nLoops and nTasks and the final value of the counter.
\<protected_mode : bool\> is a boolean argument that specifies running code with mutex protected mode : \<protected_mode : bool\> = true or with normal mode : \<protected_mode : bool\> = false. If you don't sepecify this input, the code will run by default in normal mode.
