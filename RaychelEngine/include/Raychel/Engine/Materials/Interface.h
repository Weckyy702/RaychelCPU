/**
*\file Interface.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for Material interface
*\date 2021-03-27
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/
#ifndef RAYCHEL_IMATERIAL_H
#define RAYCHEL_IMATERIAL_H

#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Core/Types.h"
#include "Raychel/Core/Forward.h"

namespace Raychel {

    /**
    *\brief Abstract interface for Materials
    *
    */
    struct IMaterial {

    protected:
        IMaterial()=default; //TODO: change that

        virtual void initializeTextureProviders(const vec3& parent_position, const vec3& parent_size)=0;

    public:
        
        virtual color getSurfaceColor(const ShadingData& data)const =0;

        virtual void setParentRenderer(not_null<RaymarchRenderer*> new_renderer)=0;

        virtual ~IMaterial()=default;
    };

    /**
    *\brief Base class for all Materials
    *
    */
    class Material : public IMaterial {

    public: 

    void setParentRenderer(not_null<RaymarchRenderer*> new_renderer) override;
    
    protected:
        Material()=default;

    protected:
        //Reference to renderer that renders this materials scene
        const RaymarchRenderer* parent_renderer_=nullptr;
    };
    
}

#endif //RAYCHEL_IMATERIAL_H