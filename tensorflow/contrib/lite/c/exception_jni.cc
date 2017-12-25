/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "tensorflow/contrib/lite/c/exception_jni.h"

void throwException(ExceptionContext *context, EXCEPTION_TYPE exc, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  const size_t max_msg_len = 512;
  auto* message = static_cast<char*>(malloc(max_msg_len));
  context->exception_type = exc;
  if (vsnprintf(message, max_msg_len, fmt, args) >= 0) {
    snprintf(context->buffer, context->buffer_size, "%s", message);
  } else {
    snprintf(context->buffer, context->buffer_size, "");
  }
  free(message);
  va_end(args);
}

BufferErrorReporter::BufferErrorReporter(ExceptionContext *context, int limit) {
  buffer_ = new char[limit];
  if (!buffer_) {
    throwException(context, EXCEPTION_TYPE::NullPointerException,
                   "Malloc of BufferErrorReporter to hold %d char failed.",
                   limit);
    return;
  }
  start_idx_ = 0;
  end_idx_ = limit - 1;
}

BufferErrorReporter::~BufferErrorReporter() { delete[] buffer_; }

int BufferErrorReporter::Report(const char* format, va_list args) {
  int size = 0;
  if (start_idx_ < end_idx_) {
    size = vsnprintf(buffer_ + start_idx_, end_idx_ - start_idx_, format, args);
  }
  start_idx_ += size;
  return size;
}

const char* BufferErrorReporter::CachedErrorMessage() { return buffer_; }
