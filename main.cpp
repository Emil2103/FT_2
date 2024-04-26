//
//  main.cpp
//  FT_2
//
//  Created by Эмиль Саубанов on 26.04.2024.
//

#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

int sharedData = 0;

void Write_Data(){
    for(int i = 0; i < 10; ++i){
        mtx.lock();
        sharedData = i;
        std::cout << "Write thread - Записано число: " << i << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}

void Read_Data(){
    for(int i = 0; i < 10; ++i){
        mtx.lock();
        std::cout << "Read thread - Прочтено число: " << sharedData << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}

int main(int argc, const char * argv[]) {
    std::thread writer(Write_Data);
    std::thread reader(Read_Data);

    writer.join();
    reader.join();

    return 0;
}
