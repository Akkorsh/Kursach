#include <iostream>
#include <cstdint>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include "server.h"

int Calculator::calc(int work_sock)
{
    uint32_t Quantity;
    uint32_t Length;
    uint64_t Vector_numbers; 
    int64_t Amount; 

    std::ofstream outfile("results.txt", std::ios::app);
    if (!outfile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return -1; 
    }

    recv(work_sock, &Quantity, sizeof(Quantity), 0);
    for(uint64_t j = 0; j < Quantity; j++) {
        recv(work_sock, &Length, sizeof(Length), 0);
        Amount = 0; 
        for(uint64_t i = 0; i < Length; i++) {
            recv(work_sock, &Vector_numbers, sizeof(Vector_numbers), 0);
            Amount = Amount + Vector_numbers;
        }
        
        int64_t Average_value;
        if (Amount > 1844674407370955161) {
            Average_value = 1844674407370955161;
        } else if (Amount < 0) {
            Average_value = 0;
        } else {
            Average_value = static_cast<int32_t>(Amount / Length); 
        }

        outfile << "Average value for vector " << j + 1 << ": " << Average_value << std::endl;

        send(work_sock, &Average_value, sizeof(Average_value), 0);
    }

    outfile.close();

    std::cout << "Завершение работы программы" << std::endl;
    close(work_sock);
    return 1;
}
