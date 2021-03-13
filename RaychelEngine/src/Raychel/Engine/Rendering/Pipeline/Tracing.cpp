#include <algorithm>
#include <execution>

#include "Raychel/Engine/Rendering/Pipeline/Tracing.h"
#include "Logger.h"

namespace Raychel {

    std::vector<HitData> RaymarchController::trace(const std::vector<RaymarchRequest>& requests) const
    {
        std::vector<HitData> res;
        res.reserve(requests.size());

        std::transform(std::execution::seq, requests.cbegin(), requests.cend(), std::back_inserter(res),
            [](const RaymarchRequest& req) -> HitData
            {
                return HitData{vec3{}, req.direction};
            }
        );

        return res;
    }

}