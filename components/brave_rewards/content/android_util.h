/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CONTENT_ANDROID_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CONTENT_ANDROID_UTIL_H_

#include "brave/components/brave_rewards/core/mojom/rewards.mojom.h"

namespace android_util {

brave_rewards::mojom::ClientInfoPtr GetAndroidClientInfo();

}  // namespace android_util

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CONTENT_ANDROID_UTIL_H_
