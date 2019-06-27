project main files is that : {main.c , Uart.c , Uart.h , App_function.c , App_function.h}

files contains : 
main.c : integration of all APIs to handel requirements.
Uart.c : Implemntation of uart driver.
App_function.c : Implemntaion of calculation's functions.

Prepherals used : UART0 , SSi0,(include Cnf pins SW1(F3).

Note:
When am making a separate driver for the ssi I find some issues with linking so I put all APIs of it on main.c file cause of no time for debugging.

Very welcome for any queries ..

Thanks for this challenge ..
