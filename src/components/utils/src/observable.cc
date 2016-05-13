/*
 * Copyright (c) 2016, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "utils/observable.h"

#include <string>
#include <vector>
#include <algorithm>

#include "utils/observer.h"

void utils::Observable::AddObserver(Observer* observer,
                                    const std::string& events) {}

void utils::Observable::AddObserver(
    Observer* observer, const std::vector<std::string>& events_vector) {
  if (FindObserverByName(observer->get_name())) {
  }
}

void utils::Observable::RemoveObserver(Observer* observer,
                                       const std::string& events) {}

void utils::Observable::RemoveObserver(
    Observer* observer, const std::vector<std::string>& events_vector) {}

Observer* utils::Observable::FindObserverByName(const std::string& name) const {
  ObserversMap::const_iterator it = observers_map_.begin();
  for (; it != observers_map_.end(); ++it) {
    if (it->first->get_name() == name) {
      return it->first;
    }
  }
  return NULL;
}

std::vector<Observer*> utils::Observable::FindObserversByEvents(
    const std::vector<std::string>& events_vector) const {
  std::vector<Observer*> result_vector;
  ObserversMap::const_iterator it = observers_map_.begin();
  for (; it != observers_map_.end(); ++it) {
    const std::vector<std::string>& observer_events_vector = it->second;
    if (events_vector.size() == observer_events_vector.size() &&
        std::equal(events_vector.begin(),
                   events_vector.end(),
                   observer_events_vector.begin())) {
      result_vector.push_back(it->first);
    }
  }
  return result_vector;
}
