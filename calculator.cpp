#include <iostream>
#include <cstdint>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

int Calculator::calc(int work_sock)
{
    uint32_t Quantity;
    uint32_t Length;
    int32_t Vector_numbers; 
    int64_t Amount; 

    recv(work_sock, &Quantity, sizeof(Quantity), 0);
    for(uint32_t j = 0; j < Quantity; j++) {
        recv(work_sock, &Length, sizeof(Length), 0);
        Amount = 0; 
        for(uint32_t i = 0; i < Length; i++) {
            recv(work_sock, &Vector_numbers, sizeof(Vector_numbers), 0);
            Amount = Amount + Vector_numbers;
        }
        int32_t Average_value;
        if (Amount > 4294967294) {
            Average_value = 4294967294;
        } else if (Amount < 0) {
            Average_value = 0;
        } else {
            Average_value = static_cast<int32_t>(Amount / Length); 
        }
        send(work_sock, &Average_value, sizeof(Average_value), 0);
    }

    std::cout << "Завершение работы программы" << std::endl;
    close(work_sock);
    return 1;
}

