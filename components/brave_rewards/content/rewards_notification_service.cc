/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/content/rewards_notification_service.h"

#include "brave/components/brave_rewards/content/rewards_notification_service_observer.h"

namespace brave_rewards {

RewardsNotificationService::RewardsNotificationService() = default;

RewardsNotificationService::~RewardsNotificationService() = default;

RewardsNotificationService::RewardsNotification::RewardsNotification() =
    default;

RewardsNotificationService::RewardsNotification::RewardsNotification(
    const RewardsNotificationService::RewardsNotification& prop) = default;

RewardsNotificationService::RewardsNotification::RewardsNotification(
    RewardsNotificationService::RewardsNotificationID id,
    RewardsNotificationService::RewardsNotificationType type,
    RewardsNotificationService::RewardsNotificationTimestamp timestamp,
    RewardsNotificationService::RewardsNotificationArgs args)
    : id_(id), type_(type), timestamp_(timestamp), args_(args) {}

RewardsNotificationService::RewardsNotification::~RewardsNotification() =
    default;

void RewardsNotificationService::AddObserver(
    RewardsNotificationServiceObserver* observer) {
  // Send any pending notifications immediately.
  RewardsNotificationsMap notifications = GetAllNotifications();
  for (auto& notification : notifications) {
    observer->OnNotificationAdded(this, notification.second);
  }

  observers_.AddObserver(observer);
}

void RewardsNotificationService::RemoveObserver(
    RewardsNotificationServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

}  // namespace brave_rewards
