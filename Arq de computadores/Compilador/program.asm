ADD $t2, $zero, 10
ADD $t3, $zero, 20
ADD $t4, $zero, 5
ADD $t5, $zero, 16
ADD $t6, $zero, 8
ADD $t7, $zero, 12
BLE $t3, $t2, 1024
SUB $t8, $t5, $t7
J 512
MUL $t1, $t2, $t4
DIV $t0, 9, 2
