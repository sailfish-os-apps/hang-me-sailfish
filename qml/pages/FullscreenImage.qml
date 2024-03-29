/*

Hanghish
Copyright (C) 2015 Daniele Rogora

This file is part of Hangish.

Hangish is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Hangish is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>

*/


import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: fsImage
    objectName: "fsImage"
    allowedOrientations: Orientation.All

    function loadImage(url) {
        imageView.source = url;
    }

    Image {
        id: imageView
        fillMode: Image.PreserveAspectFit
        asynchronous: true
        cache: true
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        x: Theme.paddingSmall
    }

    PinchArea {
                id: pinchArea

                property real minScale: 1.0
                property real maxScale: 4.0

                anchors.fill: parent
                enabled: imageView.status == Image.Ready
                pinch.target: imageView
                pinch.minimumScale: minScale * 0.5 // This is to create "bounce back effect"
                pinch.maximumScale: maxScale * 1.5 // when over zoomed

                onPinchFinished: {
                    //imageFlickable.returnToBounds()
                    if (imageView.scale < pinchArea.minScale) {
                        bounceBackAnimation.to = pinchArea.minScale
                        bounceBackAnimation.start()
                    }
                    else if (imageView.scale > pinchArea.maxScale) {
                        bounceBackAnimation.to = pinchArea.maxScale
                        bounceBackAnimation.start()
                    }
                }

                NumberAnimation {
                    id: bounceBackAnimation
                    target: imageView
                    duration: 250
                    property: "scale"
                    from: imageView.scale
                }
            }

            //ScrollDecorator {}


}
