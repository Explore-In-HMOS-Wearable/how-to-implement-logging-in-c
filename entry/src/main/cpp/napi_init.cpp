/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2026. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "napi/native_api.h"
#include "logger.h"

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    double a = 0;
    double b = 0;
    napi_get_value_double(env, args[0], &a);
    napi_get_value_double(env, args[1], &b);

    LOGI("Add called: a=%{public}f b=%{public}f", a, b);

    double sum = a + b;
    if (sum > 100) {
        LOGW("Result is large: %{public}f", sum);
    }

    napi_value result;
    napi_create_double(env, sum, &result);
    return result;
}

static napi_value Divide(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    double a = 0;
    double b = 0;
    napi_get_value_double(env, args[0], &a);
    napi_get_value_double(env, args[1], &b);

    LOGI("Divide called: a=%{public}f b=%{public}f", a, b);

    napi_value result;
    if (b == 0) {
        LOGE("Division by zero error! a=%{public}f, returning 0", a);
        napi_create_double(env, 0, &result);
        return result;
    }

    double value = a / b;
    LOGD("Division result: %{public}f", value);
    napi_create_double(env, value, &result);
    return result;
}

static napi_value LogDemo(napi_env env, napi_callback_info info)
{
    
    LOGD("DEBUG message");
    LOGI("INFO message");
    LOGW("WARN message");
    LOGE("ERROR message");

    int count = 5;
    const char *name = "watch";
    double ratio = 0.75;
    LOGI("int=%{public}d string=%{public}s double=%{public}.2f", count, name, ratio);

    LOGI("public: %{public}s", name);
    LOGI("private: %{private}s", name);
    LOGI("unmarked: %s", name);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_DOMAIN, "OtherTag", "This message usses a different tag");
 
    if (OH_LOG_IsLoggable(LOG_DOMAIN, LOG_TAG, LOG_DEBUG)) {
        LOGD("DEBUG is enabled, printing detailed info");
    } else {
        LOGI("DEBUG is disabled, skipping detailed info");
    }

    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "divide", nullptr, Divide, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "logDemo", nullptr, LogDemo, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    LOGI("Native modul loaded");
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}