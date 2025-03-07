/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/core/engine/legacy/publisher_state.h"

#include <utility>

#include "brave/components/brave_rewards/core/engine/legacy/publisher_settings_properties.h"
#include "brave/components/brave_rewards/core/engine/rewards_engine.h"

namespace brave_rewards::internal::publisher {

LegacyPublisherState::LegacyPublisherState(RewardsEngine& engine)
    : engine_(engine) {}

LegacyPublisherState::~LegacyPublisherState() = default;

uint64_t LegacyPublisherState::GetPublisherMinVisitTime() const {
  return state_.min_page_time_before_logging_a_visit;
}

unsigned int LegacyPublisherState::GetPublisherMinVisits() const {
  return state_.min_visits_for_publisher_relevancy;
}

bool LegacyPublisherState::GetPublisherAllowNonVerified() const {
  return state_.allow_non_verified_sites_in_list;
}

void LegacyPublisherState::Load(ResultCallback callback) {
  engine_->client()->LoadPublisherState(
      base::BindOnce(&LegacyPublisherState::OnLoad, base::Unretained(this),
                     std::move(callback)));
}

void LegacyPublisherState::OnLoad(ResultCallback callback,
                                  mojom::Result result,
                                  const std::string& data) {
  if (result != mojom::Result::OK) {
    std::move(callback).Run(result);
    return;
  }

  PublisherSettingsProperties state;
  if (!state.FromJson(data)) {
    std::move(callback).Run(mojom::Result::FAILED);
    return;
  }

  state_ = std::move(state);
  std::move(callback).Run(mojom::Result::OK);
}

std::vector<std::string> LegacyPublisherState::GetAlreadyProcessedPublishers()
    const {
  return state_.processed_pending_publishers;
}

void LegacyPublisherState::GetAllBalanceReports(
    std::vector<mojom::BalanceReportInfoPtr>* reports) {
  DCHECK(reports);

  for (auto const& report : state_.monthly_balances) {
    auto report_ptr = mojom::BalanceReportInfo::New();
    report_ptr->id = report.first;
    report_ptr->grants = report.second.grants;
    report_ptr->earning_from_ads = report.second.ad_earnings;
    report_ptr->auto_contribute = report.second.auto_contributions;
    report_ptr->recurring_donation = report.second.recurring_donations;
    report_ptr->one_time_donation = report.second.one_time_donations;

    reports->push_back(std::move(report_ptr));
  }
}

}  // namespace brave_rewards::internal::publisher
