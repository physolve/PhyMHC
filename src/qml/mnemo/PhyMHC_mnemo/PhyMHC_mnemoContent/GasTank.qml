import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material 2.12

Item {
    id: root
    width: 70
    height: 130
    Rectangle{
        width:40
        height:50
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 15
        color: "#536878"
        border.color: "black"
        border.width: 3
    }
    Rectangle{
        y: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width:60
        height: 100
        radius: 20
        color: "#36454f"
        border.color: "black"
        border.width: 3
    }
    RoundButton{
        id: supplyOpen
        y: 50
        width:50
        height:50
        anchors.horizontalCenter: parent.horizontalCenter
        checkable: true
        text: checked ? "c" : "o"
        Material.background: checked ? Material.Red : Material.Blue
        onClicked: scriptDefault.startCustomFlow(checked)
    }
    Rectangle {
        id: sliderPlacer1
        z:1
        x: -10
        y: -65
        width: 90
        height: 90
        radius: 45
        color: "transparent"

        CircularSlider {
            anchors.centerIn: parent
            id: slider1 // pressure
            handle: Rectangle {
                id: handleItem1
                width: 6
                height: 6
                color: "#908990"
                radius: width / 2
                border.color: "#fefefe"
                border.width: 5
                antialiasing: true
                transform: [
                    Translate {
                        x: (slider1.handleWidth - width) / 2
                        y: (slider1.handleHeight - height) / 2
                    }
                ]
            }
            minValue: 0
            rotation: 180
            progressWidth: 10
            startAngle: 40
            //Layout.fillWidth: false
            trackWidth: 10
            value: supplyOpen.checked ? 10 : 1
            maxValue: 10
            endAngle: 320

            Label {
                width: 40
                height: 20
                color: "white"
                text: slider1.value.toFixed(3) // changing to exp function
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                rotation: 180
                font.pointSize: 13
            }
        }
    }
}
