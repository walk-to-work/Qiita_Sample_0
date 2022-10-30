open_project -reset proj
add_files  -cflags -I. sample.cpp
add_files  -cflags -I. -tb tb_sample.cpp
set_top top_func 
open_solution -reset solution1 -flow_target vivado
set_part  {xcu280-fsvh2892-2L-e}
create_clock -period 5

csim_design
csynth_design
cosim_design

exit
