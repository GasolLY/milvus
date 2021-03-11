// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License

#pragma once
#include <string_view>
#include <stdexcept>
#include <exception>
#include <stdio.h>
#include <stdlib.h>

/* Paste this on the file you want to debug. */

namespace milvus {
namespace impl {
void
EasyAssertInfo(
    bool value, std::string_view expr_str, std::string_view filename, int lineno, std::string_view extra_info);

[[noreturn]] void
ThrowWithTrace(const std::exception& exception);

}  // namespace impl

class WrappedRuntimeError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

}  // namespace milvus

#define AssertInfo(expr, info)                                                          \
    do {                                                                                \
        auto _expr_res = bool(expr);                                                    \
        /* call func only when needed */                                                \
        if (!_expr_res) {                                                               \
            milvus::impl::EasyAssertInfo(_expr_res, #expr, __FILE__, __LINE__, (info)); \
        }                                                                               \
    } while (0)

#define Assert(expr) AssertInfo((expr), "")
#define PanicInfo(info)                                                      \
    do {                                                                     \
        milvus::impl::EasyAssertInfo(false, (info), __FILE__, __LINE__, ""); \
        __builtin_unreachable();                                             \
    } while (0)