#ifndef RAYCHEL_TRACING_H
#define RAYCHEL_TRACING_H
#pragma once

#include "Raychel/Engine/Raymarchable/Interface.h"

namespace Raychel {

    class RaymarchController
    {
        public:

            RaymarchController(const std::vector<IRaymarchable>* objects);

            std::vector<HitData>

        private:
            const std::vector<IRaymarchable>* objects_;
    };

}

#endif //RAYCHEL_TRACING_H