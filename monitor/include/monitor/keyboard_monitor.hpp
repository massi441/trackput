#pragma once

#include "monitor/key.hpp"
#include "monitor/result.hpp"

namespace tckp {
    class IKeyboardMonitor {
    public:
        virtual Result run() = 0;
        virtual Result stop() = 0;

        virtual Key getCurrentKey() = 0;

    private:
        
    };
}
