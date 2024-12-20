import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 270
    height: 80
    color: "transparent"
    // radius: 30

    property double intencity: 1
    property double mood: 1

    property color centerColor: "#d83632"
    //
    function makeBrighter(intence){
        // centerColor.a is a transparent
        // you can make gray in corelDraw or user other way
        console.log(intence)
        centerColor.a = intence
    }

    Rectangle{
        z: 0
        y: 5
        // x: 0.1*parent.width/2
        width: parent.width
        height: parent.height - 10
        radius: 0.1*parent.width/2
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "yellow" }
            GradientStop { position: 0.15; color: centerColor }
            GradientStop { position: 0.85; color: centerColor }
            GradientStop { position: 1.0; color: "yellow" }
        }
        border.color: "#2B2B2B"
        border.width: 4
    }

}
