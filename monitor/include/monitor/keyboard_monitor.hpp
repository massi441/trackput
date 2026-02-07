#pragma once

#include "monitor/input_code.hpp"
#include "monitor/result.hpp"

// each monitor needs to hook into OS api
// each monitor should be able to retrieve current state

namespace tckp {
    class IKeyboardMonitor {
    public:
        virtual Result run() = 0;
        virtual Result stop() = 0;

        virtual InputCode getCurrentKey() = 0;

    private:
        
    };
}
