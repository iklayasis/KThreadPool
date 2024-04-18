#include <iostream>
#include "KThreadPool.h"

using namespace std;

int main()
{
    KThreadPool ktPool(10);
    for(int i = 0; i < 10; ++i){
        ktPool.Commit([i]{
            cout << "Task: " << i << "is runing" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Task: " << i << "is done" << endl;
        });
    }
    return 0;
}
