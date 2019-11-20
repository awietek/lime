// Copyright 2018 Alexander Wietek - All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIME_COLLECTION_H
#define LIME_COLLECTION_H

#include <vector>
#include <string>
#include <unordered_map>

namespace lime {

  template <class key_t, class estimator_t>
  class Collection 
  {
    using container_t = std::unordered_map<key_t, estimator_t>;
    using iterator_t = typename container_t::iterator;
    using const_iterator_t = typename container_t::const_iterator;

  public:
    Collection() = default;
    
    // estimator_t operator[](key_t const& key) const;
    estimator_t& operator[](key_t const& key);
    std::vector<key_t> keys() const { return keys_; }

    iterator_t begin() { return keys_estimators_.begin(); }
    iterator_t end() { return keys_estimators_.end(); }
    const_iterator_t begin() const { return keys_estimators_.begin(); }
    const_iterator_t end() const { return keys_estimators_.end(); }
    const_iterator_t cbegin() const { return keys_estimators_.cbegin(); }
    const_iterator_t cend() const { return keys_estimators_.cend(); }
    
  private:
    std::vector<key_t> keys_;
    container_t keys_estimators_;
  };

}

#endif 
