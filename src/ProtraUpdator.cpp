#include <stdio.h>
#include <iostream>
#include <memory>
#include <thread>

#include "PriceDataUpdator.h"
#include "IndexUpdator.h"
#include "KabukaJohoUpdator.h"
#include "MujinzouUpdator.h"

static int f_key = 0;
static int f_mujin = 0;

void thread_main()
{
    int ret;
    std::shared_ptr<Protra::Lib::Update::PriceDataUpdator> u;
    
    u = std::shared_ptr<Protra::Lib::Update::PriceDataUpdator>(new Protra::Lib::Update::IndexUpdator());
    ret = u->Update();
    
    if (f_mujin==0) {
        u = std::shared_ptr<Protra::Lib::Update::PriceDataUpdator>(new Protra::Lib::Update::KabukaJohoUpdator());
        ret = u->Update();
    }
    else {
        u = std::shared_ptr<Protra::Lib::Update::PriceDataUpdator>(new Protra::Lib::Update::MujinzouUpdator());
        ret = u->Update();
    }
}

int main(int argc,char *argv[])
{
    char buf[256];
    std::thread th;
    for (int i = 1; i < argc; i++)if (strcmp(argv[i], "-k") == 0)f_key = 1;
    for (int i = 1; i < argc; i++)if (strcmp(argv[i], "-m") == 0)f_mujin = 1;
    th = std::thread(thread_main);
    if (f_key) {
        fgets(buf, sizeof(buf), stdin);
        Protra::Lib::Update::PriceDataUpdator::set_stop();
    }
    if(th.joinable())th.join();
    return 0;
}
