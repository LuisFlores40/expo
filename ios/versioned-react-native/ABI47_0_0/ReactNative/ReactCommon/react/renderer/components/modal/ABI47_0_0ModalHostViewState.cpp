/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI47_0_0ModalHostViewState.h"

namespace ABI47_0_0facebook {
namespace ABI47_0_0React {

#ifdef ANDROID
folly::dynamic ModalHostViewState::getDynamic() const {
  return folly::dynamic::object("screenWidth", screenSize.width)(
      "screenHeight", screenSize.height);
}
#endif

} // namespace ABI47_0_0React
} // namespace ABI47_0_0facebook
