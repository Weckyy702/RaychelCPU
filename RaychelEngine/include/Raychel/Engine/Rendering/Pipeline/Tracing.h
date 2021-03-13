#ifndef RAYCHEL_TRACING_H
#define RAYCHEL_TRACING_H
#pragma once

#include "Raychel/Engine/Objects/Interface.h"

namespace Raychel {

    class RaymarchController
    {
        public:

            RaymarchController(const std::vector<IRaymarchable*>* objects)
                :objects_{objects}
            {}

            std::vector<HitData> trace(const std::vector<RaymarchRequest>& requests) const;

        private:
            const std::vector<IRaymarchable*>* objects_;
            const Camera* cam_;
    };

}

#endif //RAYCHEL_TRACING_H