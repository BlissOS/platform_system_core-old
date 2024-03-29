/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "modalias_handler.h"

#include <string>
#include <vector>

#include <modprobe/modprobe.h>

namespace android {
namespace init {

ModaliasHandler::ModaliasHandler(const std::vector<std::string>& base_paths)
    : modprobe_(base_paths) {
    modprobe_.EnableDeferred(true);
}

void ModaliasHandler::HandleUevent(const Uevent& uevent) {
    if (uevent.modalias.empty()) return;
    modprobe_.LoadWithAliases(uevent.modalias, true);
}

bool ModaliasHandler::IsUeventDeferred(const Uevent& uevent) {
    if (! uevent.modalias.empty() && modprobe_.IsAliasDeferred(uevent.modalias)) return true;
    return false;
}

void ModaliasHandler::ColdbootDone() {
    modprobe_.EnableDeferred(false);
}

}  // namespace init
}  // namespace android
