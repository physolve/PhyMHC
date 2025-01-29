import QtQuick
import QtQuick.Controls
Item {
    width: 75; height: 50
    transform: Rotation { origin.x: 0; origin.y: 20; axis { x: 1; y: 0; z: 0 } angle: 73 }
    property bool cooling: false 
    Image {
        id: cooler
        source: "pics/cooler.svg"
        width: 70
        height: 75
        antialiasing: true
        RotationAnimator on rotation {
            from: 0;
            to: 360;
            duration: 3000
            direction: RotationAnimation.Clockwise
            loops: Animation.Infinite;
            running: cooling
        }
        // for stop and start animation transition!
        // states: State {
        //             name: "rotated"
        //             PropertyChanges { target: cooler; rotation: 180 }
        //         }

        //         transitions: Transition {
        //             RotationAnimation { duration: 3000; direction: RotationAnimation.Clockwise }
        //         }
    }
        // MouseArea { anchors.fill: parent; onClicked: cooler.state = "rotated" }
}
