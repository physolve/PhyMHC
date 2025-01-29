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

    property color centerColor: "red"
    property double positionHeatLeft: 0.5
    property double positionHeatRight: 0.5
    //
    function makeBrighter(intence){
        // centerColor.a is a transparent
        // you can make gray in corelDraw or user other way
        // console.log(intence)
        // centerColor.a = intence
        centerColor.r = intence
        // centerColor.b = 1 - intence
        centerColor.g = 1 - intence

        positionHeatRight = 0.35*intence + 0.5
        positionHeatLeft = -0.35*intence + 0.5
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
            GradientStop { position: 0.01; color: "green" }
            GradientStop { position: positionHeatLeft; color: centerColor }
            GradientStop { position: positionHeatRight; color: centerColor }
            GradientStop { position: 1.0; color: "green" }
        }
        border.color: "#2B2B2B"
        border.width: 4
    }

    Switch {
        id: _sampleSwitch
        x: 140
        y: -25
        text: qsTr("Sample")
        onClicked: scriptDefault.sampleSwitchChanged(checked)
    }

}
