#ifndef SD_OBJECT_INTERFACE_H
#define SD_OBJECT_INTERFACE_H
#pragma once

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Engine/Materials/Interface.h"

namespace Raychel {

    //Interface for Raymarchable Objects
    struct IRaymarchable
    {
    protected:

        IRaymarchable()=default;

        IRaymarchable(const IRaymarchable&)=delete;
        IRaymarchable(IRaymarchable&&)=delete;

        IRaymarchable& operator=(const IRaymarchable&)=delete;
        IRaymarchable& operator=(IRaymarchable&&)=delete;

    public:

        virtual float eval(const vec3&) const=0;

        virtual vec3 getDirection(const vec3&) const=0;

        virtual color getSurfaceColor(const ShadingData&, size_t recursion_depth) const=0;

        virtual void onRendererAttached(const not_null<RaymarchRenderer*>)=0;

        virtual ~IRaymarchable()=default;
    };


    //Base class for Raymarchable Objects
    class SdObject : public IRaymarchable
    {
    
    protected:
        SdObject(const ObjectData& _data)
            :transform_{_data.t} , material_{_data.mat}
        {}

    public:

    vec3 getDirection(const vec3& p) const override;

    color getSurfaceColor(const ShadingData& data, size_t recursion_depth) const override;

    void onRendererAttached(const not_null<RaymarchRenderer*>) override;

    virtual ~SdObject()=default;

    friend ObjectData makeObjectData(SdObject&&);

    protected:
        Transform transform_;
        IMaterial_p material_;
    };

    class SdLamp : public IRaymarchable
    {

    protected:
        SdLamp(const LampData& _data)
            :lampColor{_data.c}, lampBrightness{_data.b}, lampSize{_data.sz}
        {}

    protected:
        color lampColor;
        float lampBrightness=1.0;
        float lampSize=1.0;
    };

    inline ObjectData makeObjectData(SdObject&& rhs)
    {
        //release the previous objects ownership of the material
        IMaterial* mat = rhs.material_.release();

        return {rhs.transform_, mat};
    }

    template<typename T, typename Mat, typename... Args>
    T make_object(const Transform& transform, Mat&& mat, Args&&... args) {
        static_assert(std::is_base_of_v<SdObject, T>, "Raychel::make_object<T> requires T to be derived from Raychel::SdObject!");
        static_assert(std::is_base_of_v<Material, Mat>, "Raychel::make_object<Mat> requires Mat to be derived from Raychel::Material!");
        return T(ObjectData{transform, new Mat{std::move(mat)}}, std::forward<Args>(args)...);
    }

}


#endif //SD_OBJECT_INTERFACE_H