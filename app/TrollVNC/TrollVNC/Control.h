/*
 This file is part of TrollVNC
 Copyright (c) 2025 82Flex <82flex@gmail.com> and contributors

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2
 as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

FOUNDATION_EXTERN BOOL gShouldApplyOrientationFix;

NS_INLINE BOOL shouldApplyOrientationFixForCurrentRuntime(void) {
    if (!gShouldApplyOrientationFix)
        return NO;

    static BOOL sNeedsOrientationFix = NO;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        BOOL isPad = ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad);
        BOOL isAtLeastIOS17 = NO;
        if (@available(iOS 17.0, *)) {
            isAtLeastIOS17 = YES;
        }
        // iPad orientation offset behavior changed on iOS 17+, so the legacy +270° CW (−90°) fix
        // should only apply to iOS 17+ iPad runtimes where it may still be needed.
        sNeedsOrientationFix = (isPad && isAtLeastIOS17);
    });
    return sNeedsOrientationFix;
}

static const int kTvAlivePort = 46751;
static const int kTvDefaultCtlPort = 46752;
